#include "common.h"

extern s32 D_800294FC;

typedef struct {
    u8 unk0;
    s8 unk1;
    s8 unk2;
    s8 unk3;
    s32 unk4;
    s8 pad8[2];
    s8 unkA;
    s8 unkB;
} Packet;

/* Initialize and return a packet with the shared payload and a variant-dependent field. */
void *func_80026708(Packet *packet, s32 variant) {
    s32 payload;

    packet->unk1 = 0x28;
    payload = D_800294FC;
    packet->unk2 = -0x21;
    packet->unk3 = 5;
    packet->unk4 = payload;
    packet->unkA = (variant == 1) ? 0x42 : 0x5A;
    packet->unkB = 0x16;
    packet->unk0 = 0x80;
    return packet;
}
