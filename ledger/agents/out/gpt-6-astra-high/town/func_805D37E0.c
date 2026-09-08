#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} TownStruct_800198A4;

extern TownStruct_800198A4 D_800198A4[];
extern s32 D_80019B8C;

/* Returns unk8 from the currently selected town entry. */
s32 func_800177E0(void) {
    return D_800198A4[D_80019B8C].unk8;
}
