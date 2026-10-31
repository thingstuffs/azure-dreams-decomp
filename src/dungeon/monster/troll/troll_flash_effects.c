#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
/* Troll color flashes, moving effects, attachments, and actor creation. */
#include "shared/entity.h"
#include "shared/object_node.h"
#include "dungeon/monster/troll/troll_flash_effects.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"

/* Fade the primitive color by one step and flag completion when the counter reaches zero. */
void update_stepped_rgb_flash(void *fade_state, void *unused, T_80170D40_S_80170D40_1 *primitive)
{
    u16 steps_left;
    u8 red;

    ((T_80170D40_S_80170D40_0 *)fade_state)->unk_02 = (u8)(((T_80170D40_S_80170D40_0 *)fade_state)->unk_02 - 0x40);
    red = ((T_80170D40_S_80170D40_0 *)fade_state)->unk_00 - 0x40;
    ((T_80170D40_S_80170D40_0 *)fade_state)->unk_00 = red;
    ((T_80170D40_S_80170D40_0 *)fade_state)->unk_01 = (u8)(((T_80170D40_S_80170D40_0 *)fade_state)->unk_01 - 0x40);
    primitive->unk_0C = red;
    primitive->unk_0D = ((T_80170D40_S_80170D40_0 *)fade_state)->unk_01;
    primitive->unk_0E = ((T_80170D40_S_80170D40_0 *)fade_state)->unk_02;
    steps_left = ((T_80170D40_S_80170D40_0 *)fade_state)->unk_18 - 1;
    ((T_80170D40_S_80170D40_0 *)fade_state)->unk_18 = steps_left;
    if ((steps_left << 0x10) <= 0) {
        ((T_80170D40_S_80170D40_0_pre *)fade_state)[-1].unk_00 = (u16)(((T_80170D40_S_80170D40_0_pre *)fade_state)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32)(object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}

/* Decrement the countdown, update three scaled output components, and flag completion. */
void update_normalized_gray_fade(void *countdownState, s32 unused, T_80170DC4_S_80170DC4_1 *output) {
    s32 scaledRemaining;
    u16 remainingCount;

    remainingCount = ((T_80170DC4_S_80170DC4_0 *)countdownState)->unk_96 - 1;
    scaledRemaining = (s32) ((s32) (remainingCount << 16) >> 9) / ((T_80170DC4_S_80170DC4_0 *)countdownState)->unk_9E;
    ((T_80170DC4_S_80170DC4_0 *)countdownState)->unk_96 = remainingCount;
    output->unk_0C = (s8) scaledRemaining;
    output->unk_0E = (s8) scaledRemaining;
    output->unk_0D = (s8) scaledRemaining;
    if ((s16) ((T_80170DC4_S_80170DC4_0 *)countdownState)->unk_96 <= 0) {
        ((T_80170DC4_S_80170DC4_0_pre *)countdownState)[-1].unk_00 = ((T_80170DC4_S_80170DC4_0_pre *)countdownState)[-1].unk_00 | 0x8000;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}

/* Advance the RGB fade toward black and set completion flags when it ends. */
void update_saved_rgb_fade(T_80170E2C_FadeState *fade, s32 unused, T_80170E2C_FadeOutput *output)
{
    s16 remaining;

    remaining = fade->remaining - 1;
    fade->remaining = remaining;
    output->red = (fade->red * remaining) / fade->divisor;
    output->green = (fade->green * (s16)fade->remaining) / fade->divisor;
    output->blue = (fade->blue * (s16)fade->remaining) / fade->divisor;

    if ((s16)fade->remaining <= 0) {
        *(u16 *)((u8 *)fade - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Update the effect transform, fade its color, and mark expiration when its timer runs out. */
void update_growing_rotating_flash(void *effect, s32 unused, void *visual) {
    u16 transform_value;
    u16 ticks_left;
    s8 intensity;

    transform_value = *(u16 *)((u8 *)visual + 0x1E) + 0x78;
    *(u16 *)((u8 *)visual + 0x1E) = transform_value;
    *(u16 *)((u8 *)visual + 0x1C) = transform_value;
    *(u16 *)((u8 *)visual + 0x1A) += 0x2BC;

    ticks_left = *(u16 *)((u8 *)effect + 0x18) - 1;
    *(u16 *)((u8 *)effect + 0x18) = ticks_left;
    if ((s16)ticks_left < 12) {
        intensity = ((s16)ticks_left << 7) / 12;
        *(s8 *)((u8 *)visual + 0xE) = intensity;
        *(s8 *)((u8 *)visual + 0xD) = intensity;
        *(s8 *)((u8 *)visual + 0xC) = intensity;
    }

    if (*(s16 *)((u8 *)effect + 0x18) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Updates effect motion, handles collisions, grows the sprite, and flags expiration. */
void update_growing_bouncing_effect(void *effect, void *position, SpriteFrameState *sprite)
{
    s32 height;
    u16 frame_count;
    u16 scale_x;
    u16 scale_y;
    u16 ticks_left;

    ((T_80170F94_S_80170F94_0 *)position)->unk_00.at00.v += ((T_80170F94_S_80170F94_1 *)effect)->unk_40;
    ((T_80170F94_S_80170F94_1 *)effect)->unk_40 += ((T_80170F94_S_80170F94_1 *)effect)->unk_4C;
    if (check_left_tile_and_center_height(((T_80170F94_S_80170F94_0 *)position)->unk_00.at02.v,
                      ((T_80170F94_S_80170F94_0 *)position)->unk_04.at02.v,
                      ((T_80170F94_S_80170F94_0 *)position)->unk_08.at02.v) << 16) {
        ((T_80170F94_S_80170F94_0 *)position)->unk_00.at00.v -= ((T_80170F94_S_80170F94_1 *)effect)->unk_40;
        ((T_80170F94_S_80170F94_1 *)effect)->unk_40 = 0;
        ((T_80170F94_S_80170F94_1 *)effect)->unk_4C = 0;
    }

    ((T_80170F94_S_80170F94_0 *)position)->unk_04.at00.v += ((T_80170F94_S_80170F94_1 *)effect)->unk_44;
    ((T_80170F94_S_80170F94_1 *)effect)->unk_44 += ((T_80170F94_S_80170F94_1 *)effect)->unk_50;
    if (check_left_tile_and_center_height(((T_80170F94_S_80170F94_0 *)position)->unk_00.at02.v,
                      ((T_80170F94_S_80170F94_0 *)position)->unk_04.at02.v,
                      ((T_80170F94_S_80170F94_0 *)position)->unk_08.at02.v) << 16) {
        ((T_80170F94_S_80170F94_0 *)position)->unk_04.at00.v -= ((T_80170F94_S_80170F94_1 *)effect)->unk_44;
        ((T_80170F94_S_80170F94_1 *)effect)->unk_44 = 0;
        ((T_80170F94_S_80170F94_1 *)effect)->unk_50 = 0;
    }

    ((T_80170F94_S_80170F94_0 *)position)->unk_08.at00.v += ((T_80170F94_S_80170F94_1 *)effect)->unk_48;
    ((T_80170F94_S_80170F94_1 *)effect)->unk_48 += ((T_80170F94_S_80170F94_1 *)effect)->unk_54;
    height = ((T_80170F94_S_80170F94_0 *)position)->unk_08.at02.v;
    if (sample_terrain_surface_height(((T_80170F94_S_80170F94_0 *)position)->unk_00.at02.v,
                      ((T_80170F94_S_80170F94_0 *)position)->unk_04.at02.v,
                      (s16)(((T_80170F94_S_80170F94_0 *)position)->unk_08.at02u.v - 4)) - 0x10 < height) {
        ((T_80170F94_S_80170F94_1 *)effect)->unk_48 = 0;
        ((T_80170F94_S_80170F94_0 *)position)->unk_08.at02.v = sample_terrain_surface_height(
            ((T_80170F94_S_80170F94_0 *)position)->unk_00.at02.v, ((T_80170F94_S_80170F94_0 *)position)->unk_04.at02.v,
            (s16)(((T_80170F94_S_80170F94_0 *)position)->unk_08.at02u.v - 4)) - 0x11;
        ((T_80170F94_S_80170F94_0 *)position)->unk_08.at00u.v = 0;
        if (((T_80170F94_S_80170F94_1 *)effect)->unk_0E == 0) {
            ((T_80170F94_S_80170F94_1 *)effect)->unk_0E = 1;
            ((T_80170F94_S_80170F94_1 *)effect)->unk_18.s = 0;
        }
    }

    frame_count = ((T_80170F94_S_80170F94_1 *)effect)->unk_1A + 1;
    ((T_80170F94_S_80170F94_1 *)effect)->unk_1A = frame_count;
    if ((frame_count & 3) == 0) {
        advance_sprite_animation_and_textures(sprite);
    }

    scale_x = sprite->scale_x + 100;
    sprite->scale_x = scale_x;
    if (scale_x > 0x1000) {
        sprite->scale_x = 0x1000;
    }

    scale_y = sprite->scale_y + 100;
    sprite->scale_y = scale_y;
    if (scale_y > 0x1000) {
        sprite->scale_y = 0x1000;
    }

    ticks_left = ((T_80170F94_S_80170F94_1 *)effect)->unk_18.u - 1;
    ((T_80170F94_S_80170F94_1 *)effect)->unk_18.u = ticks_left;
    if ((s16)ticks_left <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }

    if (sprite->flags & 0x8000) {
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates an effect and sets its movement toward a tracked target or grid position. */
/* Creates a flashing Troll effect with position offsets toward a tracked actor or the stored target tile
 * coordinates. */
void create_targeted_motion_effect(ActorRecord *body, ObjectPosition *position, s32 unused, EntityRec *target)
{
    T_8017121C_Vec3u16 offset;
    ObjectNodeHeader *effect;
    void *init_effect;
    void *init_data;
    ObjectPosition *coords;
    T_8017121C_S_8017121C_0 *effect_state;
    T_8017121C_S_8017121C_6 *source;
    SpriteFrameState *part;
    T_8017121C_S_8017121C_9 *target_coords;
    s16 *direction_table;
    T_8017121C_S_8017121C_8_pre *tracked_target;
    s32 delta_x;
    s32 delta_z;
    s32 fallback_x;
    s32 fallback_y;
    u32 untracked_mask;
    u32 target_flags;
    s32 effect_x;
    s16 *x_entry;
    s32 x_offset;
    s32 target_x;
    u32 y_table_addr;
    s16 *y_entry;
    s32 y_offset;
    s32 z_delta;
    s32 effect_z;
    s32 grid_x_bits;
    s32 grid_axis;
    s32 grid_y;
    s32 scaled_x;
    s32 scaled_y;
    s32 centered_coord;

    effect = allocate_flagged_object_node(0x212);
    if (effect == NULL) {
        return;
    }

    init_effect = effect;
    init_data = ((u8 *)update_rotating_actor_aura);
    effect_state = (T_8017121C_S_8017121C_0 *)((u8 *)effect + 0x20);
    effect_state->unk_18 = 2;
    effect_state->unk_1A = 2;
    effect->update_callback = update_stepped_rgb_flash;
    register_node(init_effect, init_data);

    part = effect->sprite;
    part->flags &= 0xFFF3;

    coords = effect->position;
    coords->x.w.i = position->x.w.i;
    coords->y.w.i = position->y.w.i;
    coords->z.w.i = position->z.w.i;

    source = ((T_8017121C_S_8017121C_5_pre *)body)[-1].unk_00;
    if (resolve_record_orientation_or_fallback(source->unk_08, source, &offset, 0) != 0) {
        coords->x.w.i = (u16)coords->x.w.i + (offset.raw_y);
        coords->y.w.i = (u16)coords->y.w.i + (offset.y);
        coords->z.w.i = (u16)coords->z.w.i + (offset.z);
        part = effect->sprite;
        part->scale_y = 0x1000;
        part->scale_x = 0x1000;
    } else {
        coords->z.w.i = (u16)coords->z.w.i - (0x14);
        part = effect->sprite;
        part->scale_y = 0x1000;
        part->scale_x = 0x1000;
    }
    part->color.c.b = 0xA0;
    part->color.c.g = 0xA0;
    part->color.c.r = 0xA0;
    effect_state->unk_00 = 0xA0;
    effect_state->unk_01 = part->color.c.g;

    effect_state->unk_02 = part->color.c.b;

    if (target->target == NULL) {
        effect_state->unk_60 = 0;
        effect_state->unk_5C = 0;
        effect_state->unk_58 = 0;
        grid_axis = ((u8)target->unk_73);
    } else {
        target_flags = ((u32)target->flags14);
        untracked_mask = 0x04000000;
        if ((target_flags & untracked_mask) == 0) {
            direction_table = ((s16 *)D_80175EBC);
            effect_state->unk_60 = 0;
            effect_state->unk_5C = 0;
            effect_state->unk_58 = 0;

            grid_axis = ((u16)target->facing);
            tracked_target = target->target;
            effect_x = coords->x.w.i;
            grid_axis = (u32)grid_axis >> 7;
            grid_axis &= 0x1C;
            grid_axis += (u32)direction_table;
            x_entry = (s16 *)grid_axis;
            target_coords = tracked_target[-1].unk_00;
            x_offset = *x_entry;
            target_x = target_coords->unk_02;
            x_offset <<= 4;
            delta_x = target_x - effect_x;
            delta_x -= x_offset;
            effect_state->unk_5A = delta_x / 2;

            y_table_addr = ((u16)target->facing);
            centered_coord = target_coords->unk_06;
            effect_z = coords->y.w.i;
            y_table_addr = (y_table_addr >> 7) & 0x1C;
            y_table_addr += (u32)direction_table;
            y_entry = (s16 *)y_table_addr;
            y_offset = y_entry[1];
            centered_coord = centered_coord - effect_z;
            y_offset <<= 4;
            centered_coord -= y_offset;
            centered_coord += (u32)centered_coord >> 31;
            centered_coord >>= 1;
            effect_state->unk_5E = centered_coord;

            effect_z = coords->z.w.i;
            z_delta = target_coords->unk_0A - effect_z;
            delta_z = z_delta;
            delta_z -= entity_height_offsets[((T_8017121C_S_8017121C_10 *)(target->target))->unk_13] >> 1;
            effect_state->unk_62 = delta_z / 2;
            return;
        }

        effect_state->unk_60 = 0;
        effect_state->unk_5C = 0;
        effect_state->unk_58 = 0;

        grid_axis = ((u8)target->unk_73);
    }
    ;
    grid_x_bits = ((u8)target->unk_72);
    grid_axis <<= 24;
    grid_y = grid_axis >> 24;
    grid_x_bits <<= 24;
    grid_axis = grid_x_bits >> 24;
    if (grid_x_bits < 0) {
        grid_axis = -grid_axis;
    }
    if ((s16)grid_y < 0) {
        grid_y = -grid_y;
    }
    scaled_x = grid_axis << 16;
    centered_coord = coords->x.w.i;
    scaled_x >>= 10;
    centered_coord -= 0x20;

    fallback_x = scaled_x - centered_coord;
    effect_state->unk_5A = fallback_x / 2;
    centered_coord = coords->y.w.i;
    scaled_y = (grid_y << 16) >> 10;
    effect_state->unk_62 = 0;
    centered_coord -= 0x20;
    fallback_y = scaled_y - centered_coord;
    effect_state->unk_5E = fallback_y / 2;
}

/* MECHANISM: Raw u8 shift/sign-extension idioms reproduce the fallback branches without widening
   artifacts. Mutating scaled_x with >>= 10 lets its sra fill an lh delay; scaled_y is shifted in one
   expression (single-set pseudos are scheduled as births), which keeps the second half in source order
   around the zero store. */

/* Create and position an effect using a linked object or stored tile coordinates. */
void create_actor_action_effect(ActorRecord *source_object, ObjectPosition *source_pos, SpriteFrameState *sprite_template, ActorRecord *actor) {
    ObjectNodeHeader *effect;
    T_801714FC_S_801714FC_1 *effect_state;
    void *effect_data;
    void *template_data;
    T_801714FC_S_801714FC_4 *linked_pos;
    u16 pos_offset[4];

    if ((actor->target) == 0 &&actor->target_tile_x >= 0) {
        return;
    }
    effect = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (effect == 0) {
        return;
    }
    effect_state = (T_801714FC_S_801714FC_1 *)((u8 *)effect + 0x20);
    effect_state->unk_96 = 0xa;
    effect_state->unk_9E = 0xa;
    effect->update_callback = (void *)&update_normalized_gray_fade;
    effect_state->unk_94 = ((u16)actor->facing);
    effect_data = effect->sprite;
    template_data = sprite_template;
    {
        Blk16 *src_block = (Blk16 *)template_data;
        Blk16 *dst_block = (Blk16 *)effect_data;
        Blk16 *src_end = src_block + 3;
        do {
            *dst_block = *src_block;
            dst_block++;
            src_block++;
        } while (src_block != src_end);
    }
    ((T_801714FC_S_801714FC_3 *)effect_data)->unk_1E = 0x1000;
    ((T_801714FC_S_801714FC_3 *)effect_data)->unk_1C = 0x1000;
    ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0E = 0x80;
    ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0D = 0x80;
    ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0C = 0x80;
    ((T_801714FC_S_801714FC_3 *)effect_data)->unk_14 = ((T_801714FC_S_801714FC_3 *)effect_data)->unk_14 & 0xfff3;
    register_node(effect, project_sprite_chain);
    (*(void * *)((u8 *)effect_data + 0x2c)) = (void *)&D_80175EB4;
    select_sprite_entry(effect_data,
        ((u8 *)&D_80175EB4)[(((s32)g_game_work.view.camera_rotation.parts.viewAngle + (s32)actor->facing + 0x100) >> 9) & 7],
        0);
    effect_data = effect->position;
    if ((actor->target) != 0 && (actor->flags14 & 0x04000000) == 0) {
        u8 *direction_offsets = (u8 *)((u8 *)D_80175EBC);
        linked_pos = ((T_801714FC_S_801714FC_8_pre *)(actor->target))[-1].unk_00;
        ((T_801714FC_S_801714FC_3 *)effect_data)->unk_02 = linked_pos->unk_02
        - ((*(s16 *)((u8 *)direction_offsets + ((((u16)actor->facing) >> 7) & 0x1c))) * 0x10);
        ((T_801714FC_S_801714FC_3 *)effect_data)->unk_06 = linked_pos->unk_06
        - ((*(s16 *)((u8 *)direction_offsets + (((((u16)actor->facing) >> 7) & 0x1c) + 2))) * 0x10);
        ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0A = linked_pos->unk_0A
        - (entity_height_offsets[((T_801714FC_S_801714FC_8 *)(actor->target))->unk_13] >> 1);
        return;
    }
    if (actor->target_tile_x < 0) {
        s32 tile_x, tile_y;
        actor->target_tile_x = -(u8)((u8)actor->target_tile_x);
        if (actor->target_tile_y < 0) {
            actor->target_tile_y = -(u8)((u8)actor->target_tile_y);
        }
        tile_x = actor->target_tile_x;
        ((T_801714FC_S_801714FC_3 *)effect_data)->unk_02 = (tile_x << 6) + 0x20;
        tile_y = actor->target_tile_y;
        ((T_801714FC_S_801714FC_3 *)effect_data)->unk_06 = (tile_y << 6) + 0x20;
        ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0A = ((Rec_func_8017121C_arg1 *)source_pos)->unk_0A;
        {
            T_801714FC_S_801714FC_7 *source_data = ((T_801714FC_S_801714FC_6_pre *)source_object)[-1].unk_00;
            if (resolve_record_orientation_or_fallback(source_data->unk_08, source_data, pos_offset, 0) != 0) {
                ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0A = ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0A + pos_offset[2];
                return;
            }
        }
        ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0A = ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0A - 0x28;
    }
}

/* Creates an effect at an offset position with randomized attributes and motion. */
void spawn_random_color_burst_particle(void *source, ObjectPosition *position) {
    T_80171790_S_80171790_5 *source_obj;
    ObjectPosition *source_pos;
    s32 obj_or_angle;
    s32 data_or_speed;
    T_80171790_S_80171790_0 *effect_state;
    void *init_obj;
    ObjectPosition *effect_pos;
    u8 random_byte_1;
    u8 random_byte_2;

    source_obj = source;
    source_pos = position;
    obj_or_angle = (s32) allocate_flagged_object_node(0x212);
    if (obj_or_angle != 0) {
        init_obj = (void *) obj_or_angle;
        effect_state = (void *) obj_or_angle + 0x20;
        effect_state->unk_18 = 6;
        effect_state->unk_1A = 6;
        ((T_80171790_S_80171790_1 *)((void *) obj_or_angle))->unk_10 = &update_saved_rgb_fade;
        register_node(init_obj, ((s32 *)update_rotating_actor_aura));
        data_or_speed = (s32) ((T_80171790_S_80171790_1 *)((void *) obj_or_angle))->unk_0C;
        ((SpriteFrameState *)data_or_speed)->tpage_abr = 0x60;
        ((SpriteFrameState *)data_or_speed)->flags =
            (u16) (((SpriteFrameState *)data_or_speed)->flags | 0xC);
        effect_pos = ((T_80171790_S_80171790_1 *)((void *) obj_or_angle))->unk_08;
        effect_pos->x.w.i = *(u16 *)&source_pos->x.w.i;
        effect_pos->y.w.i = *(u16 *)&source_pos->y.w.i;
        effect_pos->z.w.i =
            (s16) (*(u16 *)&source_pos->z.w.i - 0x50);
        data_or_speed = (s32) ((T_80171790_S_80171790_1 *)((void *) obj_or_angle))->unk_0C;
        ((SpriteFrameState *)data_or_speed)->scale_y = 0x1000;
        ((SpriteFrameState *)data_or_speed)->scale_x = 0x1000;
        ((SpriteFrameState *)data_or_speed)->color.c.r = rand();
        ((SpriteFrameState *)data_or_speed)->color.c.g = rand();
        ((SpriteFrameState *)data_or_speed)->color.c.b = rand();
        ((T_80171790_S_80171790_1 *)((void *) obj_or_angle))->unk_20 =
            ((SpriteFrameState *)data_or_speed)->color.c.r;
        random_byte_1 = ((SpriteFrameState *)data_or_speed)->color.c.g;
        effect_state->unk_01 = random_byte_1;
        random_byte_2 = ((SpriteFrameState *)data_or_speed)->color.c.b;
        effect_state->unk_60 = 0;
        effect_state->unk_5C = 0;
        effect_state->unk_58 = 0;
        effect_state->unk_02 = random_byte_2;
        obj_or_angle = rand() & 0xFFF;
        data_or_speed =
            (source_obj->unk_AE * rcos(obj_or_angle)) >> 0xC;
        effect_state->unk_62 =
            (source_obj->unk_AE * rsin(obj_or_angle)) >> 0xC;
        obj_or_angle = rand() & 0xFFF;
        effect_state->unk_5A =
            (data_or_speed * rcos(obj_or_angle)) >> 0xC;
        effect_state->unk_5E =
            (data_or_speed * rsin(obj_or_angle)) >> 0xC;
    }
}

/*
 * Creates and initializes an object at an offset from the supplied position.
 *
 * MECHANISM: The fixed s0/s1/s2 object roles leave natural argument holds to allocate as s4/s3,
 * reproducing the 0x28 frame and prologue schedule; s0 holds object+0x20 across the body. Two
 * scheduler seams retain the random_byte_1 load-delay nop, while a split random_byte_2 live range
 * hoists its lbu.
 */
void spawn_growing_rotating_flash(void *unused, ObjectPosition *position, SpriteFrameState *unused_sprite) {
    T_80171928_Object *object;
    T_80171928_Header *header;
    SpriteFrameState *child;
    ObjectPosition *object_pos;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        header = (T_80171928_Header *)((u8 *)object + 0x20);
        header->value18 = 0x1C;
        header->value1a = 0x1C;
        object->header.update_callback = &update_growing_rotating_flash;
        register_node(&object->header, project_sprite_chain);
        child = object->header.sprite;
        child->tpage_abr = 0x60;
        child->flags |= 0xC;
        object_pos = object->header.position;
        object_pos->x.v = position->x.v;
        object_pos->y.v = position->y.v;
        object_pos->z.v = position->z.v + (s32)0xFFB00000;
        child = object->header.sprite;
        child->scale_y = 0x190;
        child->scale_x = 0x190;
        child->color.c.b = 0x80;
        child->color.c.g = 0x80;
        child->color.c.r = 0x80;
        object->blob = D_80175EDC;
        child->source = &object->blob;
    }
}

/* Update position and part state, then mark the object used unless its part is exempt. */
void update_tracked_attachment_sprite(void *object, T_80171A38_S_80171A38_4 *position, T_80171A38_S_80171A38_3 *part_state)
{
    T_80171A38_S_80171A38_1 *record;
    T_80171A38_S_80171A38_2 *part;
    T_80171A38_S_80171A38_5 *base_position;
    u16 part_value;
    T_80171A38_Vec3s position_delta;

    record = (u8 *)((T_80171A38_S_80171A38_0 *)object)->unk_20 - 0x20;
    if ((record->unk_1E & 0x8000) == 0) {
        part = record->unk_0C;
        part_value = part->unk_06;
        base_position = record->unk_08;
        part_state->unk_06 = part_value + 1;

        if (part->unk_04 == 0) {
            part_state->unk_1E = 0x400;
            part_state->unk_1C = 0x400;
        }
        if (part->unk_04 == 1) {
            part_state->unk_1E = 0x700;
            part_state->unk_1C = 0x700;
        }
        if (part->unk_04 == 2) {
            part_state->unk_1E = 0xa00;
            part_state->unk_1C = 0xa00;
        }
        if (part->unk_04 == 3) {
            part_state->unk_1E = 0x700;
            part_state->unk_1C = 0x700;
        }
        if (part->unk_04 == 4) {
            part_state->unk_1E = 0x400;
            part_state->unk_1C = 0x400;
        }

        position->unk_02 = base_position->unk_02;
        position->unk_06 = base_position->unk_06;
        position->unk_0A = base_position->unk_0A;

        if (resolve_record_orientation_or_fallback(
                ((T_80171A38_S_80171A38_6 *)(record->unk_0C))->unk_08,
                record->unk_0C, &position_delta, 0) != 0) {
            position->unk_02 += position_delta.x;
            position->unk_06 += position_delta.y;
            position->unk_0A += position_delta.z;
        }

        if (part->unk_2C == troll_kind13_direction_frames ||
            part->unk_2C == troll_kind14_direction_frames ||
            part->unk_2C == troll_kind15_direction_frames) {
            return;
        }
    }

    ((T_80171A38_S_80171A38_0_pre *)object)[-1].unk_00 |= 0x8000;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}

/* Creates a render object at the supplied position with an optional owner offset. */
void create_tracked_attachment_sprite(ActorRecord *body, T_80171BEC_S_80171BEC_3 *base_position)
{
    T_80171BEC_Offset3 offset;
    ObjectNodeHeader *object;
    SpriteFrameState *render;
    T_80171BEC_S_80171BEC_5 *owner;
    ObjectPosition *position;

    object = allocate_list_node(0x212, &scene_object_list_anchor.next);
    if (object != 0) {
        ((T_80171BEC_S_80171BEC_0 *)object)->unk_40 = body;
        object->update_callback = &update_tracked_attachment_sprite;
        register_node(object, project_sprite_chain);

        render = object->sprite;
        render->tpage_abr = 0x20;
        render->depth_bias = 8;
        render->flags |= 0xC;

        position = object->position;
        position->x.v = base_position->unk_00;
        position->y.v = base_position->unk_04;
        position->z.v = base_position->unk_08;

        owner = ((T_80171BEC_S_80171BEC_4_pre *)body)[-1].unk_00;
        if (resolve_record_orientation_or_fallback(owner->unk_08, owner, &offset, 0) != 0) {
            *(u16 *)&position->x.w.i += offset.x;
            *(u16 *)&position->y.w.i += offset.y;
            *(u16 *)&position->z.w.i += offset.z;
        }

        render = object->sprite;
        render->scale_y = 0x800;
        render->scale_x = 0x800;
        render->color.c.b = 0x80;
        render->color.c.g = 0x80;
        render->color.c.r = 0x80;
        *(T_80171BEC_Packed3 *)((u8 *)object + 0x44) = D_80175EE8;
        render->source = (u8 *)object + 0x44;
    }
}

/* Creates an object and initializes its position, flags, and directional frame table. */
/* Creates Troll, selecting item values and directional sprite tables from the global spawn variant. */
void *create_actor_entity(s16 spawn_flags, s32 sprite_x, s32 sprite_y, s32 initial_height)
{
    u8 * record_addr;
    ActorRecord *result;
    s16 saved_y;
    s16 saved_x;
    SpriteFrameState *sprite;
    s16 init_flags;
    ObjectNodeHeader *object;
    void *position;
    s32 call_object;
    s32 call_position;
    s32 alternate_kind;
    s32 state_flags;
    void *new_frames;
    s32 kind;
    s32 mode;
    u32 global_kind;
    u32 branch_flags;
    void *current_frames;
    u8 *frame_table;
    u8 * default_frames;
    s32 direction_index;
    s32 record_kind;

    result = 0;
    call_object = 0x112;
    saved_x = sprite_x;
    call_position = (s32)((u8 *)(&scene_object_list_anchor));
    saved_y = sprite_y;
    object = allocate_list_node(call_object, (void *)call_position);
    init_flags = spawn_flags;
    if (object != 0) {
        result = (ActorRecord *)((u8 *)object + 0x20);
        object->update_callback = D_801720B4;
        result->species = 0x16;
        register_node(object, project_sprite_chain);

        default_frames = troll_frame_set_1;
        call_position = 0xE;
        position = object->position;
        alternate_kind = 0xF;
        ((T_80171D64_S_80171D64_2 *)position)->unk_0A = initial_height;
        sprite = object->sprite;
        
        sprite->tile_x = saved_x;
        sprite->frameTable = (void *)default_frames;
        record_kind = 0x20;
        sprite->tile_y = saved_y;
        record_addr = (u8 *)result;
        result->unk_4B = record_kind;
        result->unk_48 = call_position;
        result->unk_49 = alternate_kind;
        mode = spawn_flags & 3;

        if (mode == 1) {
            (*(u32 *)((u8 *)result + 0x14)) |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            branch_flags = result->flags1C;
            global_kind = (u8)entity_spawn_variant_code;
            result->flags1C = branch_flags | 0x6000;
            if (global_kind >= 0xA) {
                if (global_kind < 0xD) {
                    result->unk_48 = alternate_kind;
                } else {
                    result->unk_48 = 0xD;
                }
            }
        } else {
            if (mode >= 2) {
                result->flags14 |= ACTOR_CLASS_ENABLED;
                result->flags1C |= ACTOR_PLAYER_SIDE;
            } else {
                global_kind = (u8)entity_spawn_variant_code;
                if (global_kind < 0xA) {
                    result->unk_48 = call_position;
                } else if (global_kind < 0xD) {
                    result->unk_48 = alternate_kind;
                } else {
                    result->unk_48 = 0xD;
                }

                if (((init_flags & ~3) << 16) == 0) {
                    if (!(result->flags14 & ACTOR_RESIST_SLEEP)) {
                        state_flags = generate_random_value();
                        if (state_flags & 1) {
                            set_or_clear_actor_status_slot(result, STATUS_SLEEP,
                                (generate_random_value() & 0x3F) | 0x20);
                            kind = result->unk_48;
                            switch (kind) {
                            case 0xD:
                                current_frames = sprite->frameTable;
                                new_frames = troll_kind13_direction_frames;
                                if (current_frames != new_frames) {
                                    sprite->frameTable = new_frames;
                                }
                                break;
                            case 0xE:
                                current_frames = sprite->frameTable;
                                new_frames = troll_kind14_direction_frames;
                                if (current_frames != new_frames) {
                                    sprite->frameTable = new_frames;
                                }
                                break;
                            case 0xF:
                                current_frames = sprite->frameTable;
                                new_frames = troll_kind15_direction_frames;
                                if (current_frames != new_frames) {
                                    sprite->frameTable = new_frames;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }

        call_object = (s32)object;
        call_position = (s32)position;
        initialize_actor_sprite_and_animation((void *)call_object, (void *)call_position, sprite,
            (s16)init_flags);
        ((T_80171D64_S_80171D64_4 *)((void *)record_addr))->unk_9A = 0xFF;
        ((T_80171D64_S_80171D64_4 *)((void *)record_addr))->unk_9C = -1;
        ((T_80171D64_S_80171D64_4 *)((void *)record_addr))->unk_8C = update_actor_behavior;
        try_move_actor_to_valid_position((void *)record_addr, position, sprite, result);

        kind = result->unk_48;
        switch (kind) {
        case 0xD:
            current_frames = sprite->frameTable;
            frame_table = troll_frame_set_1;
            break;
        case 0xE:
            current_frames = sprite->frameTable;
            frame_table = troll_frame_set_2;
            break;
        case 0xF:
            current_frames = sprite->frameTable;
            frame_table = troll_frame_set_3;
            break;
        default:
            return result;
        }
        if (current_frames != frame_table) {
            (sprite->frameTable) = frame_table;
            direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + result->facing + 0x100) >> 9) & 7;
            select_sprite_entry(sprite,
                *(u8 *)((u32)direction_index + (unsigned long)frame_table),
                0);
        }
    }
    return result;
}
