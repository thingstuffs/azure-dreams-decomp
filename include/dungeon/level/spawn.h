#ifndef DUNGEON_FLOOR_SPAWNS_H
#define DUNGEON_FLOOR_SPAWNS_H
#include "common.h"
#include "modules/dungeon_floor_switch_owners.h"
#include "m2c_compat.h"
#include "shared/dungeon_item_entries.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_floor.h"
#include "shared/object_node.h"
#include "dungeon/level.h"
struct ObjectNodeHeader;
typedef struct {
    u8 x;
    u8 y;
    s8 pad[10];
} floor_spawns_isolated_8028B110_DungeonPosition;
typedef struct {
    u8 x;
    u8 y;
    u8 pad2[2];
    s16 field4;
    u8 pad6;
    u8 field7;
    s32 field8;
} floor_spawns_isolated_8028B18C_DungeonRecord;
typedef struct {
    u16 flags;
    u8 pad2[18];
} floor_spawns_isolated_8028B18C_DungeonItem;
typedef struct {
    u8 pad0[12];
    floor_spawns_isolated_8028B18C_DungeonItem *entries;
    u8 pad10[4];
} floor_spawns_isolated_8028B18C_DungeonGroup;
typedef struct floor_spawns_isolated_8028B660_S_8001E660_0 {
    u8 pad_00[0xFB];
    u8 unk_FB;
} floor_spawns_isolated_8028B660_S_8001E660_0;
typedef struct floor_spawns_isolated_8028B824_S_8001E824_0 {
    u8 unk_00;
    u8 unk_01;
    s8 unk_02;
    s8 unk_03;
} floor_spawns_isolated_8028B824_S_8001E824_0;
typedef struct {
    u16 flags;
    u8 pad2[18];
} floor_spawns_isolated_8028B994_DungeonItem;
typedef struct {
    u8 pad0[2];
    u8 count;
    u8 pad3[9];
    floor_spawns_isolated_8028B994_DungeonItem *entries;
    u8 pad10[4];
} floor_spawns_isolated_8028B994_DungeonGroup;
typedef struct floor_spawns_isolated_8028BAA4_ItemCategoryRow {
    u8 pad_00[0xC];
    s32 item_table;
} floor_spawns_isolated_8028BAA4_ItemCategoryRow;
typedef struct {
    u8 x;
    u8 y;
    u8 pad2[2];
    s16 height;
    u8 pad6;
    u8 flag7;
    s32 object;
} floor_spawns_isolated_8028BC54_DungeonCell;
typedef struct floor_spawns_isolated_8028BF0C_S_8001EF0C_0 {
    u8 pad_00[0x11];
    u8 unk_11;
    s8 unk_12;
    u8 pad_13[0x5];
    u32 unk_18;
    u8 pad_1C[0x27];
    union { u8 s; s8 u; } unk_43;   
} floor_spawns_isolated_8028BF0C_S_8001EF0C_0;
typedef struct floor_spawns_isolated_8028BF0C_S_8001EF0C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
} floor_spawns_isolated_8028BF0C_S_8001EF0C_1;
typedef struct {
    u8 type;
    u8 state;
    u8 unk2;
    u8 unk3;
} floor_spawns_isolated_8028BF0C_SpawnMeta;
typedef struct {
    u8 pad0[6];
    u8 x;
    u8 y;
    s32 value;
    s32 zero;
    s16 unk10;
    s16 unk12;
    u16 flags;
    u16 pad16;
} floor_spawns_isolated_8028BF0C_SpawnPosition;
typedef void *(*SpawnFunc)(s32, s32, s32, s32);
#define floor_spawns_isolated_8028BF0C_PAGE_8008 ((u8 *)0x80080000)
extern s32 select_dungeon_spawn_tile(u8 *, u8 *);
extern s16 count_matching_packed_entity_keys(s32, s32);
extern s32 generate_random_value(void);
extern s32 find_first_empty_floor_item_slot(void);
extern s32 get_item_category_value(void *item);
extern s16 get_surface_height_at_coordinates(s32, s32);
extern u8 floor_species_pool[];
extern s16 floor_generation_state[3];
extern s32 floor_loaded_content_flags[];
extern s32 test_resident_bit(s32);
extern s32 func_80033BC0(s32);
extern s32 has_recorded_value_pair(s32, s32);
extern s16 spawn_category_weight_totals[];
extern s32 random_dungeon_range_16(s32, s32);
extern u8 D_80010000[];
/* One leading experience word followed by the 100 threshold words built by
 * build_cubic_cumulative_table. These are overlapping word views, not pairs
 * of initial/limit arrays repeated at an eight-byte stride. */
extern u32 level_experience_table[101];
extern s32 entity_level_thresholds[];
extern floor_spawns_isolated_8028BF0C_SpawnPosition dungeon_floor_object_positions[];
extern u8 *D_800735C4[];
extern u8 floor_object_sprite_sources[];
extern void select_record_entry_and_value(void *state, void *entries, short index);
extern void func_80042640(void *, s32);
extern SpawnFunc load_monster_resource_data(s32 resource_id, u8 *resource_entry, s32 wait_for_read);
extern void retain_spawn_resource(s32, s32);
extern u8 *find_or_retain_sprite_resource_slot(s32, s32);
extern void raise_entity_level(void *, s32);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
extern s32 linked_sprite_renderer_address[3];
extern s32 D_800A5AF0[3];
extern void func_8004E634(s16, u8 *);
extern void *D_8001F5B4[];
extern u8 D_80077DE8[];
extern u8 D_80077E00[];
s32 is_floor_item_tile_occupied(s32 excluded_slot, s16 x, s16 y);
void populate_floor_item_records(void);
void clear_dungeon_cell_entries(void);
void build_cumulative_item_weights(void);
s32 select_weighted_floor_item(s8 *category_out, s8 *item_out);
void generate_random_dungeon_item_drops(void);
void restore_spawns_and_place_floor_traps(void);
void clear_dungeon_object_entries(void);
void create_tinted_dungeon_object(s16 x, s16 y, s16 tinted, s32 render_param);
void draw_dungeon_value_and_label(void);
extern u8 dungeon_ground_item_positions[];
extern u8 floor_special_item_selected[];
extern u8 item_category_groups[];
extern u8 current_dungeon_floor[];
extern u8 floor_objects[];
#endif
