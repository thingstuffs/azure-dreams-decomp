#include "shared/object_node.h"
#include "shared/dungeon_effect_status.h"
#include "engine/scene.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "m2c_compat.h"

#include "slus/gp_shared_81510.h"
#include "engine/node.h"
#include "dungeon/effect/sprite.h"
#include "dungeon/effect/sprite/linked_monster_effect.h"

s32 func_8002589C(void *, s32, s32);        /* extern */
s32 func_80026548(void *, s32);                 /* extern */
void step_entry_index_within_bounds(Entry *entry, s16 *step, s32 lower, s32 upper);    /* extern */
s32 func_800266D0(void *, void *);                  /* extern */
s32 find_eligible_entry_at_coordinates();                /* extern */
void apply_attack_power_and_element_effects(); /* extern */
s32 check_layer_offset_height();              /* extern */
extern u16 sprite_effect_update_count;
extern s16 linked_monster_effect_updated[6];
extern u8 linked_monster_attack_option;
extern s32 D_800C9034();




typedef struct S_80025C80_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_80025C80_2;   /* arg1 in update_linked_monster_effect */


typedef struct S_80025C80_6 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x12];
    u16 unk_1E;
} S_80025C80_6;

typedef struct S_80025C80_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    s32 unk_0C;
    u8 pad_10[0x6];
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_80025C80_7;

typedef struct S_80025C80_8 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80025C80_8;   /* ((S_80025C80_0 *)arg0)->unk_20 in update_linked_monster_effect */

#define LINKED_EFFECT ((LinkedMonsterEffectBody *)effect_in)

