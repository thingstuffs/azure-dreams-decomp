#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern M2C_UNK D_800173FC;
extern M2C_UNK *D_80017494;


/* Invokes the callback and points the shared pointer at D_800173FC. */
void func_80559100(void *callback_arg) {
    ((s32 (*)(void *))D_80016000->unk_20->callback_1F0)(callback_arg);
    D_80017494 = &D_800173FC;
}
