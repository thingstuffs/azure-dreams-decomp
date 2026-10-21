#ifndef DUNGEON_ACTOR_ABILITY_ELIGIBILITY_H
#define DUNGEON_ACTOR_ABILITY_ELIGIBILITY_H
/* Select eligible actor abilities and entries, check tile clearance, and advance status timers. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/def_table.h"
#include "shared/dungeon_moving_views.h"
#include "shared/tile_object.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_item_entries.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_D_80082E80.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

typedef struct {
    s32 unk0;
    void *unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Entry8007359C;

typedef struct S_800A34BC_0 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800A34BC_0;

typedef struct S_800A3518_0 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x16];
    u8 unk_28;
    u8 unk_29;
} S_800A3518_0;

typedef struct {
    u8 pad0[0x11];
    u8 kind;
    u8 pad12[2];
} DungeonEntry;

typedef struct {
    u8 pad[0x13];
    u8 f13;
} S_D_8006DE24;

typedef struct S_800A36B4_0 {
    void * unk_00;
    u8 pad_04[0x3A];
    u16 unk_3E;
    u8 pad_40[0x5C];
    u16 unk_9C;
} S_800A36B4_0;

/* arg0 in check_tile_path_clear; pointer addresses record offset 0x14 */
typedef struct S_800A36B4_1 {
    void * unk_00;
} S_800A36B4_1;

typedef struct Actor {
    u8 pad00[0x14];
    s32 flags14;
    u8 pad18[4];
    s32 flags1c;
    u8 pad20[0x0A];
    u16 field2a;
    u8 pad2c[0x5C];
    s16 coord88;
    u8 pad8a[0x0E];
    u16 status98;
} Actor;

typedef struct Entity {
    u8 pad00[0x24];
    u8 x;
    u8 y;
} Entity;

typedef struct S_800A3D18_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800A3D18_0;

/* owner in choose_best_eligible_entry */
typedef struct S_800A3D18_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A3D18_1_pre;

/* the 0x14 bytes before cur in choose_best_eligible_entry, addressed as cur[-1] */
typedef struct S_800A3D18_1 {
    u8 pad_00[0x43];
    u8 unk_43;
    u8 pad_44[0x18];
    void * unk_5C;
    u8 pad_60[0x28];
    s16 unk_88;
} S_800A3D18_1;

/* cur in choose_best_eligible_entry */
typedef struct S_800A3D18_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800A3D18_2;

/* other in choose_best_eligible_entry */
typedef struct S_800A3D18_3 {
    u8 pad_00[0x3D7C];
    u8 * unk_3D7C;
} S_800A3D18_3;

/* global_page in choose_best_eligible_entry */
typedef struct S_800A3D18_4 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800A3D18_4;

/* base in choose_best_eligible_entry */
typedef struct S_800A3D18_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800A3D18_5;

typedef struct S_800A3F28_0_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_800A3F28_0_pre;

/* the 0x14 bytes before current in find_eligible_nearby_entry, addressed as current[-1] */
typedef struct S_800A3F28_0 {
    u8 pad_00[0x5C];
    s32 unk_5C;
} S_800A3F28_0;

/* current in find_eligible_nearby_entry */
typedef struct S_800A3F28_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800A3F28_1;

typedef struct DungeonSlot {
    s8 pad_00[0x13];
    u8 field_13;
    u8 pad_14[0x54 - 0x14];
} DungeonSlot;

typedef struct S_800A4300_2 {
    u8 pad_00[0xF0];
    union { void * p; s32 i; } unk_F0;   /* accessed as both */
} S_800A4300_2;

typedef struct {
    s16 value;
    s16 first;
    s16 second;
    s16 unused;
} Entry;

typedef struct Slot_800A48F0 {
    s8 id;
    u8 value;
} Slot_800A48F0;

typedef struct Owner_800A48F0 {
    u8 pad_00[0x2C];
    Slot_800A48F0 slots[4];
} Owner_800A48F0;

typedef struct S_800A4A9C_0 {
    u8 pad_00[0x2C];
    s8 unk_2C;
} S_800A4A9C_0;

typedef struct S_800A4ACC_0 {
    u8 pad_00[0x2C];
    s8 unk_2C;
    s8 unk_2D;
} S_800A4ACC_0;

typedef struct S_800A4ACC_1 {
    s32 unk_00;
} S_800A4ACC_1;

extern Entry8007359C *D_8007359C[4];
extern int abs(int);
extern s32 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
extern s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 generate_random_value(void);
extern s32 check_monster_neighbor_relations(u8, u8, s16, u8, u8, s16);
extern s32 check_entity_interaction_compatibility(void *, void *);
/* data in find_eligible_nearby_entry */
extern s32 find_active_rect_containing_point(u16, u16);
extern DungeonSlot *D_800E3DF0[];
/* This data symbol has no shared-catalog address. */
extern u8 D_80081470[];
extern u8 D_800E3648[];
extern s16 find_entry_at_tile_coordinates(u8, u8, s16);
extern s16 find_floor_item_at_world_position(u8, u8, s16);
extern Entry D_800E3CD8[4];
extern void clear_slots_of_type(void *, s8);
extern void apply_entity_action_flags(void *, s32);
extern void apply_capped_damage_and_hit_effect();

/* Unified external declarations, checked against their definitions and callers. */
extern s32 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);
extern s32 get_entity_effect_value(void *entity, s32 effect_id);
extern s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
extern s32 get_tile_chebyshev_distance(void *source, void *target);
extern void end_status_effect_message(void *entity, s16 effect_id);

/* Functions defined in this translation unit. */
void copy_indexed_entry_data(void *entity);
s32 check_scaled_value_threshold(S_800A3518_0 *state);
s16 find_slot_by_definition_kind(u8 *slots, u8 kind);
u8 get_definition_field_from_triple(s32 entry_addr, s32 entry_index);
s32 compare_three_bit_masks_cyclically(s32 left_mask, s32 right_mask);
s32 check_row_column_or_diagonal_alignment(MovingTile *source, MovingTile *target);
s32 check_tile_path_clear(void *source, void *target);
s32 get_definition_entry_byte_13(s16 entry_index);
s16 choose_usable_ability_or_attack(Actor *actor, Actor *target, u16 *out_angle, s32 prefer_ability);
void *choose_best_eligible_entry(void *owner_arg, void *start, s32 score_limit);
void *find_eligible_nearby_entry(s32 x, s32 y, void *end, void *owner);
s32 check_active_object_state_567(void);
s16 select_highest_value_item(s32 records_addr, s32 item_kind);
s32 check_entity_eligibility(void *entity);
s32 find_type_13_slot_index(DungeonSlot *targetSlot);
void select_position_data_and_update_owner(Rec_D_80082E80 *entity, EntityRec *search_state);
u8 *get_stored_or_fallback_data(void);
s32 lookup_definition_pair_value(s16 firstKey, s16 secondKey);
s32 check_layer_offset_height(u16 x, u16 y, s16 height, u32 flags);
s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
s32 check_enabled_neighbor_height(s32 world_x, s32 world_y, s16 world_z, u32 direction, s32 disabled);
s16 check_adjacent_tile_height_clearance(u16 x, u16 y, s32 z, void *skip_check);
s16 set_or_clear_actor_status_slot(Owner_800A48F0 *owner, s8 id, s8 value);
s32 has_empty_status_slot(s32 record_addr);
s32 advance_status_timers(void *record);

#endif
