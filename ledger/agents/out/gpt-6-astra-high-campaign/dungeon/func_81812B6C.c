#include "common.h"

/* Set eight object fields to a scaled value with successive 0x10 offsets. */
void func_80027B6C(s32 object_table, s32 scale_numerator, s32 scale_denominator) {
    s32 scaled_value;
    s32 entry_index;
    s32 scaled_numerator;
    s32 entry_offset;
    void **object_entry;
    void *object;

    entry_index = 6;
    scaled_numerator = scale_numerator * 0x90;
    entry_offset = -0x90;
    object_entry = (void **)(object_table + 0x18);
    do {
        scaled_value = scaled_numerator / scale_denominator;
        object = *object_entry++;
        entry_index++;
        *(s16 *)((u8 *)*(void **)((u8 *)object + 4) + 0xA) =
            scaled_value + entry_offset + 0x90;
        entry_offset += 0x10;
    } while (entry_index < 0xE);
}
