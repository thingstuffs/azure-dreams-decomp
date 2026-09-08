#include "common.h"

/* --- gcc 2.7.2 -O2 -fno-schedule-insns -fno-schedule-insns2 translation unit --- */

typedef struct {
    /* 0x0 */ u8 pad[8];
    /* 0x8 */ s32 unk8;
} UnkStruct491CC;

/* Sets the field at offset 0x8 in each entry of a pointer array. */
void func_800491CC(UnkStruct491CC **entries, s32 value, s32 count)
{
    s32 index;
    UnkStruct491CC **slot;

    slot = entries;
    index = 0;
    if (count > 0) {
        do {
            UnkStruct491CC *entry = *slot;
            index++;
            entry->unk8 = value;
            slot++;
        } while (index < count);
    }
}
