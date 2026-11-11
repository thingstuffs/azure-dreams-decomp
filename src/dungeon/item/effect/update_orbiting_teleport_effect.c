#include "shared/object_node.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libc.h"
#include "dungeon/item/effect.h"
#include "dungeon/system.h"
#include "shared/sprite_frame_state.h"

typedef struct S_800C4F20_10 {
    u8 pad_00[0x1C];
    void * unk_1C;
    u8 pad_20[0x4];
    void * unk_24;
} S_800C4F20_10;   /* arg0 in update_orbiting_teleport_effect */


   /* ((S_800C4F20_10 *)arg0)->unk_1C in update_orbiting_teleport_effect */



typedef struct S_800C4F20_0 {
    u8 pad_00[0x20];
    void * unk_20;
    void * unk_24;
    s16 unk_28;
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[0x2];
    s16 unk_32;
    u8 pad_34[0x2];
    s16 unk_36;
} S_800C4F20_0;   /* arg0 in update_orbiting_teleport_effect */





   /* (void *) c2_v0 in update_orbiting_teleport_effect */




s32 rsin();
s32 rcos(s32);

/* Updates an object's staged scale and position animation. */
void update_orbiting_teleport_effect(void *anim, ObjectPosition *position, SpriteFrameState *transform) {
    s16 exit_mode;
    s16 move_ticks;
    s16 rise_ticks;
    s16 grow_ticks;
    s16 grow_left;
    s16 orbit_left;
    s16 move_left;
    s16 finish_left;
    s32 state_or_mode;
    s16 shrink_ticks;
    s32 height_delta;
    s32 target_y;
    s32 target_x;
    s32 orbit_offset;
    s32 x_delta;
    u16 grow_scale;
    u16 grown_scale;
    u16 grow_height;
    u16 shrink_scale;
    u16 shrunk_scale;
    u16 start_scale;
    u16 next_scale;
    u16 stretch_height;
    u16 end_scale;
    u16 final_scale;
    ActorRecord *owner;
    SpriteFrameState *grow_target;
    SpriteFrameState *shrink_target;
    ObjectPosition *orbit_center;

    state_or_mode = ((S_800C4F20_0 *)anim)->unk_28;
    switch (state_or_mode) {
    case 0: {
        S_800C4F20_0 *setup_state = (S_800C4F20_0 *)anim;
        grow_ticks = setup_state->unk_2A;
        if (grow_ticks != 0) {
            S_800C4F20_0 *state = (S_800C4F20_0 *)anim;
            grow_scale = transform->scale_y;
            grown_scale = grow_scale + ((s32) (0x1000 - grow_scale) / grow_ticks);
            grow_height = transform->offset_x;
            transform->scale_y = grown_scale;
            transform->scale_x = grown_scale;
            transform->offset_x = (u16) (grow_height + ((s32) (0x1000
                - grow_height) / (s16) state->unk_2A));
            grow_target = state->unk_20;
            start_scale = grow_target->scale_y;
            next_scale = start_scale + ((s32) (0x400 - start_scale) / (s16) state->unk_2A);
            grow_target->scale_y = next_scale;
            grow_target->scale_x = next_scale;
            state->unk_32 = (s16) ((u16) state->unk_32
                - ((s16) state->unk_32 / (s16) state->unk_2A));
        }
        grow_left = (u16) setup_state->unk_2A - 1;
        setup_state->unk_2A = grow_left;
        if ((grow_left << 0x10) > 0) {
            break;
        }
        transform->scale_y = 0x1000U;
        transform->scale_x = 0x1000U;
        transform->offset_x = 0x1000U;
        {
            SpriteFrameState *target_transform = setup_state->unk_20;
            target_transform->scale_y = 0x800U;
            target_transform->scale_x = 0x800U;
        }
        setup_state->unk_32 = 0;
        setup_state->unk_2A = 0x20;
        setup_state->unk_28++;
        break;
    }
    case 1: {
        S_800C4F20_0 *orbit_state = (S_800C4F20_0 *)anim;
        orbit_offset = rcos(orbit_state->unk_2E);
        orbit_center = &view_reference_entity;
        target_x = orbit_center->x.w.i + (orbit_offset >> 6);
        target_y = orbit_center->y.w.i + (rsin(orbit_state->unk_2E) >> 6);
        x_delta = target_x - position->x.w.i;
        if (x_delta < 0) {
            x_delta += 3;
        }
        position->x.w.i = (s16) ((u16) position->x.w.i + (x_delta >> 2));
        position->y.w.i = (s16) ((u16) position->y.w.i + ((s32) (target_y - position->y.w.i) / 4));
        orbit_offset = (rsin(orbit_state->unk_2C << 5, target_y) >> 6) + 0x40;
        height_delta = orbit_center->z.w.i - position->z.w.i;
        position->z.w.i = (s16) ((u16) position->z.w.i + ((s32) (height_delta - orbit_offset) / 4));
        orbit_state->unk_2E = (s16) ((u16) orbit_state->unk_2E + 0x40
            + (rand() & 0x1F));
        exit_mode = orbit_state->unk_36;
        if (exit_mode == 0) {
            break;
        }
        orbit_left = (u16) orbit_state->unk_2A - 1;
        orbit_state->unk_2A = orbit_left;
        if ((orbit_left << 0x10) > 0) {
            break;
        }
        state_or_mode = exit_mode;
        if (state_or_mode == 1 || state_or_mode == 3) {
            orbit_state->unk_2A = 0x10;
            orbit_state->unk_28++;
        } else {
            orbit_state->unk_2A = 0x20;
            orbit_state->unk_28 += 0x10;
            play_sound_if_enabled(0x518);
        }
        break;
    }
    case 2: {
        S_800C4F20_0 *move_state = (S_800C4F20_0 *)anim;
        move_ticks = move_state->unk_2A;
        if (move_ticks != 0) {
            s32 x_work;
            s32 x_step;

            x_work = (s32) move_state->unk_20;
            x_step = ((MovingTile *)((void *) x_work))->tile_x;
            x_work = position->x.w.i;
            x_step <<= 6;
            x_work -= 0x20;
            x_step -= x_work;
            x_step /= move_ticks;
            position->x.w.i = (s16) ((u16) position->x.w.i + x_step);
            {
                s32 y_work;
                s32 y_step;

                y_work = (s32) move_state->unk_20;
                height_delta = move_state->unk_2A;
                y_step = ((MovingTile *)((void *) y_work))->tile_y;
                y_work = position->y.w.i;
                y_step <<= 6;
                y_work -= 0x20;
                y_step -= y_work;
                y_step /= height_delta;
                position->y.w.i = (s16) ((u16) position->y.w.i + y_step);
            }
            position->z.w.i = (s16) ((u16) position->z.w.i
                + ((s32) (((ActorRecord *)(((S_800C4F20_10 *)anim)->unk_24))->ground_height
                - position->z.w.i) / (s16) move_state->unk_2A));
        }
        move_left = (u16) move_state->unk_2A - 1;
        move_state->unk_2A = move_left;
        if ((move_left << 0x10) > 0) {
            break;
        }
        move_state->unk_2A = 0x10;
        move_state->unk_28++;
        break;
    }
    case 3: {
        S_800C4F20_0 *shrink_state = (S_800C4F20_0 *)anim;
        shrink_ticks = shrink_state->unk_2A;
        if (shrink_ticks != 0) {
            shrink_scale = transform->scale_y;
            shrunk_scale = shrink_scale - ((s32) shrink_scale / shrink_ticks);
            transform->scale_y = shrunk_scale;
            transform->scale_x = shrunk_scale;
            stretch_height = transform->offset_x;
            transform->offset_x = (u16) (stretch_height + ((s32) (0x2000
                - stretch_height) / (s16) shrink_state->unk_2A));
            shrink_target = shrink_state->unk_20;
            end_scale = shrink_target->scale_y;
            final_scale = end_scale + ((s32) (0x1000 - end_scale) / (s16) shrink_state->unk_2A);
            shrink_target->scale_y = final_scale;
            shrink_target->scale_x = final_scale;
            shrink_state->unk_32 = (s16) ((u16) shrink_state->unk_32 + ((s32) (0x400
                - shrink_state->unk_32) / (s16) shrink_state->unk_2A));
        }
        finish_left = (u16) shrink_state->unk_2A - 1;
        shrink_state->unk_2A = finish_left;
        if ((finish_left << 0x10) > 0) {
            break;
        }
        owner = shrink_state->unk_24;
        owner->flags14 = (s32) (owner->flags14 & 0xFFEFFFFF);
        NODE_HEADER(anim)->flags = (u16) (NODE_HEADER(anim)->flags | 0x8000);
        (*&object_flag_block.flags) = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        return;
    }
    case 17: {
        S_800C4F20_0 *rise_state = (S_800C4F20_0 *)anim;
        rise_ticks = rise_state->unk_2A;
        if (rise_ticks != 0) {
            position->z.w.i = (s16) ((u16) position->z.w.i + ((s32) (-0x400 - position->z.w.i) / rise_ticks));
        }
        finish_left = (u16) rise_state->unk_2A - 1;
        rise_state->unk_2A = finish_left;
        if ((finish_left << 0x10) > 0) {
            break;
        }
        owner = rise_state->unk_24;
        owner->flags14 = (s32) (owner->flags14 & 0xFFEFFFFF);
        NODE_HEADER(anim)->flags = (u16) (NODE_HEADER(anim)->flags | 0x8000);
        (*&object_flag_block.flags) = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        return;
    }
    }
    if (((ActorRecord *)(((S_800C4F20_10 *)anim)->unk_24))->flags14 & 0x100000) {
        S_800C4F20_10 *post_view = (S_800C4F20_10 *)anim;
        ((MovingPosition *)(post_view->unk_1C))->x = (u16) position->x.w.i;
        ((MovingPosition *)(post_view->unk_1C))->y = (u16) position->y.w.i;
        ((MovingPosition *)(post_view->unk_1C))->z = (u16) position->z.w.i;
    }
    {
        S_800C4F20_0 *tail_view = (S_800C4F20_0 *)anim;
        tail_view->unk_2C = (s16) ((u16) tail_view->unk_2C + 1);
    }
    transform->angle_z = (u16) (transform->angle_z - 0x80);
    return;
}
