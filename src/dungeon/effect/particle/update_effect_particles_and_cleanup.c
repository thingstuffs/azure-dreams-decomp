#include "engine/scene.h"
#include "shared/sprite_frame_state.h"
#include "shared/audio_commands.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "dungeon/effect/motion.h"
#include "sdk/libc.h"
#include "sdk/libgpu.h"
#include "dungeon/system.h"
struct Row_818FE800_Target;

typedef struct { u8 bytes[8]; } Packed8 __attribute__((packed));
typedef struct { u8 bytes[12]; } Packed12 __attribute__((packed));
typedef struct { u8 bytes[32]; } Packed32 __attribute__((packed));
typedef union {
    Packed8 packed;
    s16 half[6];
} Local28;
typedef union {
    Packed32 packed;
    struct {
        s16 first;
        u16 second;
    } pair[8];
} Local38;

/* cfail-repair: tf7-phase1-cache-v3 */
void apply_random_actor_value_adjustment(struct Row_818FE800_Target *target, s32 level, void *record);          /* extern */
#include "dungeon/effect/particle.h"
#include "dungeon/actor.h"
#include "dungeon/effect/sprite.h"
#include "dungeon/effect/sprite_callbacks_api.h"
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */           /* extern */
void draw_transformed_sprite_with_clip_rect(); /* extern */
extern Packed8 D_80024028;
extern Packed32 D_80024038;
extern M2C_UNK D_800245EC;

extern Packed12 D_80025E28;
extern Packed12 D_80025E34;
extern Packed12 D_80025E40;
extern Packed12 D_80025E58;
extern Packed12 D_80025E70;
extern s16 particle_update_flag;
extern u8 current_spell_effect_variant;


typedef struct S_818FF710_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} S_818FF710_2;

   /* &D_80025E80 in update_effect_particles_and_cleanup */


typedef struct S_818FF710_7_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_818FF710_7_pre;







typedef struct S_818FF710_27 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818FF710_27;



typedef struct S_818FF710_31_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_818FF710_31_pre;

typedef struct S_818FF710_31 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818FF710_31;

typedef struct S_818FF710_32 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_818FF710_32;

typedef struct S_818FF710_33 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_818FF710_33;

/* Callback work at node +0x20. Flight duration controls the color ramp;
 * the source bytes at +0x96 are copied as an unaligned 12-byte block. */
typedef struct ParticleCleanupWork {
    void *owner;
    struct { u16 flags; } *animation;
    u8 pad_08;
    u8 variant;
    s16 state;
    u8 pad_0C[0x6C];
    s16 target_height;
    u8 flags;
    s8 flight_ticks;
    u8 pad_7C[2];
    s16 direction;
    u8 pad_80[2];
    u16 timer;
    u8 pad_84[4];
    s16 initial_ticks;
    s16 ticks_squared;
    u8 pad_8C[4];
    s16 unk_90;
    u8 pad_92[4];
    Packed12 sprite_data;
    s8 next_tile_x;
    s8 next_tile_y;
} ParticleCleanupWork;

