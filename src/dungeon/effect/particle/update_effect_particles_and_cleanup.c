#include "shared/object_node.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"

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
void apply_random_actor_value_adjustment();          /* extern */
void spawn_jittered_child_effect(); /* extern */
void func_80024DB8(); /* extern */
s32 resolve_record_orientation_or_fallback();     /* extern */
s32 register_node();           /* extern */
s16 func_80066460(); /* extern */
s32 func_80069EF8();                                /* extern */
s32 check_adjacent_tile_height_clearance();           /* extern */
s32 play_sound_if_enabled();                     /* extern */
void draw_transformed_sprite_with_clip_rect(); /* extern */
extern Packed8 D_80024028;
extern Packed32 D_80024038;
extern M2C_UNK D_800245EC;
extern M2C_UNK D_800246F8;
extern void advance_timed_visual_effect(void *state, void *position, void *visual);
extern void update_tiled_fade_effect(void *effect, void *offset_state, void *render_state);
extern Packed12 D_80025E28;
extern Packed12 D_80025E34;
extern Packed12 D_80025E40;
extern Packed12 D_80025E58;
extern Packed12 D_80025E70;
extern M2C_UNK D_80025E80;
extern u8 D_800E3D68;


typedef struct S_818FF710_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_818FF710_0;

typedef struct S_818FF710_1 {
    u8 pad_00[0x8];
    void * unk_08;
    union {
        struct { s32 v; } at00;
        struct { s8 v; } at00u;
        struct { u8 pad[0x1]; s8 v; } at01;
        struct { u8 pad[0x2]; s8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818FF710_1;   /* arg2 in update_effect_particles_and_cleanup */



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

typedef struct S_818FF710_3 {
    s16 unk_00;
} S_818FF710_3;   /* &D_80025E80 in update_effect_particles_and_cleanup */

typedef struct S_818FF710_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_818FF710_4;

typedef struct S_818FF710_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    union { s32 i; void * p; } unk_10;   /* accessed as both */
    s32 unk_14;
} S_818FF710_5;   /* arg1 in update_effect_particles_and_cleanup */



typedef struct S_818FF710_7_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_818FF710_7_pre;

typedef struct S_818FF710_7 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818FF710_7;

typedef struct S_818FF710_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_818FF710_8;





typedef struct S_818FF710_10 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818FF710_10;

typedef struct S_818FF710_11 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818FF710_11;

typedef struct S_818FF710_12 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_818FF710_12;

typedef struct S_818FF710_13 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_818FF710_13;

typedef struct S_818FF710_14 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x1E];
    void * unk_2C;
    void * unk_30;
    void * unk_34;
    void * unk_38;
    void * unk_3C;
    void * unk_40;
} S_818FF710_14;

typedef struct S_818FF710_15 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
} S_818FF710_15;

typedef struct S_818FF710_16 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_16;

typedef struct S_818FF710_17 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_17;

typedef struct S_818FF710_18 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818FF710_18;

typedef struct S_818FF710_19 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_19;

typedef struct S_818FF710_20 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_20;

typedef struct S_818FF710_21 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818FF710_21;

typedef struct S_818FF710_22 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_22;

typedef struct S_818FF710_23 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_23;

typedef struct S_818FF710_24 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818FF710_24;

typedef struct S_818FF710_25 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_25;

typedef struct S_818FF710_26 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_26;

typedef struct S_818FF710_27 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818FF710_27;

typedef struct S_818FF710_28 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_818FF710_28;

typedef struct S_818FF710_30 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818FF710_30;

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

