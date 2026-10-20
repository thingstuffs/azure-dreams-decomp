#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/position_views.h"

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void reduce_actor_food_meter(void *, s32);

extern s32 D_80171CE8;
extern u8 D_80174EE0[];

typedef struct S_80173514_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173514_0;   /* arg0 in advance_timed_sprite_flashing_sequence */

   /* arg1 in advance_timed_sprite_flashing_sequence */

/* Advance a timed sprite flashing sequence and clean up the actor when it finishes. */
void advance_timed_sprite_flashing_sequence(void *action, void *motion, void *sprite, EntityRec *actor)
{
    u8 state;
    EntityRec *call_actor;
    SpriteFrameState *call_sprite;

    state = ((S_80173514_0 *)action)->unk_9B;
    switch (state) {
    default:
        return;

    case 0:
    {
        call_actor = actor;
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((S_80173514_0 *)action)->unk_9B = 4;
            call_sprite = sprite;
            call_sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(call_actor, call_sprite, call_actor->facing, 1);
            return;
        }
        ((MotionDeltaView *)motion)->unk_14 = 0;
        ((MotionDeltaView *)motion)->unk_10 = 0;
        ((MotionDeltaView *)motion)->unk_0C = 0;
        ((SpriteFrameState *)sprite)->frameTable = D_80174EE0;
        select_sprite_entry(sprite,
            D_80174EE0[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80173514_0 *)action)->unk_96.u = 0;
        ((S_80173514_0 *)action)->unk_9B++;
        return;
    }

    case 1:
        if ((s16)++((S_80173514_0 *)action)->unk_96.u == 5) {
            ((S_80173514_0 *)action)->unk_96.u = 0;
            ((S_80173514_0 *)action)->unk_9B++;
            ((SpriteFrameState *)sprite)->flags |= 0x0800;
            return;
        }
        return;

    case 2:
        if ((s16)++((S_80173514_0 *)action)->unk_96.u == 6 ||
            (((SpriteFrameState *)sprite)->flags & 0xE000)) {
            ((S_80173514_0 *)action)->unk_96.u = 0;
            ((S_80173514_0 *)action)->unk_9B++;
            ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
            play_sound_if_enabled(0x804);
            return;
        }
        return;

    case 3:
        if ((s16)++((S_80173514_0 *)action)->unk_96.u == 5 ||
            (((SpriteFrameState *)sprite)->flags & 0xE000)) {
            ((SpriteFrameState *)sprite)->flags |= 0x0800;
        }
        if (((S_80173514_0 *)action)->unk_96.s == 12 ||
            (((SpriteFrameState *)sprite)->flags & 0xE000)) {
            ((S_80173514_0 *)action)->unk_96.u = 0;
            ((S_80173514_0 *)action)->unk_9B++;
            ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        }
        call_actor = actor;
        if (((S_80173514_0 *)action)->unk_96.s == 1 ||
            (((SpriteFrameState *)sprite)->flags & 0xE000)) {
            call_sprite = sprite;
            resolve_attack_damage_and_effects(call_actor, call_sprite, call_actor->facing, 1);
            return;
        }
        return;

    case 4:
        if (((SpriteFrameState *)sprite)->flags & 0xE000) {
            reduce_actor_food_meter(actor, 0x100);
            ((S_80173514_0 *)action)->unk_8C = &D_80171CE8;
            g_dungeon_status.unk_0C = 0;
            advance_status_timers(actor);
            actor->unk_46 &= 0x7FFF;
        }
    }
}
