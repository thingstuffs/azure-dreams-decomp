#include "common.h"

extern void func_80033AA8(s32);
extern u8 D_800CC524;

typedef struct {
    u8 unk0[0x54];
    void *unk54;
    u8 unk58[0x6C - 0x58];
    u16 unk6C;
} Struct800CED50Arg0;

typedef struct {
    u8 unk0[0xC];
    u8 unkC;
    u8 unkD;
    u8 unkE;
} Struct800CED50Arg2;

void func_800CC4B0(Struct800CED50Arg0 *arg0, s32 arg1, Struct800CED50Arg2 *arg2) {
    if ((s16)(--arg0->unk6C) <= 0) {
        func_80033AA8(0x97);
        arg0->unk54 = &D_800CC524;
        arg0->unk6C = 0xA;
        arg2->unkE = 0x80;
        arg2->unkD = 0x80;
        arg2->unkC = 0x80;
    }
}