/* Updates an effect's movement, particles, target effects, and cleanup state. */
void update_effect_particles_and_cleanup(void *effect, void *motion, void *sprite) {
    u16 offset[3];
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
    S_818FF710_12 *hit_target;
    S_818FF710_28 *released_target;
    S_818FF710_4 *parent_sprite;
    void *target_pos_or_step;
    void *sprite_resource;
    S_818FF710_0 *parent_object;
    S_818FF710_15 *first_sprite;
    S_818FF710_18 *second_sprite;
    S_818FF710_14 *child_effect;
    MovingPosition *parent_position;
    void *parent;
    void *third_object;
    void *fourth_object;
    void *first_object;
    void *second_object;
    S_818FF710_11 *target_hit_flags;
    S_818FF710_16 *first_position;
    S_818FF710_19 *second_position;
    S_818FF710_22 *third_position;
    S_818FF710_25 *fourth_position;
    S_818FF710_27 *target_release_flags;
    void *flight_target;
    void *impact_target;

#define effect effect
#define motion motion
#define sprite sprite

    parent = (*(void **)((u8 *)effect + 0));
    texture_rect.packed = D_80024028;
    direction_steps.packed = D_80024038;
    state = (*(s16 *)((u8 *)effect + 0xA));
    parent_object = parent - 0x20;
    parent_position = parent_object->unk_08;
    switch ((u32)(state)) {
    case 0:
        ((S_818FF710_1 *)sprite)->unk_0C.at00.v = 0x808080;
        (*(Packed12 *)((u8 *)effect + 0x96)) = D_80025E70;
        ((S_818FF710_1 *)sprite)->unk_08 = (void *) (effect + 0x96);
        parent_flags = ((S_818FF710_2 *)parent)->unk_2A;
        ((S_818FF710_3 *)(&D_80025E80))->unk_00 = 1;
        (*(s16 *)((u8 *)effect + 0x7E)) = (s16) ((parent_flags >> 9) & 7);
        (*(s16 *)((u8 *)effect + 0xA)) = (s16) ((u16) (*(s16 *)((u8 *)effect + 0xA)) + 1);
    case 1:
        parent_sprite = parent_object->unk_0C;
        if (resolve_record_orientation_or_fallback(parent_sprite->unk_08, parent_sprite, &offset[0], 0) == 0
            && !(((S_818FF710_30 *)(parent_object->unk_0C))->unk_14 & 0x8000)) {
            return;
        }
        ((S_818FF710_5 *)motion)->unk_00.at02.v = (u16) parent_position->unk_02;
        ((S_818FF710_5 *)motion)->unk_04.at02.v = (u16) parent_position->unk_06;
        parent_height = parent_position->unk_0A;
        ((S_818FF710_5 *)motion)->unk_08.at02.v = parent_height;
        if (!(((S_818FF710_30 *)(parent_object->unk_0C))->unk_14 & 0x8000)) {
            ((S_818FF710_5 *)motion)->unk_00.at02.v = (u16) (((S_818FF710_5 *)motion)->unk_00.at02.v + offset[0]);
            ((S_818FF710_5 *)motion)->unk_04.at02.v = (u16) (((S_818FF710_5 *)motion)->unk_04.at02.v + offset[1]);
            ((S_818FF710_5 *)motion)->unk_08.at02.v = (u16) (((S_818FF710_5 *)motion)->unk_08.at02.v + offset[2]);
        } else {
            ((S_818FF710_5 *)motion)->unk_08.at02.v = (u16) (parent_height - 0x40);
        }
        if (!((*(u8 *)((u8 *)effect + 0x7A)) & 4)) {
            register_node(effect - 0x20, project_sprite_chain);
            ((S_818FF710_1 *)sprite)->unk_10 = 0x60;
            ((S_818FF710_1 *)sprite)->unk_0C.at02.v = 0x14;
            ((S_818FF710_1 *)sprite)->unk_0C.at01.v = 0x14;
            ((S_818FF710_1 *)sprite)->unk_0C.at00u.v = 0x14;
            ((S_818FF710_1 *)sprite)->unk_1E = 0x1000;
            ((S_818FF710_1 *)sprite)->unk_1C = 0x1000;
            ((S_818FF710_1 *)sprite)->unk_14 = (u16) (((S_818FF710_1 *)sprite)->unk_14 | 0xC);
            (*(u8 *)((u8 *)effect + 0x7A)) = (u8) ((*(u8 *)((u8 *)effect + 0x7A)) | 4);
        }
        if (!(*(*(u16 **)((u8 *)effect + 4)) & 0x80)) {
            return;
        }
        flight_target = ((S_818FF710_2 *)parent)->unk_60;
        if (flight_target != NULL) {
            target_pos_or_step = ((S_818FF710_7_pre *)flight_target)[-1].unk_00;
            (*(s16 *)((u8 *)effect + 0x78)) = (s16) (((S_818FF710_8 *)target_pos_or_step)->unk_0A
                - (D_800DDC40[((S_818FF710_7 *)flight_target)->unk_13] + 0x40));
            origin = ((SpriteLinkPrefixView *)parent)[-1].unk_00;
            (*(s8 *)((u8 *)effect + 0xA2)) = (s8) (origin->unk_24 + ((u8 *)dir_step_x)[(*(s16 *)((u8 *)effect
                + 0x7E)) * 2]);
            (*(s8 *)((u8 *)effect + 0xA3)) = (s8) (origin->unk_25 + ((u8 *)dir_step_y)[(*(s16 *)((u8 *)effect
                + 0x7E)) * 2]);
            parent_tile = ((S_818FF710_2 *)parent)->unk_72;
            tile_distance = parent_tile;
            origin_tile = origin->unk_24;
            if (tile_distance != origin_tile) {
                tile_distance = tile_distance - origin_tile;
            } else {
                parent_tile = ((S_818FF710_2 *)parent)->unk_73;
                tile_distance = parent_tile;
                origin_tile = origin->unk_25;
                tile_distance = tile_distance - origin_tile;
            }
            if (tile_distance < 0) {
                tile_distance = 0 - tile_distance;
            }
            (*(s8 *)((u8 *)effect + 0x7B)) = (s8) ((tile_distance * 2) - 1);
        } else {
            (*(s16 *)((u8 *)effect + 0x78)) = (s16) (((S_818FF710_2 *)parent)->unk_88 - 0x50);
            (*(s8 *)((u8 *)effect + 0x7B)) = 0x20;
        }
        ((S_818FF710_5 *)motion)->unk_0C = (s32) (direction_steps.pair[(*(s16 *)((u8 *)effect + 0x7E))].first << 0x10);
        ((S_818FF710_5 *)motion)->unk_10.i = (s32) (direction_steps.pair[(*(s16 *)((u8 *)effect + 0x7E))].second
            << 0x10);
        ((S_818FF710_5 *)motion)->unk_14 = (s32) ((s32) (((*(s16 *)((u8 *)effect + 0x78)) << 0x10)
            - ((S_818FF710_5 *)motion)->unk_08.at00.v) / (s8) (*(s8 *)((u8 *)effect + 0x7B)));
        flight_ticks = (u8) (*(s8 *)((u8 *)effect + 0x7B));
        (*(u16 *)((u8 *)effect + 0x82)) = 0U;
        (*(s16 *)((u8 *)effect + 0xA)) = (s16) ((u16) (*(s16 *)((u8 *)effect + 0xA)) + 1);
        (*(s16 *)((u8 *)effect + 0x88)) = (s16) (s8) (u8) (*(s8 *)((u8 *)effect + 0x7B));
        (*(s16 *)((u8 *)effect + 0x8A)) = (s16) ((s8) flight_ticks * (s8) flight_ticks);
        func_80024DB8(effect, motion, sprite);
        return;
    case 2:
        launch_particle = 0;
        for (; launch_particle < 4; launch_particle++) {
            {
                s32 particle_direction;
                s32 particle_color;
                s32 random_value;
                random_value = func_80069EF8();
                particle_color = 0x2020E0;
                particle_size = (random_value & 0xFF) | 0x80;
                particle_direction = (*(s16 *)((u8 *)effect + 0x7E));
                spawn_jittered_child_effect(effect - 0x20, particle_direction, particle_color, particle_size, 0, 0, 0);
            }
        }
        old_flight_angle = ((S_818FF710_1 *)sprite)->unk_1A;
        flight_angle = old_flight_angle + 0x190;
        ((S_818FF710_1 *)sprite)->unk_1A = flight_angle;
        if ((u32) (flight_angle & 0xFFFF) >= 0x1001U) {
            ((S_818FF710_1 *)sprite)->unk_1A = (u16) (old_flight_angle - 0xE70);
        }
        red_tick = ((*(s16 *)((u8 *)effect + 0x88)) - (*(s8 *)((u8 *)effect + 0x7B))) + 1;
        ((S_818FF710_1 *)sprite)->unk_0C.at00u.v =
            (s8) (((s32) (red_tick * red_tick * 0x6C) / (s16) (*(s16 *)((u8 *)effect + 0x8A))) + 0x14);
        green_tick = ((*(s16 *)((u8 *)effect + 0x88)) - (*(s8 *)((u8 *)effect + 0x7B))) + 1;
        ((S_818FF710_1 *)sprite)->unk_0C.at01.v =
            (s8) (((s32) (green_tick * green_tick * 0x6C) / (s16) (*(s16 *)((u8 *)effect + 0x8A))) + 0x14);
        blue_tick = ((*(s16 *)((u8 *)effect + 0x88)) - (*(s8 *)((u8 *)effect + 0x7B))) + 1;
        ((S_818FF710_1 *)sprite)->unk_0C.at02.v =
            (s8) (((s32) (blue_tick * blue_tick * 0x6C) / (s16) (*(s16 *)((u8 *)effect + 0x8A))) + 0x14);
        if ((check_adjacent_tile_height_clearance(((S_818FF710_5 *)motion)->unk_00.at02.v, ((S_818FF710_5 *)motion)->unk_04.at02.v,
            (s16) ((S_818FF710_5 *)motion)->unk_08.at02.v, ((S_818FF710_2 *)parent)->unk_60) << 0x10) != 0) {
            (*(s16 *)((u8 *)effect + 0xA)) = 8;
            (*(u16 *)((u8 *)effect + 0x82)) = 0U;
            ((S_818FF710_1 *)sprite)->unk_0C.at02.v = 0;
            ((S_818FF710_1 *)sprite)->unk_0C.at01.v = 0;
            ((S_818FF710_1 *)sprite)->unk_0C.at00u.v = 0;
            return;
        }
        remaining_ticks = (u8) (*(s8 *)((u8 *)effect + 0x7B)) - 1;
        (*(s8 *)((u8 *)effect + 0x7B)) = remaining_ticks;
        if ((remaining_ticks << 0x18) <= 0) {
            if (((S_818FF710_2 *)parent)->unk_60 != NULL) {
                (*(s16 *)((u8 *)effect + 0xA)) = 3;
                (*(u16 *)((u8 *)effect + 0x82)) = 0U;
                play_sound_if_enabled(0x300);
                impact_target = ((S_818FF710_2 *)parent)->unk_60;
                target_hit_flags = ((SpriteLinkPrefixView *)impact_target)[-1].unk_00;
                if ((u32) (((S_818FF710_10 *)impact_target)->unk_13 - 0x33) >= 4U) {
                    target_hit_flags->unk_14 = (u16) (target_hit_flags->unk_14 | 0x800);
                    hit_target = ((S_818FF710_2 *)parent)->unk_60;
                    hit_target->unk_14 = (s32) (hit_target->unk_14 | 0x100000);
                }
                target_pos_or_step = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_00;
                ((S_818FF710_5 *)motion)->unk_00.at02.v = (u16) ((S_818FF710_13 *)target_pos_or_step)->unk_02;
                ((S_818FF710_5 *)motion)->unk_04.at02.v = (u16) ((S_818FF710_13 *)target_pos_or_step)->unk_06;
                ((S_818FF710_5 *)motion)->unk_08.at02.v = (u16) (*(s16 *)((u8 *)effect + 0x78));
                func_80024DB8(effect, motion, sprite);
                return;
            }
            (*(s16 *)((u8 *)effect + 0xA)) = 8;
            (*(u16 *)((u8 *)effect + 0x82)) = 0U;
            ((S_818FF710_1 *)sprite)->unk_0C.at02.v = 0;
            ((S_818FF710_1 *)sprite)->unk_0C.at01.v = 0;
            ((S_818FF710_1 *)sprite)->unk_0C.at00u.v = 0;
            func_80024DB8(effect, motion, sprite);
            return;
        }
        ((S_818FF710_5 *)motion)->unk_00.at00.v += ((S_818FF710_5 *)motion)->unk_0C;
        ((S_818FF710_5 *)motion)->unk_04.at00.v += ((S_818FF710_5 *)motion)->unk_10.i;
        ((S_818FF710_5 *)motion)->unk_08.at00.v += ((S_818FF710_5 *)motion)->unk_14;
        func_80024DB8(effect, motion, sprite);
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
        old_hit_angle = ((S_818FF710_1 *)sprite)->unk_1A;
        hit_angle = old_hit_angle + 0x190;
        ((S_818FF710_1 *)sprite)->unk_1A = hit_angle;
        if ((u32) (hit_angle & 0xFFFF) >= 0x1001U) {
            ((S_818FF710_1 *)sprite)->unk_1A = (u16) (old_hit_angle - 0xE70);
        }
        func_80024DB8(effect, motion, sprite);
        hit_tick = (*(u16 *)((u8 *)effect + 0x82)) + 1;
        (*(u16 *)((u8 *)effect + 0x82)) = hit_tick;
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
            draw_transformed_sprite_with_clip_rect(((S_818FF710_2 *)parent)->unk_60, texture_start, texture_end, 1, (s32) (s16) hit_tick);
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
            draw_transformed_sprite_with_clip_rect(((S_818FF710_2 *)parent)->unk_60, texture_start, texture_end, 1, (s32) (s16) hit_tick);
        }
        impact_tick = (s16) (*(u16 *)((u8 *)effect + 0x82));
        if (impact_tick != 4) {
            return;
        }
        first_object = func_8003FC64(0x212);
        child_effect = first_object + 0x20;
        if (first_object != NULL) {
            child_effect->unk_02 = 0x78;
            (*(s32 **)((u8 *)first_object + 0x10)) = &D_800246F8;
            register_node(first_object, project_sprite_chain);
            first_sprite = (*(void **)((u8 *)first_object + 0xC));
            first_sprite->unk_06 = 0;
            render_value = first_sprite->unk_14 | 0xC;
            first_sprite->unk_14 = render_value;
            render_value = 0x40;
            first_sprite->unk_10 = render_value;
            sprite_flags = first_sprite->unk_14;
            state = sprite_flags | 0x80;
            first_sprite->unk_14 = state;
            first_position = (*(void **)((u8 *)first_object + 8));
            child_effect->unk_0A = 0;
            child_effect->unk_0C = 0;
            target_pos_or_step = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_00;
            first_position->unk_00 = (s32) ((S_818FF710_17 *)target_pos_or_step)->unk_00;
            first_position->unk_04 = (s32) ((S_818FF710_17 *)target_pos_or_step)->unk_04;
            first_position->unk_08 = (s32) ((S_818FF710_17 *)target_pos_or_step)->unk_08;
            first_sprite = (*(void **)((u8 *)first_object + 0xC));
            first_sprite->unk_1C = 0x1004;
            first_sprite->unk_1E = 0x1004;
            first_sprite->unk_22 = (s16) ((s32) (0
                - D_800DDC40[((S_818FF710_31 *)(((S_818FF710_2 *)parent)->unk_60))->unk_13]) / 2);
            first_sprite->unk_0E = 0x80;
            first_sprite->unk_0D = 0x80;
            first_sprite->unk_0C = 0x80;
            (*(Packed12 *)((u8 *)first_object + 0x40)) = D_80025E34;
            first_sprite->unk_08 = (void *) (first_object + 0x40);
            ((S_818FF710_32 *)(first_sprite->unk_08))->unk_04 = func_80066460(2, 2, 0x340, 0x154);
        }
        second_object = func_8003FC64(0x212);
        child_effect = second_object + 0x20;
        if (second_object != NULL) {
            child_effect->unk_02 = 0x78;
            (*(s32 **)((u8 *)second_object + 0x10)) = &advance_timed_visual_effect;
            register_node(second_object, project_sprite_chain);
            second_sprite = (*(void **)((u8 *)second_object + 0xC));
            second_sprite->unk_14 &= 0xFFF3;
            second_sprite->unk_10 = 0x20;
            second_sprite->unk_14 |= 0x80;
            child_effect->unk_2C = parent;
            follow_target = ((S_818FF710_2 *)parent)->unk_60;
            child_effect->unk_34 = effect;
            child_effect->unk_30 = follow_target;
            second_sprite->unk_06 = 0;
            second_position = (*(void **)((u8 *)second_object + 8));
            child_effect->unk_0A = 0;
            child_effect->unk_0C = 0;
            target_pos_or_step = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_00;
            second_position->unk_00 = (s32) ((S_818FF710_20 *)target_pos_or_step)->unk_00;
            second_position->unk_04 = (s32) ((S_818FF710_20 *)target_pos_or_step)->unk_04;
            second_position->unk_08 = (s32) ((S_818FF710_20 *)target_pos_or_step)->unk_08;
            second_sprite = (*(void **)((u8 *)second_object + 0xC));
            second_sprite->unk_1E = 0x1000;
            second_sprite->unk_1C = 0x1000;
            second_sprite->unk_0E = 0x80;
            second_sprite->unk_0D = 0x80;
            second_sprite->unk_0C = 0x80;
            (*(Packed12 *)((u8 *)second_object + 0x40)) = D_80025E40;
            second_sprite->unk_08 = (void *) (second_object + 0x40);
            ((S_818FF710_33 *)(second_sprite->unk_08))->unk_04 = func_80066460(2, 1, 0x340, 0x1A8);
        }
        third_object = func_8003FC64(0x212);
        child_effect = third_object + 0x20;
        if (third_object != NULL) {
            child_effect->unk_02 = 0x78;
            (*(s32 **)((u8 *)third_object + 0x10)) = &D_800245EC;
            register_node(third_object, project_sprite_chain);
            second_sprite = (S_818FF710_18 *)(*(void **)((u8 *)third_object + 0xC));
            ((S_818FF710_21 *)((void *)second_sprite))->unk_06 = 0;
            render_value = ((S_818FF710_21 *)((void *)second_sprite))->unk_14 & 0xFFF3;
            ((S_818FF710_21 *)((void *)second_sprite))->unk_14 = render_value;
            render_value = 0x20;
            ((S_818FF710_21 *)((void *)second_sprite))->unk_10 = render_value;
            sprite_flags = ((S_818FF710_21 *)((void *)second_sprite))->unk_14;
            state = sprite_flags | 0x80;
            ((S_818FF710_21 *)((void *)second_sprite))->unk_14 = state;
            third_position = (*(void **)((u8 *)third_object + 8));
            child_effect->unk_0A = 0;
            child_effect->unk_0C = 0;
            target_pos_or_step = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_00;
            third_position->unk_00 = (s32) ((S_818FF710_23 *)target_pos_or_step)->unk_00;
            third_position->unk_04 = (s32) ((S_818FF710_23 *)target_pos_or_step)->unk_04;
            third_position->unk_08 = (s32) ((S_818FF710_23 *)target_pos_or_step)->unk_08;
            second_sprite = (S_818FF710_18 *)(*(void **)((u8 *)third_object + 0xC));
            ((S_818FF710_21 *)((void *)second_sprite))->unk_0E = 0x80;
            ((S_818FF710_21 *)((void *)second_sprite))->unk_0D = 0x80;
            ((S_818FF710_21 *)((void *)second_sprite))->unk_0C = 0x80;
            ((S_818FF710_21 *)((void *)second_sprite))->unk_1E = 0;
            ((S_818FF710_21 *)((void *)second_sprite))->unk_1C = 0;
            (*(Packed12 *)((u8 *)third_object + 0x40)) = D_80025E58;
            ((S_818FF710_21 *)((void *)second_sprite))->unk_08 = (void *) (third_object + 0x40);
        }
        fourth_object = func_8003FC64(0x212);
        child_effect = fourth_object + 0x20;
        if (fourth_object != NULL) {
            particle_owner = fourth_object;
            sprite_resource = (void *) project_sprite_chain;
            child_effect->unk_2C = parent;
            fourth_position = (void *) ((S_818FF710_2 *)parent)->unk_60;
            child_effect->unk_30 = (void *) fourth_position;
            child_effect->unk_34 = effect;
            child_effect->unk_38 = first_object + 0x20;
            child_effect->unk_3C = third_object + 0x20;
            child_effect->unk_40 = second_object + 0x20;
            (*(s32 **)((u8 *)fourth_object + 0x10)) = &update_tiled_fade_effect;
            register_node(particle_owner, sprite_resource);
            second_sprite = (S_818FF710_18 *)(*(void **)((u8 *)fourth_object + 0xC));
            ((S_818FF710_24 *)((void *)second_sprite))->unk_06 = 0;
            render_value = ((S_818FF710_24 *)((void *)second_sprite))->unk_14 | 0xC;
            ((S_818FF710_24 *)((void *)second_sprite))->unk_14 = render_value;
            render_value = 0x20;
            ((S_818FF710_24 *)((void *)second_sprite))->unk_10 = render_value;
            sprite_flags = ((S_818FF710_24 *)((void *)second_sprite))->unk_14;
            state = sprite_flags | 0x80;
            ((S_818FF710_24 *)((void *)second_sprite))->unk_14 = state;
            fourth_position = (*(void **)((u8 *)fourth_object + 8));
            child_effect->unk_0A = 0;
            child_effect->unk_0C = 0;
            target_pos_or_step = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_00;
            fourth_position->unk_00 = (s32) ((S_818FF710_26 *)target_pos_or_step)->unk_00;
            fourth_position->unk_04 = (s32) ((S_818FF710_26 *)target_pos_or_step)->unk_04;
            fourth_position->unk_08 = (s32) ((S_818FF710_26 *)target_pos_or_step)->unk_08;
            second_sprite = (S_818FF710_18 *)(*(void **)((u8 *)fourth_object + 0xC));
            ((S_818FF710_24 *)((void *)second_sprite))->unk_1E = 0x1000;
            ((S_818FF710_24 *)((void *)second_sprite))->unk_1C = 0x1000;
            ((S_818FF710_24 *)((void *)second_sprite))->unk_0E = 0x80;
            ((S_818FF710_24 *)((void *)second_sprite))->unk_0D = 0x80;
            ((S_818FF710_24 *)((void *)second_sprite))->unk_0C = 0x80;
            (*(Packed12 *)((u8 *)fourth_object + 0x40)) = D_80025E28;
            ((S_818FF710_24 *)((void *)second_sprite))->unk_08 = (void *) (fourth_object + 0x40);
        }
        spawn_tick = (s16) (*(u16 *)((u8 *)effect + 0x82));
        if (spawn_tick != impact_tick) {
            return;
        }
        (*(s16 *)((u8 *)effect + 0xA)) = spawn_tick;
        (*(u16 *)((u8 *)effect + 0x82)) = 0U;
        (*(s16 *)((u8 *)effect + 0x90)) = 0;
        return;
    }
    case 4:
        impact_particle = 0;
        (*(u16 *)((u8 *)effect + 0x82)) = (u16) ((*(u16 *)((u8 *)effect + 0x82)) + 1);
        for (; impact_particle < 3; impact_particle++) {
            {
                s32 particle_direction;
                s32 particle_color;
                s32 random_value;
                random_value = func_80069EF8();
                particle_color = 0x2020E0;
                particle_size = (random_value & 0xFF) | 0x80;
                particle_direction = (*(s16 *)((u8 *)effect + 0x7E));
                spawn_jittered_child_effect(effect - 0x20, particle_direction, particle_color, particle_size, 0, 0, 0);
            }
        }
        old_impact_angle = ((S_818FF710_1 *)sprite)->unk_1A;
        impact_angle = old_impact_angle + 0x190;
        ((S_818FF710_1 *)sprite)->unk_1A = impact_angle;
        if ((u32) (impact_angle & 0xFFFF) >= 0x1001U) {
            ((S_818FF710_1 *)sprite)->unk_1A = (u16) (old_impact_angle - 0xE70);
        }
        fade_tick = (s16) (*(u16 *)((u8 *)effect + 0x82));
        if (fade_tick >= 0x51) {
            ((S_818FF710_1 *)sprite)->unk_0C.at00u.v = (s8) (((0x64 - fade_tick) << 7) / 20);
            ((S_818FF710_1 *)sprite)->unk_0C.at01.v = (s8) (((0x64 - (s16) (*(u16 *)((u8 *)effect + 0x82))) << 7) / 20);
            ((S_818FF710_1 *)sprite)->unk_0C.at02.v = (s8) (((0x64 - (s16) (*(u16 *)((u8 *)effect + 0x82))) << 7) / 20);
        }
        func_80024DB8(effect, motion, sprite);
        if ((s16) (*(u16 *)((u8 *)effect + 0x82)) < 0x64) {
            return;
        }
        (*(u16 *)((u8 *)effect + 0x82)) = 0U;
        (*(s16 *)((u8 *)effect + 0xA)) = (s16) ((u16) (*(s16 *)((u8 *)effect + 0xA)) + 1);
        return;
    case 5:
        if ((*(s16 *)((u8 *)effect + 0x90)) == 0) {
            return;
        }
        source_id = 0xFF;
        if (D_800E3D68 != 0xFF) {
            source_id = (*(u8 *)((u8 *)effect + 9));
        }
        apply_random_actor_value_adjustment(((S_818FF710_2 *)parent)->unk_60, source_id, parent);
        (*(u16 *)((u8 *)effect + 0x82)) = 0U;
        (*(s16 *)((u8 *)effect + 0xA)) = (s16) ((u16) (*(s16 *)((u8 *)effect + 0xA)) + 1);
        return;
    case 6:
        release_tick = (*(u16 *)((u8 *)effect + 0x82)) + 1;
        (*(u16 *)((u8 *)effect + 0x82)) = release_tick;
        if ((s16) release_tick < 0x1F) {
            return;
        }
        target_release_flags = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_04;
        target_release_flags->unk_14 = (u16) (target_release_flags->unk_14 & 0xF7FF);
        released_target = ((S_818FF710_2 *)parent)->unk_60;
        released_target->unk_14 = (s32) (released_target->unk_14 & 0xFFEFFFFF);
        (*(s16 *)((u8 *)effect + 0xA)) = 8;
        (*(u16 *)((u8 *)effect + 0x82)) = 0x1EU;
        return;
    case 8:
        old_cleanup_tick = (*(u16 *)((u8 *)effect + 0x82));
        cleanup_tick = old_cleanup_tick + 1;
        (*(u16 *)((u8 *)effect + 0x82)) = cleanup_tick;
        if ((s16) cleanup_tick < 0x1F) {
            return;
        }
        effect_active = (s32) ((S_818FF710_3 *)(&D_80025E80))->unk_00;
        (*(u16 *)((u8 *)effect + 0x82)) = old_cleanup_tick;
        if (effect_active == 0) {
            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)effect + -2)) = (u16) ((*(u16 *)((u8 *)effect + -2)) | 0x8000);
            (*(s32 *)&object_flag_block.flags) = (s32) (object_flag_block.flags | 0x8000);
            return;
        }
        (*(s16 *)&D_80025E80) = 0;
        return;
    default:
        return;
    }
}
