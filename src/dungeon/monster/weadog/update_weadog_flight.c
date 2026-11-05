#include "shared/object_flags.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/object_links.h"
#include "dungeon/actor/effect.h"
#include "dungeon/monster/weadog.h"

typedef struct GridData {
    GridPoint point[8];
} GridData __attribute__((packed));

typedef struct FlagBlock {
    s32 value;
    s32 pad[2];
} FlagBlock;

typedef struct S_func_80EDF000_1 {
    union {
        s32 s32;
        struct {
            u8 pad_00[2];
            union { s16 s16; u16 u16; } unk_02;
        } parts;
    } unk_00;
    union {
        s32 s32;
        struct {
            u8 pad_04[2];
            union { s16 s16; u16 u16; } unk_06;
        } parts;
    } unk_04;
    union {
        s32 s32;
        struct {
            s16 unk_08;
            s16 unk_0A;
        } parts;
    } unk_08;
    u8 pad_0C[2];
    s16 unk_0E;
    u8 pad_10[2];
    s16 unk_12;
    u8 pad_14[2];
    s16 unk_16;
} S_func_80EDF000_1;

typedef struct S_func_80EDF000_2 {
    u8 pad_00[6];
    s16 unk_06;
    void *unk_08;
    u8 pad_0C[8];
    u16 unk_14;
    u8 pad_16[6];
    u16 unk_1C;
    u16 unk_1E;
} S_func_80EDF000_2;




s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
extern s16 sample_terrain_surface_height(s32, s32, s16);

extern u8 weadog_slot_g_direction_steps[];
extern FlagBlock D_800814A0;

void advance_item_flight_to_floor(WeadogFlightBody *motion, S_func_80EDF000_1 *position, S_func_80EDF000_2 *render);

/* Advance motion, resolve tile collisions, and settle at the landing position. */
/* Animates a moving item with directions from D_80170808; places it on the floor or shrinks its falling
 * sprite. */
