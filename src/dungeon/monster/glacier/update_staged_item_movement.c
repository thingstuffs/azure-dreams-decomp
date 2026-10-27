#include "common.h"
#include "dungeon/monster/glacier.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor.h"
#include "dungeon/player/object.h"

extern void begin_actor_display_action(void *actor, void *unused, SpriteFrameState *display, u8 *facing_variants);

extern u8 D_801760D4;

typedef struct S_80173730_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173730_0;   /* arg0 in update_staged_item_movement */

/* Updates staged movement toward a target tile and finalizes the action. */
void update_staged_item_movement(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *target, ActorRecord *actor) {
    u8 state;
    s16 timer;

    state = action->action_phase.u;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        ((S_80173730_0 *)action)->unk_96.u = 4;
        action->action_phase.u++;
        if (actor->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, target, &D_801760D4);
            return;
        }
        if (!(target->flags & 0x8000)) {
            return;
        }
        ((S_80173730_0 *)action)->unk_96.u = 0;
        action->action_phase.u = 3;
        return;

    case 1:
        timer = ((S_80173730_0 *)action)->unk_96.u - 1;
        ((S_80173730_0 *)action)->unk_96.u = timer;
        if (timer > 0) {
            motion->velocity_x =
                *(s16 *)(((s8 *)dir_step_x) +
                    ((actor->movement_facing >> 8) & 0xE)) << 19;
            motion->velocity_y =
                *(s16 *)(((s8 *)dir_step_y) +
                    ((actor->movement_facing >> 8) & 0xE)) << 19;
            return;
        }
        if (timer != 0) {
            return;
        }
        motion->velocity_x =
            *(s16 *)(((s8 *)dir_step_x) +
                ((actor->movement_facing >> 8) & 0xE)) << 18;
        motion->velocity_y =
            *(s16 *)(((s8 *)dir_step_y) +
                ((actor->movement_facing >> 8) & 0xE)) << 18;
        ((S_80173730_0 *)action)->unk_96.u = 12;
        action->action_phase.u++;
        return;

    case 2:
        if (actor->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, target, &D_801760D4);
            return;
        }
        {
            s16 motion_timer = ((S_80173730_0 *)action)->unk_96.s;

            if (motion_timer != 0) {
                {
                    s32 target_x = target->tile_x << 6;
                    s32 current_x = motion->x.w.i - 0x20;

                    motion->velocity_x =
                        ((target_x - current_x) << 16) / motion_timer;
                }
                {
                    s32 target_y = target->tile_y << 6;
                    s32 current_y = motion->y.w.i - 0x20;

                    motion->velocity_y = ((target_y - current_y) << 16)
                    / ((S_80173730_0 *)action)->unk_96.s;
                }
            }
        }
        {
            u16 countdown = ((S_80173730_0 *)action)->unk_96.u;

            ((S_80173730_0 *)action)->unk_96.u = countdown - 1;
            if ((countdown << 16) > 0) {
                return;
            }
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        action->action_phase.u++;
        return;

    case 3:
    {
        s32 entity_addr;

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, target->tile_x,
            target->tile_y);
        entity_addr = ((s32)g_dungeon_status.pending_display_owner);
        if (entity_addr == (s32)((u8 *)actor - 0x20)) {
            g_dungeon_status.pending_display_owner = entity_addr & 0x7FFFFFFF;
        }
        ((S_80173730_0 *)action)->unk_8C = update_actor_timed_effects;
    }
        return;
    }
}
