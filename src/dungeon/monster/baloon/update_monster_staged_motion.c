#include "common.h"
#include "dungeon/monster/baloon.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor.h"


typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} LocalVector;

typedef struct {
    u32 words[8];
} __attribute__((packed)) LocalTable;

extern void select_sprite_entry(void *, u8, s32);
extern s32 rsin(s32);
extern s32 rcos(s32);
extern void unlink_entity_node(void *);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s32 distribute_experience_and_report_gains(void *);
extern void * detach_record_and_update_slot_state(void *);
extern s32 check_left_tile_and_center_height(u16, u16, s16);
extern void play_sound_if_enabled(s32);
extern s16 sample_terrain_surface_height(u16, u16, s16);
extern s32 random_below_limit(s32);

extern u8 baloon_hop_frames[];
extern LocalTable baloon_motion_direction_vectors;

typedef struct S_8017450C_0 {
    u8 pad_00[0x90];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
    u8 pad_A4[0xA];
    s16 unk_AE;
    u8 pad_B0[0x6];
    u16 unk_B6;
} S_8017450C_0;   /* arg0 in update_monster_staged_motion */

typedef struct S_8017450C_3 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_8017450C_3;   /* actor in update_monster_staged_motion */


/* Update the monster's staged motion, choose a nearby destination, and clean up its actor. */
/* Animates Baloon's spinning defeat and fall, searches nearby tiles, awards experience, and removes the
 * actor. */
