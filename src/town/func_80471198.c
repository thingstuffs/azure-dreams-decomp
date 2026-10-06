#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


M2C_UNK func_80018824();                /* extern */

/* Pass the two context regions to func_80018824 with their sizes. */
void func_80018198(void) {
    TownStateRecord *context_base;

    context_base = D_80016000->unk_38;
    func_80018824(context_base->history, 0xC0);
    func_80018824(context_base->headIndices, 0x10);
}
