#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_801237A4_arg0.h"

extern s32 D_80126A10[];
extern s32 D_80126A60;
extern s32 D_80126AD0;


/* Select the indexed value and its paired value from the lookup table. */
void func_801237A4(Rec_func_801237A4_arg0 *record) {
    D_80126A60 = D_80126A10[record->unk_16];
    D_80126AD0 = D_80126A10[record->unk_16 ^ 1];
}
