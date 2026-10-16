#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern u8 D_80017AFC[];

/* Run town service callback 0X218 with this module's record D_80017AFC (this TOWN module's copy of the town/func_8032D78C wrapper). */
void func_80016360(void) {
    D_80016000->unk_20->callback_218(D_80017AFC);
}
