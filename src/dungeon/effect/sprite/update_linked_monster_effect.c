#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "m2c_compat.h"

#include "slus/gp_shared_81510.h"

s32 func_8002589C(void *, s32, s32);        /* extern */
s32 func_80026548(void *, s32);                 /* extern */
void func_8002660C(Entry *entry, s16 *step, s32 lower, s32 upper);    /* extern */
s32 func_800266D0(void *, void *);                  /* extern */
s32 resolve_record_orientation_or_fallback(); /* extern */
s32 register_node();           /* extern */
s32 find_eligible_entry_at_coordinates();                /* extern */
void apply_attack_power_and_element_effects(); /* extern */
s32 check_layer_offset_height();              /* extern */
extern u16 sprite_effect_update_count;
extern s16 linked_monster_effect_updated[6];
extern u8 linked_monster_attack_option;
extern s32 linked_monster_attack_event;
extern s32 D_800C9034();

typedef struct S_80025C80_0_pre {
    u16 unk_00;
} S_80025C80_0_pre;   /* the 0x2 bytes before arg0 in update_linked_monster_effect, addressed as arg0[-1] */

typedef struct S_80025C80_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
    u8 pad_2A[0x2];
    s16 unk_2C;
    s16 unk_2E;
    union { s16 n; u16 v; } unk_30;   /* accessed as both */
    s16 unk_32;
    u8 pad_34[0x2];
    s16 unk_36;
    s16 unk_38;
    u16 unk_3A;
    s16 unk_3C;
    union { s16 n; s16 v; } unk_3E;   /* accessed as both */
    union { u16 u; s16 s; } unk_40;   /* accessed as both */
    u16 unk_42;
} S_80025C80_0;   /* arg0 in update_linked_monster_effect */

typedef struct S_80025C80_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_80025C80_2;   /* arg1 in update_linked_monster_effect */

typedef struct S_80025C80_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x1E];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80025C80_3;

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

