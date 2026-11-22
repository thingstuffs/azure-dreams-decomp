#include "common.h"
#include "shared/position_views.h"
#include "shared/vector.h"
#include "town/player/position.h"
#include "town/player/action_initializers.h"
#include "shared/sprite_frame_state.h"

   /* arg0 in follow_linked_position_until_timeout */


typedef struct CopySource {
    u32 x;
    s32 y;
    s32 z;
} CopySource;

typedef struct CopyMiddle {
    s32 unk0[2];
    CopySource *source;
} CopyMiddle;

typedef struct CopyGlobal {
    s32 unk0[4];
    CopyMiddle *middle;
} CopyGlobal;


extern CopyGlobal town_actor_control;

/* Copy source coordinates, decrement the counter, and call the handler when it becomes negative. */
void follow_linked_position_until_timeout(TownObjectRecord *state, ObjectPosition *out, SpriteFrameState *handler_arg) {
    s16 remaining;

    out->x.v = town_actor_control.middle->source->x;
    out->y.v = town_actor_control.middle->source->y;
    out->z.v = town_actor_control.middle->source->z;
    remaining = state->unk_0A - 1;
    state->unk_0A = remaining;
    if (remaining < 0) {
        init_target_tile_action(state, out, handler_arg);
    }
}