/* Updates effect movement and fading, or copies a linked monster's position and appearance. */
void update_linked_monster_effect(void *effect_in, ObjectPosition *motion_in, void *sprite_in) {
    TileObject *sprite;
    s32 x_step;
    s32 end_frame;
    TileObject *resident_sprite;
    ObjectPosition *source_data;
    ActorRecord *source_data_2;
    s16 *update_ptr;
    s16 *update_y_base;
    s16 *update_y_ptr;
    s32 update_y_offset;
    u16 linked_flags;
    ObjectFlagBlock *linked_global;
    s16 frame_toggle;
    s16 fade_ticks;
    s16 next_z;
    s16 move_ticks;
    s16 phase;
    s16 rise_ticks;
    s16 follow_ticks;
    s32 delta_x;
    s32 delta_y;
    s32 target_x;
    struct SpriteAttachment *transform_result;
    s32 tile_object;
    s32 found_tile;
    u16 steps_left;
    u16 update_x;
    u16 update_y;
    u8 frame;
    u8 brightness;
    u8 next_brightness;
    u8 start_tile_y;
    S_80025C80_6 *linked_monster;
    S_80025C80_7 *linked_sprite;

    linked_monster = LINKED_EFFECT->unk_20;
    sprite = sprite_in;
    sprite_effect_update_count = sprite_effect_update_count + 1;
    if (linked_monster == NULL) {
        step_entry_index_within_bounds(sprite, effect_in + 0x32, LINKED_EFFECT->unk_38,
            LINKED_EFFECT->unk_36);
        func_80026548(effect_in, sprite->frame_entry);
        phase = LINKED_EFFECT->unk_2C;
        switch (phase) {
        case 0:
            motion_in->z.v =
                (s32) (motion_in->z.v + 0xFFFF0000);
            brightness = sprite->primitive_color.parts.color_r;
            next_brightness = brightness + ((s32) (0x80 - brightness) / (s16) LINKED_EFFECT->unk_30.n);
            sprite->primitive_color.parts.color_r = next_brightness;
            sprite->primitive_color.parts.color_b = next_brightness;
            sprite->primitive_color.parts.color_g = next_brightness;
            frame_toggle = ((u16) LINKED_EFFECT->unk_30.n ^ 1) & 1;
            LINKED_EFFECT->unk_32 = frame_toggle;
            rise_ticks = LINKED_EFFECT->unk_30.v - 1;
            LINKED_EFFECT->unk_30.n = rise_ticks;
            if (((rise_ticks << 0x10) <= 0) && (sprite->sprite_flags & 0x4000)) {
                end_frame = 8;
                source_data_2 = dungeon_actor_ring_anchor;
                LINKED_EFFECT->unk_38 = end_frame;
                LINKED_EFFECT->unk_36 = 0xF;
                LINKED_EFFECT->unk_32 = 1;
                LINKED_EFFECT->unk_3A = (u16) ((u16)source_data_2->ground_height);
                LINKED_EFFECT->unk_40.u = (u16) (((u16) ((u16)source_data_2->facing) >> 9) & 7);
                resident_sprite = &reference_tile_object;
                LINKED_EFFECT->unk_3C = resident_sprite->tile_position.parts.tile_x;
                start_tile_y = resident_sprite->tile_position.parts.tile_y;
                LINKED_EFFECT->unk_42 = end_frame;
                LINKED_EFFECT->unk_30.n = 3;
                LINKED_EFFECT->unk_2C = (s16) ((u16) LINKED_EFFECT->unk_2C + 1);
                LINKED_EFFECT->unk_3E.n = start_tile_y;
            }
            break;
        case 1:
            sprite = (u8 *)&reference_tile_object.frame_entry;
            {
                void *sprite_data = sprite;
                SpriteFrameState *orientation_sprite = sprite_data;
                GteShortVector *offset = effect_in + 0x24;

                transform_result = resolve_record_orientation_or_fallback(orientation_sprite->source, orientation_sprite, offset, 0);
            }
            follow_ticks = (u16) LINKED_EFFECT->unk_30.n - 1;
            LINKED_EFFECT->unk_30.n = follow_ticks;
            if ((follow_ticks << 0x10) <= 0 || transform_result == 0
                || (sprite->sprite_flags & 0x8000) != 0) {
                if (reference_tile_object.sprite_flags & 0x8000) {
                    motion_in->x.w.i = ((u16)view_reference_entity.x.w.i);
                    motion_in->y.w.i = ((u16)view_reference_entity.y.w.i);
                    motion_in->z.w.i = ((u16)view_reference_entity.z.w.i) - 0x10;
                }
                LINKED_EFFECT->unk_30.n = 0;
                LINKED_EFFECT->unk_2C = (u16) LINKED_EFFECT->unk_2C + 1;
            } else {
                motion_in->x.w.i =
                    (s16) (((u16)view_reference_entity.x.w.i) + LINKED_EFFECT->unk_24);
                motion_in->y.w.i =
                    (s16) (((u16)view_reference_entity.y.w.i) + LINKED_EFFECT->unk_26);
                motion_in->z.w.i =
                    (s16) (((u16)view_reference_entity.z.w.i) + LINKED_EFFECT->unk_28);
            }
            break;
        case 2:
            if (LINKED_EFFECT->unk_30.n == 0) {
                if ((check_layer_offset_height(((LINKED_EFFECT->unk_3C << 6) + 0x20) & 0xFFE0,
                    ((LINKED_EFFECT->unk_3E.n << 6) + 0x20) & 0xFFE0,
                    (s16) (LINKED_EFFECT->unk_3A - 0x20),
                    (s16) (LINKED_EFFECT->unk_40.u << 9)) << 0x10) != 0
                    || (steps_left = LINKED_EFFECT->unk_42 - 1,
                        LINKED_EFFECT->unk_42 = steps_left, (steps_left << 0x10) <= 0)) {
                    LINKED_EFFECT->unk_2C = 0x10;
                    ((S_80025C80_2 *)(motion_in))->unk_0C.at02.v =
                        dir_step_x[LINKED_EFFECT->unk_40.s] * 8;
                    ((S_80025C80_2 *)(motion_in))->unk_10.at02.v =
                        dir_step_y[LINKED_EFFECT->unk_40.s] * 8;
                    x_step = 8;
                    ((S_80025C80_2 *)(motion_in))->unk_14.at02.v = x_step;
                    LINKED_EFFECT->unk_30.n = x_step;
                } else {
                    update_ptr = &dir_step_x[LINKED_EFFECT->unk_40.s];
                    update_x = (u16) LINKED_EFFECT->unk_3C;
                    update_x += ((u16) *update_ptr);
                    LINKED_EFFECT->unk_3C = update_x;
                    update_y_base = dir_step_y;
                    update_y_offset = LINKED_EFFECT->unk_40.s << 1;
                    update_y_ptr = (s16 *) ((unsigned long) update_y_offset + (unsigned long) update_y_base);
                    update_y = (u16) LINKED_EFFECT->unk_3E.v + *update_y_ptr;
                    LINKED_EFFECT->unk_30.n = 3;
                    LINKED_EFFECT->unk_3E.n = update_y;
                }
            }
            target_x = LINKED_EFFECT->unk_3C << 6;
            delta_x = motion_in->x.w.i - 0x20;
            motion_in->x.w.i =
                (u16) motion_in->x.w.i
            + ((target_x - delta_x) / LINKED_EFFECT->unk_30.n);
            tile_object = LINKED_EFFECT->unk_3E.n;
            tile_object <<= 6;
            delta_y = motion_in->y.w.i - 0x20;
            tile_object -= delta_y;
            tile_object /= LINKED_EFFECT->unk_30.n;
            next_z = (u16) motion_in->z.w.i + 5;
            motion_in->z.w.i = next_z;
            motion_in->y.w.i =
                (u16) motion_in->y.w.i + tile_object;
            if (((s16) LINKED_EFFECT->unk_3A - 0x10) < next_z) {
                motion_in->z.w.i =
                    (s16) (LINKED_EFFECT->unk_3A - 0x10);
            }
            move_ticks = (u16) LINKED_EFFECT->unk_30.n - 1;
            LINKED_EFFECT->unk_30.n = move_ticks;
            if (move_ticks == 2) {
                found_tile = find_eligible_entry_at_coordinates(dungeon_actor_ring_anchor, (u16) LINKED_EFFECT->unk_3C,
                    (u16) LINKED_EFFECT->unk_3E.n);
                if (found_tile != 0) {
                    tile_object = found_tile;
                    apply_attack_power_and_element_effects(tile_object, 0xC, linked_monster_attack_option, 9,
                        (s32) (s16) (LINKED_EFFECT->unk_40.u << 9), linked_monster_attack_event[0], 5);
                }
            }
            func_8002589C(effect_in - 0x20, (s16) LINKED_EFFECT->unk_40.u, 0xF0);
            break;
        case 0x10:
            motion_in->x.v += motion_in->velocity_x;
            motion_in->y.v += motion_in->velocity_y;
            motion_in->z.v += motion_in->velocity_z;
            motion_in->velocity_x -= motion_in->velocity_x
            >> 2;
            motion_in->velocity_y -= motion_in->velocity_x
            >> 2;
            if (((s16) LINKED_EFFECT->unk_3A - 0x10)
                < motion_in->z.w.i) {
                motion_in->z.w.i =
                    (s16) (LINKED_EFFECT->unk_3A - 0x10);
            }
            sprite->primitive_color.parts.color_r = sprite->primitive_color.parts.color_r
            - ((s32) sprite->primitive_color.parts.color_r / LINKED_EFFECT->unk_30.n);
            sprite->primitive_color.parts.color_g = sprite->primitive_color.parts.color_g
            - ((s32) sprite->primitive_color.parts.color_g / LINKED_EFFECT->unk_30.n);
            sprite->primitive_color.parts.color_b = sprite->primitive_color.parts.color_b
            - ((s32) sprite->primitive_color.parts.color_b / LINKED_EFFECT->unk_30.n);
            fade_ticks = (u16) LINKED_EFFECT->unk_30.n - 1;
            LINKED_EFFECT->unk_30.n = fade_ticks;
            if ((fade_ticks << 0x10) <= 0) {
                linked_monster_effect_updated[0] = 0;
                linked_flags = NODE_HEADER(effect_in)->flags;
                linked_global = &object_flag_block;
                linked_flags |= 0x8000;
                NODE_HEADER(effect_in)->flags = linked_flags;
                linked_global->flags |= 0x8000;
                return;
            }
            frame = ((u8)(sprite->frame_index));
            if ((s8) frame == LINKED_EFFECT->unk_36) {
                LINKED_EFFECT->unk_32 = -1;
            } else if ((s8) frame == LINKED_EFFECT->unk_38) {
                LINKED_EFFECT->unk_32 = 1;
            }
            func_8002589C(effect_in - 0x20, (s16) LINKED_EFFECT->unk_40.u, 0xF0);
            break;
        }
    } else {
        if ((linked_monster->unk_1E) & 0x8000) {
            linked_flags = NODE_HEADER(effect_in)->flags;
            linked_global = &object_flag_block;
            linked_flags |= 0x8000;
            NODE_HEADER(effect_in)->flags = linked_flags;
            linked_global->flags |= 0x8000;
            return;
        }
        source_data = linked_monster->unk_08;
        motion_in->x.w.i = (s16) source_data->x.unsigned_parts.integer;
        motion_in->y.w.i = (s16) source_data->y.unsigned_parts.integer;
        motion_in->z.w.i = (s16) source_data->z.unsigned_parts.integer;
        linked_sprite = ((S_80025C80_8 *)(LINKED_EFFECT->unk_20))->unk_0C;
        func_800266D0(sprite, linked_sprite->unk_04);
        func_80026548(effect_in, sprite->frame_entry);
        sprite->scale_x = (u16) linked_sprite->unk_1C;
        sprite->scale_y = (u16) linked_sprite->unk_1E;
        sprite->offset_x = (u16) linked_sprite->unk_20;
        sprite->primitive_color.word = linked_sprite->unk_0C;
        sprite->angle_x = (u16) linked_sprite->unk_16;
        sprite->angle_y = (u16) linked_sprite->unk_18;
        sprite->angle_z = (u16) linked_sprite->unk_1A;
    }
    if (LINKED_EFFECT->unk_2E == 0) {
        register_node(effect_in - 0x20, &D_800C9034);
        LINKED_EFFECT->unk_2E = (s16) ((u16) LINKED_EFFECT->unk_2E + 1);
    }
}


#undef LINKED_EFFECT
