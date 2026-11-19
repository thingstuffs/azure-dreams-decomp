#include "shared/audio_commands.h"
#include "shared/dungeon_height_query.h"
/* Moving target effects, tint changes, radial sprite emission, and shaded point rendering. */
#include "modules/dungeon_ovl_18a0800.h"
#include "dungeon/effect/travel.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "sdk/libgpu.h"
#include "dungeon/actor/status.h"
#include "dungeon/effect/sprite.h"
#include "dungeon/item.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "dungeon/effect.h"
#include "dungeon/system.h"
#include "dungeon/data.h"

void (*const dungeon_18a0800_entry)(TrackingEffect *, ObjectPosition *, SpriteFrameState *) = update_accelerating_condition_projectile;
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern u8 D_800257D0[];
extern u8 D_800257E8[];

#include "dungeon/effect/screen.h"
extern s16 get_byte_coordinate_chebyshev_distance(s32 start_x, s32 start_y, s32 end_x, s32 end_y);

/* Updates a moving effect through initialization, target tracking, fading, and cleanup. */
void update_accelerating_condition_projectile(TrackingEffect *self, ObjectPosition *motion, SpriteFrameState *part)
{
    ActorRecord *owner;
    ObjectNodeHeader *owner_base;
    ObjectPosition *owner_motion;
    void *target;
    s32 state;
    s16 spawn_height;
    s32 direction_step;
    long state_step;
    s32 height_result;
    u32 height_offset;
    u32 target_height;
    s32 velocity;
    s32 position;
    s32 over_limit;
    s32 z_pos;
    s32 z_delta;
    s32 coord;
    ActorRecord *spawn_target;
    s32 cell_center_x;
    u32 red;
    u32 green;
    u32 blue;
    u32 color;
    u32 texture_flags;
    u32 texture_size;
    s16 attach_offset[3];
    GpuRectBuffer texture_init;

    owner = self->owner;
    state = (s16)self->state;
    owner_base = NODE_HEADER(owner);
    owner_motion = owner_base->position;
    switch (state) {
    case 0:
        color = 0x00808080;
        texture_flags = 0x01000340;
        texture_size = 0x00200020;
        part->color.word = color;
        part->scale_y = 0x800;
        part->scale_x = 0x800;
        part->source = D_800257E8;
        self->direction = (owner->facing >> 9) & 7;
        texture_init.words[0] = texture_flags;
        texture_init.words[1] = texture_size;
        draw_textured_ellipse(D_800257D0, &texture_init.rect, 1, 0);
        self->state++;

    case 1:
        if (get_sprite_attachment_vector(owner_base->sprite->source,
                          owner_base->sprite, attach_offset, 0) == 0) {
            if ((owner_base->sprite->flags & 0x8000) == 0) {
                break;
            }
        }

        motion->x.w.i = (u16)owner_motion->x.w.i;
        motion->y.w.i = (u16)owner_motion->y.w.i;
        if (owner_base->sprite->flags & 0x8000) {
            motion->z.w.i = (u16)owner_motion->z.w.i - 0x40;
        } else {
            motion->z.w.i = (u16)owner_motion->z.w.i + attach_offset[2];
        }

        if ((self->animation->flags & 0x80) == 0) {
            break;
        }
        if ((self->flags & 4) == 0) {
            register_node((u8 *)self - 0x20, project_sprite_chain);
            part->tpage_abr = 0x20;
            part->color.c.b = 0x80;
            part->color.c.g = 0x80;
            part->color.c.r = 0x80;
            part->flags |= 0xC;
            self->flags |= 4;
        }

        if (owner->target != 0) {
            ObjectPosition *target_position;
            SpriteFrameState *owner_sprite;
            ActorRecord *target_actor;
            u8 target_type;
            u8 *height_table;
            u8 tile_coord;
            target_position = NODE_HEADER(owner->target)->position;
            self->target_x = target_position->x.unsigned_parts.integer;
            self->target_y = target_position->y.unsigned_parts.integer;
            height_table = entity_height_offsets;
            target_actor = owner->target;
            target_type = target_actor->species;
            height_offset = height_table[target_type];
            height_offset += 0x20;
            target_height = target_position->z.unsigned_parts.integer;
            self->target_z = target_height - height_offset;

            {
                s16 direction;
                direction = self->direction;
                owner_sprite = NODE_HEADER(owner)->sprite;
                tile_coord = owner_sprite->tile_x + dir_step_x[direction];
                self->current_tile.tile.x.u = tile_coord;
                self->previous_tile.tile.x.u = tile_coord;
            }
            {
                s16 direction;
                direction = self->direction;
                tile_coord = owner_sprite->tile_y + dir_step_y[direction];
                self->current_tile.tile.y.u = tile_coord;
                self->previous_tile.tile.y.u = tile_coord;
            }
            {
                s32 owner_coord;
                s32 tile_distance;
                owner_coord = owner->target_tile_x;
                z_pos = owner_sprite->tile_x;
                if (owner_coord == z_pos) {
                    owner_coord = owner->target_tile_y;
                    z_pos = owner_sprite->tile_y;
                    tile_distance = owner_coord - z_pos;
                } else {
                    tile_distance = owner_coord - z_pos;
                }
                if (tile_distance < 0) {
                    tile_distance = -tile_distance;
                }
                self->tiles_left = tile_distance + 1;
            }
        } else {
            self->tiles_left = 8;
            self->target_x = (u16)motion->x.w.i;
            self->target_y = (u16)motion->y.w.i;
            self->target_z = owner->ground_height - 0x50;
        }
        direction_step = dir_step_x[self->direction];
        F(motion, s16, 0x0E) = direction_step << 3;
        direction_step = dir_step_y[self->direction];
        F(motion, s16, 0x12) = direction_step << 3;
        state_step = self->state;
        self->unk_1C = 0;
        self->state = state_step + 1;
        break;

    case 2:
    {
        s32 next_velocity;
        velocity = motion->velocity_x;
        position = motion->x.v;
        position += velocity;
        motion->x.v = position;
        next_velocity = motion->velocity_x;
        position = next_velocity >> 4;
        next_velocity += position;
        velocity = abs(next_velocity);
        position = 0x200000;
        over_limit = velocity > position;
        motion->velocity_x = next_velocity;
        if (over_limit) {
            position = -0x200000;
            if (next_velocity > 0) {
                position = 0x200000;
            }
            motion->velocity_x = position;
        }
    }
        {
            s32 next_velocity;
            velocity = motion->velocity_y;
            position = motion->y.v;
            position += velocity;
            motion->y.v = position;
            next_velocity = motion->velocity_y;
            position = next_velocity >> 4;
            next_velocity += position;
            velocity = abs(next_velocity);
            position = 0x200000;
            over_limit = velocity > position;
            motion->velocity_y = next_velocity;
            if (over_limit) {
                position = -0x200000;
                if (next_velocity > 0) {
                    position = 0x200000;
                }
                motion->velocity_y = position;
            }
        }

        z_delta = self->target_z << 16;
        z_pos = motion->z.v;
        z_delta -= z_pos;
        z_delta >>= 3;
        z_pos += z_delta;
        motion->z.v = z_pos;
        create_effect_from_endpoints(motion, part);

        coord = motion->x.w.i;
        if (coord < 0) {
            coord += 0x3F;
        }
        self->current_tile.tile.x.s = coord >> 6;
        coord = motion->y.w.i;
        if (coord < 0) {
            coord += 0x3F;
        }
        self->current_tile.tile.y.s = coord >> 6;
        if (self->previous_tile.packed == self->current_tile.packed) {
            break;
        }

        if (owner->target != 0) {
            if (self->sound_played == 0) {
                if ((s16)get_byte_coordinate_chebyshev_distance(self->current_tile.tile.x.u, self->current_tile.tile.y.u,
                                     (u8)owner->target_tile_x, (u8)owner->target_tile_y) < 5) {
                    self->sound_played = 1;
                    play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                }
            }
        }
        if (owner->target != 0 &&
            F(owner, s16, 0x72) == self->current_tile.packed) {
            motion->x.w.i = self->target_x;
            motion->y.w.i = self->target_y;
            motion->z.w.i = self->target_z;
            self->state++;
            break;
        }

        coord = self->current_tile.tile.x.u;
        z_pos = self->tiles_left;
        z_pos -= 1;
        target = self->current_tile.tile.y.u;
        self->tiles_left = z_pos;
        z_pos <<= 16;
        self->previous_tile.tile.x.u = coord;
        self->previous_tile.tile.y.u = target;
        if (z_pos != 0) {
            cell_center_x = (((s32)self->current_tile.tile.x.s << 6) + 0x20) & 0xFFE0;
            height_result = check_left_tile_and_center_height(
                cell_center_x,
                (((s32)self->current_tile.tile.y.s << 6) + 0x20) & 0xFFE0,
                motion->z.w.i);
            if ((height_result << 16) == 0) {
                break;
            }
        }
        self->state = 0x10;
        break;

    case 3:
        spawn_target = owner->target;
        spawn_height = spawn_target->ground_height;
        self->child = create_brightening_follower(self, motion, spawn_height, spawn_target);
        if (self->child == 0) {
            break;
        }
        part->flags |= 0x80;
        state_step = self->state;
        state_step++;
        self->state = state_step;

    case 4:
        state_step = (long)self->child;
        if ((F((void *)state_step, u16, 0x1E) & 0x8000) == 0) {
            break;
        }
        target = owner->target;
        if (target != 0) {
            apply_indexed_effect_condition(target, self->variant, owner);
        }
        self->state = 0x11;
        break;

    case 16:
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        z_delta = self->target_z << 16;
        z_pos = motion->z.v;
        z_delta -= z_pos;
        z_delta >>= 3;
        z_pos += z_delta;
        motion->z.v = z_pos;
        red = part->color.c.r;
        green = part->color.c.g;
        blue = part->color.c.b;
        part->color.c.r = red - (red >> 1);
        part->color.c.g = green - (green >> 1);
        part->color.c.b = blue - (blue >> 1);
        create_effect_from_endpoints(motion, part);
        if (part->color.c.r >= 2) {
            break;
        }
        self->state++;
        break;

    case 17:
        if (*(s16 *)tint_effect_update_count == 0) {
            g_dungeon_status.active_actor = 0;
            NODE_HEADER(self)->flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
    tint_effect_update_count[0] = 0;
}



/* Tint the object red, restore its color, and advance its motion. */
void tint_effect_and_advance_motion(BrighteningFollowerEffectBody *effect, ObjectPosition *motion) {
    ActorRecord *object;
    SpriteFrameState *sprite;
    s16 state;
    s32 channel_value;

    tint_effect_update_count[0]++;
    state = effect->state;

    switch (state) {
    case 0:
        object = effect->target;
        object->flags1C |= 0x10000000;
        effect->state++;

    case 1:
        sprite = NODE_HEADER(effect->target)->sprite;

        channel_value = sprite->color.c.r + 1;
        sprite->color.c.r = channel_value;
        if ((u32)(channel_value & 0xFF) >= 0xC1U) {
            sprite->color.c.r = 0xC0;
        }

        channel_value = sprite->color.c.g - 1;
        sprite->color.c.g = channel_value;
        if ((u32)(channel_value & 0xFF) < 0x40U) {
            sprite->color.c.g = 0x40;
        }

        channel_value = sprite->color.c.b - 1;
        sprite->color.c.b = channel_value;
        if ((u32)(channel_value & 0xFF) < 0x40U) {
            sprite->color.c.b = 0x40;
        }

        if (tint_effect_phase_counts[0] < 14) {
            effect->state++;
        }
        break;
    case 2:
        sprite = NODE_HEADER(effect->target)->sprite;

        channel_value = sprite->color.c.r - 4;
        sprite->color.c.r = channel_value;
        if ((u32)(channel_value & 0xFF) < 0x80U) {
            sprite->color.c.r = 0x80;
        }

        channel_value = sprite->color.c.g + 4;
        sprite->color.c.g = channel_value;
        if ((u32)(channel_value & 0xFF) >= 0x81U) {
            sprite->color.c.g = 0x80;
        }

        channel_value = sprite->color.c.b + 4;
        sprite->color.c.b = channel_value;
        if ((u32)(channel_value & 0xFF) >= 0x81U) {
            sprite->color.c.b = 0x80;
        }

        if (tint_effect_phase_counts[0] == 0) {
            effect->target->flags1C &= ~0x10000000;
            NODE_HEADER(effect)->flags |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }

    motion->z.v += motion->velocity_z;
    motion->velocity_z += -0x80000;
    create_spark_burst_effect(motion);
    effect->particle_count++;
}
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

/* Creates an object, copies three values into its data, and initializes it. */
void *create_brightening_follower(TrackingEffect *parent, ObjectPosition *source_values, s16 setup_value, ActorRecord *target) {
    ObjectPosition *target_values;
    ObjectNodeHeader *object;
    BrighteningFollowerEffectBody *body;

    object = allocate_list_node(2, &NODE_HEADER(parent)->next);
    if (object != NULL) {
        target_values = object->position;
        object->update_callback = tint_effect_and_advance_motion;
        target_values->x.w.i = source_values->x.w.i;
        target_values->y.w.i = source_values->y.w.i;
        target_values->z.w.i = source_values->z.w.i;
        body = NODE_BODY(object);
        body->target = target;
        spawn_ring_effects(target_values, setup_value);
    }
    return object;
}

typedef struct {
    u16 value;
    u8 pad[10];
} Global16;

/* Advances counters and conditionally processes the target, propagating its status flag. */
void advance_sprite_every_other_tick(void *record, ObjectPosition *unused, SpriteFrameState *target)
{
    u16 flags = *(u16 *)((u8 *)record + 0x1C);

    tint_effect_update_count[0] = tint_effect_update_count[0] + 1;
    if (flags & 1) {
        advance_sprite_animation_and_textures(target);
        if (target->flags & 0x4000) {
            *(u16 *)((u8 *)record - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
    *(u16 *)((u8 *)record + 0x1C) += 1;
}
#include "shared/sprite_frame_state.h"

   /* coords in create_spark_burst_effect */

   /* arg0 in create_spark_burst_effect */

/* Creates a visual node at the supplied coordinates with 16 evenly spaced radial effects. */
void *create_spark_burst_effect(ObjectPosition *source_coords)
{
    s16 angle;
    s32 effect_index;
    SpriteFrameState *part;
    ObjectPosition *coords;
    ObjectNodeHeader *node;

    node = allocate_flagged_object_node(0x202);
    if (node != 0) {
        node->update_callback = advance_sprite_every_other_tick;
        register_node(node, project_sprite_chain);
        coords = node->position;
        coords->x.w.i = source_coords->x.w.i;
        coords->y.w.i = source_coords->y.w.i;
        coords->z.w.i = source_coords->z.w.i;
        part = node->sprite;
        part->scale_y = 0x1000;
        part->scale_x = 0x1000;
        part->color.word = 0x808080;
        select_record_entry_and_value(part, spark_sprite_entries, 0);
        part->tpage_abr = 0x20;
        part->flags |= 0xC;
        effect_index = 0;
        angle = (s16)rand();
        do {
            create_spark_effect(coords, angle, 0x10, 1);
            effect_index++;
            angle += 0x100;
        } while (effect_index < 0x10);
    }
    return node;
}

/* Advance an effect through its delay, motion, brightness changes, and periodic emissions. */
void advance_rising_fading_emitter(RisingFadingEmitterBody *effect, ObjectPosition *motion, SpriteFrameState *primitive) {
    s16 state;
    s32 wave_value;
    u16 frame_count;

    tint_effect_update_count[0]++;
    state = effect->state;
    if (state != 2) {
        if (state == 0) {
            frame_count = effect->initial_delay - 1;
            effect->initial_delay = frame_count;
            if ((s16)frame_count > 0) {
                return;
            }
            effect->state++;
        }
        frame_count = effect->frame_count + 1;
        effect->frame_count = frame_count;
        if ((s16)frame_count >= 0x41) {
            effect->state = 2;
        }
    } else {
        primitive->color.word += 0xFFFBFBFC;
        if (primitive->color.c.r < 4) {
            tint_effect_phase_counts[0]--;
            (*(u16 *)((u8 *)effect + (-2))) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
    }
    motion->z.v += motion->velocity_z;
    motion->velocity_z += 0x10000;
    if (motion->z.w.i > effect->height_limit)
        motion->z.w.i = effect->height_limit;
    wave_value = rsin((s16)effect->frame_count << 6);
    primitive->color.word += 0x20202;
    primitive->scale_y -= wave_value >> 5;
    if (primitive->color.c.r >= 0x41)
        primitive->color.word = 0x404040;
    advance_sprite_animation_and_textures(primitive);
    if (!(effect->frame_count & 0x1F))
        create_tinted_travel_sprite(motion, effect->height_limit, effect->effect_value);
    if (!(effect->frame_count & 3))
        create_spark_effect(motion, (effect->effect_value << 24) >> 16, 0x10, 0);
}

#ifndef NULL
#define NULL 0
#endif

   /* saved_arg0 in spawn_ring_effects */

/* Spawns sixteen effects in a ring around the source position. */
void *spawn_ring_effects(void *source_pos, s16 effect_param) {
    register ObjectPosition *origin = source_pos;
    register s16 state_param = effect_param;
    register s32 effect_index = 0;
    register s32 *callback = advance_rising_fading_emitter;
    register u16 *counter_page = (u16 *)0x80020000;
    register s32 component_offset = -0x400;
    register ObjectNodeHeader *effect;
    ObjectPosition *position;
    register s32 angle;
    s32 value;
    register SpriteFrameState *component;

    do {
        effect = allocate_flagged_object_node(0x202);
        if (effect != NULL) {
            effect->update_callback = callback;
            register_node(effect, draw_linked_sprites_clipped);
            angle = effect_index << 8;
            position = effect->position;
            value = (u16)origin->x.w.i + (rcos(angle) >> 7);
            position->x.w.i = value;
            value = (u16)origin->y.w.i + (rsin(angle) >> 7);
            position->y.w.i = value;
            position->z.w.i =
                origin->z.w.i - 0x100;
            component = effect->sprite;
            component->scale_x = 0x800;
            component->scale_y = 0x1CCC;
            component->color.word = 0;
            select_record_entry_and_value(component, tinted_travel_sprite_data, 0);
            value = counter_page[0x57CC / 2];
            source_pos = NODE_BODY(effect);
            component->angle_x = 0x400;
            component->angle_y = component_offset;
            ((RisingFadingEmitterBody *)source_pos)->effect_value = effect_index;
            ((RisingFadingEmitterBody *)source_pos)->height_limit = state_param;
            ((RisingFadingEmitterBody *)source_pos)->initial_delay = (s16)(effect_index * 2);
            value += 1;
            counter_page[0x57CC / 2] = value;
        }
        effect_index += 1;
        component_offset += 0x100;
    } while (effect_index < 0x10);
    return effect;
}


typedef struct TravelSpriteEffectBody {
    u8 pad_00[0x14];
    s16 height_limit;
    u8 pad_16[0x8];
    s16 unk_1E;
    u8 pad_20[0x4];
    s16 direction_index;
} TravelSpriteEffectBody;

/* Moves and fades an effect, marking it inactive when its brightness falls below the cutoff. */
void move_and_fade_effect(TravelSpriteEffectBody *effect, ObjectPosition *position_data, SpriteFrameState *visual_data) {
    ObjectPosition *position;
    register SpriteFrameState *visual;
    u16 decay_value;
    u8 brightness;
    s32 angle;

    visual = visual_data;
    position = position_data;
    angle = effect->direction_index << 8;
    tint_effect_update_count[0] = tint_effect_update_count[0] + 1;
    position->x.v = position->x.v + (rcos(angle) * 8);
    position->y.v = position->y.v + (rsin(effect->direction_index << 8) * 8);
    brightness = visual->color.c.b - 2;
    visual->color.c.b = brightness;
    visual->color.c.g = brightness;
    visual->color.c.r = brightness;
    if ((u32)(brightness & 0xFF) < 0x20U) {
        tint_effect_phase_counts[0] = (s16)((u16)tint_effect_phase_counts[0] - 1);
        NODE_HEADER(effect)->flags |= NODE_REMOVE;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
    decay_value = visual->scale_y;
    visual->scale_y = (u16)(decay_value - (decay_value >> 7));
    visual->scale_x = (u16)(visual->scale_x + 8);
}

   /* arg0 in create_tinted_travel_sprite */

/* Creates a render object at the supplied position and initializes its effect state. */
void *create_tinted_travel_sprite(ObjectPosition *source_pos, s16 effect_param, s16 size)
{
    s32 signed_size;
    s32 render_code;
    u16 object_count;
    SpriteFrameState *render_state;
    ObjectNodeHeader *object;
    ObjectPosition *position;
    TravelSpriteEffectBody *effect_state;

    object = allocate_flagged_object_node(0x202);
    if (object != 0) {
        object->update_callback = move_and_fade_effect;
        register_node(object, draw_linked_sprites_clipped);
        position = object->position;
        position->x.w.i = source_pos->x.w.i;
        position->y.w.i = source_pos->y.w.i;
        position->z.w.i = source_pos->z.w.i;
        render_state = object->sprite;
        render_state->color.word = 0x808080;
        render_state->scale_x = 0x400;
        render_state->scale_y = 0x1CCC;
        select_record_entry_and_value(render_state, tinted_travel_sprite_data, 0);
        signed_size = size;
        render_state->angle_y = (signed_size << 8) - 0x400;
        render_code = 0x60;
        effect_state = NODE_BODY(object);
        render_state->tpage_abr = render_code;
        object_count = (*(u16 *)tint_effect_phase_counts);
        render_state->angle_x = 0x400;
        effect_state->direction_index = size;
        effect_state->height_limit = effect_param;
        effect_state->unk_1E = signed_size * 2;
        tint_effect_phase_counts[0] = object_count + 1;
    }
    return object;
}

#include "dungeon/effect/travel/jittered_spark.h"

/* Updates effect motion and marks it inactive when its lifetime or owner expires. */
void update_spark_effect(JitteredSparkEffectBody *effect, ObjectPosition *motion, SpriteFrameState *owner)
{
    s32 life_left;
    s32 y_step;
    s32 z_velocity;
    s32 z_position;
    s32 z_velocity_copy;
    s32 y_motion;
    s32 x_direction;
    s32 y_direction;
    u16 x;
    u16 y;
    s16 probe_z;
    u16 counter;
    u16 *counter_ptr;

    counter_ptr = tint_effect_update_count;
    x = motion->x.w.i;
    counter = counter_ptr[0];
    probe_z = motion->z.w.i;
    y = motion->y.w.i;
    counter++;
    probe_z -= 2;
    counter_ptr[0] = counter;
    if (motion->z.w.i <
        (s16)sample_terrain_surface_height(x, y, probe_z)) {
        if (effect->spawn_mode == 0) {
            x_direction = rcos(effect->heading);
            motion->x.v = (s32)(motion->x.v +
                (((s32)(x_direction * effect->remaining_steps) >> 4) +
                 (rand() & 0xFFFF)));

            y_direction = rsin(effect->heading);
            y_step = ((y_direction * effect->remaining_steps) >> 4) +
                       (rand() & 0xFFFF);
            motion->y.v = (s32)(motion->y.v + y_step);

            z_velocity_copy = rand();
            motion->z.v = (s32)(motion->z.v +
                (0xFFFE0000 - (z_velocity_copy & 0xFFF)));
        } else {
            motion->x.v = (s32)(motion->x.v +
                rcos(effect->heading) *
                effect->remaining_steps * 8);
            y_motion = rsin(effect->heading) *
                      effect->remaining_steps;
            z_velocity = motion->velocity_z;
            z_position = motion->z.v;
            motion->z.v = z_position + z_velocity;
            motion->velocity_z += 0x6000;
            motion->y.v = (s32)(motion->y.v + y_motion * 8);
        }
    }

    life_left = (u16)effect->remaining_steps - 1;
    effect->remaining_steps = life_left;
    if ((life_left << 16) <= 0 ||
        (owner->flags & 0x8000)) {
        NODE_HEADER(effect)->flags |= NODE_REMOVE;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
#include "shared/game_work.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800252E0_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800252E0_0;   /* global in queue_projected_point_primitives */

typedef struct S_800252E0_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x12];
    void * unk_18;
    u8 pad_1C[0x4];
    void * unk_20;
    u8 pad_24[0x6C];
    s32 depth_cue; /* RotTransPers depth-cue output */
    s32 gte_flag; /* RotTransPers GTE flag output */
    u8 pad_98[0x28];
    u32 unk_C0;
} S_800252E0_1;   /* scratch in queue_projected_point_primitives */

   /* input in queue_projected_point_primitives */

typedef struct S_800252E0_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_04;   /* overlapping accesses */
} S_800252E0_4;   /* p in queue_projected_point_primitives */

typedef struct S_800252E0_6 {
    void * unk_00;
} S_800252E0_6;   /* global_slot in queue_projected_point_primitives */

typedef struct S_800252E0_8 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800252E0_8;   /* ((S_800252E0_6 *)global_slot)->unk_00 in queue_projected_point_primitives */

extern u8 resident_globals_page[];

/* Queue projected point primitives from a linked list into the ordering table. */
s32 queue_projected_point_primitives(JitteredSparkEffectBody *node_data, ObjectPosition *position, SpriteFrameState *appearance) {
    S_800252E0_1 *scratch = (S_800252E0_1 *)0x1F800000;
    u8 *render_slot = resident_globals_page + 0x3160;
    u32 addr_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;
    S_800252E0_4 *packet;
    union { s32 * pointer; u32 value; } ot_entry;

    {
        S_800252E0_0 *render_state = (*(void **)(resident_globals_page + 0x3160));
        void *packet_cursor = render_state->unk_8D0;
        scratch->unk_20 = (u8 *)render_state + 0xB0;
        scratch->unk_18 = packet_cursor;
    }
    for (;;) {
        u16 coord = position->x.w.i;
        scratch->unk_00 = coord;
        coord = position->y.w.i;
        scratch->unk_02 = coord;
        scratch->unk_04 = position->z.w.i;
        packet = scratch->unk_18;
        scratch->unk_18 = (u8 *)packet + 0xC;
        scratch->unk_C0 = RotTransPers(
            scratch, (u8 *)packet + 8, &scratch->depth_cue, &scratch->gte_flag);
        if (scratch->unk_C0 < 0x1E0) {
            s32 color = appearance->color.word;
            packet->unk_00.at03.v = 2;
            packet->unk_04.at00.v = color;
            packet->unk_04.at03.v = 0x6A;
            packet->unk_00.at00.v = (packet->unk_00.at00.v & length_mask) |
                (*(s32 *)((scratch->unk_C0 << 2) +
                          (u32)scratch->unk_20) & addr_mask);
            {
                u32 depth_index;
                depth_index = scratch->unk_C0;
                ot_entry.pointer = (s32 *)((depth_index << 2) +
                              (u32)scratch->unk_20);
            }
            *ot_entry.pointer = (*ot_entry.pointer & length_mask) | ((u32)packet & addr_mask);
            packet = scratch->unk_18;
            scratch->unk_18 = (u8 *)packet + 0xC;
            SetDrawMode(packet, 0, 0, GetTPage(0, 1, 0, 0) & 0xFFFF, 0);
            packet->unk_00.at00.v = (packet->unk_00.at00.v & length_mask) |
                (*(s32 *)((scratch->unk_C0 << 2) +
                          (u32)scratch->unk_20) & addr_mask);
            {
                ot_entry.value = scratch->unk_C0;
                ot_entry.value = (ot_entry.value << 2) +
                           (u32)scratch->unk_20;
                packet = (void *)((u32)packet & addr_mask);
                *(s32 *)ot_entry.value = (*(s32 *)ot_entry.value & length_mask) |
                                   (u32)packet;
            }
        }
        {
            ObjectNodeHeader *next_node = NODE_HEADER(node_data)->chain_next;
            if (next_node == NULL) {
                ((S_800252E0_8 *)(((S_800252E0_6 *)render_slot)->unk_00))->unk_8D0 =
                    scratch->unk_18;
                return 0;
            }
            node_data = NODE_BODY(next_node);
            position = next_node->position;
            appearance = next_node->sprite;
        }
    }
}

   /* payload in create_spark_effect */

   /* source in create_spark_effect */

/* Allocates a node, copies or jitters its source values, and initializes its fields. */
void create_spark_effect(ObjectPosition *source_data, s16 initial_1a, s16 initial_1c, s16 spawn_mode) {
    register ObjectPosition *source = source_data;
    register s16 field_1a = initial_1a;
    register s16 field_1c = initial_1c;
    register s16 mode = spawn_mode;
    register ObjectNodeHeader *node;

    node = allocate_flagged_object_node(0x202);
    if (node != 0) {
        s32 mode_test;

        node->update_callback = update_spark_effect;
        register_node(node, queue_projected_point_primitives);
        mode_test = mode << 0x10;
        {
            ObjectPosition *payload = node->position;

            s32 value_0a;

            if (mode_test == 0) {
                payload->x.w.i =
                    (u16)(((u16)source->x.w.i + (rand() & 0x1F)) - 0x10);
                payload->y.w.i =
                    (u16)(((u16)source->y.w.i + (rand() & 0x1F)) - 0x10);
                value_0a = (u16)source->z.w.i - 0x50;
            } else {
                payload->x.w.i = (u16)source->x.w.i;
                payload->y.w.i = (u16)source->y.w.i;
                value_0a = (u16)source->z.w.i;
            }
            payload->z.w.i = value_0a;
        }
        node->sprite->color.c.r = 0xF0;
        {
            JitteredSparkEffectBody *fields = NODE_BODY(node);

            fields->heading = field_1a;
            fields->remaining_steps = field_1c;
            fields->spawn_mode = mode;
        }
    }
}

#include "shared/object_flags.h"

/* Fade the effect color and set completion flags when red falls below eight. */
void fade_effect_color_below_eight(u16 *effect_data, ObjectPosition *unused, SpriteFrameState *color) {
    u8 red;
    u8 green;
    u8 blue;

    tint_effect_update_count[0]++;

    red = color->color.c.r;
    green = color->color.c.g;
    color->color.c.r = red - (red >> 3);
    blue = color->color.c.b;
    color->color.c.g = green - (green >> 3);
    color->color.c.b = blue - (blue >> 3);

    if (color->color.c.r < 8) {
        effect_data[-1] |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}


typedef struct S_80025654_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_80025654_2;   /* arg0 in create_effect_from_endpoints */

typedef struct S_80025654_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80025654_4;   /* arg1 in create_effect_from_endpoints */

/* Creates an object with initial values, endpoint differences, and copied settings. */
void *create_effect_from_endpoints(S_80025654_2 *endpoints, S_80025654_4 *settings) {
    ObjectPosition *transition;
    ObjectNodeHeader *object;
    SpriteFrameState *object_settings;

    object = allocate_flagged_object_node(0x202);
    if (object != 0) {
        object->update_callback = fade_effect_color_below_eight;
        register_node(object, draw_linked_segment_aligned_quads);
        transition = object->position;
        transition->x.w.i = (u16) endpoints->unk_02;
        transition->y.w.i = (u16) endpoints->unk_06;
        transition->z.w.i = (u16) endpoints->unk_0A;
        *((s16 *)&transition->velocity_x + 1) = (s16) (endpoints->unk_02 - endpoints->unk_0E);
        *((s16 *)&transition->velocity_y + 1) = (s16) (endpoints->unk_06 - endpoints->unk_12);
        *((s16 *)&transition->velocity_z + 1) = (s16) (endpoints->unk_0A - endpoints->unk_16);
        object_settings = object->sprite;
        object_settings->scale_x = (u16) settings->unk_1C;
        object_settings->scale_y = (u16) settings->unk_1E;
        object_settings->color.word = (s32) settings->unk_0C;
        object_settings->source = settings->unk_08;
        object_settings->flags = (u16) settings->unk_14;
    }
    return object;
}

extern u8 D_800E1CD5[9];

/* Conditionally applies D_800E1CD5 using a check indexed by the supplied value's low byte. */
void apply_indexed_effect_condition(ActorRecord *target, u8 packedValue, ActorRecord *owner_context) {
    if (try_trigger_target_record_effect(target, 1, owner_context) == 0) {
        s32 valueGroupIndex = packedValue >> 2;
        valueGroupIndex += 2;
        /*
         * BUG: set_or_clear_actor_status_slot returns a slot index (0..3), or -1 on
         * failure. Testing it as nonzero misreports slot 0 as failure and -1 as success.
         * Slot-0 success loses its message; rejected insertion prints success.
         * try_apply_confusion_status uses the nonnegative success test.
         */
        if ((set_or_clear_actor_status_slot(target, 0x15, valueGroupIndex) << 16) != 0) {
            adjust_source_value_and_finalize(target, D_800E1CD5);
        }
    }
}
