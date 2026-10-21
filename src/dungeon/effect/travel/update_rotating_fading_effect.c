#include "dungeon/effect/travel/update_rotating_fading_effect.h"
#include "shared/sprite_frame_state.h"
void (*const dungeon_ovl_18ca83c_entry)(void) = (void (*)(void))advance_target_travel_effect;

void func_8002403C(void *target, s32 amount_input, void *owner) {
    s32 base_amount;
    register s32 adjusted_amount;

    if (try_trigger_target_record_effect(target, 2) == 0) {
        base_amount = get_random_scaled_value(amount_input & 0xFF) + 16;
        adjusted_amount = base_amount;
        if (*(u8 *)((u8 *)target + 0x28) & 2) {
            adjusted_amount = base_amount + ((s32)(base_amount << 16) >> 19);
        }
        *(u16 *)((u8 *)target + 0x64) += adjusted_amount;
        cap_pending_actor_value_delta(target);
        base_amount = 0x8004;
        create_actor_value_popup(base_amount, target, (s16)*(u16 *)((u8 *)target + 0x64), 1);
        apply_clamped_actor_value_delta(target);
    }
}


void update_rotating_fading_effect(void *effect, void *position, void *sprite)
{
    s32 quarter_turn;
    s32 rot;
    s32 rand_value;
    s32 rounded_random;
    s32 z_upper;
    s32 scale;
    s32 brightness;
    u16 state;
    void *owner;
    owner = *((void **) (((u8 *) effect) + 0));
    *(u16 *)((u8 *) owner + 0x14) = (*(u16 *)((u8 *) owner + 0x14)) + 1;
    *(u16 *)((u8 *) effect + 0x36) = (*(u16 *)((u8 *) effect + 0x36)) + 1;
    *(u16 *)((u8 *) sprite + 0x1A) = (*(u16 *)((u8 *) sprite + 0x1A)) + 0x10;
    rot = *(u16 *)((u8 *) sprite + 0x1A);
    *(u16 *)((u8 *) sprite + 0x1A) = rot & 0xFFF;
    switch (*(s16 *)((u8 *) effect + 0x34)) {
    case 0:
        if ((*(s16 *)((u8 *) effect + 0x36)) < (*(s16 *)((u8 *) effect + 0x38))) {
            break;
        }
        state = *(u16 *)((u8 *) effect + 0x34);
        *(u16 *)((u8 *) effect + 0x36) = 0;
        state++;
        *(u16 *)((u8 *) effect + 0x34) = state;
        register_node(((u8 *) effect) - 0x20, project_sprite_chain);
        return;

    case 1:
        quarter_turn = 0x400;
        *(s32 *)((u8 *) position + 0) =
            (*(s32 *)((u8 *) effect + 4))
        + ((func_800644B8((quarter_turn / (*(s16 *)((u8 *) effect + 0x3A)))
            * (*(s16 *)((u8 *) effect + 0x36))) >> 4)
            * ((*(s32 *)((u8 *) effect + 0x28)) >> 8));
        *(s32 *)((u8 *) position + 4) =
            (*(s32 *)((u8 *) effect + 8))
        + ((func_800644B8((quarter_turn / (*(s16 *)((u8 *) effect + 0x3A)))
            * (*(s16 *)((u8 *) effect + 0x36))) >> 4)
            * ((*(s32 *)((u8 *) effect + 0x2C)) >> 8));
        *(s32 *)((u8 *) position + 8) =
            (*(s32 *)((u8 *) effect + 0xC))
        + ((func_800644B8((quarter_turn / (*(s16 *)((u8 *) effect + 0x3A)))
            * (*(s16 *)((u8 *) effect + 0x36))) >> 4)
            * ((*(s32 *)((u8 *) effect + 0x30)) >> 8));
        if ((*(s16 *)((u8 *) effect + 0x36)) < (*(s16 *)((u8 *) effect + 0x3A))) {
            break;
        }
        state = *(u16 *)((u8 *) effect + 0x34);
        *(u16 *)((u8 *) effect + 0x36) = 0;
        state++;
        *(u16 *)((u8 *) effect + 0x34) = state;
        return;

    case 2:
        rand_value = rand();
        z_upper = (*(u16 *)((u8 *) position + 0xA)) - 1;
        rounded_random = rand_value;
        *(u16 *)((u8 *) position + 0xA) = z_upper - (rand_value % 4);

        *(u8 *)((u8 *) sprite + 0xE) = (brightness = (*(u8 *)((u8 *) sprite + 0xE)) - 8);
        scale = (*(u16 *)((u8 *) sprite + 0x1E)) + 0x100;
        *(u16 *)((u8 *) sprite + 0x1E) = scale;
        *(u16 *)((u8 *) sprite + 0x1C) = scale;
        *(u8 *)((u8 *) sprite + 0xD) = brightness;
        *(u8 *)((u8 *) sprite + 0xC) = brightness;
        if (((u16) scale) < 0x1801U) {
            break;
        }
        *(u16 *)((u8 *) effect + 0x34) = (*(u16 *)((u8 *) effect + 0x34)) + 1;
        *(u8 *)((u8 *) sprite + 0xE) = 0x80;
        *(u8 *)((u8 *) sprite + 0xD) = 0x80;
        *(u8 *)((u8 *) sprite + 0xC) = 0x80;
        *(u16 *)((u8 *) sprite + 0x1E) = 0x1000;
        *(u16 *)((u8 *) sprite + 0x1C) = 0x1000;
        *(u16 *)((u8 *) sprite + 0x10) |= 0x20;
        select_record_entry_and_value(sprite, &D_800DECF8, 0);
        return;

    case 3:
        advance_sprite_animation_and_textures(sprite);
        if (!((*(u16 *)((u8 *) sprite + 0x14)) & 0x6000)) {
            break;
        }

    case 4:
    default:
        *(u16 *)((u8 *) effect + (-2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        break;
    }
}

void *create_randomized_target_effect(Rec_func_800243B8_arg0 *source, ovl_18ca83c_818AABB8_S_800243B8_3 *start, ovl_18ca83c_818AABB8_S_800243B8_4 *center, s16 index)
{
    s16 amplitude;
    s32 angle_x;
    s32 angle_y;
    void *obj;
    ovl_18ca83c_818AABB8_S_800243B8_1 *data;
    SpriteFrameState *sprite;
    ovl_18ca83c_818AABB8_S_800243B8_6 *position;
    register s32 start_z;

    obj = allocate_flagged_object_node(0x212);
    if (obj != NULL) {
        data = (u8 *)obj + 0x20;
        ((ovl_18ca83c_818AABB8_S_800243B8_0 *)obj)->unk_10 = (void *)update_rotating_fading_effect;
        ((ovl_18ca83c_818AABB8_S_800243B8_0 *)obj)->unk_20 = source;
        data->unk_34 = 0;
        data->unk_36 = 0;
        data->unk_3A = source->unk_12.as_u16;

        amplitude = func_80069EF8() % 48;
        angle_x = func_80069EF8() % 0x1000;
        angle_y = func_80069EF8() % 0x1000;

        data->unk_04 = start->unk_00;
        data->unk_08 = start->unk_04;
        data->unk_0C = start->unk_08;

        {
            s32 trig_x, trig_y;
            s32 raw_trig_x;
            s32 sample_angle;
            raw_trig_x = func_800644B8(angle_x);
            sample_angle = angle_y;
            trig_x = raw_trig_x;
            trig_y = func_800644B8(sample_angle);
            trig_x >>= 4;
            trig_y >>= 4;
            data->unk_1C = center->unk_00 +
                (trig_x * trig_y * amplitude);
        }

        {
            s32 trig_x, trig_y;
            s32 raw_trig_x;
            s32 sample_angle;
            raw_trig_x = func_800644B8(angle_x);
            sample_angle = angle_y;
            trig_x = raw_trig_x;
            trig_y = func_80064584(sample_angle);
            trig_x >>= 4;
            trig_y >>= 4;
            data->unk_20 = center->unk_04 +
                (trig_x * trig_y * amplitude);
        }

        {
            s32 trig_x;
            trig_x = func_80064584(angle_x);
            data->unk_24 = center->unk_08 +
                (((trig_x >> 4) * amplitude) << 8);
        }

        data->unk_28 = data->unk_1C - start->unk_00;
        data->unk_2C = data->unk_20 - start->unk_04;
        data->unk_30 = data->unk_24 - start->unk_08;

        sprite = ((ovl_18ca83c_818AABB8_S_800243B8_0 *)obj)->unk_0C;
        sprite->color.c.b = 0xFF;
        sprite->color.c.g = 0xFF;
        sprite->color.c.r = 0xFF;
        sprite->scale_y = 0x300;
        sprite->scale_x = 0x300;
        sprite->angle_z = func_80069EF8() % 0x1000;
        sprite->clut = 0x7E06;
        sprite->source = D_800777DC;
        sprite->flags |= 0x100;
        sprite->tpage_abr |= 0x60;
        sprite->flags |= 0xC;

        position = ((ovl_18ca83c_818AABB8_S_800243B8_0 *)obj)->unk_08;
        position->unk_00 = start->unk_00;
        position->unk_04 = start->unk_04;
        start_z = start->unk_08;
        position->unk_08 = start_z;
        return obj;
    }
    return NULL;
}

void advance_target_travel_effect(void *effect, void *motion, void *appearance) {
    ovl_18ca83c_818AAE60_Func818AAE60Scratch scratch;
    s16 *target_dist_cursor;
    s16 *path_dist_cursor;
    s32 *destination;
    s32 state;
    s16 target_frames;
    s16 path_frames;
    s32 target_x_dist;
    s32 target_dist_fixed;
    s32 path_dist_fixed;
    s32 index;
    s32 axis_dist;
    s32 origin_coord;
    void *tile_x;
    u16 source_z;
    void *source_info;
    void *source_record;
    void *source;
    void *target;
    void *source_pos;
    u16 elapsed;

    elapsed = ((Rec_func_800243B8_arg0 *)effect)->unk_10;
    state = ((Rec_func_800243B8_arg0 *)effect)->unk_0A;
    source = ((Rec_func_800243B8_arg0 *)effect)->unk_00;
    ((Rec_func_800243B8_arg0 *)effect)->unk_10 = elapsed + 1;
    switch (state) {
    case 0:
        ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
        ((Rec_func_800243B8_arg0 *)effect)->unk_0A = (s16) ((u16) ((Rec_func_800243B8_arg0 *)effect)->unk_0A + 1);
        ((Rec_func_800243B8_arg0 *)effect)->unk_0E = (u16) (((u16) ((ovl_18ca83c_818AAE60_S_80024660_1 *)source)->unk_2A >> 9) & 7);
        ((ovl_18ca83c_818AAE60_S_80024660_2 *)appearance)->unk_0C = 0x808080;
    case 1:
        source_record = source - 0x20;
        source_info = ((ovl_18ca83c_818AAE60_S_80024660_3 *)source_record)->unk_0C;
        if (resolve_record_orientation_or_fallback(((ovl_18ca83c_818AAE60_S_80024660_4 *)source_info)->unk_08, source_info, &scratch.dist[0], 0) == 0) {
            if (!(((ovl_18ca83c_818AAE60_S_80024660_12 *)(((ovl_18ca83c_818AAE60_S_80024660_3 *)source_record)->unk_0C))->unk_14 & 0x8000)) {
                ((Rec_func_800243B8_arg0 *)effect)->unk_14 = 0;
                return;
            }
        }
        source_pos = ((ovl_18ca83c_818AAE60_S_80024660_3 *)source_record)->unk_08;
        ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_00.at02.v = (u16) ((ovl_18ca83c_818AAE60_S_80024660_6 *)source_pos)->unk_02;
        ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_04.at02.v = (u16) ((ovl_18ca83c_818AAE60_S_80024660_6 *)source_pos)->unk_06;
        source_z = ((ovl_18ca83c_818AAE60_S_80024660_6 *)source_pos)->unk_0A;
        ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_08.at02.v = source_z;
        if (!(((ovl_18ca83c_818AAE60_S_80024660_12 *)(((ovl_18ca83c_818AAE60_S_80024660_3 *)source_record)->unk_0C))->unk_14 & 0x8000)) {
            ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_00.at02.v = (u16) (((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_00.at02.v + scratch.dist[0]);
            ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_04.at02.v = (u16) (((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_04.at02.v + scratch.dist[1]);
            ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_08.at02.v = (u16) (((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_08.at02.v + scratch.dist[2]);
        } else {
            ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_08.at02.v = source_z - 0x40;
        }
        if (!(*((Rec_func_800243B8_arg0 *)effect)->unk_04 & 0x80)) {
            ((Rec_func_800243B8_arg0 *)effect)->unk_14 = 0;
            return;
        }
        target = ((ovl_18ca83c_818AAE60_S_80024660_1 *)source)->unk_60;
        index = 1;
        if (target != 0) {
            destination = ((ovl_18ca83c_818AAE60_S_80024660_7_pre *)target)[-1].unk_00;
            target_x_dist = ((ovl_18ca83c_818AAE60_S_80024660_8 *)destination)->unk_00.at02.v;
            target_x_dist -= ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_00.at02u.v;
            if (target_x_dist < 0) {
                target_x_dist = 0 - target_x_dist;
            }
            scratch.dist[0] = (u16) target_x_dist;
            axis_dist = ((ovl_18ca83c_818AAE60_S_80024660_8 *)destination)->unk_04.at02.v;
            origin_coord = ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_04.at02u.v;
            target_dist_cursor = (s16 *)((u8 *)&scratch + 2);
            axis_dist -= origin_coord;
            axis_dist = abs(axis_dist);
            scratch.dist[1] = (u16) axis_dist;
            origin_coord = ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_08.at02u.v;
            origin_coord += 0x20;
            axis_dist = ((ovl_18ca83c_818AAE60_S_80024660_8 *)destination)->unk_08.at02.v - origin_coord;
            axis_dist = abs(axis_dist);
            scratch.dist[2] = (u16) axis_dist;
            ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = target_x_dist;
            do {
                if (target_dist_cursor[12] > ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16) {
                    ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = (s16) (u16) target_dist_cursor[12];
                }
                index += 1;
                target_dist_cursor += 1;
            } while (index < 3);
            target_dist_fixed = (u16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 << 0x10;
            target_frames = (target_dist_fixed >> 0x14) + (target_dist_fixed >> 0x15);
            ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = target_frames;
            if (target_frames == 0) {
                ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = 1;
            }
            ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_0C = (s32) ((s32) (((ovl_18ca83c_818AAE60_S_80024660_8 *)destination)->unk_00.at00.v
                - ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_00.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
            ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_10 = (s32) ((s32) (((ovl_18ca83c_818AAE60_S_80024660_8 *)destination)->unk_04.at00.v
                - ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_04.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
            ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_14 = (s32) ((s32) (((ovl_18ca83c_818AAE60_S_80024660_8 *)destination)->unk_08.at00.v
                - ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_08.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
            play_sound_if_enabled(0x300);
            ((Rec_func_800243B8_arg0 *)effect)->unk_0A += 1;
        } else {
            u16 path_x;
            u16 path_y;
            s16 grid_x;
            s16 grid_y;
            u16 last_x;
            u16 saved_y;
            s32 probe_z;
            s16 *step_y;
            s32 floor_height;
            s32 dest_x;
            s32 dest_y;

            index = 0;
            path_y = ((ovl_18ca83c_818AAE60_S_80024660_9 *)((ovl_18ca83c_818AAE60_S_80024660_3 *)source_record)->unk_0C)->unk_25;
            path_x = ((ovl_18ca83c_818AAE60_S_80024660_9 *)((ovl_18ca83c_818AAE60_S_80024660_3 *)source_record)->unk_0C)->unk_24;
            saved_y = path_y;
            last_x = path_x;
            while (index < 8) {
                grid_x = (s16)path_x;
                grid_y = (s16)path_y;
                if ((s16)check_layer_offset_height((grid_x << 6) & 0xFFC0, (grid_y << 6) & 0xFFC0,
                        ((ovl_18ca83c_818AAE60_S_80024660_1 *)source)->unk_88,
                        (s16)(((Rec_func_800243B8_arg0 *)effect)->unk_0E << 9)) != 0) {
                    break;
                }
                source_pos = &dir_step_x[(s16)((Rec_func_800243B8_arg0 *)effect)->unk_0E];
                probe_z = (u16)((ovl_18ca83c_818AAE60_S_80024660_1 *)source)->unk_88;
                probe_z -= 32;
                probe_z = (u32)probe_z << 16;
                probe_z >>= 16;
                step_y = &dir_step_y[(s16)((Rec_func_800243B8_arg0 *)effect)->unk_0E];
                floor_height = sample_terrain_surface_height(((grid_x + *(s16 *)source_pos) << 6) + 32 & 0xFFE0,
                    ((grid_y + *step_y) << 6) + 32 & 0xFFE0, probe_z);
                if ((s16)floor_height >= 513 ||
                    (s16)(floor_height - ((ovl_18ca83c_818AAE60_S_80024660_1 *)source)->unk_88) < -63) {
                    break;
                }
                index++;
                path_x += dir_step_x[(s16)((Rec_func_800243B8_arg0 *)effect)->unk_0E];
                path_y += dir_step_y[(s16)((Rec_func_800243B8_arg0 *)effect)->unk_0E];
                saved_y = path_y;
                last_x = path_x;
            }
            destination = (s32 *)&scratch;
            index = 1;
            path_dist_cursor = (s16 *)((u8 *)&scratch + 2);
            dest_x = ((last_x << 16) >> 10) + ((dir_step_x[(s16)((Rec_func_800243B8_arg0 *)effect)->unk_0E] + 1) << 5);
            ((ovl_18ca83c_818AAE60_S_80024660_8 *)destination)->unk_00.at02.v = dest_x;
            dest_y = ((saved_y << 16) >> 10) + ((dir_step_y[(s16)((Rec_func_800243B8_arg0 *)effect)->unk_0E] + 1) << 5);
            ((ovl_18ca83c_818AAE60_S_80024660_8 *)destination)->unk_04.at02.v = dest_y;
            ((ovl_18ca83c_818AAE60_S_80024660_8 *)destination)->unk_08.at02.v = ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_08.at02.v + 32;
            scratch.dist[0] = abs(((ovl_18ca83c_818AAE60_S_80024660_8 *)destination)->unk_00.at02.v - ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_00.at02u.v);
            scratch.dist[1] = abs(((ovl_18ca83c_818AAE60_S_80024660_8 *)destination)->unk_04.at02.v - ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_04.at02u.v);
            scratch.dist[2] = abs(((ovl_18ca83c_818AAE60_S_80024660_8 *)destination)->unk_08.at02.v - ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_08.at02u.v);
            ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = scratch.dist[0];
            do {
                if (path_dist_cursor[12] > ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16) {
                    ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = (s16) (u16) path_dist_cursor[12];
                }
                index += 1;
                path_dist_cursor += 1;
            } while (index < 3);
            path_dist_fixed = (u16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 << 0x10;
            path_frames = (path_dist_fixed >> 0x14) + (path_dist_fixed >> 0x15);
            ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = path_frames;
            if (path_frames == 0) {
                ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = 1;
            }
            ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_0C = (s32) ((s32) (((ovl_18ca83c_818AAE60_S_80024660_8 *)destination)->unk_00.at00.v
                - ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_00.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
            ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_10 = (s32) ((s32) (((ovl_18ca83c_818AAE60_S_80024660_8 *)destination)->unk_04.at00.v
                - ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_04.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
            ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_14 = (s32) ((s32) (((ovl_18ca83c_818AAE60_S_80024660_8 *)destination)->unk_08.at00.v
                - ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_08.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
            ((Rec_func_800243B8_arg0 *)effect)->unk_0A = 5;
        }
        index = 0x1F;
        tile_x = effect + 0x7C;
        do {
            ((ovl_18ca83c_818AAE60_S_80024660_10 *)tile_x)->unk_18 = create_randomized_target_effect(effect, motion, destination, (s16)index);
            index -= 1;
            tile_x -= 4;
        } while (index >= 0);
        ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
        break;
    case 3:
        if ((s16) ((Rec_func_800243B8_arg0 *)effect)->unk_10 < 0x28) {
            break;
        }
        func_8002403C(((ovl_18ca83c_818AAE60_S_80024660_1 *)source)->unk_60, ((Rec_func_800243B8_arg0 *)effect)->unk_09, source);
        ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
        ((Rec_func_800243B8_arg0 *)effect)->unk_0A = (s16) ((u16) ((Rec_func_800243B8_arg0 *)effect)->unk_0A + 1);
        break;
    case 4:
        if (((Rec_func_800243B8_arg0 *)effect)->unk_14 != 0) {
            break;
        }
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)effect + -2)) = (u16) ((*(u16 *)((u8 *)effect + -2)) | 0x8000);
        (*(s32 *)&object_flag_block.flags) = (s32) (object_flag_block.flags | 0x8000);
        break;
    case 2:
        ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_00.at00.v = (s32) (((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_00.at00.v
            + ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_0C);
        ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_04.at00.v = (s32) (((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_04.at00.v
            + ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_10);
        ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_08.at00.v = (s32) (((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_08.at00.v
            + ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_14);
        if ((s16) ((Rec_func_800243B8_arg0 *)effect)->unk_10 < ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16) {
            break;
        }
        ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
        ((Rec_func_800243B8_arg0 *)effect)->unk_0A = (s16) ((u16) ((Rec_func_800243B8_arg0 *)effect)->unk_0A + 1);
        break;
    case 5:
        ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_00.at00.v = (s32) (((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_00.at00.v
            + ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_0C);
        ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_04.at00.v = (s32) (((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_04.at00.v
            + ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_10);
        ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_08.at00.v = (s32) (((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_08.at00.v
            + ((ovl_18ca83c_818AAE60_S_80024660_5 *)motion)->unk_14);
        if ((s16) ((Rec_func_800243B8_arg0 *)effect)->unk_10 < ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16) {
            break;
        }
        ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
        ((Rec_func_800243B8_arg0 *)effect)->unk_0A = (s16) ((u16) ((Rec_func_800243B8_arg0 *)effect)->unk_0A + 1);
        break;
    case 6:
        if ((s16) ((Rec_func_800243B8_arg0 *)effect)->unk_10 < 0x28) {
            break;
        }
        ((Rec_func_800243B8_arg0 *)effect)->unk_0A = 4;
        ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
    default:
        break;
    }
    ((Rec_func_800243B8_arg0 *)effect)->unk_14 = 0;
    return;
}
