#include "common.h"

typedef struct TownB4C60 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} TownB4C60;

/* Sets the zero-based group of ten for the entry's value, with zero mapping to zero. */
void func_800B23C0(TownB4C60 *entry) {
    s32 value = entry->unkC;

    if (value != 0) {
        entry->unk4 = (value - 1) / 10;
        return;
    }
    entry->unk4 = 0;
}
