#include "common.h"

#include "common.h"

typedef struct {
    s16 unk0;
    s16 unk2;
} S_80013564;

typedef struct {
    char unk[0x13];
} S_800133E8;

extern S_80013564 D_80013564[];
extern s32 func_8004A6C0(s32 a0, s32 a1);

/* Stores two values in the selected slot and returns the corresponding record. */
S_800133E8 *func_8004A700(s16 first_value, s16 second_value)
{
    S_800133E8 *record = 0;
    s32 slot = func_8004A6C0(0, 0);

    if (slot < 0x14) {
        record = (S_800133E8 *)0x800133E8 + slot;
        D_80013564[slot].unk0 = first_value;
        D_80013564[slot].unk2 = second_value;
    }

    return record;
}
