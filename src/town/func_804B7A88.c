#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern u8 D_80018DDC[];

/* Run town service callback 0X218 with this module's record D_80018DDC (this TOWN module's copy of the town/func_8032D78C wrapper). */
void func_80016288(void) {
    D_80016000->unk_20->callback_218(D_80018DDC);
}