/* Updates an effect's movement, particles, target effects, and cleanup state. */
void update_effect_particles_and_cleanup(ParticleCleanupWork *effect, ObjectPosition *motion, SpriteFrameState *sprite) {
    GteShortVector offset;
    Local28 texture_rect;
    Local38 direction_steps;
    void *particle_owner;
    s32 particle_size;
    s32 spawn_tick;
    s32 state;
    u32 render_value;
    s32 effect_active;
    void *follow_target;
    s16 fade_tick;
    s32 red_tick;
    s32 green_tick;
    s32 blue_tick;
    s32 launch_particle;
    s32 impact_particle;
    s32 tile_distance;
    s8 parent_tile;
    s8 remaining_ticks;
    u16 impact_angle;
    u16 release_tick;
    u16 cleanup_tick;
    u16 flight_angle;
    u16 hit_angle;
    u16 hit_tick;
    u16 old_hit_angle;
    u16 old_impact_angle;
    u16 old_cleanup_tick;
    u16 parent_height;
    u16 old_flight_angle;
    u16 parent_flags;
    u8 flight_ticks;
    s32 origin_tile;
    u16 sprite_flags;
    s32 source_id;
    MovingTile *origin;
    ObjectPosition *hit_target;
    ObjectPosition *released_target;
    SpriteFrameState *parent_sprite;
    ObjectPosition *target_pos_or_step;
    void *sprite_resource;
    ObjectNodeHeader *parent_object;
    SpriteFrameState *first_sprite;
    SpriteFrameState *second_sprite;
    ParticleCleanupEffectBody *child_effect;
    MovingPosition *parent_position;
    S_818FF710_2 *parent;
    ObjectNodeHeader *third_object;
    ObjectNodeHeader *fourth_object;
    ObjectNodeHeader *first_object;
    ObjectNodeHeader *second_object;
    SpriteFrameState *target_hit_flags;
    ObjectPosition *first_position;
    ObjectPosition *second_position;
    ObjectPosition *third_position;
    ObjectPosition *fourth_position;
    S_818FF710_27 *target_release_flags;
    void *flight_target;
    void *impact_target;

    parent = effect->owner;
    texture_rect.packed = D_80024028;
    direction_steps.packed = D_80024038;
    state = effect->state;
    parent_object = NODE_HEADER(parent);
    parent_position = (MovingPosition *)parent_object->position;
    switch ((u32)(state)) {
    case 0:
        sprite->color.word = 0x808080;
        effect->sprite_data = D_80025E70;
        sprite->source = &effect->sprite_data;
        parent_flags = parent->unk_2A;
        particle_update_flag = 1;
        effect->direction = (s16) ((parent_flags >> 9) & 7);
        effect->state = (s16) ((u16) effect->state + 1);
    case 1:
        parent_sprite = parent_object->sprite;
        if (resolve_record_orientation_or_fallback(parent_sprite->source, parent_sprite, &offset, 0) == 0
            && !(parent_object->sprite->flags & 0x8000)) {
            return;
        }
        motion->x.unsigned_parts.integer = (u16) parent_position->x;
        motion->y.unsigned_parts.integer = (u16) parent_position->y;
        parent_height = parent_position->z;
        motion->z.unsigned_parts.integer = parent_height;
        if (!(parent_object->sprite->flags & 0x8000)) {
            motion->x.unsigned_parts.integer = (u16) (motion->x.unsigned_parts.integer + ((u16)offset.vx));
            motion->y.unsigned_parts.integer = (u16) (motion->y.unsigned_parts.integer + ((u16)offset.vy));
            motion->z.unsigned_parts.integer = (u16) (motion->z.unsigned_parts.integer + ((u16)offset.vz));
        } else {
            motion->z.unsigned_parts.integer = (u16) (parent_height - 0x40);
        }
        if (!(effect->flags & 4)) {
            register_node(NODE_HEADER(effect), project_sprite_chain);
            sprite->tpage_abr = 0x60;
            sprite->color.c.b = 0x14;
            sprite->color.c.g = 0x14;
            sprite->color.c.r = 0x14;
            sprite->scale_y = 0x1000;
            sprite->scale_x = 0x1000;
            sprite->flags = (u16) (sprite->flags | 0xC);
            effect->flags = (u8) (effect->flags | 4);
        }
        if (!(effect->animation->flags & 0x80)) {
            return;
        }
        flight_target = parent->unk_60;
        if (flight_target != NULL) {
            target_pos_or_step = ((S_818FF710_7_pre *)flight_target)[-1].unk_00;
            effect->target_height = (s16) (target_pos_or_step->z.unsigned_parts.integer
                - (entity_height_offsets[((ActorRecord *)flight_target)->species] + 0x40));
            origin = ((SpriteLinkPrefixView *)parent)[-1].sprite;
            effect->next_tile_x = (s8) (origin->tile_x + ((u8 *)dir_step_x)[effect->direction * 2]);
            effect->next_tile_y = (s8) (origin->tile_y + ((u8 *)dir_step_y)[effect->direction * 2]);
            parent_tile = parent->unk_72;
            tile_distance = parent_tile;
            origin_tile = origin->tile_x;
            if (tile_distance != origin_tile) {
                tile_distance = tile_distance - origin_tile;
            } else {
                parent_tile = parent->unk_73;
                tile_distance = parent_tile;
                origin_tile = origin->tile_y;
                tile_distance = tile_distance - origin_tile;
            }
            if (tile_distance < 0) {
                tile_distance = 0 - tile_distance;
            }
            effect->flight_ticks = (s8) ((tile_distance * 2) - 1);
        } else {
            effect->target_height = (s16) (parent->unk_88 - 0x50);
            effect->flight_ticks = 0x20;
        }
        motion->velocity_x = (s32) (direction_steps.pair[effect->direction].first << 0x10);
        motion->velocity_y = (s32) (direction_steps.pair[effect->direction].second
            << 0x10);
        motion->velocity_z = (s32) ((s32) ((effect->target_height << 0x10)
            - motion->z.v) / (s8) effect->flight_ticks);
        flight_ticks = (u8) effect->flight_ticks;
        effect->timer = 0U;
        effect->state = (s16) ((u16) effect->state + 1);
        effect->initial_ticks = (s16) (s8) (u8) effect->flight_ticks;
        effect->ticks_squared = (s16) ((s8) flight_ticks * (s8) flight_ticks);
        create_owner_linked_mirrored_sprite(effect, motion, sprite);
        return;
    case 2:
        launch_particle = 0;
        for (; launch_particle < 4; launch_particle++) {
            {
                s32 particle_direction;
                s32 particle_color;
                s32 random_value;
                random_value = rand();
                particle_color = 0x2020E0;
                particle_size = (random_value & 0xFF) | 0x80;
                particle_direction = effect->direction;
                spawn_jittered_child_effect(NODE_HEADER(effect), particle_direction, particle_color, particle_size, 0, 0, 0);
            }
        }
        old_flight_angle = sprite->angle_z;
        flight_angle = old_flight_angle + 0x190;
        sprite->angle_z = flight_angle;
        if ((u32) (flight_angle & 0xFFFF) >= 0x1001U) {
            sprite->angle_z = (u16) (old_flight_angle - 0xE70);
        }
        red_tick = (effect->initial_ticks - effect->flight_ticks) + 1;
        sprite->color.c.r =
            (s8) (((s32) (red_tick * red_tick * 0x6C) / (s16) effect->ticks_squared) + 0x14);
        green_tick = (effect->initial_ticks - effect->flight_ticks) + 1;
        sprite->color.c.g =
            (s8) (((s32) (green_tick * green_tick * 0x6C) / (s16) effect->ticks_squared) + 0x14);
        blue_tick = (effect->initial_ticks - effect->flight_ticks) + 1;
        sprite->color.c.b =
            (s8) (((s32) (blue_tick * blue_tick * 0x6C) / (s16) effect->ticks_squared) + 0x14);
        if ((check_adjacent_tile_height_clearance(motion->x.unsigned_parts.integer, motion->y.unsigned_parts.integer,
            (s16) motion->z.unsigned_parts.integer, parent->unk_60) << 0x10) != 0) {
            effect->state = 8;
            effect->timer = 0U;
            sprite->color.c.b = 0;
            sprite->color.c.g = 0;
            sprite->color.c.r = 0;
            return;
        }
        remaining_ticks = (u8) effect->flight_ticks - 1;
        effect->flight_ticks = remaining_ticks;
        if ((remaining_ticks << 0x18) <= 0) {
            if (parent->unk_60 != NULL) {
                effect->state = 3;
                effect->timer = 0U;
                play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                impact_target = parent->unk_60;
                target_hit_flags = ((SpriteLinkPrefixView *)impact_target)[-1].sprite;
                if ((u32) (((ActorRecord *)impact_target)->species - 0x33) >= 4U) {
                    target_hit_flags->flags = (u16) (target_hit_flags->flags | 0x800);
                    hit_target = parent->unk_60;
                    hit_target->velocity_z = (s32) (hit_target->velocity_z | 0x100000);
                }
                target_pos_or_step = ((S_818FF710_31_pre *)(parent->unk_60))[-1].unk_00;
                motion->x.unsigned_parts.integer = (u16) target_pos_or_step->x.unsigned_parts.integer;
                motion->y.unsigned_parts.integer = (u16) target_pos_or_step->y.unsigned_parts.integer;
                motion->z.unsigned_parts.integer = (u16) effect->target_height;
                create_owner_linked_mirrored_sprite(effect, motion, sprite);
                return;
            }
            effect->state = 8;
            effect->timer = 0U;
            sprite->color.c.b = 0;
            sprite->color.c.g = 0;
            sprite->color.c.r = 0;
            create_owner_linked_mirrored_sprite(effect, motion, sprite);
            return;
        }
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        motion->z.v += motion->velocity_z;
        create_owner_linked_mirrored_sprite(effect, motion, sprite);
        return;
    case 3:
    {
        s32 impact_tick;
        s32 rect_y;
        s32 rect_width;
        s32 rect_bottom;
        s16 *rect_start;
        s16 *rect_end;
        s16 *texture_start;
        s16 *texture_end;
        s32 rect_right;
        s32 rect_height;
        s32 rect_left;
        old_hit_angle = sprite->angle_z;
        hit_angle = old_hit_angle + 0x190;
        sprite->angle_z = hit_angle;
        if ((u32) (hit_angle & 0xFFFF) >= 0x1001U) {
            sprite->angle_z = (u16) (old_hit_angle - 0xE70);
        }
        create_owner_linked_mirrored_sprite(effect, motion, sprite);
        hit_tick = effect->timer + 1;
        effect->timer = hit_tick;
        if ((s16) hit_tick == 1) {
            rect_start = &texture_rect.half[0];
            texture_start = rect_start;
            rect_end = &texture_rect.half[4];
            texture_end = rect_end;
            rect_left = 0x340;
            texture_rect.half[0] = (s16) rect_left;
            texture_rect.half[1] = 0x154;
            texture_rect.half[2] = 0x60;
            rect_height = 0x54;
            rect_right = 0x370;
            texture_rect.half[3] = (s16) rect_height;
            texture_rect.half[4] = (s16) rect_right;
            texture_rect.half[5] = (s16) 0x19A;
            draw_transformed_sprite_with_clip_rect(parent->unk_60, texture_start, texture_end, 1, (s32) (s16) hit_tick);
            texture_start = rect_start;
            texture_end = rect_end;
            texture_rect.half[0] = (s16) rect_left;
            rect_y = 0x1A8;
            texture_rect.half[1] = (s16) rect_y;
            rect_width = 0x60;
            texture_rect.half[2] = (s16) rect_width;
            texture_rect.half[3] = (s16) rect_height;
            texture_rect.half[4] = (s16) rect_right;
            rect_bottom = 0x1EF;
            texture_rect.half[5] = (s16) rect_bottom;
            draw_transformed_sprite_with_clip_rect(parent->unk_60, texture_start, texture_end, 1, (s32) (s16) hit_tick);
        }
        impact_tick = (s16) effect->timer;
        if (impact_tick != 4) {
            return;
        }
        first_object = allocate_flagged_object_node(0x212);
        child_effect = NODE_BODY(first_object);
        if (first_object != NULL) {
            child_effect->unk_02.s = 0x78;
            (first_object->update_callback) = expire_effect_at_unit_scale;
            register_node(first_object, project_sprite_chain);
            first_sprite = first_object->sprite;
            first_sprite->depth_bias = 0;
            render_value = first_sprite->flags | 0xC;
            first_sprite->flags = render_value;
            render_value = 0x40;
            first_sprite->tpage_abr = render_value;
            sprite_flags = first_sprite->flags;
            state = sprite_flags | 0x80;
            first_sprite->flags = state;
            first_position = first_object->position;
            child_effect->unk_0A = 0;
            child_effect->unk_0C = 0;
            target_pos_or_step = ((S_818FF710_31_pre *)(parent->unk_60))[-1].unk_00;
            first_position->x.v = (s32) target_pos_or_step->x.v;
            first_position->y.v = (s32) target_pos_or_step->y.v;
            first_position->z.v = (s32) target_pos_or_step->z.v;
            first_sprite = first_object->sprite;
            first_sprite->scale_x = 0x1004;
            first_sprite->scale_y = 0x1004;
            first_sprite->offset_y = (s16) ((s32) (0
                - entity_height_offsets[((S_818FF710_31 *)(parent->unk_60))->unk_13]) / 2);
            first_sprite->color.c.b = 0x80;
            first_sprite->color.c.g = 0x80;
            first_sprite->color.c.r = 0x80;
            (*(Packed12 *)((u8 *)first_object + 0x40)) = D_80025E34;
            first_sprite->source = (((void *)first_object) + 0x40);
            ((S_818FF710_32 *)(first_sprite->source))->unk_04 = GetTPage(2, 2, 0x340, 0x154);
        }
        second_object = allocate_flagged_object_node(0x212);
        child_effect = NODE_BODY(second_object);
        if (second_object != NULL) {
            child_effect->unk_02.s = 0x78;
            (second_object->update_callback) = &advance_timed_visual_effect;
            register_node(second_object, project_sprite_chain);
            second_sprite = second_object->sprite;
            second_sprite->flags &= 0xFFF3;
            second_sprite->tpage_abr = 0x20;
            second_sprite->flags |= 0x80;
            child_effect->unk_2C = parent;
            follow_target = parent->unk_60;
            child_effect->unk_34 = effect;
            child_effect->unk_30 = follow_target;
            second_sprite->depth_bias = 0;
            second_position = second_object->position;
            child_effect->unk_0A = 0;
            child_effect->unk_0C = 0;
            target_pos_or_step = ((S_818FF710_31_pre *)(parent->unk_60))[-1].unk_00;
            second_position->x.v = (s32) target_pos_or_step->x.v;
            second_position->y.v = (s32) target_pos_or_step->y.v;
            second_position->z.v = (s32) target_pos_or_step->z.v;
            second_sprite = second_object->sprite;
            second_sprite->scale_y = 0x1000;
            second_sprite->scale_x = 0x1000;
            second_sprite->color.c.b = 0x80;
            second_sprite->color.c.g = 0x80;
            second_sprite->color.c.r = 0x80;
            (*(Packed12 *)((u8 *)second_object + 0x40)) = D_80025E40;
            second_sprite->source = (((void *)second_object) + 0x40);
            ((S_818FF710_33 *)(second_sprite->source))->unk_04 = GetTPage(2, 1, 0x340, 0x1A8);
        }
        third_object = allocate_flagged_object_node(0x212);
        child_effect = NODE_BODY(third_object);
        if (third_object != NULL) {
            child_effect->unk_02.s = 0x78;
            (third_object->update_callback) = &D_800245EC;
            register_node(third_object, project_sprite_chain);
            second_sprite = third_object->sprite;
            second_sprite->depth_bias = 0;
            render_value = second_sprite->flags & 0xFFF3;
            second_sprite->flags = render_value;
            render_value = 0x20;
            second_sprite->tpage_abr = render_value;
            sprite_flags = second_sprite->flags;
            state = sprite_flags | 0x80;
            second_sprite->flags = state;
            third_position = third_object->position;
            child_effect->unk_0A = 0;
            child_effect->unk_0C = 0;
            target_pos_or_step = ((S_818FF710_31_pre *)(parent->unk_60))[-1].unk_00;
            third_position->x.v = (s32) target_pos_or_step->x.v;
            third_position->y.v = (s32) target_pos_or_step->y.v;
            third_position->z.v = (s32) target_pos_or_step->z.v;
            second_sprite = third_object->sprite;
            second_sprite->color.c.b = 0x80;
            second_sprite->color.c.g = 0x80;
            second_sprite->color.c.r = 0x80;
            second_sprite->scale_y = 0;
            second_sprite->scale_x = 0;
            (*(Packed12 *)((u8 *)third_object + 0x40)) = D_80025E58;
            second_sprite->source = (((void *)third_object) + 0x40);
        }
        fourth_object = allocate_flagged_object_node(0x212);
        child_effect = NODE_BODY(fourth_object);
        if (fourth_object != NULL) {
            particle_owner = fourth_object;
            sprite_resource = (void *) project_sprite_chain;
            child_effect->unk_2C = parent;
            fourth_position = parent->unk_60;
            child_effect->unk_30 =  fourth_position;
            child_effect->unk_34 = effect;
            child_effect->unk_38 = NODE_BODY(first_object);
            child_effect->unk_3C = NODE_BODY(third_object);
            child_effect->unk_40 = NODE_BODY(second_object);
            (fourth_object->update_callback) = &update_tiled_fade_effect;
            register_node(particle_owner, sprite_resource);
            second_sprite = fourth_object->sprite;
            second_sprite->depth_bias = 0;
            render_value = second_sprite->flags | 0xC;
            second_sprite->flags = render_value;
            render_value = 0x20;
            second_sprite->tpage_abr = render_value;
            sprite_flags = second_sprite->flags;
            state = sprite_flags | 0x80;
            second_sprite->flags = state;
            fourth_position = fourth_object->position;
            child_effect->unk_0A = 0;
            child_effect->unk_0C = 0;
            target_pos_or_step = ((S_818FF710_31_pre *)(parent->unk_60))[-1].unk_00;
            fourth_position->x.v = (s32) target_pos_or_step->x.v;
            fourth_position->y.v = (s32) target_pos_or_step->y.v;
            fourth_position->z.v = (s32) target_pos_or_step->z.v;
            second_sprite = fourth_object->sprite;
            second_sprite->scale_y = 0x1000;
            second_sprite->scale_x = 0x1000;
            second_sprite->color.c.b = 0x80;
            second_sprite->color.c.g = 0x80;
            second_sprite->color.c.r = 0x80;
            (*(Packed12 *)((u8 *)fourth_object + 0x40)) = D_80025E28;
            second_sprite->source = (((void *)fourth_object) + 0x40);
        }
        spawn_tick = (s16) effect->timer;
        if (spawn_tick != impact_tick) {
            return;
        }
        effect->state = spawn_tick;
        effect->timer = 0U;
        effect->unk_90 = 0;
        return;
    }
    case 4:
        impact_particle = 0;
        effect->timer = (u16) (effect->timer + 1);
        for (; impact_particle < 3; impact_particle++) {
            {
                s32 particle_direction;
                s32 particle_color;
                s32 random_value;
                random_value = rand();
                particle_color = 0x2020E0;
                particle_size = (random_value & 0xFF) | 0x80;
                particle_direction = effect->direction;
                spawn_jittered_child_effect(NODE_HEADER(effect), particle_direction, particle_color, particle_size, 0, 0, 0);
            }
        }
        old_impact_angle = sprite->angle_z;
        impact_angle = old_impact_angle + 0x190;
        sprite->angle_z = impact_angle;
        if ((u32) (impact_angle & 0xFFFF) >= 0x1001U) {
            sprite->angle_z = (u16) (old_impact_angle - 0xE70);
        }
        fade_tick = (s16) effect->timer;
        if (fade_tick >= 0x51) {
            sprite->color.c.r = (s8) (((0x64 - fade_tick) << 7) / 20);
            sprite->color.c.g = (s8) (((0x64 - (s16) effect->timer) << 7) / 20);
            sprite->color.c.b = (s8) (((0x64 - (s16) effect->timer) << 7) / 20);
        }
        create_owner_linked_mirrored_sprite(effect, motion, sprite);
        if ((s16) effect->timer < 0x64) {
            return;
        }
        effect->timer = 0U;
        effect->state = (s16) ((u16) effect->state + 1);
        return;
    case 5:
        if (effect->unk_90 == 0) {
            return;
        }
        source_id = 0xFF;
        if (current_spell_effect_variant != 0xFF) {
            source_id = effect->variant;
        }
        apply_random_actor_value_adjustment(parent->unk_60, source_id, parent);
        effect->timer = 0U;
        effect->state = (s16) ((u16) effect->state + 1);
        return;
    case 6:
        release_tick = effect->timer + 1;
        effect->timer = release_tick;
        if ((s16) release_tick < 0x1F) {
            return;
        }
        target_release_flags = ((S_818FF710_31_pre *)(parent->unk_60))[-1].unk_04;
        target_release_flags->unk_14 = (u16) (target_release_flags->unk_14 & 0xF7FF);
        released_target = parent->unk_60;
        released_target->velocity_z = (s32) (released_target->velocity_z & 0xFFEFFFFF);
        effect->state = 8;
        effect->timer = 0x1EU;
        return;
    case 8:
        old_cleanup_tick = effect->timer;
        cleanup_tick = old_cleanup_tick + 1;
        effect->timer = cleanup_tick;
        if ((s16) cleanup_tick < 0x1F) {
            return;
        }
        effect_active = (s32) particle_update_flag;
        effect->timer = old_cleanup_tick;
        if (effect_active == 0) {
            g_dungeon_status.active_actor = 0;
            ((MovingEffectState_pre *)effect)[-1].unk_00 = (u16) (((MovingEffectState_pre *)effect)[-1].unk_00 | NODE_REMOVE);
            (*&object_flag_block.flags) = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
            return;
        }
        particle_update_flag = 0;
        return;
    default:
        return;
    }
}
