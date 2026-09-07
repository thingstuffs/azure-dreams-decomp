#include "common.h"

typedef struct Func800B8500Inner {
    u8 pad[8];
    s16 field_8;
    s16 field_A;
} Func800B8500Inner;

typedef struct Func800B8500Entry {
    void *value;
    Func800B8500Inner *inner;
} Func800B8500Entry;

extern s32 func_800498EC(s32 value);
extern s32 func_80049984(s32 value, s32 arg1);
extern s32 D_80077FBC[];

void func_800B5C60(s32 unused, Func800B8500Entry **entries, s32 value) {
    s32 eight = 8;

    entries[0]->inner->field_8 = -0x38;
    entries[0]->inner->field_A = eight;
    entries[0]->value = &D_80077FBC[0];

    entries[1]->inner->field_8 = -0x38;
    entries[1]->inner->field_A = eight;
    entries[1]->value = value;

    entries[2]->inner->field_8 = -0x10;
    entries[2]->inner->field_A = 0x16;
    entries[2]->value = func_800498EC(func_80049984(unused, eight));
}

/* MECHANISM: The 24-byte frame and entries base held in s0 already matched retail.
   Naming constant 8 as one live range holds it in a1 across both earlier stores
   and the final call, replacing the redundant rematerialization with retail's nop. */
