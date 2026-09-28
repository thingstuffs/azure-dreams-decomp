#include "common.h"
#include "shared/record_ptrs.h"

typedef struct TownSubState {
    s32 pad0;
    s32 val4;
    s32 val8;
} TownSubState;

typedef struct TownContext {
    u8 pad_00[0x1C];
    TownSubState *sub;
} TownContext;


/* Set the town substate values to 800 and 1184. */
void func_80016ECC(void) {
    ((TownContext *)D_80016000)->sub->val4 = 800;
    ((TownContext *)D_80016000)->sub->val8 = 1184;
}
