#include "dungeon/effect/motion/initialize_entity_position_and_motion.h"

void (*const dungeon_ovl_19a332c_entry)(void) = (void (*)(void))func_80024064;

void func_80024064(void *transition) {
    ovl_19a332c_81982864_StackPair setup_args;
    s16 restore_frames;
    s16 restore_left;
    s16 dim_left;
    s32 state_or_frames;
    s32 result_or_state;
    u8 transition_kind;
    void *transition_data;
    GameWork *levels;
    void *active_state;
    void *source_data;

    levels = &g_game_work;
    state_or_frames = ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.s;
    switch (state_or_frames) {
    case 0:
        setup_args.first = 0x010003A0;
        setup_args.second = 0x400020;
        decode_and_upload_image(&D_80027750, &setup_args);
        upload_vram_row_and_cache(&D_80027C74, 0x7AC0, 1, 2);
        D_80027C94 = 1;
        transition_kind = ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_09;
        active_state = (*(void * *)&((EntityRec *)((int *)(&D_800814A8)))->x);
        D_800269D0 = 0;
        D_80027C96 = transition_kind;
        source_data = (*(void **)((u8 *)transition + 0));
        ((ovl_19a332c_81982864_S_80024064_2 *)active_state)->unk_F4 = 0;
        D_80027C98 = source_data;
        ((ovl_19a332c_81982864_S_80024064_2 *)active_state)->unk_A8 = (u8) ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_08;
        inventory_clear_circular_list_flag_2000(active_state);
        ((ovl_19a332c_81982864_S_80024064_6 *)((*(void **)((u8 *)((int *)(&D_800814A8)) + 0))))->unk_96 = 0x14;
        ((ovl_19a332c_81982864_S_80024064_7 *)((*(void * *)&((EntityRec *)((int *)(&D_800814A8)))->x)))->unk_102 = 1;
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.s = (s16) ((u16) ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.s + 1);
    case 1:
        if (!(*((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_04 & 0x80)) {
            break;
        }
        transition_data = ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_00;
        result_or_state = allocate_two_part_object(((ovl_19a332c_81982864_S_80024064_3_pre *)transition_data)[-1].unk_00, transition_data);
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0C = result_or_state;
        if (result_or_state == 0) {
            break;
        }
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_20 = -1;
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_22 = 0x20;
        play_sound_if_enabled(0x300);
        result_or_state = ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.p;
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.p = result_or_state + 1;
        break;
    case 2:
        state_or_frames = 0x10;
        if (D_80027C94 != 0) {
            break;
        }
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_1A = (s16) state_or_frames;
        result_or_state = ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.p;
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.p = result_or_state + 1;
        break;
    case 3:
        levels->view.unk_091 = (u8) (levels->view.unk_091 + ((s32) (0x80
            - levels->view.unk_091) / (s16) ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_1A));
        restore_frames = ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_1A;
        levels->view.unk_090 = (u8) (levels->view.unk_090 + ((s32) (0x80 - levels->view.unk_090) / restore_frames));
        restore_left = (u16) ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_1A - 1;
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_1A = restore_left;
        if ((restore_left << 0x10) > 0) {
            break;
        }
        levels->view.unk_091 = 0x80U;
        levels->view.unk_090 = 0x80U;
        result_or_state = ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.p;
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.p = result_or_state + 1;
        break;
    case 4:
        if (*(s16 *)&D_800269F8 != 0) {
            break;
        }
        g_dungeon_status.unk_0C = 0;
        g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) - 1);
        ((ovl_19a332c_81982864_S_80024064_0_pre *)transition)[-1].unk_00 = (u16) (((ovl_19a332c_81982864_S_80024064_0_pre *)transition)[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | 0x8000;
    default:
        break;
    }
update_dimming:
    if (((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_20 < 0) {
        levels->view.unk_091 = (u8) (levels->view.unk_091 + ((s32) (0x20
            - levels->view.unk_091) / (s16) ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_22));
        levels->view.unk_090 = (u8) (levels->view.unk_090 + ((s32) (0x20
            - levels->view.unk_090) / (s16) ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_22));
        dim_left = (u16) ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_22 - 1;
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_22 = dim_left;
        if ((dim_left << 0x10) <= 0) {
            ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_20 = 0;
        }
    }
    D_800269F8 = 0;
    return;
}
/* Warning: struct S_8003E2D8 is not defined (only forward-declared) */

void initialize_entity_position_and_motion(ovl_19a332c_81982B2C_Entity *entity, ovl_19a332c_81982B2C_Position *position, ovl_19a332c_81982B2C_Motion *motion)
{
    s16 state;
    void *actor;
    u16 *base_coords;

    D_800269F8++;
    state = entity->state;

    if (state == 0) {
        actor = entity->inner->actor;
        if (entity->active == 0) {
            if (resolve_record_orientation_or_fallback(*(s32 *)((u8 *)actor + 8), actor,
                              &entity->x, 0) != 0) {
                entity->active = 1;
            } else if (*(u16 *)((u8 *)actor + 0x14) & 0x8000) {
                entity->active = 1;
                entity->z = -0x40;
            }
            if (entity->active == 0) {
                return;
            }
        }

        base_coords = entity->inner->coords;
        position->x = base_coords[1] + entity->x;
        position->y = base_coords[3] + entity->y;
        position->z = base_coords[5] + entity->z;
        register_node((u8 *)entity - 0x20, project_sprite_chain);
        entity->state++;
        return;
    }

    if (state == 1) {
        if ((u8)motion->value < 0xC0) {
            motion->value += 0x00202020;
            return;
        }
        if (create_nine_linked_effects(position->x, position->y, position->z,
                          *(s16 *)(((u8 **)&D_80027C98)[0] + 0x2A)) != 0) {
            entity->state++;
        }
        return;
    }

    if (state == 2) {
        motion->value += 0xFFFBFBFC;
        if ((u8)motion->value == 0) {
            *(u16 *)((u8 *)entity - 2) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
    }
}

void *allocate_two_part_object(ovl_19a332c_81982CEC_S_800244EC_2 *source_part, s32 offset)
{
    s32 rect[2];
    s32 rect_size;
    void *obj;
    ovl_19a332c_81982CEC_S_800244EC_1 *part;
    void *result;

    obj = func_8003FC64(2);
    if (obj != NULL) {
        rect[0] = 0x01000340;
        rect_size = 0x200020;
        rect[1] = rect_size;
        draw_textured_ellipse(&D_800DF31C, rect, 1, 0);
        rect[0] = 0x01200340;
        rect[1] = rect_size;
        draw_textured_ellipse(&D_800269D4, rect, 1, 0);
        part = ((ovl_19a332c_81982CEC_S_800244EC_0 *)obj)->unk_08;
        ((ovl_19a332c_81982CEC_S_800244EC_0 *)obj)->unk_10 = (void *)initialize_entity_position_and_motion;
        part->unk_02 = source_part->unk_02;
        part->unk_06 = source_part->unk_06;
        part->unk_08.at02.v = source_part->unk_0A;
        part = ((ovl_19a332c_81982CEC_S_800244EC_0 *)obj)->unk_0C;
        part->unk_08.at00.v = &D_800269FC;
        part->unk_1E = 0xC00;
        part->unk_1C = 0xC00;
        ((ovl_19a332c_81982CEC_S_800244EC_0 *)obj)->unk_28 = offset - 0x20;
    }
    result = NULL;
    if (obj != NULL) {
        result = (u8 *)obj + 0x20;
    }
    return result;
}

void move_fade_and_expand_effect(void *effect_data, void *motion_data, void *sprite_data)
{
    ovl_19a332c_81982DF8_Arg2 *sprite = (ovl_19a332c_81982DF8_Arg2 *) sprite_data;
    void *effect = effect_data;
    ovl_19a332c_81982DF8_Arg1 *motion = (ovl_19a332c_81982DF8_Arg1 *) motion_data;
    s16 frames_left;
    s32 next_x;
    u16 scale;
    u16 count_or_scale;
    int zero;
    u8 brightness;
    u8 faded_brightness;
    count_or_scale = D_800269F8 + 1;
    next_x = motion->f0 + motion->fc;
    D_800269F8 = (u16) count_or_scale;
    motion->f0 = next_x;
    zero = 0;
    motion->f4 = motion->f4 + motion->f10;
    motion->f8 = motion->f8 + motion->f14;
    motion->f14 = motion->f14 + 0xC000;
    func_800478B8(sprite);
    brightness = sprite->c;
    faded_brightness = brightness - (((s32) brightness) / ((s16) (*((s16 *) (((s8 *) effect) + 0x30)))));
    sprite->c = faded_brightness;
    sprite->d = faded_brightness;
    sprite->e = faded_brightness;
    scale = sprite->f1c;
    count_or_scale = scale + (((s32) (0x400 - scale)) / ((s16) (*((s16 *) (((s8 *) effect) + 0x30)))));
    sprite->f1c = count_or_scale;
    sprite->f1e = count_or_scale;
    frames_left = ((u16) (*((s16 *) (((s8 *) effect) + 0x30)))) - 1;
    *((s16 *) (((s8 *) effect) + 0x30)) = frames_left;
    if ((frames_left << 0x10) <= zero) {
        *((u16 *) (((s8 *) effect) + (-2))) = (u16) ((*((u16 *) (((s8 *) effect) + (-2)))) | 0x8000);
        ((s32 *)(&object_flag_block))[zero] = (s32) (object_flag_block.flags | 0x8000);
    }
}

void *spawn_random_motion_particles(s16 x, s16 y, s16 z, s16 heading, s16 count)
{
    ovl_19a332c_81982F0C_Object *particle = 0;
    s16 base_angle = (s16)heading;
    s32 remaining = count;

    while (remaining > 0) {
        particle = (ovl_19a332c_81982F0C_Object *)func_8003FC64(0x202);
        if (particle != 0) {
            s32 angle_offset;
            s32 move_angle;
            ovl_19a332c_81982F0C_S_8002470C_0 *motion;
            ovl_19a332c_81982F0C_S_8002470C_1 *sprite;
            u8 *extra;

            particle->callback = move_fade_and_expand_effect;
            register_node(particle, project_sprite_chain);
            motion = particle->dst;
            motion->unk_02 = (s16)x;
            motion->unk_06 = (s16)y;
            motion->unk_0A = (s16)(z + 0x10);

            angle_offset = (s16)((rand() & 0x7FF) - 0x400);
            angle_offset -= 0x800;
            move_angle = base_angle + angle_offset;
            motion->unk_0C = func_80064584(move_angle) << 6;
            motion->unk_10 = func_800644B8(move_angle) << 6;
            motion->unk_14 =
                (rand() & 0x1FFFF) - 0x10000;

            sprite = particle->sprite;
            sprite->unk_1E = 0x1000;
            sprite->unk_1C = 0x1000;
            sprite->unk_0C = 0x808080;
            func_8003DB94(sprite, D_80026AB0, rand() & 7);

            extra = (u8 *)particle + 0x20;
            ((ovl_19a332c_81982F0C_S_8002470C_2 *)extra)->unk_30 = (s16)((rand() & 7) + 0x10);
            ((ovl_19a332c_81982F0C_S_8002470C_2 *)extra)->unk_36 = (s16)heading;
        }
        remaining--;
    }
    return particle;
}

void advance_effect_motion_and_color_fade(void *effect, ovl_19a332c_81983088_S_80024888_0 *motion, ovl_19a332c_81983088_S_80024888_1 *color) {
    s32 velocity_x;
    s32 velocity_y;
    u16 update_count;
    u8 brightness;
    u8 faded_brightness;
    u16 life_left;

    update_count = D_800269F8;
    velocity_x = motion->unk_0C;
    velocity_y = motion->unk_10;
    D_800269F8 = update_count + 1;
    motion->unk_00 = motion->unk_00 + velocity_x;
    motion->unk_04 = motion->unk_04 + velocity_y;
    motion->unk_08 = motion->unk_08 + motion->unk_14;
    motion->unk_14 = motion->unk_14 + 0x2000;
    brightness = color->unk_0C;
    faded_brightness = brightness - (brightness >> 4);
    color->unk_0C = faded_brightness;
    color->unk_0D = faded_brightness;
    color->unk_0E = faded_brightness;
    life_left = ((ovl_19a332c_81983088_S_80024888_2 *)effect)->unk_30 - 1;
    ((ovl_19a332c_81983088_S_80024888_2 *)effect)->unk_30 = life_left;
    if ((life_left << 0x10) <= 0) {
        ((ovl_19a332c_81983088_S_80024888_2_pre *)effect)[-1].unk_00 = ((ovl_19a332c_81983088_S_80024888_2_pre *)effect)[-1].unk_00 | 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

void *spawn_thirty_two_angled_particles(s16 x, s16 y, s16 z, s16 angle, s32 unused_context) {
    s32 direction_x;
    s32 direction_y;
    s32 ring_angle;
    s32 direction_angle;
    s32 particle_index;
    ovl_19a332c_81983138_S_80024938_2 *sprite;
    ovl_19a332c_81983138_S_80024938_1 *motion;
    void *particle;
    union { ovl_19a332c_81983138_S_80024938_3 * pointer; s32 value; } effect_state;
    union { s32 value; s32 *pointer; } size_texture;

    particle_index = 0;
    direction_angle = angle + 0x400;
    do {
        particle = func_8003FC64(0x202);
        if (particle != NULL) {
            ((ovl_19a332c_81983138_S_80024938_0 *)particle)->unk_10 = (void *)advance_effect_motion_and_color_fade;
            register_node(particle, project_sprite_chain);
            motion = ((ovl_19a332c_81983138_S_80024938_0 *)particle)->unk_08;
            motion->unk_02 = x;
            motion->unk_06 = y;
            motion->unk_0A = z;
            ring_angle = particle_index << 7;
            direction_x = func_80064584(direction_angle);
            motion->unk_0C = (s32) ((s32) (direction_x * func_80064584(ring_angle)) >> 6);
            direction_y = func_800644B8(direction_angle);
            motion->unk_10 = (s32) ((s32) (direction_y * func_80064584(ring_angle)) >> 6);
            motion->unk_14 = (s32) (func_800644B8(ring_angle) << 6);
            effect_state.value = 0x808080;
            sprite = ((ovl_19a332c_81983138_S_80024938_0 *)particle)->unk_0C;
            size_texture.value = 0x400;
            sprite->unk_1E = size_texture.value;
            sprite->unk_1C = size_texture.value;
            size_texture.pointer = &D_800269EC;
            sprite->unk_0C = effect_state.value;
            effect_state.value = sprite->unk_14;
            sprite->unk_08 = size_texture.pointer;
            sprite->unk_10 = 0x20;
            sprite->unk_14 = (u16) (effect_state.value | 0xC);
            effect_state.pointer = particle + 0x20;
            effect_state.pointer->unk_30 = 0xC;
            effect_state.pointer->unk_36 = (u16) angle;
        }
        particle_index += 1;
    } while (particle_index < 0x20);
    return particle;
}

void fade_effect_color_by_quarter(u16 *effect_data, s32 unused, ovl_19a332c_819832B4_EffectColor *color) {
    u8 red;
    u8 green;
    u8 blue;

    D_800269F8++;

    red = color->red;
    green = color->green;
    color->red = red - (red >> 2);
    blue = color->blue;
    color->green = green - (green >> 2);
    color->blue = blue - (blue >> 2);

    if (color->red < 4) {
        effect_data[-1] |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

void *spawn_effect_actor_or_curved_trail(s16 x, s16 y, s16 z, s16 angle, s16 spawn_actor) {
    ovl_19a332c_8198332C_Actor *actor;
    ovl_19a332c_8198332C_Coord *coord;
    ovl_19a332c_8198332C_Prim *prim;
    s16 step_x;
    s16 step_y;
    s16 step_z;
    s16 path_x;
    s16 path_y;
    s16 path_z;
    s32 point_index;

    actor = NULL;
    if (spawn_actor != 0) {
        actor = func_8003FC64(514);
        if (actor != NULL) {
            actor->update = (void *)fade_effect_color_by_quarter;
            register_node(actor, project_sprite_chain);
            coord = actor->pos;
            coord->x = x;
            coord->y = y;
            coord->z = z;
            prim = actor->prim;
            prim->unk1E = 2048;
            prim->unk1C = 2048;
            prim->unk8 = D_800269EC;
            prim->color = 0x808080;
            prim->unk10 = 96;
            prim->unk14 |= 0xC;
            actor->unk50 = 16;
        }
    } else {
        if (D_80026B28 == 3) {
            step_x = (D_80027CA4.x - x) / 16;
            step_y = (D_80027CA4.y - y) / 16;
            step_z = (D_80027CA4.z - z) / 16;
            path_x = x + step_x;
            path_y = y + step_y;
            path_z = z + step_z;
            for (point_index = 0; point_index < 16; point_index++) {
                spawn_effect_actor_or_curved_trail(path_x + ((func_80064584(angle) * func_800644B8(point_index << 7)) >> 21),
                              path_y + ((func_800644B8(angle) * func_800644B8(point_index << 7)) >> 21),
                              path_z, angle, 1);
                path_x += step_x;
                path_y += step_y;
                path_z += step_z;
            }
        }
        if (D_80026B28 == 0) {
            D_80027CA4.x = x;
            D_80027CA4.y = y;
            D_80027CA4.z = z;
        }
        D_80026B28 = D_80026B28 + 1;
    }
    return actor;
}

void update_homing_effect_and_attached_copies(ovl_19a332c_819835AC_S_819835AC_1 *effect, ovl_19a332c_819835AC_S_819835AC_2 *motion, ovl_19a332c_819835AC_S_819835AC_3 *visual) {
    struct { s16 x, y, z; } emit_offset;
    s32 aim_angle;
    s32 angle_mask;
    s32 normalized_angle;
    s32 state;
    s32 approach_angle;
    s32 travel_angle;
    s32 homing_angle;
    s32 world_y;
    s32 world_x;
    s16 frame_step;
    s32 next_tile_y;
    s32 rise_speed;
    s32 owner_ptr;
    s32 sin_x;
    s32 sin_y;
    s32 sin_y_shift;
    s32 fade_speed_x;
    s32 boost_speed_x;
    s32 alternate_value;
    s32 height_value;
    s32 hit_origin;
    s32 cos_x;
    s32 cos_y;
    s32 owner_ref;
    s32 fade_speed_y;
    s16 height_frames;
    s32 height_numerator;
    s32 height_numerator_2;
    s32 history_index;
    s32 travel_turn_gap;
    s32 travel_gap_x;
    s32 travel_gap_y;
    s32 hit_height_gap;
    s32 homing_wrap_gap;
    s32 homing_turn_gap;
    s32 target_gap_x;
    s32 target_gap_y;
    s32 approach_wrap_gap;
    s32 approach_turn_gap;
    s32 approach_gap_y;
    s32 approach_gap_z;
    s32 travel_wrap_gap;
    u16 approach_ticks;
    u16 fade_ticks;
    u16 travel_ticks;
    u16 launch_ticks;
    u16 aim_ticks;
    u16 bob_phase;
    u16 search_ticks;
    u16 approach_heading;
    u16 travel_heading;
    u16 homing_heading;
    u16 approach_signed_angle;
    u16 travel_next_angle;
    u16 homing_signed_angle;
    u16 homing_next_angle;
    u16 approach_next_angle;
    u16 travel_signed_angle;
    u8 frame;
    u8 fade_red;
    u8 fade_green;
    u8 fade_blue;
    ovl_19a332c_819835AC_S_819835AC_9 *owner_state;
    ovl_19a332c_819835AC_S_819835AC_7 *actor_data;
    ovl_19a332c_819835AC_S_819835AC_2 *related_motion;
    ovl_19a332c_819835AC_S_819835AC_6 *new_target;
    ovl_19a332c_819835AC_S_819835AC_6 *target;
    ovl_19a332c_819835AC_S_819835AC_4 *history;
    ovl_19a332c_819835AC_S_819835AC_6 *hit_actor;
    EntityRec *state0_move;
    ovl_19a332c_819835AC_S_819835AC_5 *state0_actor;
    ovl_19a332c_819835AC_S_819835AC_5 *state0_height_actor;
    s32 state0_delta_x;
    s32 coord_delta;
    s32 step_y;
    s32 step_z;
    ovl_19a332c_819835AC_S_819835AC_6 *state1_global;
    s32 target_coord;
    EntityRec *state1_move;
    ovl_19a332c_819835AC_S_819835AC_6 *state1_actor;
    ovl_19a332c_819835AC_S_819835AC_6 *state2_stage;
    u8 tile_x;
    u16 tile_counter;
    u8 tile_y;
    s32 tile_div;
    TileObject *state34_base;
    EntityRec *state34_move;
    EntityRec *state34_emit;
    ovl_19a332c_819835AC_S_819835AC_5 *state2_actor;
    u32 state2_angle;
    TileObject *tile_base;
    u32 tile_coord;
    s32 tile_call_arg;
    s32 state6_timer_signed;
    u16 state6_timer;
    u16 state6_next;
    u16 state6_height;
    s32 state6_spin_arg;
    s32 state6_target_base;
    s32 alternate_delta;
    s32 alternate_scale;
    u16 approach_frames;

    (*(s16 *)&D_800269F8) = (s16) (((ovl_19a332c_819835AC_S_819835AC_10 *) &D_800269F8)->unk_00 + 1);
    for (history_index = 0; history_index >= 0; history_index--) {
        history = (ovl_19a332c_819835AC_S_819835AC_4 *) ((u8 *) effect + history_index * 8);
        history->unk_50 = history->unk_48;
    }
    owner_ref = effect->unk_20;
    effect->unk_48 = (u16) motion->unk_00.half.unk_02.u16;
    effect->unk_4A = (u16) motion->unk_04.half.unk_06.u16;
    effect->unk_4C = (u16) motion->unk_08.half.unk_0A.u16;
    if (owner_ref == 0) {
        state = effect->unk_30;
        switch (state) {
        case 0:
            resolve_record_orientation_or_fallback(*(s32 *)((((s32) (g_game_work.view.viewAngle
                + ((ovl_19a332c_819835AC_S_819835AC_5 *) ((ovl_19a332c_819835AC_S_819835AC_11 *) &D_800E3D7C)->unk_00)->unk_2A.s16 + 0x100) >> 7) & 0x1C)
                + D_800E3D18), &D_80082E80.unk_000, (u8 *) effect + 0x28, 0);
            sin_x = func_80064584(((ovl_19a332c_819835AC_S_819835AC_5 *) (*(void **)&D_800E3D7C))->unk_2A.s16);
            cos_x = func_80064584(((ovl_19a332c_819835AC_S_819835AC_5 *) (*(void **)&D_800E3D7C))->unk_2A.s16 - 0x400);
            state0_move = &D_80083780;
            sin_x >>= 4;
            state0_delta_x = ((u16)state0_move->x.w.i);
            cos_x >>= 4;
            state0_delta_x -= sin_x;
            state0_delta_x += cos_x;
            state0_actor = ((ovl_19a332c_819835AC_S_819835AC_11 *) &D_800E3D7C)->unk_00;
            effect->unk_28.u16 += state0_delta_x;
            sin_y = func_800644B8(state0_actor->unk_2A.s16);
            cos_y = func_800644B8(((ovl_19a332c_819835AC_S_819835AC_5 *) (*(void **)&D_800E3D7C))->unk_2A.s16 - 0x400);
            sin_y_shift = sin_y >> 4;
            cos_y >>= 4;
            step_y = ((u16)state0_move->y.w.i);
            coord_delta = effect->unk_2A.u16;
            step_y -= sin_y_shift;
            step_y += cos_y;
            state0_height_actor = ((ovl_19a332c_819835AC_S_819835AC_11 *) &D_800E3D7C)->unk_00;
            coord_delta += step_y;
            effect->unk_2A.u16 = (u16) coord_delta;
            coord_delta = effect->unk_2C.u16;
            step_y = state0_height_actor->unk_88.u16;
            approach_frames = 0x10U;
            coord_delta -= 0x50;
            step_y += coord_delta;
            effect->unk_2C.u16 = (u16) step_y;
            effect->unk_34.u16 = approach_frames;
            height_numerator_2 = (effect->unk_2C.s16 - motion->unk_08.half.unk_0A.s16) << 0x10;
            height_frames = 16;
            motion->unk_14.word = height_numerator_2 / height_frames;
            effect->unk_30 = (s16) ((u16) effect->unk_30 + 1);
        case 1:
            aim_angle = (s16)forward_monster_coordinate_delta((s16) motion->unk_00.half.unk_02.u16, (s16) motion->unk_04.half.unk_06.u16,
                (s16) effect->unk_28.u16, (s16) effect->unk_2A.u16);
            approach_heading = effect->unk_38;
            if (approach_heading & 0x800) {
                approach_signed_angle = approach_heading | 0xF800;
            } else {
                approach_signed_angle = approach_heading & 0x7FF;
            }
            effect->unk_38 = approach_signed_angle;
            if (aim_angle & 0x800) {
                angle_mask = ~0x7FF;
                normalized_angle = aim_angle | angle_mask;
            } else {
                normalized_angle = aim_angle & 0x7FF;
            }
            aim_angle = normalized_angle;
            approach_wrap_gap = (s16) effect->unk_38 - aim_angle;
            if (approach_wrap_gap < 0) {
                approach_wrap_gap = 0 - approach_wrap_gap;
            }
            if (approach_wrap_gap >= 0x801) {
                effect->unk_38 = (u16) ((aim_angle & ~0xFFF) | (effect->unk_38 & 0xFFF));
            }
            approach_angle = (s16) effect->unk_38;
            approach_turn_gap = aim_angle - approach_angle;
            if (approach_turn_gap < 0) {
                approach_turn_gap = 0 - approach_turn_gap;
            }
            if (approach_turn_gap >= 0x81) {
                if (effect->unk_96 != 0) {
                    approach_next_angle = approach_angle + 0x80;
                } else {
                    approach_next_angle = approach_angle - 0x80;
                }
                effect->unk_38 = approach_next_angle;
            } else {
                effect->unk_38 = aim_angle;
            }
            motion->unk_0C.word = (s32) (func_80064584((s16) effect->unk_38) << 8);
            motion->unk_10.word = (s32) (func_800644B8((s16) effect->unk_38) << 8);
            approach_ticks = effect->unk_34.u16 - 1;
            effect->unk_34.u16 = approach_ticks;
            if ((approach_ticks << 0x10) <= 0) {
                motion->unk_08.half.unk_0A.u16 = (u16) effect->unk_2C.u16;
                effect->unk_34.u16 = 0U;
                motion->unk_14.word = 0;
            }
            state1_global = ((ovl_19a332c_819835AC_S_819835AC_11 *) &D_800814A8)->unk_00;
            state1_global->unk_96 = 2;
            boost_speed_x = motion->unk_00.word;
            coord_delta = motion->unk_0C.word;
            step_y = motion->unk_10.word;
            step_z = motion->unk_14.word;
            boost_speed_x += coord_delta;
            motion->unk_00.word = boost_speed_x;
            boost_speed_x = motion->unk_04.word;
            coord_delta = motion->unk_08.word;
            boost_speed_x += step_y;
            motion->unk_04.word = boost_speed_x;
            boost_speed_x = motion->unk_00.half.unk_02.s16;
            coord_delta += step_z;
            motion->unk_08.word = coord_delta;
            coord_delta = effect->unk_28.s16;
            boost_speed_x -= coord_delta;
            if (__builtin_abs(boost_speed_x) >= 0x40) {
                break;
            }
            approach_gap_y = motion->unk_04.half.unk_06.s16;
            target_coord = effect->unk_2A.s16;
            approach_gap_y -= target_coord;
            if (__builtin_abs(approach_gap_y) >= 0x40) {
                break;
            }
            approach_gap_z = motion->unk_08.half.unk_0A.s16;
            target_coord = effect->unk_2C.s16;
            approach_gap_z -= target_coord;
            if (__builtin_abs(approach_gap_z) >= 0x40) {
                break;
            }
            resolve_record_orientation_or_fallback(*(s32 *)((((s32) (g_game_work.view.viewAngle
                + ((ovl_19a332c_819835AC_S_819835AC_5 *) ((ovl_19a332c_819835AC_S_819835AC_11 *) &D_800E3D7C)->unk_00)->unk_2A.s16 + 0x100) >> 7) & 0x1C)
                + D_800E3D18), &D_80082E80.unk_000, (u8 *) effect + 0x28, 0);
            state1_move = &D_80083780;
            effect->unk_28.u16 += (u16)state1_move->x.w.i;
            state1_actor = ((ovl_19a332c_819835AC_S_819835AC_11 *) &D_800814A8)->unk_00;
            effect->unk_2A.u16 += (u16)state1_move->y.w.i;
            coord_delta = effect->unk_2C.u16;
            boost_speed_x = ((ovl_19a332c_819835AC_S_819835AC_5 *) ((ovl_19a332c_819835AC_S_819835AC_11 *) &D_800E3D7C)->unk_00)->unk_88.u16;
            coord_delta -= 0x50;
            boost_speed_x += coord_delta;
            effect->unk_2C.u16 = boost_speed_x;
            state1_actor->unk_A6 = state1_actor->unk_A6 - 1;
            effect->unk_30 = (s16) ((u16) effect->unk_30 + 1);
            break;
        case 2:
            aim_angle = (s16)forward_monster_coordinate_delta((s16) motion->unk_00.half.unk_02.u16, (s16) motion->unk_04.half.unk_06.u16,
                (s16) effect->unk_28.u16, (s16) effect->unk_2A.u16);
            travel_heading = effect->unk_38;
            if (travel_heading & 0x800) {
                travel_signed_angle = travel_heading | 0xF800;
            } else {
                travel_signed_angle = travel_heading & 0x7FF;
            }
            effect->unk_38 = travel_signed_angle;
            if (aim_angle & 0x800) {
                angle_mask = ~0x7FF;
                normalized_angle = aim_angle | angle_mask;
            } else {
                normalized_angle = aim_angle & 0x7FF;
            }
            aim_angle = normalized_angle;
            travel_wrap_gap = (s16) effect->unk_38 - aim_angle;
            if (travel_wrap_gap < 0) {
                travel_wrap_gap = 0 - travel_wrap_gap;
            }
            if (travel_wrap_gap >= 0x801) {
                effect->unk_38 = (u16) ((aim_angle & ~0xFFF) | (effect->unk_38 & 0xFFF));
            }
            travel_angle = (s16) effect->unk_38;
            travel_turn_gap = aim_angle - travel_angle;
            if (travel_turn_gap < 0) {
                travel_turn_gap = 0 - travel_turn_gap;
            }
            if (travel_turn_gap >= 0x81) {
                if (effect->unk_96 != 0) {
                    travel_next_angle = travel_angle + 0x80;
                } else {
                    travel_next_angle = travel_angle - 0x80;
                }
                effect->unk_38 = travel_next_angle;
            } else {
                effect->unk_38 = aim_angle;
            }
            motion->unk_0C.word = (s32) (func_80064584((s16) effect->unk_38) << 8);
            motion->unk_10.word = (s32) (func_800644B8((s16) effect->unk_38) << 8);
            travel_ticks = effect->unk_34.u16 - 1;
            effect->unk_34.u16 = travel_ticks;
            if ((travel_ticks << 0x10) <= 0) {
                motion->unk_08.half.unk_0A.u16 = (u16) effect->unk_2C.u16;
                effect->unk_34.u16 = 0U;
                motion->unk_14.word = 0;
            }
            boost_speed_x = motion->unk_00.word;
            coord_delta = motion->unk_0C.word;
            step_y = motion->unk_10.word;
            step_z = motion->unk_14.word;
            boost_speed_x += coord_delta;
            motion->unk_00.word = boost_speed_x;
            boost_speed_x = motion->unk_04.word;
            coord_delta = motion->unk_08.word;
            boost_speed_x += step_y;
            coord_delta += step_z;
            motion->unk_04.word = boost_speed_x;
            state2_stage = (*(void **)((u8 *)&D_800814A8 + 0));
            motion->unk_08.word = coord_delta;
            state2_stage->unk_96 = 2;
            travel_gap_x = motion->unk_00.half.unk_02.s16;
            target_coord = effect->unk_28.s16;
            travel_gap_x -= target_coord;
            if (travel_gap_x < 0) {
                travel_gap_x = 0 - travel_gap_x;
            }
            if (travel_gap_x >= 0x20) {
                break;
            }
            travel_gap_y = motion->unk_04.half.unk_06.s16;
            target_coord = effect->unk_2A.s16;
            travel_gap_y -= target_coord;
            if (travel_gap_y < 0) {
                travel_gap_y = 0 - travel_gap_y;
            }
            if (travel_gap_y >= 0x20) {
                break;
            }
            effect->unk_34.u16 = 4U;
            state2_actor = ((ovl_19a332c_819835AC_S_819835AC_11 *) &D_800E3D7C)->unk_00;
            effect->unk_30 = (s16) ((u16) effect->unk_30 + 1);
            ((ovl_19a332c_819835AC_S_819835AC_6 *) ((ovl_19a332c_819835AC_S_819835AC_11 *) &D_800814A8)->unk_00)->unk_96 = 0;
            effect->unk_38 = (u16) state2_actor->unk_2A.s16;
            state2_angle = state2_actor->unk_2A.u16;
            D_80026B28 = 0;
            effect->unk_44 = (u16) ((state2_angle >> 9) & 7);
            break;
        case 3:
        case 4:
            state34_base = &D_80082E80;
            if (resolve_record_orientation_or_fallback(state34_base->unk_008, state34_base, &emit_offset, 0) != 0) {
                if (effect->unk_30 == 3) {
                    state34_move = &D_80083780;
                    spawn_blinking_sprite_flash(state34_move->x.w.i + emit_offset.x, state34_move->y.w.i + emit_offset.y,
                        state34_move->z.w.i + emit_offset.z);
                    effect->unk_30 = (s16) ((u16) effect->unk_30 + 1);
                }
                state34_emit = &D_80083780;
                spawn_effect_actor_or_curved_trail((s16) (((u16)state34_emit->x.w.i) + (u16) emit_offset.x),
                    (s16) (((u16)state34_emit->y.w.i) + (u16) emit_offset.y),
                    (s16) (((u16)state34_emit->z.w.i) + (u16) emit_offset.z),
                    ((ovl_19a332c_819835AC_S_819835AC_5 *) ((ovl_19a332c_819835AC_S_819835AC_11 *) &D_800E3D7C)->unk_00)->unk_2A.s16, 0);
            }
            motion->unk_0C.word = (s32) (func_80064584((s16) effect->unk_38) << 8);
            motion->unk_10.word = (s32) (func_800644B8((s16) effect->unk_38) << 8);
            motion->unk_14.half.unk_16 = 0x16;
            rise_speed = motion->unk_14.word;
            motion->unk_00.word = (s32) (motion->unk_00.word + motion->unk_0C.word);
            motion->unk_04.word = (s32) (motion->unk_04.word + motion->unk_10.word);
            motion->unk_08.word = (s32) (motion->unk_08.word + motion->unk_14.word);
            if ((s16) motion->unk_08.half.unk_0A.u16 > ((ovl_19a332c_819835AC_S_819835AC_5 *) (*(void **)((u8 *)&D_800E3D7C
                + 0)))->unk_88.s16) {
                motion->unk_08.half.unk_0A.u16 =
                    (u16) ((ovl_19a332c_819835AC_S_819835AC_5 *) ((ovl_19a332c_819835AC_S_819835AC_11 *) &D_800E3D7C)->unk_00)->unk_88.s16;
            }
            launch_ticks = effect->unk_34.u16 - 1;
            effect->unk_34.u16 = launch_ticks;
            if ((launch_ticks << 0x10) > 0) {
                break;
            }
            tile_base = &D_80082E80;
            tile_coord = tile_base->tileX;
            tile_call_arg = 0x300;
            effect->unk_40 = (s16) tile_coord;
            effect->unk_98 = (u8) tile_coord;
            tile_coord = tile_base->tileY;
            effect->unk_30 = 5;
            effect->unk_46 = 3U;
            effect->unk_34.u16 = 0U;
            effect->unk_42 = (s16) tile_coord;
            effect->unk_99 = (u8) tile_coord;
            play_sound_if_enabled(tile_call_arg, rise_speed);
            break;
        case 5:
            motion->unk_0C.word = (s32) (func_80064584((s16) effect->unk_38) << 8);
            motion->unk_10.word = (s32) (func_800644B8((s16) effect->unk_38) << 8);
            motion->unk_14.word = 0;
            motion->unk_00.word = (s32) (motion->unk_00.word + motion->unk_0C.word);
            world_x = motion->unk_00.half.unk_02.s16;
            motion->unk_04.word = (s32) (motion->unk_04.word + motion->unk_10.word);
            motion->unk_08.word = (s32) (motion->unk_08.word + motion->unk_14.word);
            if (world_x < 0) {
                world_x += 0x3F;
            }
            tile_div = world_x >> 6;
            effect->unk_40 = (s16) tile_div;
            world_y = motion->unk_04.half.unk_06.s16;
            next_tile_y = (world_y / 64);
            effect->unk_42 = (s16) next_tile_y;
            if (effect->unk_98 == effect->unk_40) {
                if (effect->unk_99 == next_tile_y) {
                    break;
                }
            }
            hit_actor = ((ovl_19a332c_819835AC_S_819835AC_11 *) &D_800814A8)->unk_00;
            hit_origin = (s32)(hit_actor);
            coord_delta = hit_actor->unk_5C;
            hit_actor = coord_delta + 0x20;
            if (hit_actor != (void *)hit_origin) {
                do {
                    actor_data = ((ovl_19a332c_819835AC_S_819835AC_8 *) ((u8 *) hit_actor - 0x20))->unk_0C;
                    if ((actor_data->unk_24 == effect->unk_40) &&
                        (actor_data->unk_25 == effect->unk_42)) {
                        hit_height_gap = hit_actor->unk_88;
                        target_coord = motion->unk_08.half.unk_0A.s16;
                        hit_height_gap -= target_coord;
                        if (hit_height_gap < 0) {
                            hit_height_gap = -hit_height_gap;
                        }
                        actor_data = (u8 *) hit_actor - 0x20;
                        if ((hit_height_gap < 0x80) && !(actor_data->unk_1E & 0x2000)) {
                            apply_attack_power_and_element_effects(hit_actor, 0xC, D_80027C96, 0xA, (s32) (s16) (effect->unk_44 << 9),
                                D_80027C98, 2);
                            related_motion = ((ovl_19a332c_819835AC_S_819835AC_8 *) ((u8 *) hit_actor - 0x20))->unk_08;
                            spawn_thirty_two_angled_particles(related_motion->unk_00.half.unk_02.s16,
                                related_motion->unk_04.half.unk_06.s16, related_motion->unk_08.half.unk_0A.s16,
                                (s16) effect->unk_38, (func_80069EF8() & 3) | 4);
                            actor_data->unk_1E = (u16) (actor_data->unk_1E | 0x2000);
                        }
                    }
                    coord_delta = hit_actor->unk_5C;
                    hit_actor = coord_delta + 0x20;
                } while (hit_actor != ((ovl_19a332c_819835AC_S_819835AC_11 *) &D_800814A8)->unk_00);
            }
            tile_x = (u8) effect->unk_40;
            tile_counter = effect->unk_46;
            tile_y = (u8) effect->unk_42;
            tile_counter -= 1;
            effect->unk_46 = tile_counter;
            effect->unk_98 = tile_x;
            effect->unk_99 = tile_y;
            if ((tile_counter << 0x10) > 0) {
                break;
            }
            effect->unk_8A = (u16) ((func_80069EF8() & 0x1F) + 0x10);
            effect->unk_9C = 0;
            effect->unk_30 = (s16) ((u16) effect->unk_30 + 1);
            break;
        case 6:
            target = effect->unk_9C;
            if (target != 0) {
                related_motion = ((ovl_19a332c_819835AC_S_819835AC_8 *) ((u8 *) target - 0x20))->unk_08;
                aim_angle = (s16)forward_monster_coordinate_delta((s16) motion->unk_00.half.unk_02.u16, (s16) motion->unk_04.half.unk_06.u16,
                    related_motion->unk_00.half.unk_02.s16, related_motion->unk_04.half.unk_06.s16);
                homing_heading = effect->unk_38;
                if (homing_heading & 0x800) {
                    homing_signed_angle = homing_heading | 0xF800;
                } else {
                    homing_signed_angle = homing_heading & 0x7FF;
                }
                effect->unk_38 = homing_signed_angle;
                if (aim_angle & 0x800) {
                    angle_mask = ~0x7FF;
                    normalized_angle = aim_angle | angle_mask;
                } else {
                    normalized_angle = aim_angle & 0x7FF;
                }
                aim_angle = normalized_angle;
                homing_wrap_gap = (s16) effect->unk_38 - aim_angle;
                if (homing_wrap_gap < 0) {
                    homing_wrap_gap = 0 - homing_wrap_gap;
                }
                if (homing_wrap_gap >= 0x801) {
                    effect->unk_38 = (u16) ((aim_angle & ~0xFFF) | (effect->unk_38 & 0xFFF));
                }
                aim_ticks = effect->unk_9A - 1;
                effect->unk_9A = aim_ticks;
                if ((aim_ticks << 0x10) <= 0) {
                    effect->unk_9A = 0x1EU;
                    effect->unk_38 = aim_angle;
                }
                homing_angle = (s16) effect->unk_38;
                homing_turn_gap = aim_angle - homing_angle;
                if (homing_turn_gap < 0) {
                    homing_turn_gap = 0 - homing_turn_gap;
                }
                if (homing_turn_gap >= 0x81) {
                    if (effect->unk_96 != 0) {
                        homing_next_angle = homing_angle + 0x80;
                    } else {
                        homing_next_angle = homing_angle - 0x80;
                    }
                    effect->unk_38 = homing_next_angle;
                } else {
                    effect->unk_38 = aim_angle;
                }
                state6_timer_signed = effect->unk_34.s16;

                state6_timer = effect->unk_34.u16;
                if (state6_timer_signed != 0) {
                    state6_next = state6_timer - 1;
                    effect->unk_34.u16 = state6_next;
                    if ((state6_next << 0x10) == 0) {
                        state6_height = related_motion->unk_08.half.unk_0A.u16;
                        motion->unk_14.word = 0;
                        state6_height -= 0x40;
                        motion->unk_08.half.unk_0A.u16 = state6_height;
                        effect->unk_8A = 0U;
                    }
                } else {
                    bob_phase = effect->unk_8A + 1;
                    state6_spin_arg = (s32) (bob_phase << 0x10);

                    state6_spin_arg >>= 9;
                    effect->unk_8A = bob_phase;
                    motion->unk_14.half.unk_16 = (s16) (func_800644B8(state6_spin_arg) >> 9);
                }
                target_gap_x = motion->unk_00.half.unk_02.s16;
                target_coord = related_motion->unk_00.half.unk_02.s16;
                target_gap_x -= target_coord;
                if (target_gap_x < 0) {
                    target_gap_x = 0 - target_gap_x;
                }
                if (target_gap_x < 0x20) {
                    target_gap_y = motion->unk_04.half.unk_06.s16;
                    target_coord = related_motion->unk_04.half.unk_06.s16;
                    target_gap_y -= target_coord;
                    if (target_gap_y < 0) {
                        target_gap_y = 0 - target_gap_y;
                    }
                    if (target_gap_y < 0x20) {
                        actor_data = effect->unk_9C - 0x20;
                        apply_attack_power_and_element_effects(effect->unk_9C, 0xC, D_80027C96, 0xA, (s32) (s16) (effect->unk_44 << 9),
                            D_80027C98, 2);
                        play_sound_if_enabled(0x300);
                        spawn_thirty_two_angled_particles(related_motion->unk_00.half.unk_02.s16, related_motion->unk_04.half.unk_06.s16,
                            (s16) related_motion->unk_08.half.unk_0A.u16, (s16) effect->unk_38,
                            (func_80069EF8() & 3) | 4);
                        actor_data->unk_1E = (u16) (actor_data->unk_1E | 0x2000);
                        effect->unk_9C = 0;
                        effect->unk_8A = (u16) ((func_80069EF8() & 0x1F) + 0x10);
                    }
                }
                motion->unk_0C.word = func_80064584((s16) effect->unk_38) << 8;
                motion->unk_10.word = func_800644B8((s16) effect->unk_38) << 8;

                if ((s16) effect->unk_38 == aim_angle) {
                    motion->unk_0C.word += motion->unk_0C.word >> 1;
                    motion->unk_10.word += motion->unk_10.word >> 1;
                }
            } else {
                motion->unk_14.word = 0;
                search_ticks = effect->unk_8A - 1;
                effect->unk_8A = search_ticks;
                if ((search_ticks << 0x10) <= 0) {
                    new_target = find_eligible_nearby_entity(&D_80082E80.unk_000);
                    effect->unk_9C = new_target;
                    if (new_target == 0) {
                        effect->unk_30 = 0x10;
                        effect->unk_8A = 8U;
                    } else {
                        related_motion = ((ovl_19a332c_819835AC_S_819835AC_8 *) ((u8 *) new_target - 0x20))->unk_08;
                        effect->unk_34.u16 = 0x10U;
                        state6_target_base = motion->unk_08.half.unk_0A.s16;
                        height_value = related_motion->unk_08.half.unk_0A.s16;
                        state6_target_base += 0x40;
                        height_numerator = (height_value - state6_target_base) << 0x10;
                        height_frames = 16;
                        motion->unk_14.word = height_numerator / height_frames;
                        effect->unk_9A = 0x3CU;
                    }
                } else {
                    effect->unk_38 = (u16) (effect->unk_38 + 0x80);
                }
                motion->unk_0C.word = (s32) (func_80064584((s16) effect->unk_38) << 8);
                motion->unk_10.word = (s32) (func_800644B8((s16) effect->unk_38) << 8);
            }
            motion->unk_00.word = (s32) (motion->unk_00.word + motion->unk_0C.word);
            motion->unk_04.word = (s32) (motion->unk_04.word + motion->unk_10.word);
            motion->unk_08.word = (s32) (motion->unk_08.word + motion->unk_14.word);
            break;
        case 16:
            fade_speed_x = motion->unk_0C.word;
            fade_speed_y = motion->unk_10.word;
            motion->unk_0C.word = (s32) (fade_speed_x - (fade_speed_x >> 3));
            motion->unk_10.word = (s32) (fade_speed_y - (fade_speed_y >> 3));
            if ((effect->unk_3E - 0x10) < (s16) motion->unk_08.half.unk_0A.u16) {
                motion->unk_08.half.unk_0A.u16 = (u16) ((u16) effect->unk_3E - 0x10);
            }
            motion->unk_00.word = (s32) (motion->unk_00.word + motion->unk_0C.word);
            motion->unk_04.word = (s32) (motion->unk_04.word + motion->unk_10.word);
            motion->unk_08.word = (s32) (motion->unk_08.word + motion->unk_14.word);
            fade_red = visual->unk_0C.half.unk_0C;
            visual->unk_0C.half.unk_0C = (u8) (fade_red - ((s32) fade_red / (s16) effect->unk_8A));
            fade_green = visual->unk_0C.half.unk_0D;
            visual->unk_0C.half.unk_0D = (u8) (fade_green - ((s32) fade_green / (s16) effect->unk_8A));
            fade_blue = visual->unk_0C.half.unk_0E;
            visual->unk_0C.half.unk_0E = (u8) (fade_blue - ((s32) fade_blue / (s16) effect->unk_8A));
            fade_ticks = effect->unk_8A - 1;
            effect->unk_8A = fade_ticks;
            if ((fade_ticks << 0x10) > 0) {
                return;
            }
            D_80027C94 = 0;
            goto block_139;
        }
        visual->unk_1A = (u16) ((s16)forward_monster_coordinate_delta(0, 0, motion->unk_0C.half.unk_0E, motion->unk_10.half.unk_12) - 0x400);
        boost_speed_x = motion->unk_14.half.unk_16;
        step_y = (*(u16 *)((u8 *)visual + 0x1C));
        coord_delta = visual->unk_0C.half.unk_0C;
        aim_angle = boost_speed_x * 4;
        boost_speed_x = aim_angle + 0x400;
        visual->unk_16 = (u16) boost_speed_x;
        boost_speed_x = 0x2000;
        boost_speed_x -= step_y;
        boost_speed_x >>= 2;
        step_y += boost_speed_x;
        coord_delta += 8;
        visual->unk_0C.half.unk_0C = coord_delta;
        visual->unk_1C = (u16) step_y;
        visual->unk_20 = (u16) step_y;
        visual->unk_1E = (u16) step_y;
        coord_delta &= 0xFF;
        coord_delta = (u32)coord_delta < 0x81U;
        if (!coord_delta) {
            visual->unk_0C.word = 0x808080;
        } else {
            visual->unk_0C.half.unk_0D = (u8) (visual->unk_0C.half.unk_0D + 8);
            visual->unk_0C.half.unk_0E = (u8) (visual->unk_0C.half.unk_0E + 8);
        }
        inventory_reset_shared_state_mode_13((u8 *) effect - 0x20, motion, 8, 0x300);
        step_and_clamp_entry_index(visual, (u8 *) effect + 0x36, effect->unk_3C, effect->unk_3A);
        inventory_copy_and_sign_extend_record_fields(effect, visual->unk_00);
        frame = visual->unk_04;
        if ((s8) frame == effect->unk_3A) {
            frame_step = -1;
            effect->unk_36 = frame_step;
        } else if ((s8) frame == effect->unk_3C) {
            frame_step = 1;
            effect->unk_36 = frame_step;
        }
        spawn_random_motion_particles((s16) motion->unk_00.half.unk_02.u16, (s16) motion->unk_04.half.unk_06.u16,
            (s16) motion->unk_08.half.unk_0A.u16, (s16) effect->unk_38, D_80026BD4[(s8) visual->unk_04]);
        effect->unk_94 = (u16) (effect->unk_94 + 1);
        return;
    }
    owner_ptr = owner_ref | 0x80000000;
    if (((ovl_19a332c_819835AC_S_819835AC_8 *) owner_ptr)->unk_1E & 0x8000) {
block_139:
        ((ovl_19a332c_819835AC_S_819835AC_8 *) ((u8 *) effect - 0x20))->unk_1E = (u16) (((ovl_19a332c_819835AC_S_819835AC_8 *) ((u8 *) effect - 0x20))->unk_1E
            | 0x8000);
        (*(s32 *)&object_flag_block.flags) = (s32) (object_flag_block.flags | 0x8000);
        return;
    }
    actor_data = ((ovl_19a332c_819835AC_S_819835AC_8 *) owner_ptr)->unk_0C;
    related_motion = ((ovl_19a332c_819835AC_S_819835AC_8 *) owner_ptr)->unk_08;
    if (owner_ref & 0x80000000) {
        owner_state = owner_ptr + 0x20;
        visual->unk_1A = (u16) ((s16)forward_monster_coordinate_delta((s16) motion->unk_00.half.unk_02.u16,
            (s16) motion->unk_04.half.unk_06.u16, related_motion->unk_00.half.unk_02.s16,
            related_motion->unk_04.half.unk_06.s16) - 0x400);
        alternate_delta = related_motion->unk_08.half.unk_0A.s16;
        alternate_value = motion->unk_08.half.unk_0A.s16;
        alternate_delta -= alternate_value;
        alternate_scale = alternate_delta << 2;
        alternate_scale += alternate_delta;
        aim_angle = alternate_scale << 1;
        alternate_value = aim_angle + 0x400;
        visual->unk_16 = (u16) alternate_value;
        visual->unk_14 = (u16) actor_data->unk_14;
        motion->unk_00.half.unk_02.u16 = (u16) owner_state->unk_50;
        motion->unk_04.half.unk_06.u16 = (u16) owner_state->unk_52;
        motion->unk_08.half.unk_0A.u16 = (u16) owner_state->unk_54;
    } else {
        motion->unk_00.half.unk_02.u16 = (u16) related_motion->unk_00.half.unk_02.s16;
        motion->unk_04.half.unk_06.u16 = (u16) related_motion->unk_04.half.unk_06.s16;
        motion->unk_08.half.unk_0A.u16 = (u16) related_motion->unk_08.half.unk_0A.s16;
        visual->unk_16 = (u16) actor_data->unk_16;
        visual->unk_18 = (u16) actor_data->unk_18;
        visual->unk_1A = (u16) actor_data->unk_1A;
        visual->unk_14 = (u16) actor_data->unk_14;
    }
    visual->unk_1C = (u16) actor_data->unk_1C;
    visual->unk_1E = (u16) actor_data->unk_1E;
    visual->unk_20 = (u16) actor_data->unk_20;
    visual->unk_0C.word = actor_data->unk_0C;
    if (D_80026BC8[effect->unk_88] != 0) {
        inventory_set_object_entry_address(visual, actor_data->unk_04);
        inventory_copy_and_sign_extend_record_fields(effect, visual->unk_00);
    }
    effect->unk_94 = (u16) (effect->unk_94 + 1);
    return;
}

void *create_nine_linked_effects(s32 x, s32 y, s32 z, s32 angle)
{
    ovl_19a332c_81984754_Object *objects[9];
    u16 spawn_x;
    u16 spawn_y;
    u16 spawn_z;
    s32 spawn_angle;
    EntityRec *target_pos;
    ovl_19a332c_81984754_Object **object_base;
    ovl_19a332c_81984754_Object **object_slot;
    ovl_19a332c_81984754_Pos *pos;
    ovl_19a332c_81984754_Part *part;
    ovl_19a332c_81984754_Entity *entity;
    ovl_19a332c_81984754_Entity *prev_entity;
    s32 object_index;
    s32 history_index;
    s32 target_angle;
    s32 normalized_target;
    s32 signed_target;
    s32 angle_bits;
    s32 angle_delta;
    u8 *allocation_page;
    ovl_19a332c_81984754_Object *prev_object;

    spawn_angle = angle;
    prev_entity = 0;
    spawn_x = x;
    spawn_y = y;
    spawn_z = z;
    if (has_enough_available_runtime_nodes(9) == 0) {
        return prev_entity;
    }

    object_index = 0;
    object_base = &objects[object_index];
    target_pos = &D_80083780;
    object_slot = object_base;
    do {
        allocation_page = (u8 *)0x80080000;
        if (object_index != 0) {
            prev_object = object_slot[-1];
        } else {
            prev_object = (ovl_19a332c_81984754_Object *)((u8 *)(&D_80083498));
        }
        *object_slot = allocate_list_node(2, prev_object);
        (*object_slot)->state = (void (*)(void *))(void *)update_homing_effect_and_attached_copies;
        register_node(*object_slot, draw_linked_model_chain);

        pos = (*object_slot)->pos;
        pos->x = spawn_x;
        pos->y = spawn_y;
        pos->z = spawn_z;

        part = (*object_slot)->part;
        part->f16 = 0x400;
        part->f1A = spawn_angle - 0x400;
        part->table = D_80026B2C + (object_index * 0x10);
        part->f10 = 0x60;
        part->flags |= 0xC;

        entity = &(*object_slot)->entity;
        if (object_index != 0) {
            u32 parent_link;
            u32 link_scratch;
            parent_link = (u32)D_80026BBC;
            link_scratch = parent_link + object_index;
            parent_link = *(u8 *)link_scratch;
            if (parent_link != 0) {
                link_scratch = 0x7FFFFFFF;
                entity->parent = (ovl_19a332c_81984754_Object *)((u32)object_base[parent_link - 1] & link_scratch);
            } else {
                entity->parent = object_slot[-1];
            }
        }

        entity->f34 = 0x10;
        entity->angle = spawn_angle + 0x400;
        entity->f44 = ((u32)spawn_angle >> 9) & 7;
        entity->f3C = 0;
        entity->f3A = D_80026BC8[object_index] != 0 ? 0xF : 0;
        entity->f36 = 1;
        entity->index = object_index;

        if (prev_entity != 0) {
            prev_entity->next = *object_slot;
        }

        target_angle = forward_monster_coordinate_delta(pos->x, pos->y,
                              target_pos->x.w.i,
                              target_pos->y.w.i);

        angle_bits = (u16)entity->angle;
        entity->angle = (angle_bits & 0x800)
            ? (angle_bits | 0xF800)
        : (angle_bits & 0x7FF);

        normalized_target = target_angle & 0x800;
        if (normalized_target != 0) {
            normalized_target = target_angle | 0xF800;
        } else {
            normalized_target = target_angle & 0x7FF;
        }
        target_angle = normalized_target;

        angle_bits = (s32)((u32)target_angle << 16);
        signed_target = angle_bits >> 16;
        angle_delta = (s16)entity->angle;
        angle_delta -= signed_target;
        angle_bits = (u16)entity->angle;
        if (angle_delta < 0) {
            angle_delta = -angle_delta;
        }
        if (angle_delta >= 0x801) {
            entity->angle = (target_angle & -0x1000) |
                            (angle_bits & 0xFFF);
        }

        entity->direction = (s16)entity->angle < signed_target;

        history_index = 7;
        do {
            entity->history[history_index].x = pos->x;
            entity->history[history_index].y = pos->y;
            entity->history[history_index].z = pos->z;
            history_index--;
        } while (history_index >= 0);

        inventory_select_entry_and_reset_object(part, 0);
        inventory_copy_and_sign_extend_record_fields(entity, part->unk0);
        prev_entity = entity;
        object_slot++;
        object_index++;
    } while (object_index < 9);

    return objects[0];
}

void inventory_copy_and_sign_extend_record_fields(ovl_19a332c_81984A40_Dest81984A40 *dst, ovl_19a332c_81984A40_Source81984A40 *src)
{
    s32 sourceHalfword;

    dst->words = src->words;
    sourceHalfword = src->field_10;
    dst->field_10 = sourceHalfword;
    dst->field_14 = src->field_12;
    dst->field_18 = src->field_13;
    dst->field_1C = src->field_14;
}

void inventory_select_entry_and_reset_object(ovl_19a332c_81984AB0_S_81984AB0_0 *object, s16 entry_index) {
    s32 entry_base;

    object->unk_04 = entry_index;
    object->unk_05 = 0;
    entry_base = ((ovl_19a332c_81984AB0_S_81984AB0_2 *)(((ovl_19a332c_81984AB0_S_81984AB0_1 *)object)->unk_08))->unk_0C;
    object->unk_14 = (u16) (object->unk_14 & 0x9FFF);
    object->unk_00 = (s32) (entry_base + (entry_index * 0x16));
}

void step_and_clamp_entry_index(void *object, s16 *index_step, s32 min_index, s32 max_index) {
    s16 step;
    s32 shifted_index;
    u32 clamp_flags;
    u8 index;
    ovl_19a332c_81984AF4_S_81984AF4_0 *obj = object;
    s32 initial_index = obj->unk_04.s;
    ovl_19a332c_81984AF4_S_81984AF4_1 *owner = obj->unk_08;

    obj->unk_00 =
        owner->unk_0C + (initial_index * 22);
    step = *index_step;
    if (step > 0) {
        obj->unk_04.u = obj->unk_04.u + 1;
    } else if (step < 0) {
        obj->unk_04.u =
            obj->unk_04.u - 1;
    }
    index = (u8)obj->unk_04.s;
    shifted_index = index << 24;
    if ((s8)index < (s16)min_index) {
        clamp_flags = obj->unk_14.s | 0x4000;
        obj->unk_04.s = min_index;
        obj->unk_14.u = clamp_flags;
        return;
    }
    if ((s8)index > (s16)max_index) {
        clamp_flags = obj->unk_14.s | 0x4000;
        obj->unk_04.s = max_index;
        obj->unk_14.u = clamp_flags;
        return;
    }
    obj->unk_14.u &= 0xBFFF;
}

void inventory_set_object_entry_address(ovl_19a332c_81984BC0_S_81984BC0_0 *object, s16 entry_index) {
    object->unk_00 = (s32) (((ovl_19a332c_81984BC0_S_81984BC0_2 *)(((ovl_19a332c_81984BC0_S_81984BC0_1 *)object)->unk_08))->unk_0C + (entry_index * 0x16));
}

void inventory_clear_circular_list_flag_2000(void *unused_actor)
{
    void *link;
    void *object;
    void *head;
    s32 link_value;
    s32 next;

    link = D_800814A8;
    next = ((ovl_19a332c_81984BF0_S_81984BF0_0 *)link)->unk_5C;
    link_value = (u32)link;
    next += 0x20;
    link = next;
    if (link == (void *)(u32)link_value) {
        return;
    }
    head = (void *)(u32)link_value;
    do {
        object = link - 0x20;
        next = ((ovl_19a332c_81984BF0_S_81984BF0_1 *)object)->unk_1E;
        next &= 0xDFFF;
        ((ovl_19a332c_81984BF0_S_81984BF0_1 *)object)->unk_1E = next;
        link_value = ((ovl_19a332c_81984BF0_S_81984BF0_0 *)link)->unk_5C;
        link = (void *)(link_value + 0x20);
    } while (link != head);
}

void *find_eligible_nearby_entity(void *source_entity)
{
    void *node;
    s16 owner_limit;
    s32 initial_limit;
    void *next_link;
    s8 entity_floor;
    ovl_19a332c_81984C44_S_81984C44_4 *owner;

    node = D_800814A8;
    initial_limit = 0x100;
    if (((ovl_19a332c_81984C44_S_81984C44_1 *)source_entity)->unk_26 < 0) {
        initial_limit = 4;
    }
    next_link = ((ovl_19a332c_81984C44_S_81984C44_2 *)node)->unk_5C;
    node = (u8 *)next_link + 0x20;
    if (node != D_800814A8) {
        do {
            void *next_link;
            if (((check_entity_interaction_compatibility(D_800814A8, node) << 16) != 0) &&
                ((check_entity_eligibility(node) << 16) != 0) &&
                !(((ovl_19a332c_81984C44_S_81984C44_2_pre *)node)[-1].unk_12 & 0x2000)) {
                entity_floor = ((ovl_19a332c_81984C44_S_81984C44_1 *)source_entity)->unk_26;
                owner = ((ovl_19a332c_81984C44_S_81984C44_2_pre *)node)[-1].unk_00;
                if (entity_floor >= 0) {
                    if (entity_floor == owner->unk_26) {
                        return node;
                    }
                } else {
                    owner_limit = initial_limit;
                    if (get_tile_chebyshev_distance(owner, source_entity) < owner_limit) {
                        return node;
                    }
                }
            }
            next_link = ((ovl_19a332c_81984C44_S_81984C44_2 *)node)->unk_5C;
            node = (u8 *)next_link + 0x20;
        } while (node != D_800814A8);
    }
    return 0;
}

void clear_object_buffer_and_state(void *tracker) {
    s16 blend_ticks;
    s16 next_ticks;
    ovl_19a332c_81984D4C_S_81984D4C_2 *target;
    GameView *state;
    u8 *timer;
    u8 *z_pending;

    blend_ticks = (*(s16 *)((u8 *)tracker + 0x24));
    state = &g_game_work.view;
    if (blend_ticks > 0) {
        state->unk_098 = (u16) ((u16)state->unk_098) + ((s32) ((*(s16 *)((u8 *)tracker + 0x26))
            - state->unk_098) / blend_ticks);
    }
    next_ticks = (u16) (*(s16 *)((u8 *)tracker + 0x24)) - 1;
    (*(s16 *)((u8 *)tracker + 0x24)) = next_ticks;
    if (next_ticks < -0x80) {
        (*(s16 *)((u8 *)tracker + 0x24)) = -0x80;
    }
    timer = D_800E3D20;
    if (((ovl_19a332c_81984D4C_S_81984D4C_1 *)timer)->unk_00.u != 0) {
        ((ovl_19a332c_81984D4C_S_81984D4C_1 *)timer)->unk_00.s = (s8) (((ovl_19a332c_81984D4C_S_81984D4C_1 *)timer)->unk_00.u - 1);
    }
    (*(u16 *)((u8 *)tracker + 4)) = (u16) ((ovl_19a332c_81984D4C_S_81984D4C_4 *)((*(void **)((u8 *)tracker + 0xC))))->unk_02;
    target = (*(void **)((u8 *)tracker + 0xC));
    (*(u16 *)((u8 *)tracker + 6)) = (u16) target->unk_06;
    (*(u16 *)((u8 *)tracker + 8)) = (u16) target->unk_0A;
    state->unk_0A4 = (u16) ((u16)state->unk_0A4) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 4)) - state->unk_0A4) >> 2);
    state->unk_0A6 = (u16) ((u16)state->unk_0A6) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 6)) - state->unk_0A6) >> 2);
    z_pending = D_80026BE4;
    if (((ovl_19a332c_81984D4C_S_81984D4C_3 *)z_pending)->unk_00.u != 0) {
        state->unk_0A8 = (u16) ((u16)state->unk_0A8) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 8)) - state->unk_0A8)
            >> 2);
    }
    ((ovl_19a332c_81984D4C_S_81984D4C_3 *)z_pending)->unk_00.s = (s8) (state->unk_0A8 != (s16) (*(u16 *)((u8 *)tracker + 8)));
    state->unk_094 = (u16) ((s32) (((u16)state->unk_094) << 0x10) >> 0x12);
    state->unk_096 = (u16) ((s32) (((u16)state->unk_096) << 0x10) >> 0x12);
}

