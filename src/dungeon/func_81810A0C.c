#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 pad18[0x3C];
    s32 unk54;
} DungeonArg;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} DungeonState;

extern DungeonState D_80083160[];

extern void func_80053DA8(s32 arg0);
extern s32 func_80025514(s32 arg0);
extern s32 func_80025850(DungeonArg *arg0, s32 arg1);
extern s32 func_80025888(s32 arg0, s32 arg1);
extern s32 func_800258B0(DungeonArg *arg0);
extern s32 func_800258B8(DungeonArg *arg0);
extern void func_80025964(DungeonArg *arg0);
extern s32 func_800259CC(DungeonArg *arg0);
extern s32 func_80049DE8(s32 arg0, s32 arg1, s32 arg2);

void func_80025A0C(DungeonArg *arg0) {
    DungeonState *state = D_80083160;
    s32 delta;

    if (state->unk8 == 0 || arg0->unk10 == 0) {
        goto done;
    }

    if (state->unk10 & 0x20) {
        func_80053DA8(0x515);
        func_80025514(arg0->unk14);
        func_800258B8(arg0);
        goto done;
    }

    if (state->unk10 & 0x40) {
        if (func_800258B0(arg0) != 0 || func_800259CC(arg0) != 0) {
            func_80053DA8(0x506);
            goto done;
        }
        if (arg0->unk8 == 4) {
            func_80053DA8(0x503);
        } else {
            func_80053DA8(0x514);
        }
        func_80025850(arg0, arg0->unk8);
        goto done;
    }

    if (state->unk10 & 0x10) {
        arg0->unk8 = 4;
        func_80025888(arg0->unk54, arg0->unk8);
        goto done;
    }

    if (state->unk8 & 0x5000) {
        delta = 0;
        if (state->unk10 & 0x5000) {
            arg0->unk4 = 0;
            if (state->unk10 & 0x1000) {
                delta = -1;
            } else if (state->unk10 & 0x4000) {
                delta = 1;
            }
        } else {
            if (arg0->unk4 >= 9) {
                arg0->unk4 = arg0->unk4 - 1;
                if (state->unk8 & 0x1000) {
                    delta = -1;
                } else if (state->unk8 & 0x4000) {
                    delta = 1;
                }
            } else {
                arg0->unk4 = arg0->unk4 + 1;
            }
        }
        if (delta != 0) {
            func_80053DA8(0x502);
            arg0->unk8 = func_80049DE8(delta, arg0->unk8, 5);
            func_80025888(arg0->unk54, arg0->unk8);
        }
    }

done:
    func_80025964(arg0);
}
