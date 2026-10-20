#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172C98_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x12];
    union { s16 s; u16 u; } unk_AE;   /* accessed as both */
} S_80172C98_0;   /* arg0 in advance_backward_forward_motion */

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void reduce_actor_food_meter(void *, s32);
extern void create_directional_effect(void *, void *, void *);
extern void create_offset_directional_effect(void *, void *, void *);

extern u8 D_80171094[];
extern u8 D_80176488[];

/* Updates a timed backward-then-forward movement sequence and handles animation completion. */
void advance_backward_forward_motion(void *action, EntityRec *motion, void *animation, EntityRec *actor)
{
    u16 timer;
    s32 state;

    state = ((S_80172C98_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        ((S_80172C98_0 *)action)->unk_AE.s = 6;
        motion->unk_0C =
            -(((func_80064584(actor->facing) >> 4) << 13) /
              ((S_80172C98_0 *)action)->unk_AE.s);
        motion->unk_10 =
            -(((func_800644B8(actor->facing) >> 4) << 13) /
              ((S_80172C98_0 *)action)->unk_AE.s);
        ((S_80172C98_0 *)action)->unk_9B++;

    case 1:
        if (((SpriteFrameState *)animation)->flags & 0x8000) {
            ((S_80172C98_0 *)action)->unk_9B = 3;
            motion->unk_0C =
                motion->unk_10 =
                    motion->flags14 = 0;
            ((SpriteFrameState *)animation)->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            return;
        }

        timer = ((S_80172C98_0 *)action)->unk_AE.u - 1;
        ((S_80172C98_0 *)action)->unk_AE.u = timer;
        if ((s16)timer < 0) {
            motion->unk_0C =
                motion->unk_10 =
                    motion->flags14 = 0;
        }

        if (((SpriteFrameState *)animation)->flags & 0x6000) {
            u8 *direction_anims = D_80176488;

            ((SpriteFrameState *)animation)->frameTable = direction_anims;
            select_sprite_entry(
                animation,
                direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80172C98_0 *)action)->unk_AE.s = 6;
            motion->unk_0C =
                ((func_80064584(actor->facing) >> 4) << 14) /
                ((S_80172C98_0 *)action)->unk_AE.s;
            motion->unk_10 =
                ((func_800644B8(actor->facing) >> 4) << 14) /
                ((S_80172C98_0 *)action)->unk_AE.s;
            ((S_80172C98_0 *)action)->unk_AE.u--;
            create_directional_effect(action, motion, animation);
            create_offset_directional_effect(action, motion, animation);
            play_sound_if_enabled(0x80E);
            ((S_80172C98_0 *)action)->unk_9B++;
            ((S_80172C98_0 *)action)->unk_96 = 0;
        }
        return;

    case 2:
        timer = ((S_80172C98_0 *)action)->unk_AE.u - 1;
        ((S_80172C98_0 *)action)->unk_AE.u = timer;
        if ((s16)timer < 0) {
            motion->unk_0C =
                motion->unk_10 =
                    motion->flags14 = 0;
        }

        timer = ((S_80172C98_0 *)action)->unk_96 + 1;
        ((S_80172C98_0 *)action)->unk_96 = timer;
        if (((s16)timer == 5) || (((SpriteFrameState *)animation)->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            play_sound_if_enabled(0x808);
        }

    case 3:
        if (((SpriteFrameState *)animation)->flags & 0xE000) {
            reduce_actor_food_meter(actor, 0x100);
            set_record_integer_tile_center(motion, ((SpriteFrameState *)animation)->unk_24, ((SpriteFrameState *)animation)->unk_25);
            motion->unk_0C =
                motion->unk_10 =
                    motion->flags14 = 0;
            ((S_80172C98_0 *)action)->unk_8C = D_80171094;
            g_dungeon_status.active_actor = 0;
            (actor->unk_46) &= 0x7FFF;
            advance_status_timers(actor);
        }
    }
}
