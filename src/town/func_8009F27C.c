/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

extern void townSelectObjectStateByMode(void *record, s32 context, s32 state, void *default_value, void *alternate_value, void *update_value);

extern s32 D_800CFD00[];
extern s32 D_800D071C[];
extern s32 D_800F8D10[];
extern s32 D_800F8D1C[];

void func_8009C9DC(void *object, s32 setup_arg1, s32 setup_arg2) {
    *(void **)((u8 *)object + 0x7C) = D_800D071C;
    townSelectObjectStateByMode(object, setup_arg1, setup_arg2, D_800F8D10, D_800F8D1C, D_800CFD00);
}
