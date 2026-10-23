/* Ghosh level clamping and actor animation, movement, and terrain updates. */
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "shared/dir_step.h"
#include "shared/sys_flags.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
extern u8 resident_globals_page[];

void enqueue_runtime_pool_script(void *);                   /* extern */
void select_indirect_table_entry(void *, u8, s8);              /* extern */
void advance_sprite_animation_and_textures(void *);                      /* extern */
void apply_monster_koyaw_data(s32, void *);                 /* extern */
void raise_entity_level(void *, s32);             /* extern */
s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);  /* extern */
void try_move_actor_to_valid_position(void *, void *, void *, void *); /* extern */
s16 sample_terrain_surface_height(u16, u16, s16);                   /* extern */
void clear_actor_action_markers(u8 *state);                         /* extern */
extern u8 D_80013610[0x3612];
extern u32 level_experience_table[64];
extern u8 D_800F927E[16];
extern void D_8016B778(void);
extern void (*ghosh_callbacks[256])(void *, void *, void *, void *);

typedef struct S_8016B0E8_0 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x6];
    u32 unk_18;
    u8 pad_1C[0x70];
    s32 (*unk_8C)(void *, void *, void *, void *);
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
    s16 unk_94;
    u8 pad_96[0x2];
    u16 unk_98;
    u8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x1];
    s8 unk_9D;
    u8 pad_9E[0x6];
    void * unk_A4;
    u8 pad_A8[0x8];
    union { u8 n; u8 v; } unk_B0;   /* accessed as both */
    u8 unk_B1;
    u8 pad_B2[0x2];
    u8 unk_B4;
} S_8016B0E8_0;   /* arg0 in update_actor_animation_movement_and_terrain */

typedef struct S_8016B0E8_1 {
    u8 pad_00[0x3610];
    u8 unk_3610;
    u8 unk_3611;
} S_8016B0E8_1;   /* page_8001 in update_actor_animation_movement_and_terrain */

typedef struct S_8016B0E8_2 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x2];
    s32 unk_14;
    u32 unk_18;
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_8016B0E8_2;   /* obj in update_actor_animation_movement_and_terrain */


typedef struct S_8016B0E8_4 {
    u8 pad_00[0x3D7C];
    s32 unk_3D7C;
} S_8016B0E8_4;   /* page_e in update_actor_animation_movement_and_terrain */

typedef struct S_8016B0E8_5 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8016B0E8_5;   /* entry_base in update_actor_animation_movement_and_terrain */

typedef struct S_8016B0E8_6 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8016B0E8_6;

typedef struct S_8016B0E8_8 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8016B0E8_8;

typedef struct S_8016B0E8_9_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8016B0E8_9_pre;

typedef struct S_8016B0E8_10 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8016B0E8_10;


typedef struct S_8016B0E8_12 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_8016B0E8_12;

typedef struct S_8016B0E8_13 {
    u8 pad_00[0x3462];
    u16 unk_3462;
} S_8016B0E8_13;

typedef struct S_8016B0E8_14 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    s32 unk_2C;
} S_8016B0E8_14;   /* arg2 in update_actor_animation_movement_and_terrain */


typedef struct S_8016B0E8_16 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8016B0E8_16;

static __inline__ u16 clamp_level(u32 level)
{
    if (level >= 26)
        level = 25;
    return level;
}

/* Update actor state, animation, movement, and terrain height. */
/* Initializes Ghosh's experience and scripted events, then runs callbacks, updates facing, and resolves
 * movement and ground height. */
