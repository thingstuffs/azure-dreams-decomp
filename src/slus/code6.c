#include "common.h"

typedef struct {
    /* 0x0 */ u8 pad[8];
    /* 0x8 */ s32 unk8;
} UnkStruct491CC;

/* Sets the field at offset 0x8 in each entry of a pointer array. */
void func_800491CC(UnkStruct491CC **entries, s32 value, s32 count)
{
    s32 index;

    for (index = 0; index < count; index++) {
        entries[index]->unk8 = value;
    }
}