void advance_item_flight_to_floor(WeadogFlightBody *motion, S_func_80EDF000_1 *position, S_func_80EDF000_2 *render)
{
    s32 first_pass;
    s8 command[4];
    GridPoint tile_steps[8];
    GridPoint *step_table;
    s32 fall_height;
    s32 move_height;
    u16 travel_frames;
    u16 scale;
    u32 tile_distance;
    s32 interp_goal;


    __builtin_memcpy(tile_steps, weadog_slot_g_direction_steps, 32);

interpolate:
    if (motion->phase == 1) {
        if (motion->phase_timer == 0) {
            motion->phase_timer = (s16)((u16)motion->phase_timer + 1);
            {
                s32 abs_x;
                s32 abs_y;
                s32 map_y;

                abs_x = position->unk_0E;
                abs_y = motion->spawner_tile_x;
                map_y = motion->spawner_tile_y;
                abs_x -= abs_y;
                abs_y = position->unk_12;
                if (abs_x < 0)
                    abs_x = -abs_x;
                abs_y -= map_y;
                if (abs_y < 0)
                    abs_y = -abs_y;
                tile_distance = abs_x + abs_y;
            }
            switch (tile_distance) {
            case 0:
                travel_frames = 4;
                break;
            case 1:
                travel_frames = 8;
                break;
            case 2:
                travel_frames = 12;
                break;
            case 3:
                travel_frames = 14;
                break;
            case 4:
            default:
                travel_frames = 16;
                break;
            }
            motion->travel_frames = travel_frames;
        }
        {
            u32 countdown_raw;
            s32 countdown;
            s32 shifted_countdown;

            countdown_raw = (u16)motion->travel_frames - 1;
            motion->travel_frames = countdown_raw;
            countdown_raw <<= 16;
            shifted_countdown = (s32)countdown_raw;
            countdown = shifted_countdown >> 16;
            if (countdown != 0) {
                s32 interp_current;

                interp_goal = position->unk_0E;
                interp_current = position->unk_00.parts.unk_02.s16;
                interp_goal *= 64;
                interp_current -= 32;
                interp_goal -= interp_current;
                interp_goal /= countdown;
                position->unk_00.parts.unk_02.s16 += interp_goal;

                {
                    s32 goal = position->unk_12;
                    s32 current = position->unk_04.parts.unk_06.s16;
                    s32 ticks = motion->travel_frames;
                    s32 delta;
                    s32 scaled = goal;
                    scaled *= 64;
                    delta = current - 32;
                    interp_goal = scaled - delta;
                    interp_goal /= ticks;
                }
                interp_current = position->unk_04.parts.unk_06.u16;
                countdown = position->unk_08.parts.unk_0A;
                interp_current += interp_goal;

                interp_goal = position->unk_16;
                position->unk_04.parts.unk_06.s16 = interp_current;
                interp_goal -= countdown;
                interp_goal /= (s16)motion->travel_frames;
                position->unk_08.parts.unk_0A += interp_goal;
            }
        }
        if ((s16)motion->travel_frames <= 0) {
            command[0] = 6;
            command[1] = 12;
            command[2] = 0;
            command[3] = 0;
            place_item_at_valid_floor_position(position->unk_0E, position->unk_12,
                          position->unk_16, render->unk_08, command);
            ((ActorRecord *)motion->owner)->unk_A4.halves.low.s = 0;
            ((ObjectRetirementFlags *)((u8 *)motion - 2))->flags |= 0x8000;
            D_800814A0.value |= OBJECT_REMOVE_PENDING;
            return;
        }
        if (render->unk_14 & 0x8000)
            goto interpolate;
    }
fall:
    if (motion->phase == 2) {
        position->unk_08.s32 += motion->velocity_z;
        motion->velocity_z += motion->gravity;
        scale = render->unk_1E - 0xC8;
        render->unk_1E = scale;
        render->unk_1C = scale;
        fall_height = position->unk_08.parts.unk_0A;
        if (sample_terrain_surface_height((motion->spawner_tile_x << 6) & 0xFFC0,
                          (motion->spawner_tile_y << 6) & 0xFFC0,
                          (s16)((u16)position->unk_08.parts.unk_0A - 0x20)) - 7 <
            fall_height) {
            position->unk_08.parts.unk_0A = sample_terrain_surface_height(
                (motion->spawner_tile_x << 6) & 0xFFC0,
                (motion->spawner_tile_y << 6) & 0xFFC0,
                (s16)((u16)position->unk_08.parts.unk_0A - 0x20));
            position->unk_08.parts.unk_08 = 0;
            ((ActorRecord *)motion->owner)->unk_A4.halves.low.s = 0;
            ((ObjectRetirementFlags *)((u8 *)motion - 2))->flags |= 0x8000;
            D_800814A0.value |= OBJECT_REMOVE_PENDING;
            return;
        }
        if (render->unk_14 & 0x8000)
            goto fall;
    }
    for (first_pass = 1; first_pass || (render->unk_14 & 0x8000); first_pass = 0) {
        step_table = tile_steps;
        if (motion->phase != 0)
            return;
        position->unk_00.s32 += motion->velocity_x;
        motion->velocity_x += motion->acceleration_x;
        position->unk_04.s32 += motion->velocity_y;
        {
            s32 coord;
            s32 world_coord;
            GridPoint *step;

            coord = motion->velocity_y;
            world_coord = motion->acceleration_y;
            interp_goal = motion->direction;
            interp_goal <<= 2;
            step = (GridPoint *)((u8 *)step_table + interp_goal);
            interp_goal = motion->spawner_tile_x;
            coord += world_coord;
            motion->velocity_y = coord;

            coord = step->unk_00.x;
            world_coord = position->unk_00.parts.unk_02.s16;
            interp_goal += coord;
            if (world_coord < 0)
                world_coord += 0x3F;
            coord = world_coord >> 6;
            if (interp_goal == coord) {
                coord = step->unk_02.unk_02;
                world_coord = position->unk_04.parts.unk_06.s16;
                interp_goal = motion->spawner_tile_y;
                coord = (s16)coord;
                interp_goal += coord;
                if (world_coord < 0)
                    world_coord += 0x3F;
                coord = world_coord >> 6;
                if (interp_goal == coord) {
                    if ((check_left_tile_and_center_height(position->unk_00.parts.unk_02.u16, position->unk_04.parts.unk_06.u16,
                        position->unk_08.parts.unk_0A) << 16) != 0 ||
                        sample_terrain_surface_height(position->unk_00.parts.unk_02.u16, position->unk_04.parts.unk_06.u16,
                                          position->unk_08.parts.unk_0A) >= 0x200) {
                        position->unk_00.s32 -= motion->velocity_x;
                        motion->velocity_x = 0;
                        motion->acceleration_x = 0;
                        position->unk_04.s32 -= motion->velocity_y;
                        motion->velocity_y = 0;
                        motion->acceleration_y = 0;
                    } else {
                        motion->spawner_tile_x +=
                            ((GridPoint *)((u8 *)step_table + (motion->direction << 2)))->unk_00.unk_00;
                        motion->spawner_tile_y +=
                            ((GridPoint *)((u8 *)step_table + (motion->direction << 2)))->unk_02.unk_02_u8;
                    }
                    render->unk_06 = 0;
                }
            }
        }
        position->unk_08.s32 += motion->velocity_z;
        motion->velocity_z += motion->gravity;
        move_height = position->unk_08.parts.unk_0A;
        if (sample_terrain_surface_height((motion->spawner_tile_x << 6) & 0xFFC0, (motion->spawner_tile_y << 6) & 0xFFC0,
            (s16)((u16)position->unk_08.parts.unk_0A - 0x20)) - 0x10 < move_height) {
            position->unk_08.parts.unk_0A = sample_terrain_surface_height(
                (motion->spawner_tile_x << 6) & 0xFFC0,
                (motion->spawner_tile_y << 6) & 0xFFC0,
                (s16)((u16)position->unk_08.parts.unk_0A - 0x20));
            position->unk_08.parts.unk_08 = 0;
            motion->acceleration_y = 0;
            motion->velocity_y = 0;
            motion->acceleration_x = 0;
            motion->velocity_x = 0;
            motion->phase = (s16)((u16)motion->phase + 1);
            if ((find_valid_floor_item_position(motion->spawner_tile_x, motion->spawner_tile_y,
                               (s16)((u16)position->unk_08.parts.unk_0A - 0x20),
                               &position->unk_0E, &position->unk_12,
                               &position->unk_16) << 16) != 0)
            return;
            motion->phase = 2;
            motion->velocity_z = (s32)0xFFF80000;
            return;
        }
    }
    return;
}