/* MECHANISM: Frameless leaf; tracker stays in a1 and D_80083178 in a2 across the CFG.
   The tracker+0xC pointer is read a second time, after the first-use load and the store to
   tracker+4: the u16 store invalidates the earlier read (cse invalidate_memory), giving retail's
   paired lw v0/v1 and keeping v1 live for offsets 6/0xA. */

s32 inventory_reset_shared_state_mode_13(s32 unused, s32 state_key, s32 value, s16 secondary_value) {
    GameView *state = &g_game_work.view;
    ovl_19a332c_81984E94_S_8191696C_state *substate = (ovl_19a332c_81984E94_S_8191696C_state *)&state->slot[0].unk_04;
    void *next_field = (void *)((u8 *)&state->slot[0].unk_04 + 4);
    s16 saved_value;
    s32 previous_key;
    s32 change_flags;

    previous_key = substate->unkC4;
    substate->unkC4 = state_key;
    substate->unkE0 = 0;
    substate->field_B8 = next_field;
    saved_value = value;
    change_flags = previous_key != state_key;
    if (substate->unkCC != 9) {
        change_flags |= 2;
    }
    substate->unkCC = 0xD;
    substate->unkD0 = 0;
    substate->unkDE = secondary_value;
    state->slot[0].callback = (void *)clear_object_buffer_and_state;
    if (change_flags & 1) {
        D_800E3D20[0] = saved_value;
    }
    substate->unkDC = value;
    return change_flags;
}
