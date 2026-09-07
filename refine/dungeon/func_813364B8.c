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

/* Selects the mode table and updates the dungeon object state. */
void func_8016D4B8(DungeonObject *object, s32 update_param, DungeonState *state, DungeonInput *input) {
    s32 mode;
    u8 *mode_table;
    u8 *current_table;

    mode = object->mode;
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
    current_table = state->field_2C;
    mode_table = D_801739A0;
    goto update_table;

mode_1:
    current_table = state->field_2C;
    mode_table = D_801739A8;
    goto update_table;

mode_2:
    current_table = state->field_2C;
    mode_table = D_801739B0;
    goto update_table;

mode_3:
    current_table = state->field_2C;
    mode_table = D_801739B8;

update_table:
    if (current_table != mode_table) {
        state->field_2C = mode_table;
        func_80047784(state, *(u8 *)((((s32) (*D_80083228 + input->field_2A + 0x100) >> 9) & 7) + (u32) mode_table), 0);
    }

call_common:
    if (func_800AC82C(object, update_param, state, input) != 0) {
        if ((func_800AD9B4(state, input) << 0x10) > 0) {
            object->field_8C = D_8016A36C;
        }
    }
    return;
}
