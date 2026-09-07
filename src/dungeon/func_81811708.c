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

void *func_80026708(Packet *arg0, s32 arg1) {
    s32 value;

    arg0->unk1 = 0x28;
    value = D_800294FC;
    arg0->unk2 = -0x21;
    arg0->unk3 = 5;
    arg0->unk4 = value;
    arg0->unkA = (arg1 == 1) ? 0x42 : 0x5A;
    arg0->unkB = 0x16;
    arg0->unk0 = 0x80;
    return arg0;
}
