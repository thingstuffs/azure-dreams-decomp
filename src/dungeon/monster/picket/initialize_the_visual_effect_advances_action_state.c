#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AD058_arg0.h"
#include "shared/entity.h"
#include "records/Rec_func_800AD058_arg2.h"
#include "dungeon/system.h"
#include "dungeon/actor.h"
#include "dungeon/monster/picket.h"

/*
 * Waits for pending actions, creates an optional display, applies the defeat tint/flags with a
 * 16-tick delay and sound 0x805, then runs the shared defeat-removal update.
 */
void initialize_the_visual_effect_advances_action_state(ActorRecord *action, ObjectPosition *context, Rec_func_800AD058_arg2 *visual, ActorRecord *entity) {
    s32 one;
    s32 phase;

    phase = action->action_phase.u;
    one = 1;
    switch (phase) {
    case 0:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        action->action_phase.s = (u8)one;
    case 1:
        if (entity->unk_49 != 0) {
            create_and_initializes_display_source_position_appearance(context, visual, entity);
            entity->unk_48 = 0;
            entity->unk_49 = 0U;
        }

        visual->unk_10 = 0x20;
        visual->unk_12 = (u16)(visual->unk_12 - 0x80);
        visual->unk_14 = (u16)(visual->unk_14 | 0xC);
        entity->flags1C = entity->flags1C | 0x10000000;
        visual->unk_0C = 0x808080;
        action->action_timer.s = 0x10;
        action->action_phase.s = (u8)(action->action_phase.u + 1);
        play_sound_if_enabled(0x805);
        return;
    case 2:
        update_actor_defeat_removal(action, context, visual, entity);
        return;
    }
}
