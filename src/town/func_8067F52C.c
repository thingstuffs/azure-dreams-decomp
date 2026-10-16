#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern u8 D_80018864[];

/* Run town service callback 0x218 with this module's record D_80018864. */
void func_8001652C(void) {
    D_80016000->unk_20->callback_218(D_80018864);
}
