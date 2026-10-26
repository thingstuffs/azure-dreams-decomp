#include "dungeon/actor/status.h"

struct SpriteFrameState;
#include "common.h"
#include "dungeon/monster/cyclone.h"
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

extern s32 rsin(s32);
extern s32 rcos(s32);
extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void create_directional_effect(void *, void *,struct SpriteFrameState *);
extern void create_offset_directional_effect(void *, void *,struct SpriteFrameState *);

extern u8 cyclone_attack_frames[];

/* Updates a timed backward-then-forward movement sequence and handles animation completion. */
void advance_backward_forward_motion(void *action, ObjectPosition *motion, SpriteFrameState *animation, ActorRecord *actor)
{
    u16 timer;
    s32 state;

    state = ((S_80172C98_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        ((S_80172C98_0 *)action)->unk_AE.s = 6;
        motion->velocity_x =
            -(((rcos(actor->facing) >> 4) << 13) /
              ((S_80172C98_0 *)action)->unk_AE.s);
        motion->velocity_y =
            -(((rsin(actor->facing) >> 4) << 13) /
              ((S_80172C98_0 *)action)->unk_AE.s);
        ((S_80172C98_0 *)action)->unk_9B++;

    case 1:
        if (animation->flags & 0x8000) {
            ((S_80172C98_0 *)action)->unk_9B = 3;
            motion->velocity_x =
                motion->velocity_y =
                    motion->velocity_z = 0;
            animation->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            return;
        }

        timer = ((S_80172C98_0 *)action)->unk_AE.u - 1;
        ((S_80172C98_0 *)action)->unk_AE.u = timer;
        if ((s16)timer < 0) {
            motion->velocity_x =
                motion->velocity_y =
                    motion->velocity_z = 0;
        }

        if (animation->flags & 0x6000) {
            u8 *direction_anims = cyclone_attack_frames;

            animation->frameTable = direction_anims;
            select_sprite_entry(
                animation,
                direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80172C98_0 *)action)->unk_AE.s = 6;
            motion->velocity_x =
                ((rcos(actor->facing) >> 4) << 14) /
                ((S_80172C98_0 *)action)->unk_AE.s;
            motion->velocity_y =
                ((rsin(actor->facing) >> 4) << 14) /
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
            motion->velocity_x =
                motion->velocity_y =
                    motion->velocity_z = 0;
        }

        timer = ((S_80172C98_0 *)action)->unk_96 + 1;
        ((S_80172C98_0 *)action)->unk_96 = timer;
        if (((s16)timer == 5) || (animation->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            play_sound_if_enabled(0x808);
        }

    case 3:
        if (animation->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            set_record_integer_tile_center(motion, animation->tile_x, animation->tile_y);
            motion->velocity_x =
                motion->velocity_y =
                    motion->velocity_z = 0;
            ((S_80172C98_0 *)action)->unk_8C = update_actor_animation;
            g_dungeon_status.active_actor = 0;
            (actor->action_flags) &= 0x7FFF;
            advance_status_timers(actor);
        }
    }
}
