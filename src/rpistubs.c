#include "board_sd_card.h"
#include "sd_protocol.h"

int sd_protocol_config(sd_card *card) {}
unsigned char sd_protocol_read(sd_card *card, unsigned char *buffer, int a, int b) {}
unsigned char sd_protocol_write(sd_card *card, unsigned char *buffer, int a, int b) {}
int board_sd_card_get_status() {}