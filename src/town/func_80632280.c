#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x04C with (2, 0x12). */
void func_80016280(void) {
    D_80016000->unk_20->callback_04C(2, 0x12);
}
