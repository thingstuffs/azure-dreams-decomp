#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800AD058_arg2.h"
#include "shared/dungeon_trail_views.h"


extern void select_sprite_entry(void *, s32, s32);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void create_and_initializes_display_source_position_appearance(void *, void *, void *);

extern u8 D_801710F4[];
extern u8 D_80174F00[];


typedef struct S_80174BF8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174BF8_0;   /* arg0 in initialize_a_timed_action_restore_animation_clear_entity_flags */


   /* counter in initialize_a_timed_action_restore_animation_clear_entity_flags */

/* Initialize a timed action, then restore animation and clear the entity flags. */
void initialize_a_timed_action_restore_animation_clear_entity_flags(S_80174BF8_0 *action, void *context, Rec_func_800AD058_arg2 *animation, ActorRecord *entity)
{
    void *entity_arg;
    u16 ticks_left;
    u8 state;

    state = action->unk_9B;
    switch (state) {
    case 0:
        play_sound_if_enabled(0x50C);
        action->unk_96 = 10;
        create_and_initializes_display_source_position_appearance(context, animation, entity);
        entity->unk_48 = 0;
        entity->unk_49 = 0;
        action->unk_9B++;
    case 1:
        break;
    default:
        return;
    }

    if (!(animation->unk_14 & 0x8000)) {
        ticks_left = action->unk_96;
        action->unk_96 = ticks_left - 1;
        if ((s16)ticks_left > 0) {
            return;
        }
    }

    entity_arg = entity;
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    animation->unk_2C = D_80174F00;
    spend_actor_mp(entity_arg, 0x200);
    select_sprite_entry(animation,
        animation->unk_2C[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
        0);
    action->unk_8C = D_801710F4;
    advance_status_timers(entity);
    entity->pending_turn_updates = 0;
    entity->action_flags &= 0x7FFF;
}
