#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/griffon.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80161234_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80161234_0;   /* arg0 in advance_entity_movement_and_settle_tile */

extern void select_sprite_entry(void *, s32, s32);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);
extern void apply_clamped_actor_value_delta(void *);

extern u8 griffon_slot_d_action_callback;
extern u8 griffon_frame_set_10[];
extern u8 D_80162C74[];

/* Advances entity movement through its phases and settles it at the tile center. */
void advance_entity_movement_and_settle_tile(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity) {
    s32 state;
    s16 timer;
    s32 entity_ref;

    state = action->action_phase.u;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_x =
            -((s16 *)((s8 *)dir_step_x))[(entity->movement_facing >> 9) & 7] << 15;
        motion->velocity_y =
            -((s16 *)((s8 *)dir_step_y))[(entity->movement_facing >> 9) & 7] << 15;
        action->action_phase.u++;

        if (entity->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, sprite, D_80162C74);
            return;
        }
        if (sprite->flags & 0x8000) {
            ((S_80161234_0 *)action)->unk_96.s = 0;
            action->action_phase.u = 3;
            return;
        }

        if (((u32)entity->flags1C) & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        } else {
            timer = -1;
        }
        ((S_80161234_0 *)action)->unk_96.s = timer;

        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;
                        /* fall through */

    case 1:
        motion->velocity_x +=
            ((s16 *)((s8 *)dir_step_x))[(entity->movement_facing >> 9) & 7] << 14;
        motion->velocity_y +=
            ((s16 *)((s8 *)dir_step_y))[(entity->movement_facing >> 9) & 7] << 14;

        if (((S_80161234_0 *)action)->unk_96.s > 0) {
            ((S_80161234_0 *)action)->unk_96.s = ((S_80161234_0 *)action)->unk_96.u - 1;
        } else if (sprite->flags & 0x6000) {
            ((S_80161234_0 *)action)->unk_96.s = 0;
        }

        if (((S_80161234_0 *)action)->unk_96.s != 0) {
            return;
        }
        if (entity->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, sprite, D_80162C74);
            return;
        }
        sprite->frameTable = griffon_frame_set_10;
        select_sprite_entry(
            sprite,
            griffon_frame_set_10[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        action->action_phase.u++;
        return;

    case 2:
        motion->velocity_x +=
            ((s16 *)((s8 *)dir_step_x))[(entity->movement_facing >> 9) & 7] << 14;
        motion->velocity_y +=
            ((s16 *)((s8 *)dir_step_y))[(entity->movement_facing >> 9) & 7] << 14;
        if (!(sprite->flags & 0x6000)) {
            return;
        }

        sprite->frameTable = griffon_frame_set_10;
        select_sprite_entry(
            sprite,
            griffon_frame_set_10[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        ((S_80161234_0 *)action)->unk_96.s = 8;
        action->action_phase.u++;
        return;

    case 3:
        timer = ((S_80161234_0 *)action)->unk_96.s;
        if (timer != 0) {
            {
                s32 target_x = sprite->tile_x << 6;
                s32 current_x = motion->x.w.i - 0x20;
                motion->velocity_x = ((target_x - current_x) << 15) / timer;
            }
            {
                s32 target_y = sprite->tile_y << 6;
                s32 current_y = motion->y.w.i - 0x20;
                motion->velocity_y =
                    ((target_y - current_y) << 15) / ((S_80161234_0 *)action)->unk_96.s;
            }
        }

        timer = ((S_80161234_0 *)action)->unk_96.u - 1;
        ((S_80161234_0 *)action)->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        motion->x.v = ((sprite->tile_x << 6) + 0x20) << 16;
        motion->y.v = ((sprite->tile_y << 6) + 0x20) << 16;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

        entity_ref = ((s32)g_dungeon_status.pending_display_owner);
        if (entity_ref == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = entity_ref & 0x7FFFFFFF;
        }
        ((S_80161234_0 *)action)->unk_8C = &griffon_slot_d_action_callback;
    }
}
