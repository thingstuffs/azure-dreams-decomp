#include "shared/object_node_flags.h"
#include "engine/graphics/sprite_scratch.h"
#include "shared/dungeon_height_query.h"
#include "sdk/libc.h"
#include "shared/audio_commands.h"
/* Targeted moving effects, radial color animation, shaded lines, and fragment creation. */
#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "shared/entity.h"
#include "modules/dungeon_native_abi.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "dungeon/effect/shaded_quad_scratch.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/effect/sprite.h"
#include "dungeon/actor/status.h"
#include "dungeon.h"
#include "dungeon/item.h"
#include "engine/graphics.h"
#include "slus.h"

struct S_func_81886800_1 {
    ActorRecord *owner;
    void *unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    s16 unk_10;
    u8 unk_12;
    u8 pad_13[0x1];
    u16 unk_14;
    s16 unk_16;
    u16 unk_18;
    u8 pad_1A[0x2];
    union {
        u32 u32;
        struct {
            u8 pad_1C[0x2];
            union {
                s16 s16;
                struct {
                    union {
                        s8 s8;
                        u8 u8;
                    } unk_1E;
                    union {
                        s8 s8;
                        u8 u8;
                    } unk_1F;
                } parts;
            } unk_1E;
        } parts;
    } unk_1C;
    union {
        s16 s16;
        struct {
            u8 unk_20;
            u8 unk_21;
        } parts;
    } unk_20;
    u8 pad_22[0x6];
    void *unk_28;
    union {
        s32 s32;
        struct {
            u8 pad_2C[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_2E;
        } parts;
    } unk_2C;
    u8 pad_30[0x28];
    s16 unk_58;
};



typedef struct S_func_81886800_4 {
    u16 unk_00;
} S_func_81886800_4;

typedef struct S_func_81886800_5 {
    u16 unk_00;
} S_func_81886800_5;

typedef struct S_func_81886800_6 {
    u16 unk_00;
} S_func_81886800_6;

typedef struct S_func_81886800_7 {
    s32 unk_00;
} S_func_81886800_7;


typedef struct S_func_81886800_9 {
    s32 unk_00;
} S_func_81886800_9;



typedef struct S_func_81886800_12 {
    u16 unk_00;
} S_func_81886800_12;


typedef struct S_func_81886800_14 {
    s16 unk_00;
} S_func_81886800_14;

typedef struct S_func_81886800_15 {
    u16 unk_00;
} S_func_81886800_15;

typedef struct S_func_81886800_17 {
    u16 unk_00;
} S_func_81886800_17;

#include "dungeon/effect/screen.h"
#include "dungeon/system.h"
#include "dungeon/data.h"

extern s32 rsin(s32);
extern void ratan2(s32, s32);

extern u8 D_8002632C[];
extern u8 D_80026344[];
extern u8 D_80026878[];

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_18a6800_entry)(RadialSequenceBody *, ObjectPosition *, SpriteFrameState *) = run_radial_sprite_sequence;

