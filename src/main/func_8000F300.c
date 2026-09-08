#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ s8 unk1;
    /* 0x02 */ s8 pad2[2];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s8 pad8[2];
    /* 0x0A */ s8 unkA;
    /* 0x0B */ s8 unkB;
} Struct_8000F300;

/* Initializes a packet for the selected slot and returns the next packet. */
void *func_80022300(s32 unused, Struct_8000F300 *packet, s32 slot_index) {
    s32 command = 0xA04010;
    u8 flags = packet->unk0;
    void *next_packet;

    packet->unk1 = 0x28;
    packet->unkA = (s8)(slot_index * 8 + 4);
    packet->unkB = 0x13;
    next_packet = packet + 1;
    packet->unk4 = command;
    flags |= 0x80;
    packet->unk0 = flags;
    return next_packet;
}
