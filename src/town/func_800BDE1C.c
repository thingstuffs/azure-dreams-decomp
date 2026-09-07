#include "common.h"

typedef struct {
    s32 unk0;
    s8 unk4;
    s8 unk5;
    u8 pad6[6];
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

extern void func_8004491C(s32, void *);
extern void func_8008F104(s32, void *, void *);
extern u8 D_80046398[];
extern u8 D_80083160[];
extern u8 D_800D1BDC[];

void func_800BB57C(s32 arg0, void *arg1, FuncData *arg2) {
    func_8004491C(arg0 - 0x20, D_80046398);

    arg2->unk12 = 0;
    arg2->unk14 = 0;
    arg2->unk10 = 0;
    arg2->unk16 = 0;
    arg2->unk18 = 0;
    arg2->unk1A = 0;
    arg2->unk0 = 0;
    arg2->unk4 = 0;
    arg2->unk5 = 0;
    arg2->unk1C = 0x1000;
    arg2->unk1E = 0x1000;
    arg2->unk20 = 0x1000;
    arg2->unkC = D_80083160[0xA8];
    arg2->unkD = D_80083160[0xA9];
    arg2->unkE = D_80083160[0xAA];
    *(s32 *)((u8 *)arg1 + 8) += 0x200000;

    func_8008F104(arg0, arg1, D_800D1BDC);
}
