#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800D9C7C_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_800D9C7C_1;   /* arg0 in settle_actor_directional_movement */

extern void set_record_integer_tile_center(ObjectPosition *record, s32 tile_x, s32 tile_y);
extern void begin_actor_display_action(void *actor, void *unused, SpriteFrameState *display, u8 *facing_variants);
extern void apply_clamped_actor_value_delta(void *entity);

extern u8 actor_action_resume_address[];

/* Updates directional movement, decelerates it, and settles the entity at its tile. */
void settle_actor_directional_movement(S_800D9C7C_1 *controller, ObjectPosition *motion, SpriteFrameState *entity, EntityRec *source)
{
    s16 ticks_left;
    s32 direction;
    s32 tracked_entity;

    direction = (source->unk_6A >> 9) & 7;
    switch (controller->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(source);
        motion->velocity_x =
            *(s16 *)((u8 *)((s8 *)dir_step_x) + (direction * 2)) << 18;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) + (direction * 2)) << 18;
        controller->unk_9B++;

        if (source->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(controller, motion, entity, 0);
            return;
        }
        if (entity->flags & 0x8000) {
            controller->unk_96.s = 0;
            controller->unk_9B = 2;
            return;
        }
        if (source->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            ticks_left = 8;
        } else {
            ticks_left = -1;
        }
        controller->unk_96.s = ticks_left;
        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;
                /* fall through */

    case 1:
        motion->velocity_x -=
            *(s16 *)((u8 *)((s8 *)dir_step_x) + (direction * 2)) << 14;
        motion->velocity_y -=
            *(s16 *)((u8 *)((s8 *)dir_step_y) + (direction * 2)) << 14;
        if (controller->unk_96.s > 0) {
            controller->unk_96.s = controller->unk_96.u - 1;
        } else if (entity->flags & 0x6000) {
            controller->unk_96.s = 0;
        }
        if (controller->unk_96.s != 0) {
            return;
        }
        if (source->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(controller, motion, entity, 0);
            return;
        }
        controller->unk_96.s = 8;
        controller->unk_9B++;
        return;

    case 2:
        if (controller->unk_96.s != 0) {
            {
                s32 target_x = entity->tile_x << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->velocity_x = ((target_x - current_x) << 15) >> 1;
            }
            {
                s32 target_y = entity->tile_y << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->velocity_y = ((target_y - current_y) << 15) >> 1;
            }
        }
        ticks_left = controller->unk_96.u - 1;
        controller->unk_96.s = ticks_left;
        if ((s32)(ticks_left << 16) > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, entity->tile_x, entity->tile_y);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)source - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        controller->unk_8C = actor_action_resume_address;
        return;

    default:
        return;
    }
}
