#include "common.h"

typedef struct {
    u32 unk0;
    s8 unk4;
    s8 unk5;
    u8 pad6[2];
    s32 unk8;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 padF;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
} FuncData;

extern void func_8004491C(void *, void *);
extern u8 D_80046398[];
extern u8 D_80083160[];
extern u8 D_800B9998[];

void func_800B9B28(u8 *arg0, u8 *arg1, FuncData *arg2) {
    u8 *colors;
    u8 blue;

    *(void **)(arg0 - 0x10) = D_800B9998;
    func_8004491C(arg0 - 0x20, D_80046398);

    *(s16 *)(arg0 + 0x66) = 0;
    arg2->unk1C = 0x1000;
    do { arg2->unk1E = 0x1000; } while (0);
    arg2->unk20 = 0x1000;
    colors = D_80083160;
    arg2->unk12 = 0;
    arg2->unk14 = 0;
    arg2->unk10 = 0;
    arg2->unk16 = 0;
    arg2->unk18 = 0;
    arg2->unk1A = 0;
    arg2->unk0 = 0;
    arg2->unk4 = 0;
    arg2->unk5 = 0;
    arg2->unkC = colors[0xA8];
    arg2->unkD = colors[0xA9];
    blue = colors[0xAA];
    arg2->unk8 = 0x1F;
    arg2->unkE = blue;
    *(s32 *)(arg1 + 8) = 0xFF600000;
}