/* Updates effect movement and fading, or copies a linked monster's position and appearance. */
void update_linked_monster_effect(void *effect_in, void *motion_in, void *sprite_in) {
    TileObject *sprite;
    s32 x_step;
    s32 end_frame;
    TileObject *resident_sprite;
    void *source_data;
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
    s32 transform_result;
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

    linked_monster = ((S_80025C80_0 *)effect_in)->unk_20;
    sprite = sprite_in;
    sprite_effect_update_count = sprite_effect_update_count + 1;
    if (linked_monster == NULL) {
        func_8002660C(sprite, effect_in + 0x32, ((S_80025C80_0 *)effect_in)->unk_38,
            ((S_80025C80_0 *)effect_in)->unk_36);
        func_80026548(effect_in, sprite->frame_entry);
        phase = ((S_80025C80_0 *)effect_in)->unk_2C;
        switch (phase) {
        case 0:
            ((S_80025C80_2 *)((void *)(motion_in)))->unk_08.at00.v =
                (s32) (((S_80025C80_2 *)((void *)(motion_in)))->unk_08.at00.v + 0xFFFF0000);
            brightness = sprite->primitive_color.parts.color_r;
            next_brightness = brightness + ((s32) (0x80 - brightness) / (s16) ((S_80025C80_0 *)effect_in)->unk_30.n);
            sprite->primitive_color.parts.color_r = next_brightness;
            sprite->primitive_color.parts.color_b = next_brightness;
            sprite->primitive_color.parts.color_g = next_brightness;
            frame_toggle = ((u16) ((S_80025C80_0 *)effect_in)->unk_30.n ^ 1) & 1;
            ((S_80025C80_0 *)effect_in)->unk_32 = frame_toggle;
            rise_ticks = ((S_80025C80_0 *)effect_in)->unk_30.v - 1;
            ((S_80025C80_0 *)effect_in)->unk_30.n = rise_ticks;
            if (((rise_ticks << 0x10) <= 0) && (sprite->sprite_flags & 0x4000)) {
                end_frame = 8;
                source_data_2 = dungeon_actor_ring_anchor;
                ((S_80025C80_0 *)effect_in)->unk_38 = end_frame;
                ((S_80025C80_0 *)effect_in)->unk_36 = 0xF;
                ((S_80025C80_0 *)effect_in)->unk_32 = 1;
                ((S_80025C80_0 *)effect_in)->unk_3A = (u16) ((u16)source_data_2->ground_height);
                ((S_80025C80_0 *)effect_in)->unk_40.u = (u16) (((u16) ((u16)source_data_2->facing) >> 9) & 7);
                resident_sprite = &reference_tile_object;
                ((S_80025C80_0 *)effect_in)->unk_3C = resident_sprite->tile_position.parts.tile_x;
                start_tile_y = resident_sprite->tile_position.parts.tile_y;
                ((S_80025C80_0 *)effect_in)->unk_42 = end_frame;
                ((S_80025C80_0 *)effect_in)->unk_30.n = 3;
                ((S_80025C80_0 *)effect_in)->unk_2C = (s16) ((u16) ((S_80025C80_0 *)effect_in)->unk_2C + 1);
                ((S_80025C80_0 *)effect_in)->unk_3E.n = start_tile_y;
            }
            break;
        case 1:
            sprite = (u8 *)&reference_tile_object.frame_entry;
            transform_result = resolve_record_orientation_or_fallback(sprite->sprite_source, sprite, effect_in + 0x24, 0);
            follow_ticks = (u16) ((S_80025C80_0 *)effect_in)->unk_30.n - 1;
            ((S_80025C80_0 *)effect_in)->unk_30.n = follow_ticks;
            if ((follow_ticks << 0x10) <= 0 || transform_result == 0
                || (sprite->sprite_flags & 0x8000) != 0) {
                if (reference_tile_object.sprite_flags & 0x8000) {
                    ((S_80025C80_2 *)((void *)(motion_in)))->unk_00.at02.v = ((u16)view_reference_entity.x.w.i);
                    ((S_80025C80_2 *)((void *)(motion_in)))->unk_04.at02.v = ((u16)view_reference_entity.y.w.i);
                    ((S_80025C80_2 *)((void *)(motion_in)))->unk_08.at02.v = ((u16)view_reference_entity.z.w.i) - 0x10;
                }
                ((S_80025C80_0 *)effect_in)->unk_30.n = 0;
                ((S_80025C80_0 *)effect_in)->unk_2C = (u16) ((S_80025C80_0 *)effect_in)->unk_2C + 1;
            } else {
                ((S_80025C80_2 *)((void *)(motion_in)))->unk_00.at02.v =
                    (s16) (((u16)view_reference_entity.x.w.i) + ((S_80025C80_0 *)effect_in)->unk_24);
                ((S_80025C80_2 *)((void *)(motion_in)))->unk_04.at02.v =
                    (s16) (((u16)view_reference_entity.y.w.i) + ((S_80025C80_0 *)effect_in)->unk_26);
                ((S_80025C80_2 *)((void *)(motion_in)))->unk_08.at02.v =
                    (s16) (((u16)view_reference_entity.z.w.i) + ((S_80025C80_0 *)effect_in)->unk_28);
            }
            break;
        case 2:
            if (((S_80025C80_0 *)effect_in)->unk_30.n == 0) {
                if ((check_layer_offset_height(((((S_80025C80_0 *)effect_in)->unk_3C << 6) + 0x20) & 0xFFE0,
                    ((((S_80025C80_0 *)effect_in)->unk_3E.n << 6) + 0x20) & 0xFFE0,
                    (s16) (((S_80025C80_0 *)effect_in)->unk_3A - 0x20),
                    (s16) (((S_80025C80_0 *)effect_in)->unk_40.u << 9)) << 0x10) != 0
                    || (steps_left = ((S_80025C80_0 *)effect_in)->unk_42 - 1,
                        ((S_80025C80_0 *)effect_in)->unk_42 = steps_left, (steps_left << 0x10) <= 0)) {
                    ((S_80025C80_0 *)effect_in)->unk_2C = 0x10;
                    ((S_80025C80_2 *)((void *)(motion_in)))->unk_0C.at02.v =
                        dir_step_x[((S_80025C80_0 *)effect_in)->unk_40.s] * 8;
                    ((S_80025C80_2 *)((void *)(motion_in)))->unk_10.at02.v =
                        dir_step_y[((S_80025C80_0 *)effect_in)->unk_40.s] * 8;
                    x_step = 8;
                    ((S_80025C80_2 *)((void *)(motion_in)))->unk_14.at02.v = x_step;
                    ((S_80025C80_0 *)effect_in)->unk_30.n = x_step;
                } else {
                    update_ptr = &dir_step_x[((S_80025C80_0 *)effect_in)->unk_40.s];
                    update_x = (u16) ((S_80025C80_0 *)effect_in)->unk_3C;
                    update_x += ((u16) *update_ptr);
                    ((S_80025C80_0 *)effect_in)->unk_3C = update_x;
                    update_y_base = (s16 *)dir_step_y;
                    update_y_offset = ((S_80025C80_0 *)effect_in)->unk_40.s << 1;
                    update_y_ptr = (s16 *) ((unsigned long) update_y_offset + (unsigned long) update_y_base);
                    update_y = (u16) ((S_80025C80_0 *)effect_in)->unk_3E.v + *update_y_ptr;
                    ((S_80025C80_0 *)effect_in)->unk_30.n = 3;
                    ((S_80025C80_0 *)effect_in)->unk_3E.n = update_y;
                }
            }
            target_x = ((S_80025C80_0 *)effect_in)->unk_3C << 6;
            delta_x = ((S_80025C80_2 *)((void *)(motion_in)))->unk_00.at02.v - 0x20;
            ((S_80025C80_2 *)((void *)(motion_in)))->unk_00.at02.v =
                (u16) ((S_80025C80_2 *)((void *)(motion_in)))->unk_00.at02.v
            + ((target_x - delta_x) / ((S_80025C80_0 *)effect_in)->unk_30.n);
            tile_object = ((S_80025C80_0 *)effect_in)->unk_3E.n;
            tile_object <<= 6;
            delta_y = ((S_80025C80_2 *)motion_in)->unk_04.at02.v - 0x20;
            tile_object -= delta_y;
            tile_object /= ((S_80025C80_0 *)effect_in)->unk_30.n;
            next_z = (u16) ((S_80025C80_2 *)((void *)(motion_in)))->unk_08.at02.v + 5;
            ((S_80025C80_2 *)((void *)(motion_in)))->unk_08.at02.v = next_z;
            ((S_80025C80_2 *)((void *)(motion_in)))->unk_04.at02.v =
                (u16) ((S_80025C80_2 *)((void *)(motion_in)))->unk_04.at02.v + tile_object;
            if (((s16) ((S_80025C80_0 *)effect_in)->unk_3A - 0x10) < next_z) {
                ((S_80025C80_2 *)((void *)(motion_in)))->unk_08.at02.v =
                    (s16) (((S_80025C80_0 *)effect_in)->unk_3A - 0x10);
            }
            move_ticks = (u16) ((S_80025C80_0 *)effect_in)->unk_30.n - 1;
            ((S_80025C80_0 *)effect_in)->unk_30.n = move_ticks;
            if (move_ticks == 2) {
                found_tile = find_eligible_entry_at_coordinates(dungeon_actor_ring_anchor, (u16) ((S_80025C80_0 *)effect_in)->unk_3C,
                    (u16) ((S_80025C80_0 *)effect_in)->unk_3E.n);
                if (found_tile != 0) {
                    tile_object = found_tile;
                    apply_attack_power_and_element_effects(tile_object, 0xC, linked_monster_attack_option, 9,
                        (s32) (s16) (((S_80025C80_0 *)effect_in)->unk_40.u << 9), linked_monster_attack_event, 5);
                }
            }
            func_8002589C(effect_in - 0x20, (s16) ((S_80025C80_0 *)effect_in)->unk_40.u, 0xF0);
            break;
        case 0x10:
            ((S_80025C80_2 *)((void *)(motion_in)))->unk_00.at00.v += ((S_80025C80_2 *)((void *)(motion_in)))->unk_0C.at00.v;
            ((S_80025C80_2 *)((void *)(motion_in)))->unk_04.at00.v += ((S_80025C80_2 *)((void *)(motion_in)))->unk_10.at00.v;
            ((S_80025C80_2 *)((void *)(motion_in)))->unk_08.at00.v += ((S_80025C80_2 *)((void *)(motion_in)))->unk_14.at00.v;
            ((S_80025C80_2 *)((void *)(motion_in)))->unk_0C.at00.v -= ((S_80025C80_2 *)((void *)(motion_in)))->unk_0C.at00.v
            >> 2;
            ((S_80025C80_2 *)((void *)(motion_in)))->unk_10.at00.v -= ((S_80025C80_2 *)((void *)(motion_in)))->unk_0C.at00.v
            >> 2;
            if (((s16) ((S_80025C80_0 *)effect_in)->unk_3A - 0x10)
                < ((S_80025C80_2 *)((void *)(motion_in)))->unk_08.at02.v) {
                ((S_80025C80_2 *)((void *)(motion_in)))->unk_08.at02.v =
                    (s16) (((S_80025C80_0 *)effect_in)->unk_3A - 0x10);
            }
            sprite->primitive_color.parts.color_r = sprite->primitive_color.parts.color_r
            - ((s32) sprite->primitive_color.parts.color_r / ((S_80025C80_0 *)effect_in)->unk_30.n);
            sprite->primitive_color.parts.color_g = sprite->primitive_color.parts.color_g
            - ((s32) sprite->primitive_color.parts.color_g / ((S_80025C80_0 *)effect_in)->unk_30.n);
            sprite->primitive_color.parts.color_b = sprite->primitive_color.parts.color_b
            - ((s32) sprite->primitive_color.parts.color_b / ((S_80025C80_0 *)effect_in)->unk_30.n);
            fade_ticks = (u16) ((S_80025C80_0 *)effect_in)->unk_30.n - 1;
            ((S_80025C80_0 *)effect_in)->unk_30.n = fade_ticks;
            if ((fade_ticks << 0x10) <= 0) {
                linked_monster_effect_updated[0] = 0;
                linked_flags = ((S_80025C80_0_pre *)effect_in)[-1].unk_00;
                linked_global = &object_flag_block;
                linked_flags |= 0x8000;
                ((S_80025C80_0_pre *)effect_in)[-1].unk_00 = linked_flags;
                linked_global->flags |= 0x8000;
                return;
            }
            frame = *(u8 *)&sprite->frame_index;
            if ((s8) frame == ((S_80025C80_0 *)effect_in)->unk_36) {
                ((S_80025C80_0 *)effect_in)->unk_32 = -1;
            } else if ((s8) frame == ((S_80025C80_0 *)effect_in)->unk_38) {
                ((S_80025C80_0 *)effect_in)->unk_32 = 1;
            }
            func_8002589C(effect_in - 0x20, (s16) ((S_80025C80_0 *)effect_in)->unk_40.u, 0xF0);
            break;
        }
    } else {
        if ((linked_monster->unk_1E) & 0x8000) {
            linked_flags = ((S_80025C80_0_pre *)effect_in)[-1].unk_00;
            linked_global = &object_flag_block;
            linked_flags |= 0x8000;
            ((S_80025C80_0_pre *)effect_in)[-1].unk_00 = linked_flags;
            linked_global->flags |= 0x8000;
            return;
        }
        source_data = linked_monster->unk_08;
        ((S_80025C80_2 *)((void *)(motion_in)))->unk_00.at02.v = (s16) ((S_80025C80_3 *)source_data)->unk_02;
        ((S_80025C80_2 *)((void *)(motion_in)))->unk_04.at02.v = (s16) ((S_80025C80_3 *)source_data)->unk_06;
        ((S_80025C80_2 *)((void *)(motion_in)))->unk_08.at02.v = (s16) ((S_80025C80_3 *)source_data)->unk_0A;
        linked_sprite = ((S_80025C80_8 *)(((S_80025C80_0 *)effect_in)->unk_20))->unk_0C;
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
    if (((S_80025C80_0 *)effect_in)->unk_2E == 0) {
        register_node(effect_in - 0x20, &D_800C9034);
        ((S_80025C80_0 *)effect_in)->unk_2E = (s16) ((u16) ((S_80025C80_0 *)effect_in)->unk_2E + 1);
    }
}

