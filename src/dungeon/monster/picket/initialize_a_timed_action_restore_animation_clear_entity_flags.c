#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800AD058_arg2.h"
#include "shared/dungeon_trail_views.h"
#include "dungeon/actor/status.h"


extern void select_sprite_entry(void *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void create_and_initializes_display_source_position_appearance(void *, void *, void *);

extern u8 picket_action_resume_address[];
extern u8 picket_frame_set_1[];


   /*
 * Plays sound 0x50C, creates the display effect, and waits for the countdown or animation
 * completion. Restores the directional picket frames and handler, charges MP, advances status
 * timers, and clears pending turn and action state.
 */
void initialize_a_timed_action_restore_animation_clear_entity_flags(ActorRecord *action, ObjectPosition *context, SpriteFrameState *animation, ActorRecord *entity) {
    void *entity_arg;
    u16 ticks_left;
    u8 state;

    state = action->action_phase.u;
    switch (state) {
    case 0:
        play_sound_if_enabled(0x50C);
        action->action_timer.u = 10;
        create_and_initializes_display_source_position_appearance(context, animation, entity);
        entity->unk_48 = 0;
        entity->unk_49 = 0;
        action->action_phase.u++;
    case 1:
        break;
    default:
        return;
    }

    if (!(animation->flags & 0x8000)) {
        ticks_left = action->action_timer.u;
        action->action_timer.u = ticks_left - 1;
        if ((s16)ticks_left > 0) {
            return;
        }
    }

    entity_arg = entity;
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    animation->frameTable = picket_frame_set_1;
    spend_actor_mp(entity_arg, 0x200);
    select_sprite_entry(animation,
        (*(u8 **)&animation->frameTable)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
        0);
    action->unk_8C.address = picket_action_resume_address;
    advance_status_timers(entity);
    entity->pending_turn_updates = 0;
    entity->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
}
