#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"

typedef void (*Callback)(s32);

extern s32 D_800183C8;

/* Save the state value in D_800183C8 and invoke the state callback with 0. */
void func_8065C2C4(void) {
    D_800183C8 = ((TownPositionState *)D_80016000->unk_1C)->unk_3C;
    D_80016000->unk_20->callback_044(0);
}
