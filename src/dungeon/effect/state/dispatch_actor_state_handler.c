#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/effect/state.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/player.h"

/* Dispatch state handlers according to the signed state value and actor flags. */
void dispatch_actor_state_handler(Rec_func_8008ACDC_arg0 *actor, void *context, SpriteFrameState *object, ActorRecord *state) {
    s16 state_value;

    state_value = state->hp_delta;
    if ((state_value < 0) || (actor->unk_10C & 1)) {
        object->flags = (u16) (object->flags & 0xF7FF);
        begin_player_damage_reaction(actor, context, object, state);
        return;
    }
    if (state_value > 0) {
        apply_pending_byte_increase(actor, context, object, state);
    }
    if ((actor->unk_9A.as_u8 != 0xD) && (state->flags1C & ACTOR_ASLEEP)) {
        object->flags = (u16) (object->flags & 0xF7FF);
        begin_player_sleep_action(actor, context, object, state);
    }
}
