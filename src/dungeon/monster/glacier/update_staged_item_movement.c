#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

extern void set_record_integer_tile_center();
extern void begin_actor_display_action();
extern void apply_clamped_actor_value_delta();

extern u8 D_801714B8;
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
void update_staged_item_movement(void *action, EntityRec *motion, void *target, EntityRec *actor)
{
    u8 state;
    s16 timer;

    state = ((S_80173730_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        ((S_80173730_0 *)action)->unk_96.u = 4;
        ((S_80173730_0 *)action)->unk_9B++;
        if (actor->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            begin_actor_display_action(action, motion, target, &D_801760D4);
            return;
        }
        if (!(((SpriteFrameState *)target)->flags & 0x8000)) {
            return;
        }
        ((S_80173730_0 *)action)->unk_96.u = 0;
        ((S_80173730_0 *)action)->unk_9B = 3;
        return;

    case 1:
        timer = ((S_80173730_0 *)action)->unk_96.u - 1;
        ((S_80173730_0 *)action)->unk_96.u = timer;
        if (timer > 0) {
            motion->unk_0C =
                *(s16 *)(((s8 *)dir_step_x) +
                    ((actor->unk_6A >> 8) & 0xE)) << 19;
            motion->unk_10 =
                *(s16 *)(((s8 *)dir_step_y) +
                    ((actor->unk_6A >> 8) & 0xE)) << 19;
            return;
        }
        if (timer != 0) {
            return;
        }
        motion->unk_0C =
            *(s16 *)(((s8 *)dir_step_x) +
                ((actor->unk_6A >> 8) & 0xE)) << 18;
        motion->unk_10 =
            *(s16 *)(((s8 *)dir_step_y) +
                ((actor->unk_6A >> 8) & 0xE)) << 18;
        ((S_80173730_0 *)action)->unk_96.u = 12;
        ((S_80173730_0 *)action)->unk_9B++;
        return;

    case 2:
        if (actor->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            begin_actor_display_action(action, motion, target, &D_801760D4);
            return;
        }
        {
            s16 motion_timer = ((S_80173730_0 *)action)->unk_96.s;

            if (motion_timer != 0) {
                {
                    s32 target_x = ((SpriteFrameState *)target)->unk_24 << 6;
                    s32 current_x = motion->x.w.i - 0x20;

                    motion->unk_0C =
                        ((target_x - current_x) << 16) / motion_timer;
                }
                {
                    s32 target_y = ((SpriteFrameState *)target)->unk_25 << 6;
                    s32 current_y = motion->y.w.i - 0x20;

                    motion->unk_10 = ((target_y - current_y) << 16)
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
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        ((S_80173730_0 *)action)->unk_9B++;
        return;

    case 3:
    {
        s32 entity_addr;

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)target)->unk_24,
            ((SpriteFrameState *)target)->unk_25);
        entity_addr = ((s32)g_dungeon_status.unk_10);
        if (entity_addr == (s32)((u8 *)actor - 0x20)) {
            g_dungeon_status.unk_10 = entity_addr & 0x7FFFFFFF;
        }
        ((S_80173730_0 *)action)->unk_8C = &D_801714B8;
    }
        return;
    }
}
