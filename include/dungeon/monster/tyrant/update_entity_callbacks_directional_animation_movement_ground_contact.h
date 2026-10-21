#ifndef DUNGEON_OVL_7F0F7800_P01_H
#define DUNGEON_OVL_7F0F7800_P01_H
#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_trail_views.h"


typedef void (*T_80170AA4_EntityCallback)(void *, void *, void *, void *);



typedef struct T_80170AA4_S_80170AA4_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xD];
    s16 unk_12;
    union { u16 n; u16 v; } unk_14;   /* accessed as both */
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} T_80170AA4_S_80170AA4_0;   /* arg2 in func_80170AA4 */

typedef struct T_80170AA4_S_80170AA4_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} T_80170AA4_S_80170AA4_1;   /* entity in func_80170AA4 */

   /* arg1 in func_80170AA4 */

extern void update_owner_class_bits();
extern void func_80042984();
extern void select_indirect_table_entry();
extern void advance_sprite_animation_and_textures();
extern void apply_monster_koyaw_data();
extern void play_sound_if_enabled();
extern s32 refresh_actor_facing_and_lifecycle();
extern void try_move_actor_to_valid_position();
extern s32 sample_terrain_surface_height();
extern T_80170AA4_EntityCallback tyrant_callbacks[];
void update_entity_callbacks_directional_animation_movement_ground_contact(void *actor, TrailMotion *motion, void *part);
extern void update_dungeon_actor_behavior();
#endif
