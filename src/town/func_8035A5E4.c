#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



/* Invoke the callback at offset 0x88 with zero. */
void func_8035A5E4(void) {
    D_80016000->unk_20->callback_088(0);
}
