#pragma once

typedef struct sd_card{

} sd_card;

int sd_protocol_config(sd_card *card);
unsigned char sd_protocol_read(sd_card *card, unsigned char *buffer, int, int);
unsigned char sd_protocol_write(sd_card *card, unsigned char *buffer, int, int);