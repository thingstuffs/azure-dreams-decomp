#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


/* Invoke the callback at offset 0x278 with settings (1, 2, 0, 0x50). */
void func_80018160(void) {
    D_80016000->unk_20->callback_278(1, 2, 0, 0x50);
}
