#include "common.h"
#include "shared/record_ptrs.h"

typedef void (*TownCallback)(s32);

typedef struct TownState {
    s32 mode;
    s32 value4;
    s32 value8;
} TownState;

typedef struct TownCallbacks {
    u8 pad0[0x244];
    TownCallback callback244;
    TownCallback callback248;
    u8 pad24C[0xC];
    TownCallback callback258;
} TownCallbacks;

typedef struct TownRoot {
    u8 pad0[0x1C];
    TownState *state;
    TownCallbacks *callbacks;
} TownRoot;


/* Invoke town callbacks and initialize state values with mode-dependent adjustments. */
void func_800174E8(void) {
    TownRoot **root_ptr;
    TownRoot *root;
    TownState *state;

    root_ptr = (TownRoot **) ((s8 *)(&D_80016000));
    (*root_ptr)->callbacks->callback258(10);
    (*root_ptr)->callbacks->callback248(1);
    (*root_ptr)->callbacks->callback244(1);

    root = *root_ptr;
    root->state->value4 = 11;
    root->state->value8 = 10;
    state = root->state;

    switch (state->mode) {
    case 1:
        break;
    case 2:
        state->value4++;
        return;
    case 0:
    case 3:
        state->value4--;
        return;
    }
    root_ptr = (TownRoot **) ((s8 *)(&D_80016000));
    state = (*root_ptr)->state;
    state->value8--;
}
