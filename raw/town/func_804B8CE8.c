#include "common.h"

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

extern s8 D_80016000[];

void func_800174E8(void) {
    TownRoot **context_ptr;
    u8 *tail_page;
    TownRoot *root;
    TownState *state;

    context_ptr = (TownRoot **) D_80016000;
    (*context_ptr)->callbacks->callback258(10);
    (*context_ptr)->callbacks->callback248(1);
    (*context_ptr)->callbacks->callback244(1);

    root = *context_ptr;
    root->state->value4 = 11;
    root->state->value8 = 10;
    state = root->state;

    switch (state->mode) {
    case 2:
        state->value4++;
        return;
    case 0:
    case 3:
        state->value4--;
        return;
    case 1:
        goto set_tail_page;
    default:
        tail_page = (u8 *) 0x80010000;
        goto load_tail_root;
    }

set_tail_page:
    tail_page = (u8 *) 0x80010000;
load_tail_root:
    state = (*(TownRoot * volatile *) (tail_page + 0x6000))->state;
    state->value8--;
}

/* MECHANISM: A D_80016000 pointer-to-root local keeps only the symbol high page live in s0.
   Typed root/state/callback records preserve the destructive v0 call chains and v1 state lifetime.
   A page-valued two-entry tail puts case/default luis in delay slots before one shared 0x6000 load. */