/* Initialize and update a moving effect through targeting, collision, and fading states. */
void run_radial_sprite_sequence(RadialSequenceBody *effect, ObjectPosition *motion, SpriteFrameState *sprite)
{
    ActorRecord *owner;
    ObjectNodeHeader *owner_base;
    ObjectPosition *owner_motion;
    ActorRecord *target_object;
    ActorRecord *target_actor;
    s32 state;
    u16 owner_flags;
    s16 surface_pos[3];
    GpuRectBuffer texture_rect;

    owner = effect->owner;
    state = (s16)effect->unk_0A;
    owner_base = NODE_HEADER(owner);
    owner_motion = owner_base->position;
    switch (state) {
    case 0:
    texture_rect.words[0] = 0x01000340;
    texture_rect.words[1] = 0x00200020;
    draw_textured_ellipse(D_8002632C, &texture_rect.rect, 1, 0);

    sprite->color.word = 0x00808080;
    sprite->scale_y = 0x555;
    sprite->scale_x = 0x555;
    sprite->source = D_80026344;
    ((S_func_81886800_4 *)(D_80026324))->unk_00 = 0;
    ((S_func_81886800_5 *)(D_80026328))->unk_00 = 0;
    ((S_func_81886800_6 *)(&D_8002632A))->unk_00 = 0;
    ((S_func_81886800_7 *)(radial_effect_colors))->unk_00 = 0;
    owner_flags = owner->facing;
    ((S_func_81886800_9 *)(D_80026474))->unk_00 = 0;
    effect->unk_16 = (owner_flags >> 9) & 7;
    effect->unk_0A++;

    case 1:
    if (get_sprite_attachment_vector(
            owner_base->sprite->source,
            owner_base->sprite, surface_pos, 0) == 0) {
        if ((owner_base->sprite->flags & 0x8000) == 0) {
            break;
        }
    }

    motion->x.w.i = owner_motion->x.w.i;
    motion->y.w.i = owner_motion->y.w.i;
    if (owner_base->sprite->flags & 0x8000) {
        motion->z.w.i = owner_motion->z.w.i - 64;
        effect->unk_2C.parts.unk_2E.u16 = motion->z.w.i;
    } else {
        motion->z.w.i = owner_motion->z.w.i + surface_pos[2];
        effect->unk_2C.parts.unk_2E.u16 = motion->z.w.i;
    }

    {
        S_func_81886800_12 *effect_flags = effect->unk_04;
        if ((effect_flags->unk_00 & 0x80) == 0) {
            break;
        }
        if ((effect->unk_12 & 4) == 0) {
            register_node((u8 *)effect - 0x20, project_sprite_chain);
            sprite->tpage_abr = 0x20;
            sprite->color.c.b = 0x80;
            sprite->color.c.g = 0x80;
            sprite->color.c.r = 0x80;
            sprite->flags |= 0xC;
            effect->unk_12 |= 4;
        }
    }

    if (owner->target != 0) {
        {
            ObjectPosition *target_position;
            SpriteFrameState *owner_sprite;

            target_position = NODE_HEADER(owner->target)->position;
            effect->unk_0C = target_position->x.w.i;
            effect->unk_0E = target_position->y.w.i;
            {
                u8 target_kind;
                u8 *height_offsets;

                height_offsets = entity_height_offsets;
                target_actor = owner->target;
                target_kind = target_actor->species;
                effect->unk_10 =
                    target_position->z.w.i - height_offsets[target_kind];
            }
            {
                s16 direction;
                u8 tile_coord;
                direction = effect->unk_16;
                owner_sprite = NODE_HEADER(owner)->sprite;
                tile_coord = owner_sprite->tile_x +
                        ((u8 *)dir_step_x)[(s32)direction * 2];
                effect->unk_1C.parts.unk_1E.parts.unk_1E.u8 = tile_coord;
                effect->unk_20.parts.unk_20 = tile_coord;
            }
            {
                s16 direction;
                u8 tile_coord;
                direction = effect->unk_16;
                tile_coord = owner_sprite->tile_y +
                        ((u8 *)dir_step_y)[(s32)direction * 2];
                effect->unk_1C.parts.unk_1E.parts.unk_1F.u8 = tile_coord;
                effect->unk_20.parts.unk_21 = tile_coord;
            }
            {
                s32 owner_tile;
                s32 tile_distance;
                owner_tile = owner->target_tile_x;
                state = owner_sprite->tile_x;
                if (owner_tile == state) {
                    owner_tile = owner->target_tile_y;
                    state = owner_sprite->tile_y;
                    tile_distance = owner_tile - state;
                } else {
                    tile_distance = owner_tile - state;
                }
                tile_distance = abs(tile_distance);
                effect->unk_14 = tile_distance + 1;
            }
        }
    } else {
        effect->unk_14 = 8;
        effect->unk_0C = motion->x.w.i;
        effect->unk_0E = motion->y.w.i;
        effect->unk_10 = owner->ground_height - 80;
    }
    {
        u8 *x_offsets = ((u8 *)dir_step_x);
        s16 direction = effect->unk_16;
        ((Fixed1616 *)&motion->velocity_x)->w.i =
            ((S_func_81886800_14 *)(x_offsets + (s32)direction * 2))->unk_00 * 8;
        {
            u8 *y_offsets = ((u8 *)dir_step_y);
            s16 y_direction = effect->unk_16;
            ((Fixed1616 *)&motion->velocity_y)->w.i =
                ((S_func_81886800_14 *)(y_offsets + (s32)y_direction * 2))->unk_00 * 8;
        }
    }
    effect->unk_0A++;
    break;

    case 2:
    {
        s32 x_velocity;
        motion->x.v += motion->velocity_x;
        x_velocity = motion->velocity_x + (motion->velocity_x >> 4);
        motion->velocity_x = x_velocity;
        if ((x_velocity < 0 ? -x_velocity : x_velocity) > 0x200000) {
            x_velocity = x_velocity > 0 ? 0x200000 : -0x200000;
            motion->velocity_x = x_velocity;
        }
    }
    {
        s32 y_velocity;
        motion->y.v += motion->velocity_y;
        y_velocity = motion->velocity_y + (motion->velocity_y >> 4);
        motion->velocity_y = y_velocity;
        if ((y_velocity < 0 ? -y_velocity : y_velocity) > 0x200000) {
            y_velocity = y_velocity > 0 ? 0x200000 : -0x200000;
            motion->velocity_y = y_velocity;
        }
    }
    {
        s32 height = effect->unk_2C.s32;
        height += (((s32)effect->unk_10 << 16) - height) >> 4;
        effect->unk_2C.s32 = height;
        height = motion->z.v;
        height += (((s32)effect->unk_10 << 16) - height) >> 4;
        motion->z.v = height;
    }
    {
        s32 bob_offset = rsin((s32)(s16)effect->unk_18 << 7);
        motion->z.v += bob_offset << 6;
    }
    create_mesh_fade_effect(motion, sprite);
    {
        s32 tile_coord = motion->x.w.i;
        if (tile_coord < 0) {
            tile_coord += 63;
        }
        effect->unk_1C.parts.unk_1E.parts.unk_1E.u8 = tile_coord >> 6;
        tile_coord = motion->y.w.i;
        effect->unk_1C.parts.unk_1E.parts.unk_1F.u8 = (tile_coord / 64);
    }
    if (effect->unk_20.s16 == effect->unk_1C.parts.unk_1E.s16) {
        break;
    }
    if (owner->target != 0) {
        if (effect->unk_58 == 0) {
            s32 target_distance = get_byte_coordinate_chebyshev_distance(
                (effect)->unk_1C.parts.unk_1E.parts.unk_1E.u8,
                (effect)->unk_1C.parts.unk_1E.parts.unk_1F.u8,
                (u8)owner->target_tile_x,
                (u8)owner->target_tile_y);
            target_distance = (s16)target_distance;
            if (target_distance < 5) {
                effect->unk_58 = 1;
                play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            }
        }
    }
    if (owner->target != 0) {
        if ((*(u32 *)&owner->unk_70 & 0xFFFF0000) ==
            ((effect)->unk_1C.u32 & 0xFFFF0000)) {
            ObjectPosition *snapped_motion;

            snapped_motion = motion;
            {
                s32 coordinate = owner->target_tile_x;
                motion->x.w.i = (coordinate << 6) + 0x20;
            }
            {
                s32 coordinate = owner->target_tile_y;
                motion->y.w.i = (coordinate << 6) + 0x20;
            }
            motion->z.w.i = effect->unk_10;
            create_mesh_fade_effect(snapped_motion, sprite);
            {
                u16 next_state = effect->unk_0A;
                u16 target_id;
                target_actor = owner->target;
                target_id = target_actor->ground_height;
                next_state++;
                effect->unk_0A = next_state;
                ((S_func_81886800_15 *)(D_80026878))->unk_00 = target_id;
            }
            break;
        }
    }

    {
        u8 x = effect->unk_1C.parts.unk_1E.parts.unk_1E.u8;
        u8 y = effect->unk_1C.parts.unk_1E.parts.unk_1F.u8;
        s32 timer = effect->unk_14 - 1;
        s32 collision;
        effect->unk_14 = timer;
        effect->unk_20.parts.unk_20 = x;
        effect->unk_20.parts.unk_21 = y;
        if ((timer << 16) != 0) {
            s32 world_x = (((s32)effect->unk_1C.parts.unk_1E.parts.unk_1E.s8 << 6) + 0x20) & 0xFFE0;
            s32 world_y = (((s32)effect->unk_1C.parts.unk_1E.parts.unk_1F.s8 << 6) + 0x20) & 0xFFE0;
            collision = check_left_tile_and_center_height(world_x, world_y, effect->unk_2C.parts.unk_2E.s16);
            if ((collision << 16) == 0) {
                break;
            }
        }
        effect->unk_0A = 16;
        break;
    }

    case 3:
    ratan2(((Fixed1616 *)&motion->velocity_x)->w.i, ((Fixed1616 *)&motion->velocity_y)->w.i);
    target_object = owner->target;
    effect->unk_28 = create_object_ring_effect(
        effect, motion, target_object->ground_height, target_object);
    if (effect->unk_28 == 0) {
        break;
    }
    effect->unk_0A++;
    case 4:
    {
        sprite->color.c.r -= sprite->color.c.r >> 2;
        sprite->color.c.g -= sprite->color.c.g >> 2;
        sprite->color.c.b -= sprite->color.c.b >> 2;
        if ((((ObjectNodeHeader *)effect->unk_28)->flags & 0x8000) == 0) {
            break;
        }
        if (owner->target != 0) {
            apply_timed_status_to_target(owner->target,
                          effect->unk_09, owner);
        }
        effect->unk_0A = 17;
        break;
    }

    case 16:
    {
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        {
            s32 target_height = (s32)effect->unk_10 << 16;
            s32 height = motion->z.v;
            height += (target_height - height) >> 4;
            motion->z.v = height;
        }
        sprite->color.c.r -= sprite->color.c.r >> 1;
        sprite->color.c.g -= sprite->color.c.g >> 1;
        sprite->color.c.b -= sprite->color.c.b >> 1;
        create_mesh_fade_effect(motion, sprite);
        if (sprite->color.c.r < 2) {
            effect->unk_0A++;
        }
        break;
    }

    case 17:
    if ((s16)((S_func_81886800_17 *)(&D_80026326))->unk_00 != 0) {
        break;
    }
    g_dungeon_status.active_actor = 0;
    NODE_HEADER(effect)->flags |= NODE_REMOVE;
    object_flag_block.flags |= 0x8000;

    }
    {
        u16 frame_count = effect->unk_18;
        ((S_func_81886800_17 *)(&D_80026326))->unk_00 = 0;
        effect->unk_18 = frame_count + 1;
    }
}


