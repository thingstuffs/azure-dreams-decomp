#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct TownSubState {
    s32 pad0;
    s32 val4;
    s32 val8;
} TownSubState;


/* Set the town substate values to 800 and 1184. */
void func_80016ECC(void) {
    ((TownSubState *)D_80016000->unk_1C)->val4 = 800;
    ((TownSubState *)D_80016000->unk_1C)->val8 = 1184;
}
