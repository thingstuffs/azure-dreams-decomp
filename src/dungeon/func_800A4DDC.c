#include "common.h"
#include "shared/tile_object.h"

extern s8 func_8009FB34(u8, u8);
extern void dungeonUpdateActorProximityFlag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
extern void dungeonUpdateAllActorProximityFlags(s16 near_limit, s16 far_limit);

/* Updates the default or linked state and dispatches action (3, 6). */
void func_800AA53C(u8 *context) {
    if ((context == 0) || (context[0x13] == 0)) {
        TileObject *state = &D_80082E80;

        state->unk_026 = func_8009FB34(state->tileX, state->tileY);
        dungeonUpdateAllActorProximityFlags(3, 6);
        return;
    } else {
        TileObject *state = *(TileObject **)(context - 0x14);

        state->unk_026 = func_8009FB34(state->tileX, state->tileY);
        dungeonUpdateActorProximityFlag(state, context, 3, 6, context + 0x9C);
    }
}
