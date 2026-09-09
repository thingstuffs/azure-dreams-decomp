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

extern void SD_Call(s32 arg0);
extern s32 func_80025514(s32 arg0);
extern s32 func_80025850(DungeonArg *arg0, s32 arg1);
extern s32 func_80025888(s32 arg0, s32 arg1);
extern s32 func_800258B0(DungeonArg *arg0);
extern s32 func_800258B8(DungeonArg *arg0);
extern void func_80025964(DungeonArg *arg0);
extern s32 func_800259CC(DungeonArg *arg0);
extern s32 func_80049DE8(s32 arg0, s32 arg1, s32 arg2);

/* Handles menu actions and selection movement with held-button repeat. */
void func_80025A0C(DungeonArg *menu) {
    DungeonState *input = D_80083160;
    s32 selection_step;

    if (input->unk8 == 0 || menu->unk10 == 0) {
        goto done;
    }

    if (input->unk10 & 0x20) {
        SD_Call(0x515);
        func_80025514(menu->unk14);
        func_800258B8(menu);
        goto done;
    }

    if (input->unk10 & 0x40) {
        if (func_800258B0(menu) != 0 || func_800259CC(menu) != 0) {
            SD_Call(0x506);
            goto done;
        }
        if (menu->unk8 == 4) {
            SD_Call(0x503);
        } else {
            SD_Call(0x514);
        }
        func_80025850(menu, menu->unk8);
        goto done;
    }

    if (input->unk10 & 0x10) {
        menu->unk8 = 4;
        func_80025888(menu->unk54, menu->unk8);
        goto done;
    }

    if (input->unk8 & 0x5000) {
        selection_step = 0;
        if (input->unk10 & 0x5000) {
            menu->unk4 = 0;
            if (input->unk10 & 0x1000) {
                selection_step = -1;
            } else if (input->unk10 & 0x4000) {
                selection_step = 1;
            }
        } else {
            if (menu->unk4 >= 9) {
                menu->unk4 = menu->unk4 - 1;
                if (input->unk8 & 0x1000) {
                    selection_step = -1;
                } else if (input->unk8 & 0x4000) {
                    selection_step = 1;
                }
            } else {
                menu->unk4 = menu->unk4 + 1;
            }
        }
        if (selection_step != 0) {
            SD_Call(0x502);
            menu->unk8 = func_80049DE8(selection_step, menu->unk8, 5);
            func_80025888(menu->unk54, menu->unk8);
        }
    }

done:
    func_80025964(menu);
}
