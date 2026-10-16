/* Relink of matched dungeon/dungeonResetGlobalEffectState at file 0x12740F8; imports and data use paired retail relocations. */
#include "common.h"

typedef struct {
    u8 pad[0x3714];
    u16 flags;
    s16 field_3716;
    s16 field_3718;
    s16 field_371A;
    s32 field_371C;
} State;

extern s32 D_80154F84[];

/* Resets global state fields and flags and loads the selected table entry. */
void func_801548F8(s32 entry_index) {
    State *state = (State *)0x80010000;

    state->field_371A = 0;
    state->field_3718 = 0;
    state->field_3716 = 0;
    state->flags = (state->flags | 9) & 0xFFEF;
    state->field_371C = D_80154F84[entry_index];
}

/* MECHANISM: A typed 0x80010000 page-base local emits retail's lone lui without
   materializing D_80013714; struct fields preserve the 0x3714..0x371C offsets. */
