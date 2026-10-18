#include "common.h"

typedef s32 M2C_UNK;

extern s32 scale_random_to_unsigned_halfword_limit();
extern void initialize_object_entries();
extern M2C_UNK D_800CD650;
extern M2C_UNK D_800D7284;

// Initializes an object with shared data and a generated value scaled in units of 21.
void initialize_object_from_context(void *object, M2C_UNK unusedArg, M2C_UNK initValue) {
    initialize_object_entries(object, initValue, &D_800D7284);
    *(M2C_UNK **)((u8 *)object + 0x50) = &D_800CD650;
    *(s16 *)((u8 *)object + 0x6C) = (s16)(((scale_random_to_unsigned_halfword_limit(4) & 0xFFFF) * 0x15) + 0x15);
}