typedef struct RadialColorEffectBody {
    ActorRecord *target;
    u8 pad4[6];
    s16 state;
    u8 padC[0xC];
    s16 timer;
    u16 ticks;
} RadialColorEffectBody;


#include "slus/animation_tick_data.h"

/* Advances the effect through color buildup, flicker, and fade, then restores the object color. */
void create_radial_effect_from_source(RadialColorEffectBody *effect, ObjectPosition *pos)
{
    ActorRecord *object;
    SpriteFrameState *color;
    s32 burst_index;
    s32 state;
    s32 channel_value;

    D_80026326++;
    state = effect->state;
    switch (state) {
    case 0:
        object = effect->target;
        object->flags1C |= 0x10000000;
        effect->state++;

    case 1:
        color = NODE_HEADER(effect->target)->sprite;
        channel_value = color->color.c.r - 1;
        color->color.c.r = channel_value;
        if ((u8)channel_value < 0x40) {
            color->color.c.r = 0x40;
        }
        channel_value = color->color.c.g - 1;
        color->color.c.g = channel_value;
        if ((u8)channel_value < 0x40) {
            color->color.c.g = 0x40;
        }
        channel_value = color->color.c.b + 1;
        color->color.c.b = channel_value;
        if ((u8)channel_value >= 0xC1) {
            color->color.c.b = 0xC0;
        }
        if (D_80026328[0] != 0) {
            effect->state++;
        }
        break;

    case 2:
    {
        u8 *primary_rgb;
        u8 *secondary_rgb;

        effect->timer++;
        radial_effect_colors[0] = effect->timer * 2;
        primary_rgb = radial_effect_colors;
        primary_rgb[1] = effect->timer * 4;
        primary_rgb[2] = effect->timer * 14;
        D_80026474[0] = effect->timer * 10;
        secondary_rgb = D_80026474;
        secondary_rgb[1] = effect->timer * 11;
        secondary_rgb[2] = effect->timer * 14;

        for (burst_index = 0; burst_index < 4; burst_index++) {
            create_falling_fading_sprite(pos->x.w.i, pos->y.w.i, pos->z.w.i);
        }
        if (effect->timer >= 0x10) {
            effect->timer = 0xA0;
            effect->state++;
        }
        break;
    }

    case 3:
    {
        u8 *random_rgb;

        D_80026474[0] = (rand() % 0x3F) - 0x80;
        random_rgb = D_80026474;
        random_rgb[1] = (rand() % 0x3F) - 0x80;
        effect->timer -= last_frame_ticks;
        if (effect->timer <= 0) {
            create_quad_fragment_effects();
            effect->timer = 0x10;
            effect->state++;
        }
        break;
    }

    case 4:
    {
        u8 *primary_rgb;
        u8 *secondary_rgb;

        radial_effect_colors[0] += -(s32)radial_effect_colors[0] / effect->timer;
        primary_rgb = radial_effect_colors;
        primary_rgb[1] += -(s32)primary_rgb[1] / effect->timer;
        primary_rgb[2] += -(s32)primary_rgb[2] / effect->timer;
        D_80026474[0] += -(s32)D_80026474[0] / effect->timer;
        secondary_rgb = D_80026474;
        secondary_rgb[1] += -(s32)secondary_rgb[1] / effect->timer;
        secondary_rgb[2] += -(s32)secondary_rgb[2] / effect->timer;
    }

        {
            s32 neutral_level;
            s32 effect_count;
            u32 flags;
            u32 clear_effect_mask;
            ActorRecord *fade_object;

            color = NODE_HEADER(effect->target)->sprite;
            neutral_level = 0x80;
            color->color.c.r += (neutral_level - color->color.c.r) / effect->timer;
            color->color.c.g += (neutral_level - color->color.c.g) / effect->timer;
            color->color.c.b += (neutral_level - color->color.c.b) / effect->timer;
            effect->timer--;
            if (effect->timer <= 0) {
                clear_effect_mask = 0xEFFFFFFF;
                color->color.c.r = neutral_level;
                color->color.c.g = neutral_level;
                color->color.c.b = neutral_level;
                fade_object = effect->target;
                effect_count = D_80026324[0];
                flags = fade_object->flags1C;
                effect_count--;
                D_80026324[0] = effect_count;
                flags &= clear_effect_mask;
                fade_object->flags1C = flags;
                NODE_HEADER(effect)->flags |= NODE_REMOVE;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            }
            break;
        }
    }
    effect->ticks++;
}

/* Creates an object, copies three source fields to its child, and runs 16 child setup steps. */
void *create_object_ring_effect(RadialSequenceBody *controller, ObjectPosition *source, s32 unused, ActorRecord *target)
{
    RadialColorEffectBody *body;
    register ActorRecord *saved_target;
    ObjectNodeHeader *parent;
    s32 step;
    ObjectPosition *child;
    ObjectNodeHeader *object;
    u16 counter;

    saved_target = target;
    object = allocate_list_node(2, &NODE_HEADER(controller)->next);
    if (object != 0) {
        counter = D_80026324[0];
        object->update_callback = create_radial_effect_from_source;
        D_80026324[0] = counter + 1;
        register_node(object, queue_glow_grid_quads);

        child = object->position;
        child->x.w.i = source->x.w.i;
        step = 0;
        child->y.w.i = source->y.w.i;
        child->z.w.i = source->z.w.i;

        parent = NODE_HEADER(controller);
        body = NODE_BODY(object);
        body->target = saved_target;

        do {
            create_offset_particle_emitter(child, (s16)(step << 8), 0x40, -0x100, parent);
            step += 1;
        } while (step < 0x10);
    }
    return object;
}
#include "shared/object_node.h"

extern u16 D_80026326;

/* Retail 81887570 (update_mesh_fade_color): fade the colour by 1/8 per call and mark the effect (header and global
 * flags) finished once red falls below eight.  effect is the effect's record; its header precedes it. */
