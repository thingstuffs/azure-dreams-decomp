#include "common.h"

extern u8 D_80408CF0[];

/* Builds four drawing packets between state packets and returns the buffer end. */
void *func_8001DDEC(void *buffer, s32 width, s32 height) {
    u8 *packet;
    s32 packet_index;

    packet = buffer;
    packet[1] = 0x81;
    *(s16 *)(packet + 4) = 0x20;
    *(s16 *)(packet + 6) = 0;
    packet += 0xC;
    packet_index = 0;
    do {
        packet[1] = 0x38;
        *(s32 *)(packet + 4) = 0x9CBCBC;
        *(s32 *)(packet + 12) = 0x9CBCBC;
        *(s32 *)(packet + 16) = 0x9CBCBC;
        *(s32 *)(packet + 20) = 0x8C9C9C;
        packet[10] = (s8)(width / 2);
        packet[11] = (s8)(height / 2);
        *packet = D_80408CF0[packet_index];
        packet_index += 1;
        packet += 0x18;
    } while (packet_index < 4);
    packet[1] = 0x81;
    *(s16 *)(packet + 4) = 0x20;
    *(s16 *)(packet + 6) = 1;
    packet[0] = 0x80;
    return packet + 0xC;
}
