#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"


extern void select_sprite_entry(void *, u8, s32);
#include "dungeon/player/object/action_state.h"
extern s32 generate_random_value(void);
extern u8 viper_frame_set_1[];

/* Start the actor's hit reaction: clear its flags, give it a random spin and arm the matching sprite frame. */
void start_actor_hit_reaction(ActorRecord *work, ObjectPosition *part_a, SpriteFrameState *part_b, ActorRecord *actor) {
    s32 value;

    actor->movement_queue_state = (u8)(actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(actor) << 16) == 0)) {
        work->unk_8C.word = 0;
        work->action_id.s = 0x17;
        work->action_phase.s = 0;
        if (actor->flags1C & ACTOR_CONFUSED) {
            value = actor->flags14;
            if (!(value & 0x80000000)) {
                value |= 0x80000000;
                actor->flags14 = (s32)value;
                actor->facing = (u16)(((u16)actor->facing) + ((generate_random_value() & 7) << 9));
            }
        }
        work->action_timer.s = 0;
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
        actor->pending_turn_updates = (u8)(((u8)actor->pending_turn_updates) - 1);
        (part_b->frameTable) = viper_frame_set_1;
        select_sprite_entry(part_b, viper_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + (s16)((u16)actor->facing) + 0x100) >> 9) & 7], 0);
    }
}
