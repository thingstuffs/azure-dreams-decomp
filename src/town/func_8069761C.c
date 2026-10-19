#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_dispatch_data.h"


void dispatch_event_d_8_a();
extern s32 D_80018BE8;

/* Initialize the shared data and store the mode-2 callback result. */
void func_8069761C(void) {

    dispatch_event_d_8_a(&D_80018AE8);

    D_80018BE8 = D_80016000->unk_20->callback_068(0, 0, 2, &D_80018AE8);
}
