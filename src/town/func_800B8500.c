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

/* Initializes three entries with offsets and fixed, supplied, and computed values. */
void func_800B5C60(s32 source_value, Func800B8500Entry **entries, s32 entry_value) {
    s32 entry_offset = 8;

    entries[0]->inner->field_8 = -0x38;
    entries[0]->inner->field_A = entry_offset;
    entries[0]->value = &D_80077FBC[0];

    entries[1]->inner->field_8 = -0x38;
    entries[1]->inner->field_A = entry_offset;
    entries[1]->value = entry_value;

    entries[2]->inner->field_8 = -0x10;
    entries[2]->inner->field_A = 0x16;
    entries[2]->value = func_800498EC(func_80049984(source_value, entry_offset));
}