void update_actor_animation_movement_and_terrain(void *entity, ObjectPosition *motion, void *sprite) {
    register s32 (*update_callback)(void *, void *, void *, void *);
    register s32 (*paused_callback)(void *, void *, void *, void *);
    register s16 base_height;
    register s32 view_direction;
    s16 direction_index;
    register s16 prior_direction;
    s16 floor_height;
    s16 height_delta;
    register s32 linked_actor;
    register s32 animation_id;
    s32 motion_position;
    s32 motion_delta;
    u16 motion_flags;
    u32 lookup_offset;
    register s32 level_seed;
    register u8 * direction_animations;
    register s32 actor_flags;
    s32 actor_index;

    register u32 level_index;
    register s16 prior_state;
    register u16 height_bits;
    u16 sprite_flags;
    u16 display_flags;
    u32 mode_bits;
    register u32 initial_exp;
    register u32 scaled_level;
    register u8 countdown;
    register u8 facing_flip;
    register u8 fall_ticks;
    register u32 *exp_table;
    register u32 *exp_limits;
    register u32 *level_limits;
    u8 *message;
    void *actor_slot;
    register void *linked_entry;
    register void *actor_header;
    register void *linked_sprite;
    register void *status_record;
    register void *slot_cursor;
    S_8016B0E8_1 *seed_page;


    void *actor;
    u8 *actors_page;
    s32 inactive_mask;

#define entity entity



    actor = entity;
    if (((S_8016B0E8_0 *)entity)->unk_18 == 0) {
        seed_page = (void *)0x80010000;
        level_seed = seed_page->unk_3611 | (seed_page->unk_3610 << 8);
        scaled_level = (u32) level_seed >> 2;
        if (level_seed < 0) {
            scaled_level = (u32) (level_seed + 3) >> 2;
        }
        level_index = clamp_level(scaled_level);
        exp_table = level_experience_table;
        exp_limits = exp_table + 1;
        initial_exp = exp_table[level_index] + 1;
        ((S_8016B0E8_0 *)entity)->unk_18 = initial_exp;
        if (initial_exp >= (u32) exp_limits[((S_8016B0E8_0 *)entity)->unk_11]) {
            level_limits = exp_limits;
            do {
                {
                    raise_entity_level(actor, 0);
                }
            } while (!((u32) level_limits[((S_8016B0E8_2 *)actor)->unk_11] > (u32) ((S_8016B0E8_2 *)actor)->unk_18));
        }
    }
    if (((S_8016B0E8_0 *)entity)->unk_B4 != 0) {
        if ((((s32)g_dungeon_status.active_actor) != 0) || (g_dungeon_status.activity_counts.parts.pending_action_count != 1)) {
            return;
        }
        if (((S_8016B0E8_0 *)entity)->unk_B4 == g_dungeon_status.activity_counts.parts.pending_action_count) {
            message = D_800F927E;



            (*(s16 *)&system_update_flags) = (s16) (system_update_flags | 8);

            enqueue_runtime_pool_script(message);
            actor_index = 0;
            actors_page = (u8 *)0x800E0000;
            inactive_mask = 0x80000000;
            ((S_8016B0E8_2 *)actor)->unk_6D = 0U;
            ((S_8016B0E8_0 *)entity)->unk_9B = 0;
            ((S_8016B0E8_0 *)entity)->unk_B4 = 0U;
            do {
                lookup_offset = actor_index * 4;
                linked_actor = ((S_8016B0E8_16 *)((lookup_offset + ((S_8016B0E8_4 *)actors_page)->unk_3D7C)))->unk_AC;
                if (linked_actor != 0) {
                    clear_actor_action_markers(linked_actor);
                    actor_slot = (void *)(lookup_offset + ((S_8016B0E8_4 *)actors_page)->unk_3D7C);
                    actor_header = ((S_8016B0E8_5 *)actor_slot)->unk_AC - 0x20;
                    ((S_8016B0E8_6 *)actor_header)->unk_10 = (s32) (((S_8016B0E8_6 *)actor_header)->unk_10
                        | inactive_mask);
                }
                actor_index += 1;
            } while (actor_index < 2);
        }
    }

    if (*(u16 *)0x80013714 & 8) {
        actor_index = 1;
        slot_cursor = ((EntityRec *)(((u8 * *)(&dungeon_actor_ring_anchor))))->x.v + 4;
        do {
            linked_entry = ((S_8016B0E8_8 *)slot_cursor)->unk_AC;
            if (linked_entry != 0) {
                linked_sprite = ((S_8016B0E8_9_pre *)linked_entry)[-1].unk_00;
                ((S_8016B0E8_10 *)linked_sprite)->unk_14 = (u16) (((S_8016B0E8_10 *)linked_sprite)->unk_14 & 0xFFBF);
            }
            actor_index -= 1;
            slot_cursor -= 4;
        } while (actor_index >= 0);
    }
    if (((S_8016B0E8_0 *)entity)->unk_B0.n != 0) {
        countdown = ((S_8016B0E8_0 *)entity)->unk_B1 - 1;
        ((S_8016B0E8_0 *)entity)->unk_B1 = countdown;
        if (!(countdown & 0xFF)) {
            ((S_8016B0E8_2 *)actor)->unk_14 = (s32) (((S_8016B0E8_2 *)actor)->unk_14 & 0xFFEFFFFF);
            ((S_8016B0E8_0 *)entity)->unk_B0.v = 0U;
            g_dungeon_status.activity_counts.parts.pending_action_count = (s16) ((u16) g_dungeon_status.activity_counts.parts.pending_action_count - 1);
            status_record = ((S_8016B0E8_0 *)entity)->unk_A4;
            ((S_8016B0E8_12 *)status_record)->unk_1E = (u16) (((S_8016B0E8_12 *)status_record)->unk_1E | 0x8000);
            object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        }
    }
    if (((S_8016B0E8_13 *)resident_globals_page)->unk_3462 & 0x2000) {
        paused_callback = ((S_8016B0E8_0 *)entity)->unk_8C;
        if (paused_callback == &D_8016B778) {
            paused_callback(entity, motion, sprite, actor);
            return;
        }
        ((S_8016B0E8_2 *)actor)->unk_71 = (u8) (((S_8016B0E8_2 *)actor)->unk_71 & 0x7F);
        return;
    }
    prior_state = (s8) ((S_8016B0E8_2 *)actor)->unk_6D;
    if (refresh_actor_facing_and_lifecycle(entity, motion, sprite, actor) == 0) {
        update_callback = ((S_8016B0E8_0 *)entity)->unk_8C;
        if (update_callback != 0) {
            update_callback(entity, motion, sprite, actor);
        }
        ghosh_callbacks[((S_8016B0E8_0 *)entity)->unk_9A](entity, motion, sprite, actor);
        if ((s16) prior_state != (s8) ((S_8016B0E8_2 *)actor)->unk_6D) {
            try_move_actor_to_valid_position(entity, motion, sprite, actor);
        }
        sprite_flags = ((S_8016B0E8_14 *)sprite)->unk_14;
        mode_bits = sprite_flags & 0x8000;
        if (!mode_bits) {
            view_direction = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016B0E8_2 *)actor)->unk_2A + 0x100) >> 9) & 7;
            prior_direction = ((S_8016B0E8_0 *)entity)->unk_94;
            direction_index = view_direction;
            if (prior_direction != direction_index) {
                direction_animations = ((S_8016B0E8_14 *)sprite)->unk_2C;
                if (direction_animations != 0) {
                    animation_id = *(direction_animations + direction_index);
                    select_indirect_table_entry(sprite, animation_id, ((S_8016B0E8_14 *)sprite)->unk_04);
                }
                ((S_8016B0E8_0 *)entity)->unk_94 = view_direction;
            }
            facing_flip = dir_sprite_flag[direction_index];
            if (facing_flip != 0) {
                ((S_8016B0E8_14 *)sprite)->unk_14 |= 1;
            } else {
                ((S_8016B0E8_14 *)sprite)->unk_14 &= 0xFFFE;
            }
            if (!(((S_8016B0E8_2 *)actor)->unk_1C & 0x20)) {
                if (!(((S_8016B0E8_14 *)sprite)->unk_14 & 0x40)) {
                    advance_sprite_animation_and_textures(sprite);
                }
            } else {
                ((S_8016B0E8_14 *)sprite)->unk_14 = (u16) (((S_8016B0E8_14 *)sprite)->unk_14 | 0x7000);
            }
            apply_monster_koyaw_data(((S_8016B0E8_2 *)actor)->unk_1C, sprite + 0xC);
        } else {
            mode_bits = sprite_flags & 0x800;
            if (mode_bits) {
                display_flags = sprite_flags & 0x8FFF;
            } else {
                display_flags = sprite_flags | 0x7000;
            }
            ((S_8016B0E8_14 *)sprite)->unk_14 = display_flags;
        }
        motion->x.v = (s32) (motion->x.v
            + motion->velocity_x);
        motion->y.v = (s32) (motion->y.v
            + motion->velocity_y);
        if (((S_8016B0E8_0 *)entity)->unk_98 & 8) {
            ((S_8016B0E8_0 *)entity)->unk_9D = 0;
        } else {
            motion->velocity_z = (s32) (motion->velocity_z
                + (((S_8016B0E8_0 *)entity)->unk_9D * 0x14000));
            fall_ticks = (u8) ((S_8016B0E8_0 *)entity)->unk_9D + 1;
            ((S_8016B0E8_0 *)entity)->unk_9D = (s8) fall_ticks;
        }
        motion_position = ((S_8016B0E8_0 *)entity)->unk_90.at00.v;
        motion_delta = motion->velocity_z;
        motion_flags = ((S_8016B0E8_0 *)entity)->unk_98;
        motion_position += motion_delta;
        ((S_8016B0E8_0 *)entity)->unk_90.at00.v = motion_position;
        if (!(motion_flags & 4)) {
            floor_height = sample_terrain_surface_height(((u16) motion->x.w.i),
                ((u16) motion->y.w.i), (s16) (((S_8016B0E8_2 *)actor)->unk_88.u - 0x20));
            if (floor_height < 0x200) {
                base_height = ((S_8016B0E8_2 *)actor)->unk_88.s;
                if ((((S_8016B0E8_0 *)entity)->unk_90.at02.v + base_height) < floor_height) {
                    ((S_8016B0E8_2 *)actor)->unk_1C = (s32) (((S_8016B0E8_2 *)actor)->unk_1C & 0xF7FFFFFF);
                } else {
                    height_bits = ((S_8016B0E8_2 *)actor)->unk_88.u;
                    if (floor_height >= base_height) {
                        ((S_8016B0E8_0 *)entity)->unk_90.at00.v = 0;
                    } else {
                        height_delta = floor_height - height_bits;
                        ((S_8016B0E8_0 *)entity)->unk_90.at02.v = height_delta;
                    }
                    motion->velocity_z = 0;
                    ((S_8016B0E8_2 *)actor)->unk_1C = (s32) (((S_8016B0E8_2 *)actor)->unk_1C | 0x08000000);
                    ((S_8016B0E8_0 *)entity)->unk_9D = 0;
                }
                actor_flags = ((S_8016B0E8_2 *)actor)->unk_1C;
                if (actor_flags & 0x40000000) {
                    ((S_8016B0E8_2 *)actor)->unk_1C = (s32) (actor_flags & 0xBFFFFFFF);
                    floor_height = sample_terrain_surface_height((((S_8016B0E8_14 *)sprite)->unk_24 << 6) | 0x20,
                        (((S_8016B0E8_14 *)sprite)->unk_25 << 6) | 0x20,
                        (s16) (((S_8016B0E8_2 *)actor)->unk_88.u - 0x20));
                    ((S_8016B0E8_0 *)entity)->unk_90.at02.v = (s16) ((u16) ((S_8016B0E8_0 *)entity)->unk_90.at02.v
                        + (((S_8016B0E8_2 *)actor)->unk_88.u - floor_height));
                    ((S_8016B0E8_2 *)actor)->unk_88.s = floor_height;
                }
                motion->z.w.i = (s16) (((S_8016B0E8_2 *)actor)->unk_88.u
                    + (u16) ((S_8016B0E8_0 *)entity)->unk_90.at02.v);
                ((S_8016B0E8_14 *)sprite)->unk_14 = (u16) (((S_8016B0E8_14 *)sprite)->unk_14 | 0x40);
                return;
            }
        }
        ((S_8016B0E8_2 *)actor)->unk_1C = (s32) (((S_8016B0E8_2 *)actor)->unk_1C & 0xF7FFFFFF);
        motion->z.w.i = (s16) (((S_8016B0E8_2 *)actor)->unk_88.u
            + (u16) ((S_8016B0E8_0 *)entity)->unk_90.at02.v);
        ((S_8016B0E8_14 *)sprite)->unk_14 = (u16) (((S_8016B0E8_14 *)sprite)->unk_14 | 0x40);
    }
    return;
}
