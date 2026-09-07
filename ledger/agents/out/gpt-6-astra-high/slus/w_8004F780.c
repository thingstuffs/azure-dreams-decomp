#include "common.h"

typedef struct S_8004F780_Obj {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ u8 *buf;
} S_8004F780_Obj;

typedef struct S_8004F780_Entry {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ S_8004F780_Obj *obj;
} S_8004F780_Entry;

typedef struct S_8004F780 {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ S_8004F780_Entry *entries[8];
    /* 0x24 */ s32 count;
    /* 0x28 */ s32 divisor;
    /* 0x2C */ s32 multiplier;
    /* 0x30 */ s32 idxB;
    /* 0x34 */ s32 idxA;
} S_8004F780;

extern u8 D_80071784[];
extern u8 D_80071790[];

/* Interpolates table values and fills each entry's three-byte buffer with the result. */
void func_8004F780(S_8004F780 *state)
{
    s32 entry_index;
    u8 *row;
    s32 start_value;
    s32 end_value;
    s32 value_delta;
    S_8004F780_Entry *entry;
    S_8004F780_Obj *obj;

    for (entry_index = 0; entry_index < state->count; entry_index++) {
        entry = state->entries[entry_index];
        row = D_80071784 + entry_index * 3;
        start_value = D_80071790[row[state->idxA] * 4];
        end_value = D_80071790[row[state->idxB] * 4];
        value_delta = (end_value - start_value) * state->multiplier / state->divisor;

        obj = entry->obj;
        obj->buf[0] = start_value + value_delta;
        obj->buf[1] = obj->buf[0];
        obj->buf[2] = obj->buf[0];
    }
}
