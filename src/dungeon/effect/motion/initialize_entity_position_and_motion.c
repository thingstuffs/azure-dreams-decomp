#include "slus.h"
#include "engine/resource.h"
#include "shared/audio_commands.h"
/* Homing attack movement, linked visual copies, and particle creation. */
#include "shared/object_node.h"
#include "shared/entity.h"
#include "dungeon/effect/motion/initialize_entity_position_and_motion.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/effect/motion.h"
#include "engine/graphics.h"

void (*const dungeon_ovl_19a332c_entry)(void *transition) = advance_image_tint_transition;

/* Loads effect graphics, starts a paired object effect, dims and restores the scene tint, and waits
   for cleanup. */
void advance_image_tint_transition(void *transition_arg) {
    ovl_19a332c_81982864_S_80024064_0 *transition = transition_arg;
    ovl_19a332c_81982864_StackPair setup_args;
    s16 restore_frames;
    s16 restore_left;
    s16 dim_left;
    s32 state_or_frames;
    s32 result_or_state;
    u8 transition_kind;
    void *transition_data;
    GameWork *levels;
    ovl_19a332c_81982864_S_80024064_2 *active_state;
    void *source_data;

    levels = &g_game_work;
    state_or_frames = transition->unk_0A.s;
    switch (state_or_frames) {
    case 0:
        setup_args.first = 0x010003A0;
        setup_args.second = 0x400020;
        decode_and_upload_image(&tint_transition_image, &setup_args);
        upload_vram_row_and_cache(&tint_transition_vram_row, 0x7AC0, 1, 2);
        tint_transition_image_pending = 1;
        transition_kind = transition->unk_09;
        active_state = (*(void **)&((EntityRec *)((int *)(&primary_actor_record)))->x);
        D_800269D0 = 0;
        tint_transition_kind = transition_kind;
        source_data = (*(void **)((u8 *)transition + 0));
        active_state->unk_F4 = 0;
        tint_transition_source = source_data;
        active_state->unk_A8 = (u8) transition->unk_08;
        inventory_clear_circular_list_flag_2000(active_state);
        ((ovl_19a332c_81982864_S_80024064_6 *)((*(void **)((u8 *)((int *)(&primary_actor_record)) + 0))))->unk_96 = 0x14;
        ((ovl_19a332c_81982864_S_80024064_7 *)((*(void **)&((EntityRec *)((int *)(&primary_actor_record)))->x)))->unk_102 = 1;
        transition->unk_0A.s = (s16) ((u16) transition->unk_0A.s + 1);
    case 1:
        if (!(*transition->unk_04 & 0x80)) {
            break;
        }
        transition_data = transition->unk_00;
        result_or_state = allocate_two_part_object(((ovl_19a332c_81982864_S_80024064_3_pre *)transition_data)[-1].unk_00, transition_data);
        transition->unk_0C = result_or_state;
        if (result_or_state == 0) {
            break;
        }
        transition->unk_20 = -1;
        transition->unk_22 = 0x20;
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        result_or_state = transition->unk_0A.p;
        transition->unk_0A.p = result_or_state + 1;
        break;
    case 2:
        state_or_frames = 0x10;
        if (tint_transition_image_pending != 0) {
            break;
        }
        transition->unk_1A = (s16) state_or_frames;
        result_or_state = transition->unk_0A.p;
        transition->unk_0A.p = result_or_state + 1;
        break;
    case 3:
        levels->view.tint.parts.tint_g = (u8) (levels->view.tint.parts.tint_g + ((s32) (0x80
            - levels->view.tint.parts.tint_g) / (s16) transition->unk_1A));
        restore_frames = transition->unk_1A;
        levels->view.tint.parts.tint_r = (u8) (levels->view.tint.parts.tint_r + ((s32) (0x80 - levels->view.tint.parts.tint_r) / restore_frames));
        restore_left = (u16) transition->unk_1A - 1;
        transition->unk_1A = restore_left;
        if ((restore_left << 0x10) > 0) {
            break;
        }
        levels->view.tint.parts.tint_g = 0x80U;
        levels->view.tint.parts.tint_r = 0x80U;
        result_or_state = transition->unk_0A.p;
        transition->unk_0A.p = result_or_state + 1;
        break;
    case 4:
        if (*(s16 *)&image_tint_update_count != 0) {
            break;
        }
        g_dungeon_status.active_actor = 0;
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        ((ovl_19a332c_81982864_S_80024064_0_pre *)transition)[-1].unk_00 = (u16) (((ovl_19a332c_81982864_S_80024064_0_pre *)transition)[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    default:
        break;
    }
update_dimming:
    if (transition->unk_20 < 0) {
        levels->view.tint.parts.tint_g = (u8) (levels->view.tint.parts.tint_g + ((s32) (0x20
            - levels->view.tint.parts.tint_g) / (s16) transition->unk_22));
        levels->view.tint.parts.tint_r = (u8) (levels->view.tint.parts.tint_r + ((s32) (0x20
            - levels->view.tint.parts.tint_r) / (s16) transition->unk_22));
        dim_left = (u16) transition->unk_22 - 1;
        transition->unk_22 = dim_left;
        if ((dim_left << 0x10) <= 0) {
            transition->unk_20 = 0;
        }
    }
    image_tint_update_count = 0;
    return;
}
/* Warning: struct S_8003E2D8 is not defined (only forward-declared) */

void initialize_entity_position_and_motion(ovl_19a332c_81982B2C_Entity *entity, ovl_19a332c_81982B2C_Position *position, ovl_19a332c_81982B2C_Motion *motion)
{
    s16 state;
    void *actor;
    u16 *base_coords;

    image_tint_update_count++;
    state = entity->state;

    if (state == 0) {
        actor = entity->inner->sprite;
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
                          *(s16 *)(((u8 **)&tint_transition_source)[0] + 0x2A)) != 0) {
            entity->state++;
        }
        return;
    }

    if (state == 2) {
        motion->value += 0xFFFBFBFC;
        if ((u8)motion->value == 0) {
            *(u16 *)((u8 *)entity - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}

/* Loads two effect textures and creates an object with copied coordinates, fixed sprite scales, and an
   owner link. */
void *allocate_two_part_object(ovl_19a332c_81982CEC_S_800244EC_2 *source_part, s32 offset)
{
    GpuRectBuffer rect;
    s32 rect_size;
    ObjectNodeHeader *obj;
    ovl_19a332c_81982CEC_S_800244EC_1 *part;
    void *result;

    obj = allocate_flagged_object_node(2);
    if (obj != NULL) {
        rect.words[0] = 0x01000340;
        rect_size = 0x200020;
        rect.words[1] = rect_size;
        draw_textured_ellipse(&D_800DF31C, &rect.rect, 1, 0);
        rect.words[0] = 0x01200340;
        rect.words[1] = rect_size;
        draw_textured_ellipse(&D_800269D4, &rect.rect, 1, 0);
        part = obj->position;
        obj->update_callback = (void *)initialize_entity_position_and_motion;
        part->unk_02 = source_part->unk_02;
        part->unk_06 = source_part->unk_06;
        part->unk_08.at02.v = source_part->unk_0A;
        part = obj->sprite;
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

/* Advances an accelerating particle, fades its color, and eases its scale toward 0x400 until its
   countdown ends. */
void move_fade_and_expand_effect(void *effect_data, void *motion_data, void *sprite_data)
{
    SpriteFrameState *sprite= (ovl_19a332c_81982DF8_Arg2 *) sprite_data;
    void *effect = effect_data;
    ovl_19a332c_81982DF8_Arg1 *motion = motion_data;
    s16 frames_left;
    s32 next_x;
    u16 scale;
    u16 count_or_scale;
    int zero;
    u8 brightness;
    u8 faded_brightness;
    count_or_scale = image_tint_update_count + 1;
    next_x = motion->f0 + motion->fc;
    image_tint_update_count = (u16) count_or_scale;
    motion->f0 = next_x;
    zero = 0;
    motion->f4 = motion->f4 + motion->f10;
    motion->f8 = motion->f8 + motion->f14;
    motion->f14 = motion->f14 + 0xC000;
    advance_sprite_animation_and_textures(sprite);
    brightness = sprite->color.c.r;
    faded_brightness = brightness - (((s32) brightness) / ((s16) (*((s16 *) (((s8 *) effect) + 0x30)))));
    sprite->color.c.r = faded_brightness;
    sprite->color.c.g = faded_brightness;
    sprite->color.c.b = faded_brightness;
    scale = sprite->scale_x;
    count_or_scale = scale + (((s32) (0x400 - scale)) / ((s16) (*((s16 *) (((s8 *) effect) + 0x30)))));
    sprite->scale_x = count_or_scale;
    sprite->scale_y = count_or_scale;
    frames_left = ((u16) (*((s16 *) (((s8 *) effect) + 0x30)))) - 1;
    *((s16 *) (((s8 *) effect) + 0x30)) = frames_left;
    if ((frames_left << 0x10) <= zero) {
        *((u16 *) (((s8 *) effect) + (-2))) = (u16) ((*((u16 *) (((s8 *) effect) + (-2)))) | NODE_REMOVE);
        ((s32 *)(&object_flag_block))[zero] = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}

/* Creates the requested number of gray particles with random velocities, animation frames, and lifetimes. */
void *spawn_random_motion_particles(s16 x, s16 y, s16 z, s16 heading, s16 count)
{
    ObjectNodeHeader *particle = 0;
    s16 base_angle = (s16)heading;
    s32 remaining = count;

    while (remaining > 0) {
        particle = allocate_flagged_object_node(0x202);
        if (particle != 0) {
            s32 angle_offset;
            s32 move_angle;
            ObjectPosition *motion;
            SpriteFrameState *sprite;
            ovl_19a332c_81982F0C_S_8002470C_2 *extra;

            particle->update_callback = move_fade_and_expand_effect;
            register_node(particle, project_sprite_chain);
            motion = particle->position;
            motion->x.w.i = (s16)x;
            motion->y.w.i = (s16)y;
            motion->z.w.i = (s16)(z + 0x10);

            angle_offset = (s16)((rand() & 0x7FF) - 0x400);
            angle_offset -= 0x800;
            move_angle = base_angle + angle_offset;
            motion->velocity_x = rcos(move_angle) << 6;
            motion->velocity_y = rsin(move_angle) << 6;
            motion->velocity_z =
                (rand() & 0x1FFFF) - 0x10000;

            sprite = particle->sprite;
            sprite->scale_y = 0x1000;
            sprite->scale_x = 0x1000;
            sprite->color.word = 0x808080;
            select_record_entry_and_value(sprite, D_80026AB0, rand() & 7);

            extra = (ovl_19a332c_81982F0C_S_8002470C_2 *)((u8 *)particle + 0x20);
            extra->unk_30 = (s16)((rand() & 7) + 0x10);
            extra->unk_36 = (s16)heading;
        }
        remaining--;
    }
    return particle;
}

/* Moves a particle with vertical acceleration, fades its grayscale color, and removes it when its
   lifetime expires. */
void advance_effect_motion_and_color_fade(void *effect, ovl_19a332c_81983088_S_80024888_0 *motion, ovl_19a332c_81983088_S_80024888_1 *color) {
    s32 velocity_x;
    s32 velocity_y;
    u16 update_count;
    u8 brightness;
    u8 faded_brightness;
    u16 life_left;

    update_count = image_tint_update_count;
    velocity_x = motion->unk_0C;
    velocity_y = motion->unk_10;
    image_tint_update_count = update_count + 1;
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
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates up to 32 gray particles with velocities distributed around a ring oriented by the supplied
   angle. */
void *spawn_thirty_two_angled_particles(s16 x, s16 y, s16 z, s16 angle, s32 unused_context) {
    s32 direction_x;
    s32 direction_y;
    s32 ring_angle;
    s32 direction_angle;
    s32 particle_index;
    SpriteFrameState *sprite;
    ObjectPosition *motion;
    ObjectNodeHeader *particle;
    union { ovl_19a332c_81983138_S_80024938_3 * pointer; s32 value; } effect_state;
    union { s32 value; s32 *pointer; } size_texture;

    particle_index = 0;
    direction_angle = angle + 0x400;
    do {
        particle = allocate_flagged_object_node(0x202);
        if (particle != NULL) {
            particle->update_callback = (void *)advance_effect_motion_and_color_fade;
            register_node(particle, project_sprite_chain);
            motion = particle->position;
            motion->x.w.i = x;
            motion->y.w.i = y;
            motion->z.w.i = z;
            ring_angle = particle_index << 7;
            direction_x = rcos(direction_angle);
            motion->velocity_x = (s32) ((s32) (direction_x * rcos(ring_angle)) >> 6);
            direction_y = rsin(direction_angle);
            motion->velocity_y = (s32) ((s32) (direction_y * rcos(ring_angle)) >> 6);
            motion->velocity_z = (s32) (rsin(ring_angle) << 6);
            effect_state.value = 0x808080;
            sprite = particle->sprite;
            size_texture.value = 0x400;
            sprite->scale_y = size_texture.value;
            sprite->scale_x = size_texture.value;
            size_texture.pointer = &positioned_motion_sprite_data;
            sprite->color.word = effect_state.value;
            effect_state.value = sprite->flags;
            sprite->source = size_texture.pointer;
            sprite->tpage_abr = 0x20;
            sprite->flags = (u16) (effect_state.value | 0xC);
            effect_state.pointer = ((void *)particle) + 0x20;
            effect_state.pointer->unk_30 = 0xC;
            effect_state.pointer->unk_36 = (u16) angle;
        }
        particle_index += 1;
    } while (particle_index < 0x20);
    return particle;
}

/* Reduces each sprite color channel by a quarter and removes the effect when red falls below 4. */
void fade_effect_color_by_quarter(u16 *effect_data, s32 unused, ovl_19a332c_819832B4_EffectColor *color) {
    u8 red;
    u8 green;
    u8 blue;

    image_tint_update_count++;

    red = color->red;
    green = color->green;
    color->red = red - (red >> 2);
    blue = color->blue;
    color->green = green - (green >> 2);
    color->blue = blue - (blue >> 2);

    if (color->red < 4) {
        effect_data[-1] |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a fading sprite or samples positions and emits 16 sprites along a curved trail on the fourth
   call. */
void *spawn_effect_actor_or_curved_trail(s16 x, s16 y, s16 z, s16 angle, s16 spawn_actor) {
    ovl_19a332c_8198332C_Actor *actor;
    ObjectPosition *coord;
    SpriteFrameState *prim;
    s16 step_x;
    s16 step_y;
    s16 step_z;
    s16 path_x;
    s16 path_y;
    s16 path_z;
    s32 point_index;

    actor = NULL;
    if (spawn_actor != 0) {
        actor = allocate_flagged_object_node(514);
        if (actor != NULL) {
            actor->update = (void *)fade_effect_color_by_quarter;
            register_node(actor, project_sprite_chain);
            coord = actor->pos;
            coord->x.w.i = x;
            coord->y.w.i = y;
            coord->z.w.i = z;
            prim = actor->prim;
            prim->scale_y = 2048;
            prim->scale_x = 2048;
            prim->source = positioned_motion_sprite_data;
            prim->color.word = 0x808080;
            prim->tpage_abr = 96;
            prim->flags |= 0xC;
            actor->unk50 = 16;
        }
    } else {
        if (curved_trail_sample_count == 3) {
            step_x = (curved_trail_position.x - x) / 16;
            step_y = (curved_trail_position.y - y) / 16;
            step_z = (curved_trail_position.z - z) / 16;
            path_x = x + step_x;
            path_y = y + step_y;
            path_z = z + step_z;
            for (point_index = 0; point_index < 16; point_index++) {
                spawn_effect_actor_or_curved_trail(path_x + ((rcos(angle) * rsin(point_index << 7)) >> 21),
                              path_y + ((rsin(angle) * rsin(point_index << 7)) >> 21),
                              path_z, angle, 1);
                path_x += step_x;
                path_y += step_y;
                path_z += step_z;
            }
        }
        if (curved_trail_sample_count == 0) {
            curved_trail_position.x = x;
            curved_trail_position.y = y;
            curved_trail_position.z = z;
        }
        curved_trail_sample_count = curved_trail_sample_count + 1;
    }
    return actor;
}

/* Moves a homing attack through launch, target hits, and fade-out, or follows its owner as an attached
   copy. */
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
    u8 * hit_origin;
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
    ObjectPosition *related_motion;
    ovl_19a332c_819835AC_S_819835AC_6 *new_target;
    ovl_19a332c_819835AC_S_819835AC_6 *target;
    ovl_19a332c_819835AC_S_819835AC_4 *history;
    ovl_19a332c_819835AC_S_819835AC_6 *hit_actor;
    ObjectPosition *state0_move;
    ovl_19a332c_819835AC_S_819835AC_5 *state0_actor;
    ovl_19a332c_819835AC_S_819835AC_5 *state0_height_actor;
    s32 state0_delta_x;
    s32 coord_delta;
    s32 step_y;
    s32 step_z;
    ovl_19a332c_819835AC_S_819835AC_6 *state1_global;
    s32 target_coord;
    ObjectPosition *state1_move;
    ovl_19a332c_819835AC_S_819835AC_6 *state1_actor;
    ovl_19a332c_819835AC_S_819835AC_6 *state2_stage;
    u8 tile_x;
    u16 tile_counter;
    u8 tile_y;
    s32 tile_div;
    TileObject *state34_base;
    ObjectPosition *state34_move;
    ObjectPosition *state34_emit;
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

    (*(s16 *)&image_tint_update_count) = (s16) (((ovl_19a332c_819835AC_S_819835AC_10 *) &image_tint_update_count)->unk_00 + 1);
    for (history_index = 0; history_index >= 0; history_index--) {
        history = (ovl_19a332c_819835AC_S_819835AC_4 *) ((u8 *) effect + history_index * 8);
        history->unk_50 = history->unk_48;
    }
    owner_ref = effect->parent_link;
    effect->previous_x = motion->x.half.unk_02.u16;
    effect->previous_y = motion->y.half.unk_06.u16;
    effect->previous_z = motion->z.half.unk_0A.u16;
    if (owner_ref == 0) {
        state = effect->phase;
        switch (state) {
        case 0:
            resolve_record_orientation_or_fallback(*(s32 *)((((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                + ((ovl_19a332c_819835AC_S_819835AC_5 *) ((ovl_19a332c_819835AC_S_819835AC_11 *) &dungeon_actor_ring_anchor)->unk_00)->unk_2A.s16 + 0x100) >> 7) & 0x1C)
                + actor_direction_sprites), &reference_tile_object.frame_entry, (u8 *) effect + 0x28, 0);
            sin_x = rcos(((ovl_19a332c_819835AC_S_819835AC_5 *) (*(void **)&dungeon_actor_ring_anchor))->unk_2A.s16);
            cos_x = rcos(((ovl_19a332c_819835AC_S_819835AC_5 *) (*(void **)&dungeon_actor_ring_anchor))->unk_2A.s16 - 0x400);
            state0_move = &view_reference_entity;
            sin_x >>= 4;
            state0_delta_x = ((u16)state0_move->x.w.i);
            cos_x >>= 4;
            state0_delta_x -= sin_x;
            state0_delta_x += cos_x;
            state0_actor = ((ovl_19a332c_819835AC_S_819835AC_11 *) &dungeon_actor_ring_anchor)->unk_00;
            effect->target_x.u16 += state0_delta_x;
            sin_y = rsin(state0_actor->unk_2A.s16);
            cos_y = rsin(((ovl_19a332c_819835AC_S_819835AC_5 *) (*(void **)&dungeon_actor_ring_anchor))->unk_2A.s16 - 0x400);
            sin_y_shift = sin_y >> 4;
            cos_y >>= 4;
            step_y = ((u16)state0_move->y.w.i);
            coord_delta = effect->target_y.u16;
            step_y -= sin_y_shift;
            step_y += cos_y;
            state0_height_actor = ((ovl_19a332c_819835AC_S_819835AC_11 *) &dungeon_actor_ring_anchor)->unk_00;
            coord_delta += step_y;
            effect->target_y.u16 = (u16) coord_delta;
            coord_delta = effect->target_z.u16;
            step_y = state0_height_actor->unk_88.u16;
            approach_frames = 0x10U;
            coord_delta -= 0x50;
            step_y += coord_delta;
            effect->target_z.u16 = (u16) step_y;
            effect->timer.u16 = approach_frames;
            height_numerator_2 = (effect->target_z.s16 - motion->z.half.unk_0A.s16) << 0x10;
            height_frames = 16;
            motion->velocity_z.word = height_numerator_2 / height_frames;
            effect->phase = (s16) ((u16) effect->phase + 1);
        case 1:
            aim_angle = (s16)calculate_planar_heading((s16) motion->x.half.unk_02.u16, (s16) motion->y.half.unk_06.u16,
                (s16) effect->target_x.u16, (s16) effect->target_y.u16);
            approach_heading = effect->heading;
            if (approach_heading & 0x800) {
                approach_signed_angle = approach_heading | 0xF800;
            } else {
                approach_signed_angle = approach_heading & 0x7FF;
            }
            effect->heading = approach_signed_angle;
            if (aim_angle & 0x800) {
                angle_mask = ~0x7FF;
                normalized_angle = aim_angle | angle_mask;
            } else {
                normalized_angle = aim_angle & 0x7FF;
            }
            aim_angle = normalized_angle;
            approach_wrap_gap = (s16) effect->heading - aim_angle;
            if (approach_wrap_gap < 0) {
                approach_wrap_gap = 0 - approach_wrap_gap;
            }
            if (approach_wrap_gap >= 0x801) {
                effect->heading = (u16) ((aim_angle & ~0xFFF) | (effect->heading & 0xFFF));
            }
            approach_angle = (s16) effect->heading;
            approach_turn_gap = aim_angle - approach_angle;
            if (approach_turn_gap < 0) {
                approach_turn_gap = 0 - approach_turn_gap;
            }
            if (approach_turn_gap >= 0x81) {
                if (effect->turn_direction != 0) {
                    approach_next_angle = approach_angle + 0x80;
                } else {
                    approach_next_angle = approach_angle - 0x80;
                }
                effect->heading = approach_next_angle;
            } else {
                effect->heading = aim_angle;
            }
            motion->velocity_x.word = (s32) (rcos((s16) effect->heading) << 8);
            motion->velocity_y.word = (s32) (rsin((s16) effect->heading) << 8);
            approach_ticks = effect->timer.u16 - 1;
            effect->timer.u16 = approach_ticks;
            if ((approach_ticks << 0x10) <= 0) {
                motion->z.half.unk_0A.u16 = effect->target_z.u16;
                effect->timer.u16 = 0U;
                motion->velocity_z.word = 0;
            }
            state1_global = ((ovl_19a332c_819835AC_S_819835AC_11 *) &primary_actor_record)->unk_00;
            state1_global->unk_96 = 2;
            boost_speed_x = motion->x.word;
            coord_delta = motion->velocity_x.word;
            step_y = motion->velocity_y.word;
            step_z = motion->velocity_z.word;
            boost_speed_x += coord_delta;
            motion->x.word = boost_speed_x;
            boost_speed_x = motion->y.word;
            coord_delta = motion->z.word;
            boost_speed_x += step_y;
            motion->y.word = boost_speed_x;
            boost_speed_x = motion->x.half.unk_02.s16;
            coord_delta += step_z;
            motion->z.word = coord_delta;
            coord_delta = effect->target_x.s16;
            boost_speed_x -= coord_delta;
            if (__builtin_abs(boost_speed_x) >= 0x40) {
                break;
            }
            approach_gap_y = motion->y.half.unk_06.s16;
            target_coord = effect->target_y.s16;
            approach_gap_y -= target_coord;
            if (__builtin_abs(approach_gap_y) >= 0x40) {
                break;
            }
            approach_gap_z = motion->z.half.unk_0A.s16;
            target_coord = effect->target_z.s16;
            approach_gap_z -= target_coord;
            if (__builtin_abs(approach_gap_z) >= 0x40) {
                break;
            }
            resolve_record_orientation_or_fallback(*(s32 *)((((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                + ((ovl_19a332c_819835AC_S_819835AC_5 *) ((ovl_19a332c_819835AC_S_819835AC_11 *) &dungeon_actor_ring_anchor)->unk_00)->unk_2A.s16 + 0x100) >> 7) & 0x1C)
                + actor_direction_sprites), &reference_tile_object.frame_entry, (u8 *) effect + 0x28, 0);
            state1_move = &view_reference_entity;
            effect->target_x.u16 += (u16)state1_move->x.w.i;
            state1_actor = ((ovl_19a332c_819835AC_S_819835AC_11 *) &primary_actor_record)->unk_00;
            effect->target_y.u16 += (u16)state1_move->y.w.i;
            coord_delta = effect->target_z.u16;
            boost_speed_x = ((ovl_19a332c_819835AC_S_819835AC_5 *) ((ovl_19a332c_819835AC_S_819835AC_11 *) &dungeon_actor_ring_anchor)->unk_00)->unk_88.u16;
            coord_delta -= 0x50;
            boost_speed_x += coord_delta;
            effect->target_z.u16 = boost_speed_x;
            state1_actor->unk_A6 = state1_actor->unk_A6 - 1;
            effect->phase = (s16) ((u16) effect->phase + 1);
            break;
        case 2:
            aim_angle = (s16)calculate_planar_heading((s16) motion->x.half.unk_02.u16, (s16) motion->y.half.unk_06.u16,
                (s16) effect->target_x.u16, (s16) effect->target_y.u16);
            travel_heading = effect->heading;
            if (travel_heading & 0x800) {
                travel_signed_angle = travel_heading | 0xF800;
            } else {
                travel_signed_angle = travel_heading & 0x7FF;
            }
            effect->heading = travel_signed_angle;
            if (aim_angle & 0x800) {
                angle_mask = ~0x7FF;
                normalized_angle = aim_angle | angle_mask;
            } else {
                normalized_angle = aim_angle & 0x7FF;
            }
            aim_angle = normalized_angle;
            travel_wrap_gap = (s16) effect->heading - aim_angle;
            if (travel_wrap_gap < 0) {
                travel_wrap_gap = 0 - travel_wrap_gap;
            }
            if (travel_wrap_gap >= 0x801) {
                effect->heading = (u16) ((aim_angle & ~0xFFF) | (effect->heading & 0xFFF));
            }
            travel_angle = (s16) effect->heading;
            travel_turn_gap = aim_angle - travel_angle;
            if (travel_turn_gap < 0) {
                travel_turn_gap = 0 - travel_turn_gap;
            }
            if (travel_turn_gap >= 0x81) {
                if (effect->turn_direction != 0) {
                    travel_next_angle = travel_angle + 0x80;
                } else {
                    travel_next_angle = travel_angle - 0x80;
                }
                effect->heading = travel_next_angle;
            } else {
                effect->heading = aim_angle;
            }
            motion->velocity_x.word = (s32) (rcos((s16) effect->heading) << 8);
            motion->velocity_y.word = (s32) (rsin((s16) effect->heading) << 8);
            travel_ticks = effect->timer.u16 - 1;
            effect->timer.u16 = travel_ticks;
            if ((travel_ticks << 0x10) <= 0) {
                motion->z.half.unk_0A.u16 = effect->target_z.u16;
                effect->timer.u16 = 0U;
                motion->velocity_z.word = 0;
            }
            boost_speed_x = motion->x.word;
            coord_delta = motion->velocity_x.word;
            step_y = motion->velocity_y.word;
            step_z = motion->velocity_z.word;
            boost_speed_x += coord_delta;
            motion->x.word = boost_speed_x;
            boost_speed_x = motion->y.word;
            coord_delta = motion->z.word;
            boost_speed_x += step_y;
            coord_delta += step_z;
            motion->y.word = boost_speed_x;
            state2_stage = (*(void **)((u8 *)&primary_actor_record + 0));
            motion->z.word = coord_delta;
            state2_stage->unk_96 = 2;
            travel_gap_x = motion->x.half.unk_02.s16;
            target_coord = effect->target_x.s16;
            travel_gap_x -= target_coord;
            if (travel_gap_x < 0) {
                travel_gap_x = 0 - travel_gap_x;
            }
            if (travel_gap_x >= 0x20) {
                break;
            }
            travel_gap_y = motion->y.half.unk_06.s16;
            target_coord = effect->target_y.s16;
            travel_gap_y -= target_coord;
            if (travel_gap_y < 0) {
                travel_gap_y = 0 - travel_gap_y;
            }
            if (travel_gap_y >= 0x20) {
                break;
            }
            effect->timer.u16 = 4U;
            state2_actor = ((ovl_19a332c_819835AC_S_819835AC_11 *) &dungeon_actor_ring_anchor)->unk_00;
            effect->phase = (s16) ((u16) effect->phase + 1);
            ((ovl_19a332c_819835AC_S_819835AC_6 *) ((ovl_19a332c_819835AC_S_819835AC_11 *) &primary_actor_record)->unk_00)->unk_96 = 0;
            effect->heading = (u16) state2_actor->unk_2A.s16;
            state2_angle = state2_actor->unk_2A.u16;
            curved_trail_sample_count = 0;
            effect->attack_direction = (u16) ((state2_angle >> 9) & 7);
            break;
        case 3:
        case 4:
            state34_base = &reference_tile_object;
            if (resolve_record_orientation_or_fallback(state34_base->sprite_source, state34_base, &emit_offset, 0) != 0) {
                if (effect->phase == 3) {
                    state34_move = &view_reference_entity;
                    spawn_blinking_sprite_flash(state34_move->x.w.i + emit_offset.x, state34_move->y.w.i + emit_offset.y,
                        state34_move->z.w.i + emit_offset.z);
                    effect->phase = (s16) ((u16) effect->phase + 1);
                }
                state34_emit = &view_reference_entity;
                spawn_effect_actor_or_curved_trail((s16) (((u16)state34_emit->x.w.i) + (u16) emit_offset.x),
                    (s16) (((u16)state34_emit->y.w.i) + (u16) emit_offset.y),
                    (s16) (((u16)state34_emit->z.w.i) + (u16) emit_offset.z),
                    ((ovl_19a332c_819835AC_S_819835AC_5 *) ((ovl_19a332c_819835AC_S_819835AC_11 *) &dungeon_actor_ring_anchor)->unk_00)->unk_2A.s16, 0);
            }
            motion->velocity_x.word = (s32) (rcos((s16) effect->heading) << 8);
            motion->velocity_y.word = (s32) (rsin((s16) effect->heading) << 8);
            motion->velocity_z.half.unk_16 = 0x16;
            rise_speed = motion->velocity_z.word;
            motion->x.word = (s32) (motion->x.word + motion->velocity_x.word);
            motion->y.word = (s32) (motion->y.word + motion->velocity_y.word);
            motion->z.word = (s32) (motion->z.word + motion->velocity_z.word);
            if ((s16) motion->z.half.unk_0A.u16 > ((ovl_19a332c_819835AC_S_819835AC_5 *) (*(void **)((u8 *)&dungeon_actor_ring_anchor
                + 0)))->unk_88.s16) {
                motion->z.half.unk_0A.u16 =
                    (u16) ((ovl_19a332c_819835AC_S_819835AC_5 *) ((ovl_19a332c_819835AC_S_819835AC_11 *) &dungeon_actor_ring_anchor)->unk_00)->unk_88.s16;
            }
            launch_ticks = effect->timer.u16 - 1;
            effect->timer.u16 = launch_ticks;
            if ((launch_ticks << 0x10) > 0) {
                break;
            }
            tile_base = &reference_tile_object;
            tile_coord = tile_base->tile_position.parts.tile_x;
            tile_call_arg = 0x300;
            effect->tile_x = (s16) tile_coord;
            effect->previous_tile_x = (u8) tile_coord;
            tile_coord = tile_base->tile_position.parts.tile_y;
            effect->phase = 5;
            effect->tiles_left = 3U;
            effect->timer.u16 = 0U;
            effect->tile_y = (s16) tile_coord;
            effect->previous_tile_y = (u8) tile_coord;
            play_sound_if_enabled(tile_call_arg, rise_speed);
            break;
        case 5:
            motion->velocity_x.word = (s32) (rcos((s16) effect->heading) << 8);
            motion->velocity_y.word = (s32) (rsin((s16) effect->heading) << 8);
            motion->velocity_z.word = 0;
            motion->x.word = (s32) (motion->x.word + motion->velocity_x.word);
            world_x = motion->x.half.unk_02.s16;
            motion->y.word = (s32) (motion->y.word + motion->velocity_y.word);
            motion->z.word = (s32) (motion->z.word + motion->velocity_z.word);
            if (world_x < 0) {
                world_x += 0x3F;
            }
            tile_div = world_x >> 6;
            effect->tile_x = (s16) tile_div;
            world_y = motion->y.half.unk_06.s16;
            next_tile_y = (world_y / 64);
            effect->tile_y = (s16) next_tile_y;
            if (effect->previous_tile_x == effect->tile_x) {
                if (effect->previous_tile_y == next_tile_y) {
                    break;
                }
            }
            hit_actor = ((ovl_19a332c_819835AC_S_819835AC_11 *) &primary_actor_record)->unk_00;
            hit_origin = (u8 *)(hit_actor);
            coord_delta = hit_actor->unk_5C;
            hit_actor = coord_delta + 0x20;
            if (hit_actor != (void *)hit_origin) {
                do {
                    actor_data = ((ObjectNodeHeader *)((u8 *)hit_actor - 0x20))->sprite;
                    if ((actor_data->unk_24 == effect->tile_x) &&
                        (actor_data->unk_25 == effect->tile_y)) {
                        hit_height_gap = hit_actor->unk_88;
                        target_coord = motion->z.half.unk_0A.s16;
                        hit_height_gap -= target_coord;
                        if (hit_height_gap < 0) {
                            hit_height_gap = -hit_height_gap;
                        }
                        actor_data = (u8 *) hit_actor - 0x20;
                        if ((hit_height_gap < 0x80) && !(actor_data->unk_1E & 0x2000)) {
                            apply_attack_power_and_element_effects(hit_actor, 0xC, tint_transition_kind, 0xA, (s32) (s16) (effect->attack_direction << 9),
                                tint_transition_source, 2);
                            related_motion = ((ObjectNodeHeader *)((u8 *)hit_actor - 0x20))->position;
                            spawn_thirty_two_angled_particles(related_motion->x.w.i,
                                related_motion->y.w.i, related_motion->z.w.i,
                                (s16) effect->heading, (rand() & 3) | 4);
                            actor_data->unk_1E = (u16) (actor_data->unk_1E | 0x2000);
                        }
                    }
                    coord_delta = hit_actor->unk_5C;
                    hit_actor = coord_delta + 0x20;
                } while (hit_actor != ((ovl_19a332c_819835AC_S_819835AC_11 *) &primary_actor_record)->unk_00);
            }
            tile_x = (u8) effect->tile_x;
            tile_counter = effect->tiles_left;
            tile_y = (u8) effect->tile_y;
            tile_counter -= 1;
            effect->tiles_left = tile_counter;
            effect->previous_tile_x = tile_x;
            effect->previous_tile_y = tile_y;
            if ((tile_counter << 0x10) > 0) {
                break;
            }
            effect->phase_counter = (u16) ((rand() & 0x1F) + 0x10);
            effect->target = 0;
            effect->phase = (s16) ((u16) effect->phase + 1);
            break;
        case 6:
            target = effect->target;
            if (target != 0) {
                related_motion = ((ObjectNodeHeader *)((u8 *)target - 0x20))->position;
                aim_angle = (s16)calculate_planar_heading((s16) motion->x.half.unk_02.u16, (s16) motion->y.half.unk_06.u16,
                    related_motion->x.w.i, related_motion->y.w.i);
                homing_heading = effect->heading;
                if (homing_heading & 0x800) {
                    homing_signed_angle = homing_heading | 0xF800;
                } else {
                    homing_signed_angle = homing_heading & 0x7FF;
                }
                effect->heading = homing_signed_angle;
                if (aim_angle & 0x800) {
                    angle_mask = ~0x7FF;
                    normalized_angle = aim_angle | angle_mask;
                } else {
                    normalized_angle = aim_angle & 0x7FF;
                }
                aim_angle = normalized_angle;
                homing_wrap_gap = (s16) effect->heading - aim_angle;
                if (homing_wrap_gap < 0) {
                    homing_wrap_gap = 0 - homing_wrap_gap;
                }
                if (homing_wrap_gap >= 0x801) {
                    effect->heading = (u16) ((aim_angle & ~0xFFF) | (effect->heading & 0xFFF));
                }
                aim_ticks = effect->aim_timer - 1;
                effect->aim_timer = aim_ticks;
                if ((aim_ticks << 0x10) <= 0) {
                    effect->aim_timer = 0x1EU;
                    effect->heading = aim_angle;
                }
                homing_angle = (s16) effect->heading;
                homing_turn_gap = aim_angle - homing_angle;
                if (homing_turn_gap < 0) {
                    homing_turn_gap = 0 - homing_turn_gap;
                }
                if (homing_turn_gap >= 0x81) {
                    if (effect->turn_direction != 0) {
                        homing_next_angle = homing_angle + 0x80;
                    } else {
                        homing_next_angle = homing_angle - 0x80;
                    }
                    effect->heading = homing_next_angle;
                } else {
                    effect->heading = aim_angle;
                }
                state6_timer_signed = effect->timer.s16;

                state6_timer = effect->timer.u16;
                if (state6_timer_signed != 0) {
                    state6_next = state6_timer - 1;
                    effect->timer.u16 = state6_next;
                    if ((state6_next << 0x10) == 0) {
                        state6_height = (u16)related_motion->z.w.i;
                        motion->velocity_z.word = 0;
                        state6_height -= 0x40;
                        motion->z.half.unk_0A.u16 = state6_height;
                        effect->phase_counter = 0U;
                    }
                } else {
                    bob_phase = effect->phase_counter + 1;
                    state6_spin_arg = (s32) (bob_phase << 0x10);

                    state6_spin_arg >>= 9;
                    effect->phase_counter = bob_phase;
                    motion->velocity_z.half.unk_16 = (s16) (rsin(state6_spin_arg) >> 9);
                }
                target_gap_x = motion->x.half.unk_02.s16;
                target_coord = related_motion->x.w.i;
                target_gap_x -= target_coord;
                if (target_gap_x < 0) {
                    target_gap_x = 0 - target_gap_x;
                }
                if (target_gap_x < 0x20) {
                    target_gap_y = motion->y.half.unk_06.s16;
                    target_coord = related_motion->y.w.i;
                    target_gap_y -= target_coord;
                    if (target_gap_y < 0) {
                        target_gap_y = 0 - target_gap_y;
                    }
                    if (target_gap_y < 0x20) {
                        actor_data = effect->target - 0x20;
                        apply_attack_power_and_element_effects(effect->target, 0xC, tint_transition_kind, 0xA, (s32) (s16) (effect->attack_direction << 9),
                            tint_transition_source, 2);
                        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                        spawn_thirty_two_angled_particles(related_motion->x.w.i, related_motion->y.w.i,
                            (s16) (u16)related_motion->z.w.i, (s16) effect->heading,
                            (rand() & 3) | 4);
                        actor_data->unk_1E = (u16) (actor_data->unk_1E | 0x2000);
                        effect->target = 0;
                        effect->phase_counter = (u16) ((rand() & 0x1F) + 0x10);
                    }
                }
                motion->velocity_x.word = rcos((s16) effect->heading) << 8;
                motion->velocity_y.word = rsin((s16) effect->heading) << 8;

                if ((s16) effect->heading == aim_angle) {
                    motion->velocity_x.word += motion->velocity_x.word >> 1;
                    motion->velocity_y.word += motion->velocity_y.word >> 1;
                }
            } else {
                motion->velocity_z.word = 0;
                search_ticks = effect->phase_counter - 1;
                effect->phase_counter = search_ticks;
                if ((search_ticks << 0x10) <= 0) {
                    new_target = find_eligible_nearby_entity(&reference_tile_object.frame_entry);
                    effect->target = new_target;
                    if (new_target == 0) {
                        effect->phase = 0x10;
                        effect->phase_counter = 8U;
                    } else {
                        related_motion = ((ObjectNodeHeader *)((u8 *)new_target - 0x20))->position;
                        effect->timer.u16 = 0x10U;
                        state6_target_base = motion->z.half.unk_0A.s16;
                        height_value = related_motion->z.w.i;
                        state6_target_base += 0x40;
                        height_numerator = (height_value - state6_target_base) << 0x10;
                        height_frames = 16;
                        motion->velocity_z.word = height_numerator / height_frames;
                        effect->aim_timer = 0x3CU;
                    }
                } else {
                    effect->heading = (u16) (effect->heading + 0x80);
                }
                motion->velocity_x.word = (s32) (rcos((s16) effect->heading) << 8);
                motion->velocity_y.word = (s32) (rsin((s16) effect->heading) << 8);
            }
            motion->x.word = (s32) (motion->x.word + motion->velocity_x.word);
            motion->y.word = (s32) (motion->y.word + motion->velocity_y.word);
            motion->z.word = (s32) (motion->z.word + motion->velocity_z.word);
            break;
        case 16:
            fade_speed_x = motion->velocity_x.word;
            fade_speed_y = motion->velocity_y.word;
            motion->velocity_x.word = (s32) (fade_speed_x - (fade_speed_x >> 3));
            motion->velocity_y.word = (s32) (fade_speed_y - (fade_speed_y >> 3));
            if ((effect->unk_3E - 0x10) < (s16) motion->z.half.unk_0A.u16) {
                motion->z.half.unk_0A.u16 = (u16) ((u16) effect->unk_3E - 0x10);
            }
            motion->x.word = (s32) (motion->x.word + motion->velocity_x.word);
            motion->y.word = (s32) (motion->y.word + motion->velocity_y.word);
            motion->z.word = (s32) (motion->z.word + motion->velocity_z.word);
            fade_red = visual->color.half.unk_0C;
            visual->color.half.unk_0C = (u8) (fade_red - ((s32) fade_red / (s16) effect->phase_counter));
            fade_green = visual->color.half.unk_0D;
            visual->color.half.unk_0D = (u8) (fade_green - ((s32) fade_green / (s16) effect->phase_counter));
            fade_blue = visual->color.half.unk_0E;
            visual->color.half.unk_0E = (u8) (fade_blue - ((s32) fade_blue / (s16) effect->phase_counter));
            fade_ticks = effect->phase_counter - 1;
            effect->phase_counter = fade_ticks;
            if ((fade_ticks << 0x10) > 0) {
                return;
            }
            tint_transition_image_pending = 0;
            do {
                ((ovl_19a332c_819835AC_S_819835AC_8 *) ((u8 *) effect - 0x20))->unk_1E = (u16) (((ovl_19a332c_819835AC_S_819835AC_8 *) ((u8 *) effect - 0x20))->unk_1E
                    | 0x8000);
                (*&object_flag_block.flags) = (s32) (object_flag_block.flags | 0x8000);
                return;
            } while (0);
        }
        visual->angle_z = (u16) ((s16)calculate_planar_heading(0, 0, motion->velocity_x.half.unk_0E, motion->velocity_y.half.unk_12) - 0x400);
        boost_speed_x = motion->velocity_z.half.unk_16;
        step_y = (visual->scale_x);
        coord_delta = visual->color.half.unk_0C;
        aim_angle = boost_speed_x * 4;
        boost_speed_x = aim_angle + 0x400;
        visual->angle_x = (u16) boost_speed_x;
        boost_speed_x = 0x2000;
        boost_speed_x -= step_y;
        boost_speed_x >>= 2;
        step_y += boost_speed_x;
        coord_delta += 8;
        visual->color.half.unk_0C = coord_delta;
        visual->scale_x = (u16) step_y;
        visual->unk_20 = (u16) step_y;
        visual->scale_y = (u16) step_y;
        coord_delta &= 0xFF;
        coord_delta = (u32)coord_delta < 0x81U;
        if (!coord_delta) {
            visual->color.word = 0x808080;
        } else {
            visual->color.half.unk_0D = (u8) (visual->color.half.unk_0D + 8);
            visual->color.half.unk_0E = (u8) (visual->color.half.unk_0E + 8);
        }
        inventory_reset_shared_state_mode_13((u8 *) effect - 0x20, motion, 8, 0x300);
        step_and_clamp_entry_index(visual, (u8 *) effect + 0x36, effect->min_frame, effect->max_frame);
        inventory_copy_and_sign_extend_record_fields(effect, visual->frame_entry);
        frame = visual->frame_index;
        if ((s8) frame == effect->max_frame) {
            frame_step = -1;
            effect->frame_step = frame_step;
        } else if ((s8) frame == effect->min_frame) {
            frame_step = 1;
            effect->frame_step = frame_step;
        }
        spawn_random_motion_particles((s16) motion->x.half.unk_02.u16, (s16) motion->y.half.unk_06.u16,
            (s16) motion->z.half.unk_0A.u16, (s16) effect->heading, D_80026BD4[(s8) visual->frame_index]);
        effect->update_count = (u16) (effect->update_count + 1);
        return;
    }
    owner_ptr = owner_ref | 0x80000000;
    if (((ovl_19a332c_819835AC_S_819835AC_8 *) owner_ptr)->unk_1E & 0x8000) {

        ((ovl_19a332c_819835AC_S_819835AC_8 *) ((u8 *) effect - 0x20))->unk_1E = (u16) (((ovl_19a332c_819835AC_S_819835AC_8 *) ((u8 *) effect - 0x20))->unk_1E
            | 0x8000);
        (*&object_flag_block.flags) = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        return;
    }
    actor_data = ((ovl_19a332c_819835AC_S_819835AC_8 *) owner_ptr)->unk_0C;
    related_motion = ((ovl_19a332c_819835AC_S_819835AC_8 *) owner_ptr)->unk_08;
    if (owner_ref & 0x80000000) {
        owner_state = owner_ptr + 0x20;
        visual->angle_z = (u16) ((s16)calculate_planar_heading((s16) motion->x.half.unk_02.u16,
            (s16) motion->y.half.unk_06.u16, related_motion->x.w.i,
            related_motion->y.w.i) - 0x400);
        alternate_delta = related_motion->z.w.i;
        alternate_value = motion->z.half.unk_0A.s16;
        alternate_delta -= alternate_value;
        alternate_scale = alternate_delta << 2;
        alternate_scale += alternate_delta;
        aim_angle = alternate_scale << 1;
        alternate_value = aim_angle + 0x400;
        visual->angle_x = (u16) alternate_value;
        visual->flags = (u16) actor_data->unk_14;
        motion->x.half.unk_02.u16 = (u16) owner_state->unk_50;
        motion->y.half.unk_06.u16 = (u16) owner_state->unk_52;
        motion->z.half.unk_0A.u16 = (u16) owner_state->unk_54;
    } else {
        motion->x.half.unk_02.u16 = (u16) related_motion->x.w.i;
        motion->y.half.unk_06.u16 = (u16) related_motion->y.w.i;
        motion->z.half.unk_0A.u16 = (u16) related_motion->z.w.i;
        visual->angle_x = (u16) actor_data->unk_16;
        visual->angle_y = (u16) actor_data->unk_18;
        visual->angle_z = (u16) actor_data->unk_1A;
        visual->flags = (u16) actor_data->unk_14;
    }
    visual->scale_x = actor_data->unk_1C;
    visual->scale_y = actor_data->unk_1E;
    visual->unk_20 = (u16) actor_data->unk_20;
    visual->color.word = actor_data->unk_0C;
    if (D_80026BC8[effect->part_index] != 0) {
        inventory_set_object_entry_address(visual, actor_data->unk_04);
        inventory_copy_and_sign_extend_record_fields(effect, visual->frame_entry);
    }
    effect->update_count = (u16) (effect->update_count + 1);
    return;
}

/* Creates nine linked homing-effect parts with shared parent links, animation frames, and position
   histories. */
void *create_nine_linked_effects(s32 x, s32 y, s32 z, s32 angle)
{
    ovl_19a332c_81984754_Object *objects[9];
    u16 spawn_x;
    u16 spawn_y;
    u16 spawn_z;
    s32 spawn_angle;
    ObjectPosition *target_pos;
    ovl_19a332c_81984754_Object **object_base;
    ovl_19a332c_81984754_Object **object_slot;
    ObjectPosition *pos;
    SpriteFrameState *part;
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
    target_pos = &view_reference_entity;
    object_slot = object_base;
    do {
        allocation_page = (u8 *)0x80080000;
        if (object_index != 0) {
            prev_object = object_slot[-1];
        } else {
            prev_object = (ovl_19a332c_81984754_Object *)((u8 *)(&scene_object_list_anchor));
        }
        *object_slot = allocate_list_node(2, prev_object);
        (*object_slot)->state = (void (*)(void *))(void *)update_homing_effect_and_attached_copies;
        register_node(*object_slot, draw_linked_model_chain);

        pos = (*object_slot)->pos;
        pos->x.w.i = spawn_x;
        pos->y.w.i = spawn_y;
        pos->z.w.i = spawn_z;

        part = (*object_slot)->part;
        part->angle_x = 0x400;
        part->angle_z = spawn_angle - 0x400;
        part->source = D_80026B2C + (object_index * 0x10);
        part->tpage_abr = 0x60;
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

        target_angle = calculate_planar_heading(pos->x.w.i, pos->y.w.i,
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
            entity->history[history_index].x = pos->x.w.i;
            entity->history[history_index].y = pos->y.w.i;
            entity->history[history_index].z = pos->z.w.i;
            history_index--;
        } while (history_index >= 0);

        inventory_select_entry_and_reset_object(part, 0);
        inventory_copy_and_sign_extend_record_fields(entity, part->unk_00);
        prev_entity = entity;
        object_slot++;
        object_index++;
    } while (object_index < 9);

    return objects[0];
}

/*
 * Copies the leading words, then widens the source halfword and three following bytes into the
 * destination fields.
 */
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

/* Resets the entry substate, clears flags 0x6000, and selects the indexed 0x16-byte animation entry. */
void inventory_select_entry_and_reset_object(ovl_19a332c_81984AB0_S_81984AB0_0 *object, s16 entry_index) {
    s32 entry_base;

    object->unk_04 = entry_index;
    object->unk_05 = 0;
    entry_base = ((ovl_19a332c_81984AB0_S_81984AB0_2 *)(((ovl_19a332c_81984AB0_S_81984AB0_1 *)object)->unk_08))->unk_0C;
    object->unk_14 = (u16) (object->unk_14 & 0x9FFF);
    object->unk_00 = (s32) (entry_base + (entry_index * 0x16));
}

/* Points to the current 22-byte entry, steps its index, and clamps the new index while recording
   whether it hit a limit. */
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

/* Sets the current animation-entry address using the owner table base and a 0x16-byte stride. */
void inventory_set_object_entry_address(ovl_19a332c_81984BC0_S_81984BC0_0 *object, s16 entry_index) {
    object->unk_00 = (s32) (((ovl_19a332c_81984BC0_S_81984BC0_2 *)(((ovl_19a332c_81984BC0_S_81984BC0_1 *)object)->unk_08))->unk_0C + (entry_index * 0x16));
}

/* Clears flag 0x2000 in every object header in the circular actor list except the primary actor's header. */
void inventory_clear_circular_list_flag_2000(void *unused_actor)
{
    void *link;
    ObjectNodeHeader *object;
    void *head;
    s32 link_value;
    s32 next;

    link = primary_actor_record;
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
        next = object->flags;
        next &= 0xDFFF;
        object->flags = next;
        link_value = ((ovl_19a332c_81984BF0_S_81984BF0_0 *)link)->unk_5C;
        link = (void *)(link_value + 0x20);
    } while (link != head);
}

/* Finds an eligible linked actor by matching its owner's +0x26 to the source, or by a four-tile
   distance limit. */
void *find_eligible_nearby_entity(void *source_entity)
{
    void *node;
    s16 owner_limit;
    s32 initial_limit;
    void *next_link;
    s8 entity_floor;
    SpriteFrameState *owner;

    node = primary_actor_record;
    initial_limit = 0x100;
    if (((ovl_19a332c_81984C44_S_81984C44_1 *)source_entity)->unk_26 < 0) {
        initial_limit = 4;
    }
    next_link = ((ovl_19a332c_81984C44_S_81984C44_2 *)node)->unk_5C;
    node = (u8 *)next_link + 0x20;
    if (node != primary_actor_record) {
        do {
            void *entry_link;
            if (((check_entity_interaction_compatibility(primary_actor_record, node) << 16) != 0) &&
                ((check_entity_eligibility(node) << 16) != 0) &&
                !(((ObjectNodeHeader *)((u8 *)node - 0x20))->flags & 0x2000)) {
                entity_floor = ((ovl_19a332c_81984C44_S_81984C44_1 *)source_entity)->unk_26;
                owner = ((ObjectNodeHeader *)((u8 *)node - 0x20))->sprite;
                if (entity_floor >= 0) {
                    if (entity_floor == (s8)owner->room_index) {
                        return node;
                    }
                } else {
                    owner_limit = initial_limit;
                    if (get_tile_chebyshev_distance(owner, source_entity) < owner_limit) {
                        return node;
                    }
                }
            }
            entry_link = ((ovl_19a332c_81984C44_S_81984C44_2 *)node)->unk_5C;
            node = (u8 *)entry_link + 0x20;
        } while (node != primary_actor_record);
    }
    return 0;
}

/* Eases the camera toward its tracked object, blends the vertical view offset, and damps horizontal
   view offsets. */
void clear_object_buffer_and_state(void *tracker) {
    s16 blend_ticks;
    s16 next_ticks;
    ovl_19a332c_81984D4C_S_81984D4C_2 *target;
    GameView *state;
    ovl_19a332c_81984D4C_S_81984D4C_1 *timer;
    ovl_19a332c_81984D4C_S_81984D4C_3 *z_pending;

    blend_ticks = (*(s16 *)((u8 *)tracker + 0x24));
    state = &g_game_work.view;
    if (blend_ticks > 0) {
        state->view_offset.parts.view_offset_z = (u16) ((u16)state->view_offset.parts.view_offset_z) + ((s32) ((*(s16 *)((u8 *)tracker + 0x26))
            - state->view_offset.parts.view_offset_z) / blend_ticks);
    }
    next_ticks = (u16) (*(s16 *)((u8 *)tracker + 0x24)) - 1;
    (*(s16 *)((u8 *)tracker + 0x24)) = next_ticks;
    if (next_ticks < -0x80) {
        (*(s16 *)((u8 *)tracker + 0x24)) = -0x80;
    }
    timer = (ovl_19a332c_81984D4C_S_81984D4C_1 *)camera_transition_timer;
    if (timer->unk_00.u != 0) {
        timer->unk_00.s = (s8) (timer->unk_00.u - 1);
    }
    (*(u16 *)((u8 *)tracker + 4)) = (u16) ((ovl_19a332c_81984D4C_S_81984D4C_4 *)((*(void **)((u8 *)tracker + 0xC))))->unk_02;
    target = (*(void **)((u8 *)tracker + 0xC));
    (*(u16 *)((u8 *)tracker + 6)) = (u16) target->unk_06;
    (*(u16 *)((u8 *)tracker + 8)) = (u16) target->unk_0A;
    state->camera_position.parts.camera_position_x = (u16) ((u16)state->camera_position.parts.camera_position_x) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 4)) - state->camera_position.parts.camera_position_x) >> 2);
    state->camera_position.parts.camera_position_y = (u16) ((u16)state->camera_position.parts.camera_position_y) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 6)) - state->camera_position.parts.camera_position_y) >> 2);
    z_pending = (ovl_19a332c_81984D4C_S_81984D4C_3 *)D_80026BE4;
    if (z_pending->unk_00.u != 0) {
        state->camera_position.parts.camera_position_z = (u16) ((u16)state->camera_position.parts.camera_position_z) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 8)) - state->camera_position.parts.camera_position_z)
            >> 2);
    }
    z_pending->unk_00.s = (s8) (state->camera_position.parts.camera_position_z != (s16) (*(u16 *)((u8 *)tracker + 8)));
    state->view_offset.parts.view_offset_x = (u16) ((s32) (((u16)state->view_offset.parts.view_offset_x) << 0x10) >> 0x12);
    state->view_offset.parts.view_offset_y = (u16) ((s32) (((u16)state->view_offset.parts.view_offset_y) << 0x10) >> 0x12);
}

/*
 * Sets camera tracking mode 13, its target and timing, installs the tracking callback, and returns
 * change flags.
 *
 * MECHANISM: Frameless leaf; tracker stays in a1 and the 0x80083178 view base in a2 across the
 * CFG. The tracker+0xC pointer is read a second time, after the first-use load and the store to
 * tracker+4: the u16 store invalidates the earlier read (cse invalidate_memory), giving retail's
 * paired lw v0/v1 and keeping v1 live for offsets 6/0xA.
 */
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
        camera_transition_timer[0] = saved_value;
    }
    substate->unkDC = value;
    return change_flags;
}
