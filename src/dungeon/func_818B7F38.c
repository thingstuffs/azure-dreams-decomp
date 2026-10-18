#include "modules/dungeon_ovl_18d6800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
extern int abs(int);

   /* arg0 in advance_movement_toward_reachable_tile */



   /* arg2 in advance_movement_toward_reachable_tile */





   /* arg1 in advance_movement_toward_reachable_tile */




















/* cfail-repair: tf7-phase1-cache-v3 */



/* Advance movement toward a target or a reachable tile, then finish the timed action. */
void advance_movement_toward_reachable_tile(void *state, void *motion_in, void *render) {
    B28_818B7F38_LocalFrame frame;
    u16 *target_delta_cursor;
    u16 *path_delta_cursor;
    u16 base_z;
    s16 floor_z;
    s32 phase;
    s32 target_dx;
    s16 next_phase;
    s32 target_ticks;
    s32 path_ticks;
    s32 world_y;
    s32 world_x;
    s16 *step_y;
    s32 probe_z;
    s32 current_z;
    s32 index;
    s32 target_dy;
    s32 target_dz;
    u16 source_z;
    u16 last_tile_x;
    u16 saved_y;
    u16 tile_x;
    u16 tile_y;
    s16 grid_x;
    s16 grid_y;
    void *source_data;
    void *destination;
    void *source_header;
    void *owner;
    void *target;
    void *source_position;
    void *tile_data;

    phase = (s32) ((B28_818B7F38_S_80025738_0 *)state)->unk_0A;
    owner = ((B28_818B7F38_S_80025738_0 *)state)->unk_00;
    ((B28_818B7F38_S_80025738_0 *)state)->unk_10 = (u16) (((B28_818B7F38_S_80025738_0 *)state)->unk_10 + 1);
    switch (phase) {
    case 0:
        ((B28_818B7F38_S_80025738_0 *)state)->unk_10 = 0U;
        ((B28_818B7F38_S_80025738_0 *)state)->unk_0A = (s16) ((u16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0A + 1);
        ((B28_818B7F38_S_80025738_0 *)state)->unk_0E = (u16) (((u16) ((B28_818B7F38_S_80025738_1 *)owner)->unk_2A >> 9) & 7);
        ((B28_818B7F38_S_80025738_2 *)render)->unk_0C = 0x808080;
    case 1:
        source_header = owner - 0x20;
        source_data = ((B28_818B7F38_S_80025738_3 *)source_header)->unk_0C;
        if (resolve_record_orientation_or_fallback(((B28_818B7F38_S_80025738_4 *)source_data)->unk_08, source_data, frame.delta, 0) != 0) {
            source_position = ((B28_818B7F38_S_80025738_3 *)source_header)->unk_08;
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at02.v = (u16) ((B28_818B7F38_S_80025738_6 *)source_position)->unk_02;
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at02.v = (u16) ((B28_818B7F38_S_80025738_6 *)source_position)->unk_06;
        } else {
            if (!(((B28_818B7F38_S_80025738_13 *)(((B28_818B7F38_S_80025738_3 *)source_header)->unk_0C))->unk_14 & 0x8000)) {
                break;
            }
            source_position = ((B28_818B7F38_S_80025738_3 *)source_header)->unk_08;
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at02.v = (u16) ((B28_818B7F38_S_80025738_6 *)source_position)->unk_02;
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at02.v = (u16) ((B28_818B7F38_S_80025738_6 *)source_position)->unk_06;
        }
        source_z = ((B28_818B7F38_S_80025738_6 *)source_position)->unk_0A;
        ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at02.v = source_z;
        if (!(((B28_818B7F38_S_80025738_13 *)(((B28_818B7F38_S_80025738_3 *)source_header)->unk_0C))->unk_14 & 0x8000)) {
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at02.v = (u16) (((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at02.v
                + frame.delta[0]);
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at02.v = (u16) (((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at02.v
                + frame.delta[1]);
            base_z = ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at02.v;
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at02.v = base_z + frame.delta[2];
            if (!(*((B28_818B7F38_S_80025738_0 *)state)->unk_04 & 0x80)) {
                break;
            }
            target = ((B28_818B7F38_S_80025738_1 *)owner)->unk_60;
            index = 1;
        } else {
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at02.v = source_z - 0x40;
            if (!(*((B28_818B7F38_S_80025738_0 *)state)->unk_04 & 0x80)) {
                break;
            }
            target = ((B28_818B7F38_S_80025738_1 *)owner)->unk_60;
            index = 1;
        }
        if (target != NULL) {
            ((B28_818B7F38_S_80025738_0 *)state)->unk_18 = target;
            destination = ((B28_818B7F38_S_80025738_14_pre *)(((B28_818B7F38_S_80025738_1 *)owner)->unk_60))[-1].unk_00;
            target_dx = ((B28_818B7F38_S_80025738_7 *)destination)->unk_00.at02.v;
            target_dx -= ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at02u.v;
            if (target_dx < 0) {
                target_dx = 0 - target_dx;
            }
            frame.delta[0] = (u16) target_dx;
            target_dy = ((B28_818B7F38_S_80025738_7 *)destination)->unk_04.at02.v;
            target_dy -= ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at02u.v;
            target_dy = abs(target_dy);
            frame.delta[1] = (u16) target_dy;
            target = ((B28_818B7F38_S_80025738_1 *)owner)->unk_60;
            current_z = ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at02u.v;
            target_dz = ((B28_818B7F38_S_80025738_8 *)target)->unk_88;
            target_dz -= current_z;
            target_delta_cursor = (u16 *)((u8 *)&frame.out_x + 2);
            target_dz = abs(target_dz);
            frame.delta[2] = (u16) target_dz;
            ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = target_dx;
            do {
                if (((B28_818B7F38_S_80025738_9 *)target_delta_cursor)->unk_18.s > ((B28_818B7F38_S_80025738_0 *)state)->unk_12) {
                    ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = ((B28_818B7F38_S_80025738_9 *)target_delta_cursor)->unk_18.u;
                }
                index += 1;
                target_delta_cursor += 1;
            } while (index < 3);
            target_ticks = (s32) ((u16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12 << 0x10) >> 0x14;
            ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = (s16) target_ticks;
            if (target_ticks == 0) {
                ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = 1;
            }
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_0C = (s32) ((s32) (((B28_818B7F38_S_80025738_7 *)destination)->unk_00.at00.v
                - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at00.v) / (s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12);
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_10 = (s32) ((s32) (((B28_818B7F38_S_80025738_7 *)destination)->unk_04.at00.v
                - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at00.v) / (s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12);
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_14 =
                (s32) ((s32) ((((B28_818B7F38_S_80025738_14 *)(((B28_818B7F38_S_80025738_1 *)owner)->unk_60))->unk_88 << 0x10)
                - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at00.v) / (s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12);
            spawn_owner_random_variant_effect(state, motion_in);
            next_phase = (u16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0A + 1;
        } else {
            index = 0;
            tile_data = ((B28_818B7F38_S_80025738_3 *)source_header)->unk_0C;
            tile_x = ((B28_818B7F38_S_80025738_10 *)tile_data)->unk_24;
            tile_y = ((B28_818B7F38_S_80025738_10 *)tile_data)->unk_25;
            last_tile_x = tile_x;
            saved_y = tile_y;
            while (index < 8) {
                grid_x = (s16)tile_x;
                grid_y = (s16)tile_y;
                if ((s16)check_layer_offset_height((grid_x << 6) & 0xFFC0, (grid_y << 6) & 0xFFC0, ((B28_818B7F38_S_80025738_1 *)owner)->unk_88,
                    (s16) (((B28_818B7F38_S_80025738_0 *)state)->unk_0E << 9)) != 0) {
                    break;
                }
                source_position = &dir_step_x[(s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0E];
                probe_z = (u16) ((B28_818B7F38_S_80025738_1 *)owner)->unk_88;
                probe_z -= 0x20;
                probe_z = (u32)probe_z << 16;
                probe_z >>= 16;
                step_y = &dir_step_y[(s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0E];
                floor_z = sample_terrain_surface_height(((grid_x + *(s16 *)source_position) << 6) + 0x20 & 0xFFE0,
                    ((grid_y + *step_y) << 6) + 0x20 & 0xFFE0, probe_z);
                if (floor_z >= 0x201 || (s16) (floor_z - (u16) ((B28_818B7F38_S_80025738_1 *)owner)->unk_88) < -0x3F) {
                    break;
                }
                index += 1;
                tile_x += dir_step_x[(s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0E];
                tile_y += dir_step_y[(s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0E];
                saved_y = tile_y;
                last_tile_x = tile_x;
            }
            destination = &frame.out_x;
            index = 1;
            path_delta_cursor = (u16 *)((u8 *)&frame.out_x + 2);
            world_x = ((last_tile_x << 16) >> 10) + ((dir_step_x[(s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0E] + 1) << 5);
            ((B28_818B7F38_S_80025738_7 *)destination)->unk_00.at02.v = world_x;
            world_y = ((saved_y << 16) >> 10) + ((dir_step_y[(s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0E] + 1) << 5);
            ((B28_818B7F38_S_80025738_7 *)destination)->unk_04.at02.v = world_y;
            ((B28_818B7F38_S_80025738_7 *)destination)->unk_08.at02.v = ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at02u.v + 0x20;
            frame.delta[0] = abs(((B28_818B7F38_S_80025738_7 *)destination)->unk_00.at02.v - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at02u.v);
            frame.delta[1] = abs(((B28_818B7F38_S_80025738_7 *)destination)->unk_04.at02.v - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at02u.v);
            frame.delta[2] = abs(((B28_818B7F38_S_80025738_7 *)destination)->unk_08.at02.v - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at02u.v);
            ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = frame.delta[0];
            do {
                if (((B28_818B7F38_S_80025738_11 *)path_delta_cursor)->unk_18.s > ((B28_818B7F38_S_80025738_0 *)state)->unk_12) {
                    ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = ((B28_818B7F38_S_80025738_11 *)path_delta_cursor)->unk_18.u;
                }
                index += 1;
                path_delta_cursor += 1;
            } while (index < 3);
            path_ticks = (s32) ((u16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12 << 0x10) >> 0x14;
            ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = (s16) path_ticks;
            if (path_ticks == 0) {
                ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = 1;
            }
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_0C = (s32) ((s32) (((B28_818B7F38_S_80025738_7 *)destination)->unk_00.at00.v
                - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at00.v) / (s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12);
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_10 = (s32) ((s32) (((B28_818B7F38_S_80025738_7 *)destination)->unk_04.at00.v
                - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at00.v) / (s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12);
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_14 = (s32) ((s32) (((B28_818B7F38_S_80025738_7 *)destination)->unk_08.at00.v
                - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at00.v) / (s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12);
            spawn_owned_random_spin_effect(state, motion_in);
            next_phase = 6;
        }
        ((B28_818B7F38_S_80025738_0 *)state)->unk_0A = next_phase;
        ((B28_818B7F38_S_80025738_0 *)state)->unk_10 = 0U;
        break;
    case 2:
        ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at00.v += ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_0C;
        ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at00.v += ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_10;
        ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at00.v += ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_14;
        if ((s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_10 < ((B28_818B7F38_S_80025738_0 *)state)->unk_12) {
            break;
        }
        play_sound_if_enabled(0x300);
        goto advance_phase;
    case 3:
        if ((s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_10 >= 0x10) {
            ((B28_818B7F38_S_80025738_0 *)state)->unk_10 = 0U;
            ((B28_818B7F38_S_80025738_0 *)state)->unk_0A = (s16) ((u16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0A + 1);
        }
        break;
    case 4:
        if ((s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_10 < 0x30) {
            break;
        }
        interpolate_view_parameters(((B28_818B7F38_S_80025738_1 *)owner)->unk_60, ((B28_818B7F38_S_80025738_0 *)state)->unk_09, owner);
advance_phase:
        ((B28_818B7F38_S_80025738_0 *)state)->unk_10 = 0U;
        ((B28_818B7F38_S_80025738_0 *)state)->unk_0A = (s16) ((u16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0A + 1);
        break;
    case 5:
        if (((B28_818B7F38_S_80025738_0 *)state)->unk_14 != 0) {
            break;
        }
        g_dungeon_status.unk_0C = 0;
        (*(u16 *)((u8 *)state + -2)) = (u16) ((*(u16 *)((u8 *)state + -2)) | 0x8000);
        (*(s32 *)&object_flag_block.flags) = (s32) (object_flag_block.flags | 0x8000);
        break;
    case 6:
        ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at00.v = (s32) (((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at00.v
            + ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_0C);
        ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at00.v = (s32) (((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at00.v
            + ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_10);
        ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at00.v = (s32) (((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at00.v
            + ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_14);
        if ((s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_10 < ((B28_818B7F38_S_80025738_0 *)state)->unk_12) {
            break;
        }
        next_phase = 5;
        ((B28_818B7F38_S_80025738_0 *)state)->unk_0A = next_phase;
        ((B28_818B7F38_S_80025738_0 *)state)->unk_10 = 0U;
    }
    ((B28_818B7F38_S_80025738_0 *)state)->unk_14 = 0;
    return;
}
