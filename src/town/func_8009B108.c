#include "common.h"

extern void townCopyMotionParametersAndResetFlag(s32 record, s32 source);
extern void townInitializeRecordWithHandlerTable(s32 record, s32 setup_value, s32 init_value);
extern s32 D_80093D48;
extern s32 *D_800FE5D8;

/* Run both initialization routines and select D_80093D48 as the active data. */
void townInitializeRecordAndSelectActiveData(s32 record, s32 setup_value, s32 init_value) {
    townCopyMotionParametersAndResetFlag(record, setup_value);
    townInitializeRecordWithHandlerTable(record, setup_value, init_value);
    D_800FE5D8 = &D_80093D48;
}
