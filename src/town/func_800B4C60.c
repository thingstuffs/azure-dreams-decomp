#include "common.h"

typedef struct TownB4C60 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} TownB4C60;

/* Convert the stored value to a zero-based group of ten, preserving zero. */
void func_800B23C0(TownB4C60 *record) {
    s32 stored_value = record->unkC;

    if (stored_value != 0) {
        record->unk4 = (stored_value - 1) / 10;
        return;
    }
    record->unk4 = 0;
}
