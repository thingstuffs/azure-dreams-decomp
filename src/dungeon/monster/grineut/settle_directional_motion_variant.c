#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8016D238_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8016D238_1;   /* arg0 in settle_directional_motion_variant */

extern void select_sprite_entry(void *, s32, s32);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);
extern void apply_clamped_actor_value_delta(void *);

extern u8 D_8016AE54;
extern u8 D_8016E150[];
extern u8 D_8016E178[];

/* Updates directional motion and settles the actor at its tile center. */
void settle_directional_motion_variant(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 state;
    s32 direction;
    s16 timer;
    s32 tracked_actor;

    direction = (actor->unk_6A >> 9) & 7;
    state = ((S_8016D238_1 *)action)->unk_9B;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        motion->unk_0C = ((s16 *)((s8 *)dir_step_x))[direction] << 18;
        motion->unk_10 = ((s16 *)((s8 *)dir_step_y))[direction] << 18;
        ((S_8016D238_1 *)action)->unk_9B++;

        if (actor->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            begin_actor_display_action(action, motion, sprite, D_8016E178);
            return;
        }
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((S_8016D238_1 *)action)->unk_96.s = 0;
            ((S_8016D238_1 *)action)->unk_9B = 3;
            return;
        }

        if (((u32)actor->flags1C) & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        ((S_8016D238_1 *)action)->unk_96.s = timer;

        motion->unk_0C -= motion->unk_0C / 4;
        motion->unk_10 -= motion->unk_10 / 4;

    case 1:
        motion->unk_0C -= ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        motion->unk_10 -= ((s16 *)((s8 *)dir_step_y))[direction] << 14;

        if (((S_8016D238_1 *)action)->unk_96.s > 0) {
            ((S_8016D238_1 *)action)->unk_96.s = ((S_8016D238_1 *)action)->unk_96.u - 1;
        } else if (((SpriteFrameState *)sprite)->flags & 0x6000) {
            ((S_8016D238_1 *)action)->unk_96.s = 0;
        }

        if (((S_8016D238_1 *)action)->unk_96.s != 0) {
            return;
        }
        if (actor->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            begin_actor_display_action(action, motion, sprite, D_8016E178);
            return;
        } else {
            ((SpriteFrameState *)sprite)->frameTable = D_8016E150;
            select_sprite_entry(
                sprite,
                D_8016E150[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_8016D238_1 *)action)->unk_9B++;
            return;
        }

    case 2:
        motion->unk_0C -= ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        motion->unk_10 -= ((s16 *)((s8 *)dir_step_y))[direction] << 14;
        if (!(((SpriteFrameState *)sprite)->flags & 0x6000)) {
            return;
        }

        ((SpriteFrameState *)sprite)->frameTable = D_8016E150;
        select_sprite_entry(
            sprite,
            D_8016E150[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_8016D238_1 *)action)->unk_96.s = 8;
        ((S_8016D238_1 *)action)->unk_9B++;
        return;

    case 3:
        timer = ((S_8016D238_1 *)action)->unk_96.s;
        if (timer != 0) {
            {
                s32 target_x = ((SpriteFrameState *)sprite)->unk_24 << 6;
                s32 current_x = motion->x.w.i - 0x20;
                motion->unk_0C = ((target_x - current_x) << 15) / timer;
            }
            {
                s32 target_y = ((SpriteFrameState *)sprite)->unk_25 << 6;
                s32 current_y = motion->y.w.i - 0x20;
                motion->unk_10 =
                    ((target_y - current_y) << 15) / ((S_8016D238_1 *)action)->unk_96.s;
            }
        }

        timer = ((S_8016D238_1 *)action)->unk_96.u - 1;
        ((S_8016D238_1 *)action)->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        motion->x.v = ((((SpriteFrameState *)sprite)->unk_24 << 6) + 0x20) << 16;
        motion->y.v = ((((SpriteFrameState *)sprite)->unk_25 << 6) + 0x20) << 16;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);

        tracked_actor = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_actor == (s32)((u8 *)actor - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_actor & 0x7FFFFFFF;
        }
        ((S_8016D238_1 *)action)->unk_8C = &D_8016AE54;

        return;
    default:
        return;
    }
}
