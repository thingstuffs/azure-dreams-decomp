#include "modules/dungeon_ovl_1930844.h"

void func_80025954(void *state, void *motion, void *appearance) {
    ovl_1930844_81912154_LocalStack stack;
    s16 floor_height;
    s32 phase;
    s32 x_distance;
    s32 y_distance;
    s32 z_distance;
    s32 z_base;
    s32 z_base2;
    s32 z_table;
    s32 z_table2;
    s32 z_velocity;
    s32 next_state;
    s32 travel_frames;
    s32 direction;
    s32 step_direction;
    s32 step_count;
    u32 origin_z;
    s16 motion_value;
    s32 axis_delta;
    s32 x_scaled;
    s32 y_velocity;
    s16 end_tile_x;
    s16 tile_x;
    s16 tile_y;
    s32 model;
    void *destination;
    void *owner_links;
    void *owner;
    void *target;
    void *origin;
    void *entity;
    void *grid_source;
    s16 *y_lookup_first;
    s16 source_coord;
    s16 *step_table;
    s16 *table_origin;
    s32 height;
    u16 end_tile_y;

    phase = ((Rec_func_80024170_arg0 *)state)->unk_0A;
    owner = ((Rec_func_80024170_arg0 *)state)->unk_00;
    ((Rec_func_80024170_arg0 *)state)->unk_10 = (u16) (((Rec_func_80024170_arg0 *)state)->unk_10 + 1);
    switch ((u32)phase) {
    case 0:
        ((Rec_func_80024170_arg0 *)state)->unk_10 = 0U;
        ((Rec_func_80024170_arg0 *)state)->unk_0A = (s16) ((u16) ((Rec_func_80024170_arg0 *)state)->unk_0A + 1);
        ((Rec_func_80024170_arg0 *)state)->unk_0E = (u16) (((u16) ((ovl_1930844_81912154_S_80025954_1 *)owner)->unk_2A >> 9) & 7);
        ((ovl_1930844_81912154_S_80025954_2 *)appearance)->unk_0C = 0x808080;
    case 1:
        owner_links = owner - 0x20;
        model = (s32)(((ovl_1930844_81912154_S_80025954_3 *)owner_links)->unk_0C);
        if (func_8003DE58(((ovl_1930844_81912154_S_80025954_4 *)((void *)model))->unk_08, (void *)model, stack.distance, 0) == 0
            && !(((ovl_1930844_81912154_S_80025954_14 *)(((ovl_1930844_81912154_S_80025954_3 *)owner_links)->unk_0C))->unk_14 & 0x8000)) {
            break;
        }
        origin = ((ovl_1930844_81912154_S_80025954_3 *)owner_links)->unk_08;
        ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_00.at02.v = (u16) ((ovl_1930844_81912154_S_80025954_6 *)origin)->unk_02;
        ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_04.at02.v = (u16) ((ovl_1930844_81912154_S_80025954_6 *)origin)->unk_06;
        origin_z = ((ovl_1930844_81912154_S_80025954_6 *)origin)->unk_0A;
        ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_08.at02.v = origin_z;
        if (!(((ovl_1930844_81912154_S_80025954_14 *)(((ovl_1930844_81912154_S_80025954_3 *)owner_links)->unk_0C))->unk_14 & 0x8000)) {
            ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_00.at02.v = (u16) (((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_00.at02.v
                + stack.distance[0]);
            ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_04.at02.v = (u16) (((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_04.at02.v
                + stack.distance[1]);
            ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_08.at02.v = (u16) (((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_08.at02.v
                + stack.distance[2]);
        } else {
            ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_08.at02.v = origin_z - 0x40;
        }
        if (!(*((Rec_func_80024170_arg0 *)state)->unk_04 & 0x80)) {
            break;
        }
        target = ((ovl_1930844_81912154_S_80025954_1 *)owner)->unk_60;
        if (target != NULL) {
            step_count = 1;
            destination = ((ovl_1930844_81912154_S_80025954_7_pre *)target)[-1].unk_00;
            x_distance = ((ovl_1930844_81912154_S_80025954_8 *)destination)->unk_00.at02.v - ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_00.at02u.v;
            x_distance = abs(x_distance);
            stack.distance[0] = x_distance;
            y_distance = ((ovl_1930844_81912154_S_80025954_8 *)destination)->unk_04.at02.v - ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_04.at02u.v;
            y_distance = abs(y_distance);
            stack.distance[1] = y_distance;
            entity = ((ovl_1930844_81912154_S_80025954_1 *)owner)->unk_60;
            z_table = D_800DDC40[((ovl_1930844_81912154_S_80025954_9 *)entity)->unk_13] << 0x10;
            z_distance = ((ovl_1930844_81912154_S_80025954_8 *)destination)->unk_08.at02.v - z_table;
            z_base = ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_08.at02u.v + 0x300000;
            z_distance -= z_base;
            stack.distance[2] = abs(z_distance);
            ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = x_distance;
            do {
                if ((s16) stack.distance[step_count] > ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16) {
                    ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = (s16) stack.distance[step_count];
                }
                step_count += 1;
            } while (step_count < 3);
            travel_frames = (s32) ((u16) ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 << 0x10) >> 0x14;
            ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = (s16) travel_frames;
            if (travel_frames == 0) {
                ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = 1;
            }
            ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_0C = (((ovl_1930844_81912154_S_80025954_8 *)destination)->unk_00.at00.v
                - ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_00.at00.v) / ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16;
            ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_10 = (((ovl_1930844_81912154_S_80025954_8 *)destination)->unk_04.at00.v
                - ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_04.at00.v) / ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16;
            entity = ((ovl_1930844_81912154_S_80025954_1 *)owner)->unk_60;
            z_table2 = D_800DDC40[((ovl_1930844_81912154_S_80025954_9 *)entity)->unk_13] << 0x10;
            z_velocity = ((ovl_1930844_81912154_S_80025954_8 *)destination)->unk_08.at00.v - z_table2;
            z_base2 = ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_08.at00.v + 0x300000;
            z_velocity -= z_base2;
            ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_14 = z_velocity / ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16;
            func_80024170(state, motion);
            next_state = (u16) ((Rec_func_80024170_arg0 *)state)->unk_0A + 1;
        } else {
            table_origin = dirStepX;
            step_count = 0;
            grid_source = ((ovl_1930844_81912154_S_80025954_3 *)owner_links)->unk_0C;
            tile_x = ((ovl_1930844_81912154_S_80025954_9 *)grid_source)->unk_24;
            tile_y = ((ovl_1930844_81912154_S_80025954_9 *)grid_source)->unk_25;
            end_tile_x = tile_x;
            end_tile_y = tile_y;
            do {
                if ((func_800A44E0(((s16) tile_x << 6) & 0xFFC0, ((s16) tile_y << 6) & 0xFFC0,
                    ((ovl_1930844_81912154_S_80025954_1 *)owner)->unk_88, (s16) (((Rec_func_80024170_arg0 *)state)->unk_0E << 9)) << 0x10)
                    != 0) {
                    goto grid_hit;
                }
                {
                    direction = (s16) ((Rec_func_80024170_arg0 *)state)->unk_0E;
                    height = (u16) ((ovl_1930844_81912154_S_80025954_1 *)owner)->unk_88;
                    entity = (void *)&dirStepX[direction];
                }
                height = (s16) (height - 0x20);
                y_lookup_first = &dirStepY[direction];
                floor_height = func_800BCB04(((((s16) tile_x + *((s16 *)entity)) << 6) + 0x20) & 0xFFE0,
                    ((((s16) tile_y + *y_lookup_first) << 6) + 0x20) & 0xFFE0, height);
                if (floor_height >= 0x201) {
                    break;
                }
                if ((s16) (floor_height - (u16) ((ovl_1930844_81912154_S_80025954_1 *)owner)->unk_88) < -0x3F) {
                    break;
                }
                step_direction = (s16) ((Rec_func_80024170_arg0 *)state)->unk_0E;
                step_count += 1;
                source_coord = tile_x + (u16) dirStepX[step_direction];
                tile_x = source_coord;
                motion_value = tile_y + (u16) dirStepY[step_direction];
                tile_y = motion_value;
                end_tile_y = motion_value;
                end_tile_x = source_coord;
            } while (step_count < 8);
            destination = stack.motion;
            x_scaled = (u32) end_tile_x << 0x10;
            step_table = table_origin;
            x_scaled >>= 0xA;
            goto grid_coords;
        grid_hit:
            destination = stack.motion;
            x_scaled = (u32) end_tile_x << 0x10;
            step_table = table_origin;
            x_scaled >>= 0xA;
        grid_coords:
            axis_delta = x_scaled;
            direction = (step_table[(s16) ((Rec_func_80024170_arg0 *)state)->unk_0E] + 1) << 5;
            axis_delta += direction;
            ((ovl_1930844_81912154_S_80025954_8 *)destination)->unk_00.at02.v = axis_delta;
            axis_delta = (u32) axis_delta << 0x10;
            model = ((s16) end_tile_y << 6) + ((dirStepY[(s16) ((Rec_func_80024170_arg0 *)state)->unk_0E] + 1) << 5);
            ((ovl_1930844_81912154_S_80025954_8 *)destination)->unk_04.at02.v = model;
            axis_delta >>= 0x10;
            ((ovl_1930844_81912154_S_80025954_8 *)destination)->unk_08.at02u.v = ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_08.at02.v;
            model = (u32) model << 0x10;
            axis_delta -= ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_00.at02u.v;
            axis_delta = __builtin_abs(axis_delta);
            stack.distance[0] = axis_delta;
            model >>= 0x10;
            model -= ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_04.at02u.v;
            model = __builtin_abs(model);
            stack.distance[1] = model;
            ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = axis_delta;
            if ((s16) stack.distance[1] > (s16) axis_delta) {
                ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = (s16) (u16) stack.distance[1];
            }
            travel_frames = (s32) ((u16) ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 << 0x10) >> 0x14;
            ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = (s16) travel_frames;
            if (travel_frames == 0) {
                ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = 1;
            }
            ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_0C = (((ovl_1930844_81912154_S_80025954_12 *)(stack.motion))->unk_00
                - ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_00.at00.v) / ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16;
            y_velocity = (((ovl_1930844_81912154_S_80025954_8 *)destination)->unk_04.at00.v
                - ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_04.at00.v) / ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16;
            ((ovl_1930844_81912154_S_80025954_11 *)motion)->unk_14 = 0;
            ((ovl_1930844_81912154_S_80025954_11 *)motion)->unk_10 = y_velocity;
            func_80024170(state, motion);
            next_state = 6;
        }
        goto set_state;
    case 2:
        ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_00.at00.v = (s32) (((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_00.at00.v
            + ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_0C);
        ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_04.at00.v = (s32) (((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_04.at00.v
            + ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_10);
        ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_08.at00.v = (s32) (((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_08.at00.v
            + ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_14);
        if ((s16) ((Rec_func_80024170_arg0 *)state)->unk_10 < ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16) {
            break;
        }
        func_80025874(state, motion, ((ovl_1930844_81912154_S_80025954_15 *)(((ovl_1930844_81912154_S_80025954_1 *)owner)->unk_60))->unk_88);
        func_800A56E0(0x300);
        ((Rec_func_80024170_arg0 *)state)->unk_10 = 0U;
        ((Rec_func_80024170_arg0 *)state)->unk_0A = (s16) ((u16) ((Rec_func_80024170_arg0 *)state)->unk_0A + 1);
        break;
    case 3:
        if ((s16) ((Rec_func_80024170_arg0 *)state)->unk_10 >= 8) {
            ((Rec_func_80024170_arg0 *)state)->unk_10 = 0U;
            ((Rec_func_80024170_arg0 *)state)->unk_0A = (s16) ((u16) ((Rec_func_80024170_arg0 *)state)->unk_0A + 1);
            break;
        }
        ((Rec_func_80024170_arg0 *)state)->unk_14 = 0;
        return;
    case 4:
        if ((s16) ((Rec_func_80024170_arg0 *)state)->unk_10 < 0x44) {
            break;
        }
        func_8009CE1C(((ovl_1930844_81912154_S_80025954_1 *)owner)->unk_60, 0x18, ((Rec_func_80024170_arg0 *)state)->unk_09, 1,
            (s32) (s16) (((Rec_func_80024170_arg0 *)state)->unk_0E << 9), owner, 1);
        ((Rec_func_80024170_arg0 *)state)->unk_10 = 0U;
        ((Rec_func_80024170_arg0 *)state)->unk_0A = (s16) ((u16) ((Rec_func_80024170_arg0 *)state)->unk_0A + 1);
        break;
    case 5:
        if (((Rec_func_80024170_arg0 *)state)->unk_14 == 0) {
            dungeonStatus.unk_0C = 0;
            (*(u16 *)((u8 *)state + -2)) = (u16) ((*(u16 *)((u8 *)state + -2)) | 0x8000);
            (*(s32 *)&objectFlagBlock.flags) = (s32) (objectFlagBlock.flags | 0x8000);
        }
        break;
    case 6:
        ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_00.at00.v = (s32) (((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_00.at00.v
            + ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_0C);
        ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_04.at00.v = (s32) (((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_04.at00.v
            + ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_10);
        ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_08.at00.v = (s32) (((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_08.at00.v
            + ((ovl_1930844_81912154_S_80025954_5 *)motion)->unk_14);
        if ((s16) ((Rec_func_80024170_arg0 *)state)->unk_10 < ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16) {
            break;
        }
        next_state = 5;
    set_state:
        ((Rec_func_80024170_arg0 *)state)->unk_0A = next_state;
        ((Rec_func_80024170_arg0 *)state)->unk_10 = 0U;
    }
    ((Rec_func_80024170_arg0 *)state)->unk_14 = 0;
    return;
}
