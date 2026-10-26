#include "common.h"
#include "dungeon/monster/picket.h"
#include "shared/object_flags.h"

typedef struct S_80174978_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
    s16 unk_AA;
} S_80174978_0;   /* arg0 in update_a_timed_movement_animation_marks_completion */




extern void place_item_at_valid_floor_position(s16, s16, s16, s32 , void *);

/* Updates a timed movement animation and marks its completion. */
void update_a_timed_movement_animation_marks_completion(void *actor, ObjectPosition *motion, SpriteFrameState *visual) {
    s32 state;
    s32 z_step;
    s32 speed_or_z;
    s32 current_z;
    s32 next_height;
    u16 timer;
    u16 next_scale;

    state = ((S_80174978_0 *)actor)->unk_9B;
    switch (state) {
    case 0:
        if (visual->flags & 0x8000) {
            ((S_80174978_0 *)actor)->unk_9B = 2;
            return;
        }
        ((S_80174978_0 *)actor)->unk_96 = 12;
        ((S_80174978_0 *)actor)->unk_9B = ((S_80174978_0 *)actor)->unk_9B + 1;

    case 1:
    {
        s32 target_x;
        s32 current_x;

        target_x = ((S_80174978_0 *)actor)->unk_A8 << 6;
        current_x = motion->x.w.i - 0x20;
        motion->x.w.i = (u16)motion->x.w.i +
            ((target_x - current_x) >> 1);
    }
        z_step = ((S_80174978_0 *)actor)->unk_AA;
        speed_or_z = motion->velocity_z + 0x30000;
        next_height = motion->z.v + speed_or_z;
        motion->velocity_z = speed_or_z;
        current_z = motion->y.w.i - 0x20;
        z_step <<= 6;
        motion->z.v = next_height;
        z_step -= current_z;
        z_step >>= 1;
        motion->y.w.i = (u16)motion->y.w.i + z_step;
        if (visual->scale_x < 0x1000U) {
            next_scale = visual->scale_y + 0x50;
            visual->scale_y = next_scale;
            visual->scale_x = next_scale;
        }
        timer = ((S_80174978_0 *)actor)->unk_96 - 1;
        ((S_80174978_0 *)actor)->unk_96 = timer;
        if ((timer << 16) != 0) {
            return;
        }
        motion->velocity_z = 0;
        ((S_80174978_0 *)actor)->unk_9B = ((S_80174978_0 *)actor)->unk_9B + 1;
        return;

    case 2:
        place_item_at_valid_floor_position(((S_80174978_0 *)actor)->unk_A8,
                      ((S_80174978_0 *)actor)->unk_AA,
                      (s16)(((u16) motion->z.w.i) - 0x20),
                      (s32)visual->source, actor + 0x48);
        (*(u16 *)((u8 *)actor + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;

        return;
    }
}