void update_mesh_fade_color(void *effect, ObjectPosition *unused, SpriteFrameState *color) {
    u8 red;
    u8 green;
    u8 blue;

    D_80026326++;

    red = color->color.c.r;
    green = color->color.c.g;
    color->color.c.r = red - (red >> 3);
    blue = color->color.c.b;
    color->color.c.g = green - (green >> 3);
    color->color.c.b = blue - (blue >> 3);

    if (color->color.c.r < 8) {
        NODE_HEADER(effect)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "shared/sprite_frame_state.h"

extern u8 linked_mesh_processor_address[];

/* Retail 818875E8 (create_mesh_fade_effect): creates a fade object (updated each frame by update_mesh_fade_color) with its start
 * values, per-channel start - end differences and a copy of the settings. */
ObjectNodeHeader *create_mesh_fade_effect(ObjectPosition *position, SpriteFrameState *settings) {
    LineEndpoints *transition;
    ObjectNodeHeader *object;
    SpriteFrameState *object_settings;

    object = allocate_flagged_object_node(0x202);
    if (object != NULL) {
        object->update_callback = update_mesh_fade_color;
        register_node(object, &linked_mesh_processor_address);
        transition = (LineEndpoints *)object->position;
        transition->start[0].w.i = position->x.w.i;
        transition->start[1].w.i = position->y.w.i;
        transition->start[2].w.i = position->z.w.i;
        transition->end[0].w.i = ((u32)position->x.v >> 16) - ((u32)position->velocity_x >> 16);
        transition->end[1].w.i = ((u32)position->y.v >> 16) - ((u32)position->velocity_y >> 16);
        transition->end[2].w.i = ((u32)position->z.v >> 16) - ((u32)position->velocity_z >> 16);
        object_settings = object->sprite;
        object_settings->scale_x = settings->scale_x;
        object_settings->scale_y = settings->scale_y;
        object_settings->color.word = settings->color.word;
        object_settings->source = settings->source;
        object_settings->flags = settings->flags;
    }
    return object;
}
#include "shared/game_work.h"
#include "sdk/libgpu.h"

#include "sdk/libgpu_types.h"
#include "sdk/libgpu_packets.h"
#include "shared/gpu_packets.h"
typedef struct EmptyCallArg {
} EmptyCallArg;

extern u32 RotTransPers4(
    void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, ...);

/*
 * Joins adjacent 16-vertex rows of staged_glow_data with translucent shaded quads, alternating the
 * two edge colors by row. Projects each quad and queues it with its draw mode when its biased
 * depth is below 0x1E0, then saves the primitive cursor.
 */
s32 queue_glow_grid_quads(void)
{
    s32 quad_index = 0;
    Scratch *scratch = (Scratch *)0x1F800000;
    u8 *state = g_game_work.draw_buffer;
    u8 *primitive_start = *(u8 **)(state + 0x8D0);
    u32 *vertices;
    u8 *vertex_record;

    scratch->table = (u32 *)(state + 0xB0);
    scratch->current = primitive_start;

            /* This address is needed only by the loop's terminal writeback. */
    {
        void **state_slot = &g_game_work.draw_buffer;

        if (D_8002632A > 0) {
            vertices = staged_glow_data;
            vertex_record = (u8 *)vertices;

            do {
                POLY_G4 *quad;
                u32 *near_vertex;
                u32 *near_next_vertex;
                u32 *far_vertex;
                u32 *far_next_vertex;
                u32 *next_row;
                u32 *far_next_ptr;
                u32 far_next_xy;
                s32 row_start;
                s32 far_index;
                u16 near_z;
                u16 far_z;
                EmptyCallArg late_stores;

                near_vertex = &scratch->value70;
                row_start = quad_index & ~0xF;
                quad = scratch->current;
                near_next_vertex = &scratch->value78;
                far_vertex = &scratch->value80;
                scratch->current = quad + 1;
                scratch->value70 = *(u32 *)vertex_record;
                scratch->value78 = vertices[
                    ((u32)row_start + (u32)((quad_index + 1) & 0xF)) * 2];
                next_row = vertices + 0x20;
                far_next_ptr = (u32 *)(((u32)row_start + (u32)((quad_index + 1) & 0xF)) * 8 + (unsigned long)next_row);
                scratch->value80 = next_row[quad_index * 2];
                far_next_xy = *far_next_ptr;
                far_next_vertex = &scratch->value88;
                near_z = *(u16 *)(vertex_record + 4);
                scratch->half74 = near_z;
                scratch->half7c = near_z;
                far_index = quad_index + 16;
                far_z = ((u16 *)vertices)[(far_index * 4) + 2];

                scratch->index = RotTransPers4(
                    near_vertex, near_next_vertex, far_vertex, far_next_vertex,
                    (u32 *)&quad->x0, (u32 *)&quad->x1,
                    (u32 *)&quad->x2, (u32 *)&quad->x3,
                    &scratch->out90, &scratch->out94,
                    (scratch->value88 = far_next_xy,
                     scratch->half84 = far_z,
                     scratch->half8c = far_z,
                     late_stores));
                scratch->index -= 8;

                if (scratch->index < 0x1E0U) {
                    if ((quad_index % 32) < 16) {
                        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
                        *(u32 *)&quad->red1 = (*(u32 *)radial_effect_colors);
                        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
                        *(u32 *)&quad->red0 = (*(u32 *)radial_effect_colors);
                        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
                        *(u32 *)&quad->red3 = (*(u32 *)D_80026474);
                        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
                        *(u32 *)&quad->red2 = (*(u32 *)D_80026474);
                    } else {
                        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
                        *(u32 *)&quad->red3 = (*(u32 *)radial_effect_colors);
                        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
                        *(u32 *)&quad->red2 = (*(u32 *)radial_effect_colors);
                        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
                        *(u32 *)&quad->red1 = (*(u32 *)D_80026474);
                        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
                        *(u32 *)&quad->red0 = (*(u32 *)D_80026474);
                    }

                    SetPolyG4(quad);
                    quad->code |= 2;
                    AddPrim(scratch->table + scratch->index, quad);

                    {
                        DR_MODE *draw_mode = scratch->current;
                        scratch->current = draw_mode + 1;
                        SetDrawMode(draw_mode, 0, 0,
                                      (u16)GetTPage(0, 1, 0, 0), 0);
                        AddPrim(scratch->table + scratch->index,
                                      draw_mode);
                    }
                }

                vertex_record += 8;
                quad_index++;
            } while (quad_index < D_8002632A);
        }
        ((GpuContext *)*state_slot)->packetCursor = scratch->current;
    }
    return 0;
}




typedef struct S_80025160_2 {
    u8 pad_00[0x6328];
    s16 unk_6328;
} S_80025160_2;   /* flag_page in update_offset_particle_emitter */

typedef struct S_80025160_3 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80025160_3;   /* flags_page in update_offset_particle_emitter */

#define COUNTER D_80026326

typedef struct Global26326 {
    u16 counter;
    s16 flag;
    u16 unused[3];
} Global26326;

typedef struct Global26328 {
    s16 flag;
    u16 unused[4];
} Global26328;

typedef struct Global814A0 {
    s32 flags;
    s32 unused[2];
} Global814A0;

/*
 * Steps the blue effect through growth, a shared-flag wait, a 16-tick delay, and a final sweep to
 * removal. May spawn a damped angular child during growth and signals D_80026328 for effect code
 * 0x6F.
 */
void update_offset_particle_emitter(GradientLineParticleBody *effect, ObjectPosition *context, SpriteFrameState *visual) {
    s16 state;
    u16 value;
    u16 angle;
    u16 damped_value;
    s32 effect_param;
    s32 angle_shifted;
    ObjectNodeHeader *owner;
    S_80025160_2 *flag_page;
    S_80025160_3 *flags_page;

    COUNTER = COUNTER + 1;
    state = effect->phase;

    switch (state) {
    case 0:
        value = visual->depth_bias + 0x80;
        visual->depth_bias = value;
        if ((s16)value > 0x100) {
            visual->depth_bias = 0x100;
            if (effect->slot < 0x61) {
                damped_value = effect->radius;
                angle = effect->height_offset;
                effect_param = effect->angle;
                damped_value = damped_value - ((s32)(damped_value << 16) >> 19);
                effect->radius = damped_value;
                angle = angle + 0x80;
                owner = NODE_HEADER(effect);
                effect->height_offset = angle;
                angle_shifted = angle << 16;
                create_offset_particle_emitter(context, effect_param, effect->radius,
                              angle_shifted >> 16, owner);
            }
            effect->phase++;
            if (effect->slot == 0x6F) {
                D_80026328[0] = 1;
            }
        }
        break;
    case 1:
        flag_page = (S_80025160_2 *)0x80020000;
        if (flag_page->unk_6328 != 0) {
            {
                s16 signed_ramp = -0x100;
                visual->depth_bias = signed_ramp;
            }
            effect->delay = 0x10;
            effect->phase++;
        }
        break;
    case 2:
        value = effect->delay - 1;
        effect->delay = value;
        if ((value << 16) > 0) {
            break;
        }
        effect->phase++;
                        /* fall through */
    case 3:
        value = visual->depth_bias + 0x80;
        visual->depth_bias = value;
        if ((value << 16) >= 0) {
            flags_page = (S_80025160_3 *)0x80080000;
            NODE_HEADER(effect)->flags |= 0x8000;
            flags_page->unk_14A0 |= 0x8000;
        }
        break;
    default:
        break;
    }
    visual->color.c.r = 0x20;
    visual->color.c.g = 0x40;
    visual->color.c.b = 0xE0;
}
#include "shared/game_work.h"
extern s32 RotTransPers(void *, void *, void *, void *);
typedef struct GradientLinePacket {
    GpuLinkTag tag;
    SpriteColor color0;
    s32 xy0;
    SpriteColor color1;
    s32 xy1;
} GradientLinePacket;

/*
 * Walks the linked nodes and interpolates one line endpoint according to the signed blend, saving
 * extended positive-blend points into staged_glow_data. Projects the endpoints and queues a
 * half-brightness gradient line and draw mode at their average depth when it is below 0x1E0.
 */
s32 queue_shaded_line_chain(GradientLineParticleBody *first_owner, ObjectPosition *first_vertices, SpriteFrameState *first_line)
{
    GpuContext *render_data = g_game_work.draw_buffer;
    GradientLineParticleBody *owner = first_owner;
    LineEndpoints *points = (LineEndpoints *)first_vertices;
    SpriteFrameState *line = first_line;
    SpriteQuadScratch *scratch = SPRITE_SCRATCH;
    GradientLinePacket *line_packet;
    GradientLinePacket *packet;
    u16 red_blue;
    u8 green;
    ObjectNodeHeader *next_node;
    s32 avg_depth;
    s16 blend;
    struct DR_MODE *draw_mode;
    s32 point_index;
    s32 color_word;
    register void **render_state = &g_game_work.draw_buffer;
    scratch->packet_cursor = render_data->packetCursor;
    scratch->ordering_table = &render_data->orderTag;
    for (;;) {
        line_packet = scratch->packet_cursor;
        scratch->packet_cursor = line_packet + 1;
        blend = line->depth_bias;
        if (blend >= 0) {
            scratch->position.vx = points->end[0].w.i;
            scratch->position.vy = points->end[1].w.i;
            scratch->position.vz = points->end[2].w.i;
            scratch->sort_depth = RotTransPers(&scratch->position, &line_packet->xy0, &scratch->depth_cue, &scratch->gte_flag);
            scratch->position.vx =
                points->end[0].w.i +
                (((points->start[0].w.i - points->end[0].w.i) * line->depth_bias) >> 8);
            scratch->position.vy =
                points->end[1].w.i +
                (((points->start[1].w.i - points->end[1].w.i) * line->depth_bias) >> 8);
            scratch->position.vz =
                points->end[2].w.i +
                (((points->start[2].w.i - points->end[2].w.i) * line->depth_bias) >> 8);
            point_index = owner->slot + 0x10;
            if (D_8002632A < point_index) {
                GlowPoint *point_table = (GlowPoint *)staged_glow_data;
                s32 table_index;
                u16 coord;
                point_table[point_index].x = scratch->position.vx;
                table_index = owner->slot;
                coord = scratch->position.vy;
                table_index += 0x10;
                point_table[table_index].y = coord;
                table_index = owner->slot;
                coord = scratch->position.vz;
                table_index += 0x10;
                point_table[table_index].z = coord;
            }
        } else {
            scratch->position.vx = points->start[0].w.i -
                (((points->end[0].w.i - points->start[0].w.i) * blend) >> 8);
            scratch->position.vy =
                points->start[1].w.i -
                (((points->end[1].w.i - points->start[1].w.i) * line->depth_bias) >> 8);
            scratch->position.vz =
                points->start[2].w.i -
                (((points->end[2].w.i - points->start[2].w.i) * line->depth_bias) >> 8);
            scratch->sort_depth = RotTransPers(&scratch->position, &line_packet->xy0, &scratch->depth_cue, &scratch->gte_flag);
            scratch->position.vx = points->start[0].w.i;
            scratch->position.vy = points->start[1].w.i;
            scratch->position.vz = points->start[2].w.i;
        }
        avg_depth = scratch->sort_depth + RotTransPers(&scratch->position, &line_packet->xy1, &scratch->depth_cue,
            &scratch->gte_flag);
        avg_depth >>= 1;
        scratch->sort_depth = avg_depth;
        if (((u32) avg_depth) < 0x1E0U) {
            packet = line_packet;
            packet->tag.len = (color_word = line->color.word, 4);
            packet->color0.word = color_word;
            red_blue = packet->color0.c.r;
            packet->color0.c.code = 0x52;
            green = packet->color0.c.g;
            red_blue >>= 1;
            packet->color1.c.r = red_blue;
            red_blue = packet->color0.c.b;
            green >>= 1;
            packet->color1.c.g = green;
            red_blue >>= 1;
            packet->color1.c.b = red_blue;
            AddPrim(scratch->ordering_table + scratch->sort_depth, packet);
            draw_mode = scratch->packet_cursor;
            scratch->packet_cursor = draw_mode + 1;
            SetDrawMode(draw_mode, 0, 0, GetTPage(0, 1, 0, 0) & 0xFFFF, 0);
            AddPrim(scratch->ordering_table + scratch->sort_depth, draw_mode);
        }
        next_node = NODE_HEADER(owner)->chain_next;
        if (next_node != 0) {
            owner = NODE_BODY(next_node);
            points = (LineEndpoints *)next_node->position;
            line = next_node->sprite;
            continue;
        }
        break;
    }
    ((GpuContext *)*render_state)->packetCursor = scratch->packet_cursor;
    return 0;
}
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"


s32 rsin(s32);                             /* extern */
s32 rcos(s32);                             /* extern */
extern s16 D_8002632A;
extern u8 D_80026878[];

/* Create an object offset from an origin and record its starting position. */
void *create_offset_particle_emitter(ObjectPosition *origin, s16 angle, s16 radius, s16 height_offset, ObjectNodeHeader *parent) {
    s16 height;
    u16 slot_index;
    u16 origin_x;
    u16 origin_z;
    u16 origin_y;
    GlowPoint *position_slot;
    u8 *position_table;
    LineEndpoints *positions;
    ObjectNodeHeader *object;
    GlowPoint *paired_slot;
    GradientLineParticleBody *object_data;

    object = allocate_list_node(0x202, &parent->next);
    if (object != NULL) {
        object->update_callback = update_offset_particle_emitter;
        register_node(object, queue_shaded_line_chain);
        positions = (LineEndpoints *)object->position;
        positions->start[0].w.i = (s16) (origin->x.w.i + ((s32) (rcos(angle) * radius) >> 0xF));
        positions->start[1].w.i = (s16) (origin->y.w.i + ((s32) (rsin(angle) * radius) >> 0xF));
        height = origin->z.w.i + ((s32) (height_offset << 0x10) >> 0x13);
        positions->start[2].w.i = height;
        if ((*(s16 *)D_80026878) < height) {
            positions->start[2].w.i = (*(s16 *)D_80026878);
        }
        positions->end[0].w.i = origin->x.w.i;
        positions->end[1].w.i = origin->y.w.i;
        positions->end[2].w.i = origin->z.w.i;
        object_data = (void *) 0xE04020;
        (*(s32 *)((u8 *)(object->sprite) + 0xC)) = (s32) object_data;
        slot_index = (u16)D_8002632A;
        object_data = NODE_BODY(object);
        object_data->angle = angle;
        object_data->height_offset = height_offset;
        object_data->radius = radius;
        object_data->slot = slot_index;
        if ((s16) slot_index < 0x71) {
            position_table = staged_glow_data;
            position_slot = (GlowPoint *)&position_table[(s16) slot_index * 8];
            origin_x = positions->end[0].w.i;
            paired_slot = (GlowPoint *)&position_table[((s16) slot_index + 0x10) * 8];
            position_slot->x = origin_x;
            paired_slot->x = origin_x;
            origin_y = positions->end[1].w.i;
            position_slot->y = origin_y;
            paired_slot->y = origin_y;
            origin_z = positions->end[2].w.i;
            D_8002632A = slot_index + 1;
            position_slot->z = origin_z;
            paired_slot->z = origin_z;
        }
    }
    return object;
}
#include "shared/object_flags.h"

typedef struct Actor {
    u8 pad00[0x1A];
    u16 timer;
} Actor;

typedef struct Motion {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

extern u16 D_80026326;

/*
 * Integrates velocity with X/Y damping and Z acceleration 0x4000, fades each color channel by one
 * quarter, and advances animation. Flags removal when the signed 16-bit lifetime expires.
 */
void update_falling_fading_sprite(Actor *actor, ObjectPosition *motion, SpriteFrameState *color)
{
    u16 *counter = &D_80026326;
    u16 timer;
    u8 red;
    u8 green;
    u8 blue;

    counter[0]++;

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;
    motion->z.v += motion->velocity_z;
    motion->velocity_x -= motion->velocity_x >> 3;
    motion->velocity_y -= motion->velocity_y >> 3;
    motion->velocity_z += 0x4000;

    red = color->color.c.r;
    green = color->color.c.g;
    color->color.c.r = red - (red >> 2);
    blue = color->color.c.b;
    color->color.c.g = green - (green >> 2);
    color->color.c.b = blue - (blue >> 2);

    advance_sprite_animation_and_textures(color);

    timer = actor->timer - 1;
    actor->timer = timer;
    if ((s16)timer <= 0) {
        *(u16 *)((u8 *)actor - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "shared/slus_callbacks.h"

struct Dst;
struct Elem;

#include "shared/sprite_source.h"
extern SpriteSourceEntry D_800263F8[];

/* Create a sprite effect at the given position with a randomized rotation. */
void create_falling_fading_sprite(s16 x, s16 y, s16 z) {
    ObjectPosition *transform;
    SpriteFrameState *sprite;
    ObjectNodeHeader *effect;

    effect = allocate_flagged_object_node(0x202);
    if (effect != NULL) {
        effect->update_callback = (s32 *)update_falling_fading_sprite;
        register_node(effect, project_sprite_chain);
        transform = effect->position;
        transform->x.w.i = x;
        transform->y.w.i = y;
        transform->z.w.i = z;
        *((s16 *)&transform->velocity_x + 1) = 0;
        *((s16 *)&transform->velocity_y + 1) = 0;
        *((s16 *)&transform->velocity_z + 1) = (s16) (rand() & 7);
        sprite = effect->sprite;
        sprite->color.word = 0x808080;
        select_record_entry_and_value(sprite, &D_800263F8, 0);
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->tpage_abr = 0x20;
        sprite->flags = (u16) (sprite->flags | 0xC);
        ((s16 *)NODE_BODY(effect))[0x1A / 2] = 0x10;
    }
}

extern void PushMatrix(s32);
extern void PopMatrix(void);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern void func_80065320(void *, void *, void *);
extern void RotMatrix(void *, void *);

#include "dungeon/effect/rotating_quad.h"
#include "shared/object_links.h"

typedef struct RadialQuadWork {
    u8 pad_00[0x1A];
    s16 frames_left;
    u8 pad_1C[0x14];
    RotatingQuadVertex vertices[4];
    RotatingQuadColor colors[2];
} RadialQuadWork;

/* Rotate and move an effect quad, fade its colors, and flag it when its lifetime ends. */
void update_rotating_quad_effect(RadialQuadWork *effect, ObjectPosition *motion_data, SpriteFrameState *rotation_data)
{
    u16 angles[3];
    s32 matrix[8];
    SpriteQuadScratch *scratch = SPRITE_SCRATCH;
    ObjectPosition *motion = motion_data;
    u16 *globals_page;
    s32 origin_z;
    u16 vertex_z;
    u16 update_count;
    u16 relative_z;
    s16 ticks_left;
    s32 ticks_test;

    scratch->vertices[0].vx = effect->vertices[0].x - (u16)motion->x.w.i;
    scratch->vertices[1].vx = effect->vertices[1].x - (u16)motion->x.w.i;
    scratch->vertices[2].vx = effect->vertices[2].x - (u16)motion->x.w.i;
    scratch->vertices[3].vx = effect->vertices[3].x - (u16)motion->x.w.i;
    scratch->vertices[0].vy = effect->vertices[0].y - (u16)motion->y.w.i;
    scratch->vertices[1].vy = effect->vertices[1].y - (u16)motion->y.w.i;
    scratch->vertices[2].vy = effect->vertices[2].y - (u16)motion->y.w.i;
    scratch->vertices[3].vy = effect->vertices[3].y - (u16)motion->y.w.i;
    scratch->vertices[0].vz = effect->vertices[0].z - (u16)motion->z.w.i;
    scratch->vertices[1].vz = effect->vertices[1].z - (u16)motion->z.w.i;
    globals_page = (u16 *)0x80020000;

    update_count = globals_page[0x6326 / 2];
    vertex_z = effect->vertices[2].z;
    origin_z = (u16)motion->z.w.i;
    update_count++;
    relative_z = vertex_z - origin_z;
    globals_page[0x6326 / 2] = update_count;
    scratch->vertices[2].vz = relative_z;
    scratch->vertices[3].vz = effect->vertices[3].z - (u16)motion->z.w.i;
    PushMatrix(origin_z);

    angles[0] = rotation_data->angle_x;
    angles[1] = rotation_data->angle_y;
    angles[2] = 0;
    matrix[7] = 0;
    matrix[6] = 0;
    matrix[5] = 0;
    RotMatrix(angles, matrix);
    SetTransMatrix(matrix);
    SetRotMatrix(matrix);

    func_80065320(&scratch->vertices[0], &scratch->rotated[0],
                  &scratch->gte_flag);
    func_80065320(&scratch->vertices[1], &scratch->rotated[1],
                  &scratch->gte_flag);
    func_80065320(&scratch->vertices[2], &scratch->rotated[2],
                  &scratch->gte_flag);
    func_80065320(&scratch->vertices[3], &scratch->rotated[3],
                  &scratch->gte_flag);
    PopMatrix();

    motion->x.v = motion->x.v + motion->velocity_x;
    motion->y.v = motion->y.v + motion->velocity_y;
    motion->z.v = motion->z.v + motion->velocity_z;

    effect->vertices[0].x = scratch->rotated[0].vx + (u16)motion->x.w.i;
    effect->vertices[1].x = scratch->rotated[1].vx + (u16)motion->x.w.i;
    effect->vertices[2].x = scratch->rotated[2].vx + (u16)motion->x.w.i;
    effect->vertices[3].x = scratch->rotated[3].vx + (u16)motion->x.w.i;
    effect->vertices[0].y = scratch->rotated[0].vy + (u16)motion->y.w.i;
    effect->vertices[1].y = scratch->rotated[1].vy + (u16)motion->y.w.i;
    effect->vertices[2].y = scratch->rotated[2].vy + (u16)motion->y.w.i;
    effect->vertices[3].y = scratch->rotated[3].vy + (u16)motion->y.w.i;
    effect->vertices[0].z = scratch->rotated[0].vz + (u16)motion->z.w.i;

    effect->vertices[1].z = scratch->rotated[1].vz + (u16)motion->z.w.i;
    effect->vertices[2].z = scratch->rotated[2].vz + (u16)motion->z.w.i;
    effect->vertices[3].z = scratch->rotated[3].vz + (u16)motion->z.w.i;
    effect->colors[0].r -= effect->colors[0].r / effect->frames_left;
    effect->colors[0].g -= effect->colors[0].g / effect->frames_left;
    effect->colors[0].b -= effect->colors[0].b / effect->frames_left;
    effect->colors[1].r -= effect->colors[1].r / effect->frames_left;
    effect->colors[1].g -= effect->colors[1].g / effect->frames_left;
    effect->colors[1].b -= effect->colors[1].b / effect->frames_left;
    ticks_left = (u16)effect->frames_left - 1;
    effect->frames_left = ticks_left;
    ticks_test = ticks_left << 16;

    if (ticks_test <= 0) {
        ((ObjectStatusPrefix16 *)effect)[-1].flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

typedef struct S_80025E4C_1_pre {
    s32 unk_00;
    u8 pad_04[0x4];
} S_80025E4C_1_pre;   /* the 0x8 bytes before arg0 in queue_linked_shaded_quads, addressed as arg0[-1] */

typedef struct S_80025E4C_1 {
    u8 pad_00[0x30];
    s32 unk_30;
    u16 unk_34;
    u8 pad_36[0x2];
    s32 unk_38;
    u16 unk_3C;
    u8 pad_3E[0x2];
    s32 unk_40;
    u16 unk_44;
    u8 pad_46[0x2];
    s32 unk_48;
    u16 unk_4C;
    u8 pad_4E[0x2];
    s32 unk_50;
    s32 unk_54;
} S_80025E4C_1;   /* arg0 in queue_linked_shaded_quads */




typedef struct GlobalState {
    u8 pad[0x8D0];
    void *next;
} GlobalState;

/*
 * Projects each linked quad with a depth bias of -8 and queues its translucent shaded packet and
 * draw-mode packet for depths below 0x1E0, then saves the packet cursor.
 */
s32 queue_linked_shaded_quads(S_80025E4C_1 *quad) {
    GlobalState **render_states = ((GlobalState **)(&g_game_work));
    PackedShadedQuadScratch *scratch = PACKED_SHADED_QUAD_SCRATCH;
    POLY_G4 *packet;
    DR_MODE *mode_packet;
    u32 depth_bucket;
    s32 first_color;
    s32 second_color;
    s32 next_node;
    s32 vertex3_xy;
    GlobalState *render_state;

    render_state = render_states[0];
    (*(void **)((u8 *)scratch + 0x20)) = (u8 *)render_state + 0xB0;
    scratch->packet_cursor = render_state->next;
    do {
        packet = scratch->packet_cursor;
        scratch->packet_cursor = packet + 1;
        scratch->vertices[0].xy = quad->unk_30;
        scratch->vertices[1].xy = quad->unk_38;
        scratch->vertices[2].xy = quad->unk_40;
        vertex3_xy = quad->unk_48;
        scratch->vertices[0].z = quad->unk_34;
        scratch->vertices[1].z = quad->unk_3C;
        scratch->vertices[2].z = quad->unk_44;
        scratch->vertices[3].xy = vertex3_xy;
        scratch->vertices[3].z = quad->unk_4C;
        depth_bucket = RotTransPers4((SVECTOR *)&scratch->vertices[0], (SVECTOR *)&scratch->vertices[1],
                              (SVECTOR *)&scratch->vertices[2], (SVECTOR *)&scratch->vertices[3],
                              (s32 *)&packet->x0, (s32 *)&packet->x1,
                              (s32 *)&packet->x2, (s32 *)&packet->x3,
                              &scratch->depth_cue, &scratch->gte_flag) - 8;
        scratch->ot_index = depth_bucket;
        if (depth_bucket < 0x1E0U) {
            first_color = quad->unk_50;
            /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
            *(s32 *)&packet->red1 = first_color;
            /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
            *(s32 *)&packet->red0 = first_color;
            second_color = quad->unk_54;
            /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
            *(s32 *)&packet->red3 = second_color;
            /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
            *(s32 *)&packet->red2 = second_color;
            SetPolyG4(packet);
            packet->code = packet->code | 2;
            AddPrim(scratch->ordering_table +
                          scratch->ot_index * 4, packet);
            mode_packet = scratch->packet_cursor;
            scratch->packet_cursor = mode_packet + 1;
            SetDrawMode(mode_packet, 0, 0,
                          (u16)GetTPage(0, 1, 0, 0), 0);
            AddPrim(scratch->ordering_table +
                          scratch->ot_index * 4, mode_packet);
        }
        next_node = ((S_80025E4C_1_pre *)quad)[-1].unk_00;
        if (next_node == 0) {
            break;
        }
        quad = (S_80025E4C_1 *)(next_node + 0x20);
    } while (1);
    render_states[0]->next =
        scratch->packet_cursor;
    return 0;
}


#ifndef NULL
#define NULL 0
#endif

typedef struct S_func_81888810_3 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    u8 pad_1C[0x14];
    s32 unk_30;
    u16 unk_34;
    u8 pad_36[0x2];
    s32 unk_38;
    u16 unk_3C;
    u8 pad_3E[0x2];
    s32 unk_40;
    u16 unk_44;
    u8 pad_46[0x2];
    s32 unk_48;
    u16 unk_4C;
    u8 pad_4E[0x2];
    s32 unk_50;
    s32 unk_54;
} S_func_81888810_3;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Cell;

extern s16 D_8002632A;
extern u8 D_80026474[];
extern Cell D_800264F8[];

/* Create quad fragments from the vertex grid with randomized motion and rotation. */
void create_quad_fragment_effects(void) {
    Cell *vertices;
    Cell *lower_right;
    Cell *lower_left;
    Cell *upper_right;
    ObjectNodeHeader *fragment;
    ObjectPosition *motion;
    SpriteFrameState *angles;
    S_func_81888810_3 *quad;
    s32 quad_index;
    s32 row_start;
    s32 column_or_coord;
    s32 right_offset;
    s32 upper_right_y;
    s32 lower_left_y;
    s32 lower_right_y;
    s32 object_or_x;
    s32 upper_right_z;
    s32 lower_left_z;
    s32 lower_right_z;
    s32 addr_or_coord;
    s32 biased_index;
    u8 *count_page;

    for (quad_index = 0; quad_index < (s16)D_8002632A; quad_index++) {
        vertices = (Cell *)staged_glow_data;
        fragment = allocate_flagged_object_node(0x202);
        if (fragment != NULL) {
            object_or_x = (s32)fragment;
            fragment->update_callback = update_rotating_quad_effect;
            register_node((void *)object_or_x, queue_linked_shaded_quads);

            row_start = quad_index & ~0xF;
            column_or_coord = (quad_index + 1) & 0xF;
            right_offset = (row_start + column_or_coord) * 8;
            upper_right = (Cell *)((unsigned long)right_offset + (unsigned long)vertices);
            lower_left = (Cell *)((unsigned long)((quad_index + 0x10) * 8) + (unsigned long)vertices);

            motion = fragment->position;
            object_or_x = (vertices[quad_index].x + upper_right->x + lower_left->x + (lower_right = &vertices[row_start + 0x10 + column_or_coord])->x) >> 2;
            upper_right_y = (vertices[quad_index].y + upper_right->y + lower_left->y + lower_right->y) >> 2;
            lower_left_y = (vertices[quad_index].z + upper_right->z + lower_left->z + lower_right->z) >> 2;
            motion->x.w.i = object_or_x;
            motion->y.w.i = upper_right_y;
            motion->z.w.i = lower_left_y;

            motion->velocity_x = ((rand() & 0xF) - 8) << 0x10;
            motion->velocity_y = ((rand() & 0xF) - 8) << 0x10;
            motion->velocity_z = ((rand() & 0xF) - 8) << 0x10;

            angles = fragment->sprite;
            angles->angle_x = (rand() & 0x1FF) - 0x100;
            angles->angle_y = (rand() & 0x1FF) - 0x100;

            quad = NODE_BODY(fragment);
            quad->unk_1A = 0x20;
            quad->unk_30 = *(s32 *)&vertices[quad_index];
            quad->unk_34 = vertices[quad_index].z;
            quad->unk_38 = *(s32 *)upper_right;
            quad->unk_3C = upper_right->z;
            quad->unk_40 = *(s32 *)&D_800264F8[quad_index];
            quad->unk_44 = lower_left->z;
            quad->unk_48 = *(s32 *)((u8 *)D_800264F8 + right_offset);
            quad->unk_4C = lower_right->z;

            if ((quad_index % 32) < 0x10) {
                *(s32 *)((u8 *)quad + 0x50) = (*(s32 *)radial_effect_colors);
                quad->unk_54 = (*(s32 *)D_80026474);
            } else {
                *(s32 *)((u8 *)quad + 0x54) = (*(s32 *)radial_effect_colors);
                quad->unk_50 = (*(s32 *)D_80026474);
            }
        }
    }
    D_8002632A = 0;
}

extern u8 D_800E1D01[9];

/*
 * BUG: Unless the initial target effect succeeds, requests status 0x16 for the low input byte divided
 * by four plus four. Applies D_800E1D01 when the returned slot is nonzero, including the existing
 * -1/slot-zero success-test bug.
 */
void apply_timed_status_to_target(ActorRecord *target, s32 value, void *record) {
    u8 pinnedValue = value;
    if (try_trigger_target_record_effect(target, 2, record) == 0) {
        u32 scaledLowByte = pinnedValue;
        scaledLowByte >>= 2;
        /*
         * BUG: set_or_clear_actor_status_slot returns a slot index (0..3), or -1 on
         * failure. Testing it as nonzero misreports slot 0 as failure and -1 as success.
         * Slot-0 success loses its message; rejected insertion prints success.
         * try_apply_confusion_status uses the nonnegative success test.
         */
        if ((set_or_clear_actor_status_slot(target, 0x16, scaledLowByte + 4) << 16) != 0) {
            adjust_source_value_and_finalize(target, D_800E1D01);
        }
    }
}
