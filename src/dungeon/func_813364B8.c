#include "common.h"

typedef struct {
    u8 pad_00[0x8C];
    u8 *field_8C;
    u8 pad_90[0x1C];
    u8 mode;
} DungeonObject;

typedef struct {
    u8 pad_00[0x2C];
    u8 *field_2C;
} DungeonState;

typedef struct {
    u8 pad_00[0x2A];
    s16 field_2A;
} DungeonInput;

extern u8 D_801739A0[];
extern u8 D_801739A8[];
extern u8 D_801739B0[];
extern u8 D_801739B8[];
extern s16 D_80083228[5];
extern u8 D_8016A36C[];

extern void func_80047784(void *, s32, s32);
extern s32 func_800AC82C(void *, s32, void *, void *);
extern s32 func_800AD9B4(void *, void *);

void func_8016D4B8(DungeonObject *arg0, s32 arg1, DungeonState *arg2, DungeonInput *arg3) {
    s32 mode;
    u8 *table;
    u8 *current;

    mode = arg0->mode;
    if (mode == 1)
        goto mode_1;
    if (mode < 2) {
        if (mode == 0)
            goto mode_0;
        goto call_common;
    }
    if (mode == 2)
        goto mode_2;
    if (mode == 3)
        goto mode_3;
    goto call_common;

mode_0:
    current = arg2->field_2C;
    table = D_801739A0;
    goto update_table;

mode_1:
    current = arg2->field_2C;
    table = D_801739A8;
    goto update_table;

mode_2:
    current = arg2->field_2C;
    table = D_801739B0;
    goto update_table;

mode_3:
    current = arg2->field_2C;
    table = D_801739B8;

update_table:
    if (current != table) {
        arg2->field_2C = table;
        func_80047784(arg2, *(u8 *)((((s32) (*D_80083228 + arg3->field_2A + 0x100) >> 9) & 7) + (u32) table), 0);
    }

call_common:
    if (func_800AC82C(arg0, arg1, arg2, arg3) != 0) {
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            arg0->field_8C = D_8016A36C;
        }
    }
    return;
}
