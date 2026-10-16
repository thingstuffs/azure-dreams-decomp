#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x1E8 with code 2 (second bank copy at link delta 0x7FC1C800). */
void func_80018270(void) {
    D_80016000->unk_20->callback_1E8(2);
}
