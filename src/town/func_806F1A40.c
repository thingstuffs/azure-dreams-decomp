#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"

M2C_UNK func_80017744();
M2C_UNK func_800177BC();
extern M2C_UNK D_80017A00;
extern M2C_UNK *D_80017A98;

/* Ask the scene object for its mode and raise the matching 0xBE9 event, then arm the next handler. */
void func_806F1A40(void) {
    if (D_80016000->unk_20->callback_334(0) != 5) {
        func_80017744(0xBE9);
    } else {
        func_800177BC(0xBE9);
    }
    D_80017A98 = &D_80017A00;
}
