#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


/* Invokes the callback with values 2 and 13 and two zero arguments. */
void func_8059E664(void) {
    ((void (*) (s32, s32, s32, s32))D_80016000->unk_20->callback_220)(2, 0xD, 0, 0);
}
