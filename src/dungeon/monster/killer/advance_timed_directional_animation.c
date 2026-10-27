#include "common.h"
#include "dungeon/monster/killer.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"

typedef struct S_801727EC_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801727EC_0;   /* arg0 in advance_timed_directional_animation */

extern void select_sprite_entry(void *, u8, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(ObjectPosition *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);

extern void *actor_update_node_cursor;
extern u8 killer_action_resume_address;
extern u8 D_80174060[];

/* Advances a timed directional animation and updates the actor when it completes. */
void advance_timed_directional_animation(ActorRecord *action_state, ObjectPosition *actor_id, SpriteFrameState *animation, ActorRecord *actor) {
    u16 ticks_left;
    u8 phase;

    phase = action_state->action_phase.u;
    switch (phase) {
    case 0:
        if (animation->flags & 0x8000) {
            action_state->action_phase.u = 1;
            animation->flags |= 0x6000;
            ((S_801727EC_0 *)action_state)->unk_96 = 1;
            break;
        }
        ((S_801727EC_0 *)action_state)->unk_96 = 7;
        animation->frameTable = D_80174060;
        select_sprite_entry(animation,
                      D_80174060[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                      0);
        action_state->action_phase.u++;
        break;

    case 1:
        ticks_left = ((S_801727EC_0 *)action_state)->unk_96 - 1;
        ((S_801727EC_0 *)action_state)->unk_96 = ticks_left;
        if (((ticks_left << 16) == 0) || (animation->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            play_sound_if_enabled(0x804);
        }
        if (animation->flags & 0xE000) {
            set_record_integer_tile_center(actor_id, animation->tile_x, animation->tile_y);
            spend_actor_mp(actor, 0x100);
            ((S_801727EC_0 *)action_state)->unk_8C = &killer_action_resume_address;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            if (actor->pending_turn_updates == 0) {
                actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
            } else {
                actor_update_node_cursor = (u8 *)actor - 0x20;
            }
        }
        break;
    }
}
