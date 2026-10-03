#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


extern M2C_UNK D_800179FC;
extern s16 D_80017AA0;

/* Dispatches the table entry selected by the current index. */
void func_8054FAA0(void) {
    D_80016000->unk_20->callback_230(*((M2C_UNK *)((s8 *)&D_800179FC + D_80017AA0 * 4)));
}
