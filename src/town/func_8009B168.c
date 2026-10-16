/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

extern void townCopyMotionParametersAndResetFlag(s32 record, s32 source);
extern void townInitializeTargetAndHandlerTable(s32 record, s32 setup_value, s32 init_value);
extern s32 D_80093D48;
extern s32 *D_800FE5D8;

void func_800988C8(s32 record, s32 setup_value, s32 init_value) {
    townCopyMotionParametersAndResetFlag(record, setup_value);
    townInitializeTargetAndHandlerTable(record, setup_value, init_value);
    D_800FE5D8 = &D_80093D48;
}
