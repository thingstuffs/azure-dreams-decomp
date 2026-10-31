#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "engine/object.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern M2C_UNK beldo_effect_pool_script;

/* Runs the global handler and clears both record flags when bit 21 is set. */
void process_global_effect_flags(ActorRecord *primary_record, ObjectPosition *unused_1, SpriteFrameState *unused_2, ActorRecord *secondary_record) {
    if ((g_game_work.pressed_buttons) & 0x200000) {
        enqueue_runtime_pool_script(&beldo_effect_pool_script);
        secondary_record->pending_turn_updates = 0;
        primary_record->action_phase.s = 0;
    }
}
