//------------------------------------------------------------------------------
// MIT license
// Copyright (c) 2020 StrawberryHacker
//------------------------------------------------------------------------------

#include "disk_interface.h"
#include "board_sd_card.h"
#include "sd_protocol.h"

#include "../../include/ide.h"

/// Make a global SD card structure
sd_card sd_slot_1;

u8 disk_get_status(disk_e disk) {
	return 1;
	switch (disk) {
		case DISK_SD_CARD: {
			return (u8)board_sd_card_get_status();
		}
		case DISK_IDE_DRV0:
		case DISK_IDE_DRV1:
		case DISK_IDE_DRV2:
		case DISK_IDE_DRV3: {
			return __ide_devices[disk - 1].connected;
		}
	}
	return 0;
}

u8 disk_initialize(disk_e disk) {
	return 1;
	switch (disk) {
		case DISK_SD_CARD: {
			return (u8)sd_protocol_config(&sd_slot_1);
		}
		case DISK_IDE_DRV0:
		case DISK_IDE_DRV1:
		case DISK_IDE_DRV2:
		case DISK_IDE_DRV3: {
			return 1;
		}
	}
	return 0;
}

u8 disk_read(disk_e disk, u8* buffer, u32 lba, u32 count) {
	switch (disk) {
		case DISK_SD_CARD: {
			return sd_protocol_read(&sd_slot_1, buffer, lba, count);
		}
		case DISK_IDE_DRV0:
		case DISK_IDE_DRV1:
		case DISK_IDE_DRV2:
		case DISK_IDE_DRV3: {
			ide_rw_t rwaction;
			rwaction.buffer = (uint32_t)buffer;
			rwaction.drive = disk - 1;
			rwaction.lba = lba;
			rwaction.rw = 0;
			rwaction.sectors = count;
			rwaction.selector = 0;

			__ide_get_access(rwaction);

			return 1;
		}
	}
	return 0;
}

u8 disk_write(disk_e disk, const u8* buffer, u32 lba, u32 count) {
	switch (disk) {
		case DISK_SD_CARD: {
			return sd_protocol_write(&sd_slot_1, buffer, lba, count);
		}
		case DISK_IDE_DRV0:
		case DISK_IDE_DRV1:
		case DISK_IDE_DRV2:
		case DISK_IDE_DRV3: {
			ide_rw_t rwaction;
			rwaction.buffer = (uint32_t)buffer;
			rwaction.drive = disk - 1;
			rwaction.lba = lba;
			rwaction.rw = 1;
			rwaction.sectors = count;
			rwaction.selector = 0;

			__ide_get_access(rwaction);

			return 1;
		}
	}
	return 0;
}