void update_monster_staged_motion(void *state, ObjectPosition *motion, SpriteFrameState *monster, void *actor_ptr)
{
    LocalVector direction;
    LocalTable direction_table;
    s16 facing_angle;
    s32 trig_value;
    s32 scaled_speed;
    s32 attempt;
    s32 random_x;
    s32 random_y;
    s32 x_offset;
    s32 y_offset;
    s32 x;
    s32 y;
    s32 direction_index;
    u32 actor;
    u8 tile_x;
    u8 tile_y;

    direction_table = baloon_motion_direction_vectors;
    actor = (u32)actor_ptr;

    switch (((S_8017450C_0 *)state)->unk_9B) {
    case 0:
        if (monster->flags & 0x8000) {
            break;
        }

        facing_angle = 0;
        do {
            if (((g_game_work.view.camera_rotation.parts.viewAngle + facing_angle + 0x100) >> 9 & 7) == 2) {
                ((S_8017450C_3 *)actor)->unk_2A = facing_angle;
            }
            facing_angle += 0x200;
        } while (facing_angle < 0x1000);

        {
            u8 *animation_table = baloon_hop_frames;
            (monster->frameTable) = animation_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + ((S_8017450C_3 *)actor)->unk_2A + 0x100) >> 9 & 7;
            select_sprite_entry(monster, animation_table[direction_index], 0);
            ((S_8017450C_0 *)state)->unk_98 |= 8;
            ((S_8017450C_3 *)actor)->unk_1C &= 0xFFFBFFFF;
            ((S_8017450C_0 *)state)->unk_90.at02.v += ((S_8017450C_3 *)actor)->unk_88;
            ((S_8017450C_3 *)actor)->unk_88 = 0;
        }
        {
            u16 next_state = ((S_8017450C_0 *)state)->unk_9B;
            u16 state_or_height;
            s32 height_offset = ((S_8017450C_0 *)state)->unk_90.at02.v;
            s32 *sound_flags = &dungeon_floor_flags;
            ((S_8017450C_0 *)state)->unk_A0 = 0;
            ((S_8017450C_0 *)state)->unk_9B = next_state + 1;
            state_or_height = ((u16) motion->z.w.i);
            state_or_height += height_offset;
            ((S_8017450C_0 *)state)->unk_B6 = state_or_height;
            *sound_flags |= 0x40;
            play_sound_if_enabled(0x807);
        }

    case 1:
        ((S_8017450C_0 *)state)->unk_96.s = 0;
        ((S_8017450C_0 *)state)->unk_9B++;
        monster->offset_y = 0xFFEC;
        monster->scale_x = 0x800;

    case 2:
        switch ((s16)((S_8017450C_0 *)state)->unk_96.s) {
        case 0:
            break;

        case 1:
        case 2:
            ((S_8017450C_0 *)state)->unk_AE = 0x30;
            monster->angle_z += 0x100;
            break;

        case 3: case 4: case 5: case 6: case 7: case 8:
            ((S_8017450C_0 *)state)->unk_AE = 0x28;
            monster->angle_z += 0x200;
            break;

        case 9:
        case 10:
            ((S_8017450C_0 *)state)->unk_AE = 0x30;
            monster->angle_z += 0x100;
            break;

        case 11: case 12: case 13: case 14:
            ((S_8017450C_0 *)state)->unk_AE = 0x70;
            monster->angle_z += 0x100;
            break;

        case 15: case 16: case 17:
            ((S_8017450C_0 *)state)->unk_AE = 0x60;
            monster->angle_z += 0x200;
            break;

        case 18: case 19: case 20: case 21:
            ((S_8017450C_0 *)state)->unk_AE = 0x50;
            monster->angle_z += 0x80;
            break;

        default:
            monster->angle_z += 0x20;
        }

        if (monster->angle_z >= 0x1000) {
            monster->angle_z -= 0x1000;
        }

        {
            s16 angle;
            s32 radial_speed;

            angle = monster->angle_z;
            angle -= 0x400;
            if (angle < 0) {
                angle += 0x1000;
            }
            angle = (s16)angle;

            trig_value = rcos(angle);
            scaled_speed = ((S_8017450C_0 *)state)->unk_AE * trig_value;
            {
                s32 original_angle = angle;

                radial_speed = scaled_speed << 4;
                trig_value = rsin(original_angle);
            }

            scaled_speed = ((S_8017450C_0 *)state)->unk_AE * trig_value;
            {
                u8 *direction_entry = (u8 *)&direction_table;
                direction.x = (*(u16 *)((u8 *)direction_entry + (((((S_8017450C_3 *)actor)->unk_2A - 0x400) >> 7) & 0x1C)));
                direction_entry +=
                    ((((S_8017450C_3 *)actor)->unk_2A - 0x400) >> 7) & 0x1C;
                direction.y = (*(u16 *)((u8 *)direction_entry + (2)));

                ((S_8017450C_0 *)state)->unk_90.at00.v += scaled_speed << 4;
                motion->velocity_x = (direction.x * radial_speed) >> 4;
                motion->velocity_y = (direction.y * radial_speed) >> 4;
            }
        }

        if ((s16)(((S_8017450C_0 *)state)->unk_96.u++) < 0x2D) {
            return;
        }

        ((S_8017450C_0 *)state)->unk_96.s = 0;
        ((S_8017450C_0 *)state)->unk_9B++;
        monster->angle_z = 0x800;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        motion->x.w.i = (monster->tile_x << 6) + 0x20;
        motion->y.w.i = (monster->tile_y << 6) + 0x20;
        motion->z.w.i = ((S_8017450C_0 *)state)->unk_B6;
        motion->velocity_z = 0x280000;
        ((S_8017450C_0 *)state)->unk_A0 = 0;
        ((S_8017450C_0 *)state)->unk_90.at02.v = ((S_8017450C_0 *)state)->unk_B6 - 0x12C;
        monster->scale_x = 0x600;

        for (attempt = 0; attempt < 0xA; attempt++) {
            random_x = random_below_limit(7) - 3;
            random_y = random_below_limit(6) - 2;
            x_offset = random_x << 6;
            x = motion->x.w.i + x_offset;
            if (x >= 0x1020) {
                continue;
            }
            if (x <= 0) {
                continue;
            }

            y_offset = random_y << 6;
            y = motion->y.w.i + y_offset;
            if (y >= 0x1020) {
                continue;
            }
            if (y <= 0) {
                continue;
            }

            actor = (u16)x;
            y = (u16)y;
            if ((check_left_tile_and_center_height(actor, y, -0x200) << 16) != 0) {
                continue;
            }
            if (sample_terrain_surface_height(actor, y, -0x200) < 0x200) {
                continue;
            }

            random_x = 0xB;
            attempt = random_x;
            *(u16 *)&motion->x.w.i += x_offset;
            *(u16 *)&motion->y.w.i += y_offset;
        }

        if (random_x == 0xB) {
            return;
        }

        ((S_8017450C_0 *)state)->unk_9B = 4;
        motion->velocity_z = 0;
        monster->flags |= 0x80;
        return;

    case 3:
        if ((s16)(((S_8017450C_0 *)state)->unk_96.u++) < 0x1E) {
            return;
        }
        ((S_8017450C_0 *)state)->unk_96.s = 0;
        ((S_8017450C_0 *)state)->unk_9B++;
        return;

    case 4:
        if ((s16)(((S_8017450C_0 *)state)->unk_96.u++) < 0xA) {
            return;
        }
        if (((S_8017450C_3 *)actor)->unk_14 & 0x4000) {
            if (!(((S_8017450C_3 *)actor)->unk_14 & 0x20000000)) {
                announce_familiar_defeat((void *)actor);
            }
        }
        break;
    default:
        return;
    }

    {
        u32 tracked_actor;
        s32 tile_flags;

        tracked_actor = ((u32)g_dungeon_status.pending_display_owner);
        if (tracked_actor == actor - 0x20) {
            g_dungeon_status.pending_display_owner = tracked_actor & 0x7FFFFFFF;
        }
        distribute_experience_and_report_gains((void *)actor);
        detach_record_and_update_slot_state((void *)actor);
        tile_x = monster->tile_x;
        tile_y = monster->tile_y;
        if (((S_8017450C_3 *)actor)->unk_1C & 0x2000) {
            tile_flags = 0x300;
        } else {
            tile_flags = 0x3000;
        }
        update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_flags);
        unlink_entity_node((void *)actor);
        (*(u16 *)((u8 *)actor + (-2))) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
