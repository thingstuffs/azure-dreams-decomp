#include "common.h"
#include "dungeon/monster/mandara.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80172BFC_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172BFC_0;   /* arg0 in advance_actor_action_animation_to_completion */

extern void select_sprite_entry(void *, u8, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(s32, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);

extern void *actor_update_node_cursor;
extern s32 mandara_action_resume_address;
extern u8 D_80175288[];

/* Advances the actor action animation and handles completion. */
void advance_actor_action_animation_to_completion(void *action, s32 actor_id, SpriteFrameState *animation, ActorRecord *actor) {
    s32 state;

    state = ((S_80172BFC_0 *)action)->unk_9B;
    ((S_80172BFC_0 *)action)->unk_96--;
    switch (state) {
    case 0:
        if (animation->flags & 0x8000) {
            ((S_80172BFC_0 *)action)->unk_9B = 0xFF;
            animation->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            return;
        }
        animation->frameTable = D_80175288;
        select_sprite_entry(animation,
            D_80175288[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172BFC_0 *)action)->unk_9B++;
        return;

    case 1:
        if (((animation->unk_04 == 3) &&
             (animation->flags & 0x1000)) ||
            (animation->flags & 0x8000)) {
            play_sound_if_enabled(0x804);
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            ((S_80172BFC_0 *)action)->unk_9B = 0xFF;
        }
        return;

    case 0xFF:
        if (animation->flags & 0xE000) {
            set_record_integer_tile_center(actor_id, animation->tile_x, animation->tile_y);
            spend_actor_mp(actor, 0x100);
            ((S_80172BFC_0 *)action)->unk_8C = &mandara_action_resume_address;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            if (actor->pending_turn_updates == 0) {
                actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
                return;
            }
            actor_update_node_cursor = (u8 *)actor - 0x20;
        }
        return;
    }
}
