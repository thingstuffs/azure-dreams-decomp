#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

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
extern void set_record_integer_tile_center(s32, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void reduce_actor_food_meter(void *, s32);

extern void *D_800E3DE8;
extern u8 D_80170EA8;
extern u8 D_80174060[];

/* Advances a timed directional animation and updates the actor when it completes. */
void advance_timed_directional_animation(void *action_state, s32 actor_id, void *animation, EntityRec *actor) {
    u16 ticks_left;
    u8 phase;

    phase = ((S_801727EC_0 *)action_state)->unk_9B;
    switch (phase) {
    case 0:
        if (((SpriteFrameState *)animation)->flags & 0x8000) {
            ((S_801727EC_0 *)action_state)->unk_9B = 1;
            ((SpriteFrameState *)animation)->flags |= 0x6000;
            ((S_801727EC_0 *)action_state)->unk_96 = 1;
            break;
        }
        ((S_801727EC_0 *)action_state)->unk_96 = 7;
        ((SpriteFrameState *)animation)->frameTable = D_80174060;
        select_sprite_entry(animation,
                      D_80174060[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                      0);
        ((S_801727EC_0 *)action_state)->unk_9B++;
        break;

    case 1:
        ticks_left = ((S_801727EC_0 *)action_state)->unk_96 - 1;
        ((S_801727EC_0 *)action_state)->unk_96 = ticks_left;
        if (((ticks_left << 16) == 0) || (((SpriteFrameState *)animation)->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            play_sound_if_enabled(0x804);
        }
        if (((SpriteFrameState *)animation)->flags & 0xE000) {
            set_record_integer_tile_center(actor_id, ((SpriteFrameState *)animation)->unk_24, ((SpriteFrameState *)animation)->unk_25);
            reduce_actor_food_meter(actor, 0x100);
            ((S_801727EC_0 *)action_state)->unk_8C = &D_80170EA8;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            if (actor->unk_6D == 0) {
                actor->unk_46 &= 0x7FFF;
            } else {
                D_800E3DE8 = (u8 *)actor - 0x20;
            }
        }
        break;
    }
}
