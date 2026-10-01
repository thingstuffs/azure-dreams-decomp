#include "common.h"
#include "shared/tile_object.h"

extern s8 func_8009FB34(u8, u8);
extern void func_800A19E4(void *, void *, s32, s32, void *);
extern void func_800A1B44(s32, s32);

/* Updates the default or linked state and dispatches action (3, 6). */
void func_800AA53C(u8 *context) {
    if ((context == 0) || (context[0x13] == 0)) {
        TileObject *state = &D_80082E80;

        state->unk_026 = func_8009FB34(state->tileX, state->tileY);
        func_800A1B44(3, 6);
        return;
    } else {
        TileObject *state = *(TileObject **)(context - 0x14);

        state->unk_026 = func_8009FB34(state->tileX, state->tileY);
        func_800A19E4(state, context, 3, 6, context + 0x9C);
    }
}
