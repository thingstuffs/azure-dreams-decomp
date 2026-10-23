#ifndef DUNGEON_FLOOR_GENERATE_H
#define DUNGEON_FLOOR_GENERATE_H
#include "common.h"
#include "modules/dungeon_floor_switch_owners.h"
#include "m2c_compat.h"
#include "shared/game_work.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_item_entries.h"
#include "shared/dir_step.h"
#include "shared/runtime_dispatch.h"
#include "shared/entity_objects.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8001CE44_arg0.h"
#include "shared/record_ptrs.h"
typedef struct floor_generate_isolated_8028444C_S_8001744C_0 {
    s16 unk_00;
} floor_generate_isolated_8028444C_S_8001744C_0;
typedef struct floor_generate_isolated_8028444C_S_8001744C_1 {
    s16 unk_00;
    s16 unk_02;
} floor_generate_isolated_8028444C_S_8001744C_1;
typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
} floor_generate_isolated_80284480_DungeonCell;
typedef struct floor_generate_isolated_80284560_S_80017560_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
} floor_generate_isolated_80284560_S_80017560_0;
typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
} floor_generate_isolated_80284584_DungeonCell;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))
typedef struct {
    s32 words[2];
    s16 field_8;
    s16 field_A;
    s16 field_C;
    s16 field_E;
    s32 field_10;
} floor_generate_isolated_802846EC_DungeonEntry;
typedef struct floor_generate_isolated_802847D8_S_800177D8_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    void * unk_10;
} floor_generate_isolated_802847D8_S_800177D8_0;
typedef struct floor_generate_isolated_802847D8_S_800177D8_1 {
    s8 unk_00;
    s8 unk_01;
    s16 unk_02;
} floor_generate_isolated_802847D8_S_800177D8_1;
typedef struct {
    s16 kind;
    s16 x;
    s16 y;
    s16 value;
} floor_generate_isolated_8028484C_SpawnEntry;
typedef struct {
    u16 flags;
    u16 value;
    u16 extra;
} floor_generate_isolated_8028484C_MapCell;
typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
} floor_generate_isolated_80284A9C_Cell;
typedef struct floor_generate_isolated_80284BEC_S_80017BEC_T {
    u8 pad_00[0x4];
    u16 unk_04;
} floor_generate_isolated_80284BEC_S_80017BEC_T;
typedef struct floor_generate_isolated_80284BEC_S_80017BEC_M {
    floor_generate_isolated_80284BEC_S_80017BEC_T *tiles;
    u8 pad_04[0x10];
    s16 unk_14;
} floor_generate_isolated_80284BEC_S_80017BEC_M;
typedef struct {
    u16 x;
    u16 y;
    s16 width;
    s16 height;
    s8 pad[12];
} floor_generate_isolated_80284EBC_DungeonEntry;
typedef struct {
    u16 f0;
    u16 f2;
    u16 flags;
} floor_generate_isolated_80284EBC_DungeonCell;
typedef struct {
    u16 x;
    u16 y;
    u16 flags;
} floor_generate_isolated_80284F88_DungeonCell;
typedef struct floor_generate_isolated_8028516C_DungeonCell {
    s16 unk0;
    s16 unk2;
    u16 flags;
} floor_generate_isolated_8028516C_DungeonCell;
typedef struct floor_generate_isolated_80285464_MapCell {
    s16 kind;
    u16 value;
    s16 flags;
} floor_generate_isolated_80285464_MapCell;
typedef struct floor_generate_isolated_80285464_Room {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
    u8 pad08[2];
    s16 active;
    u8 pad0C[2];
    s16 count;
    u8 *tiles;
} floor_generate_isolated_80285464_Room;
typedef struct floor_generate_isolated_80285464_RoomCell {
    u8 a;
    u8 b;
    u16 c;
} floor_generate_isolated_80285464_RoomCell;
typedef struct floor_generate_isolated_80285464_Ent8 {
    s16 kind;
    s16 x;
    s16 y;
    s16 value;
} floor_generate_isolated_80285464_Ent8;
typedef struct floor_generate_isolated_80285464_RecB {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
    s16 f4;
    s16 f6;
    s32 f8;
} floor_generate_isolated_80285464_RecB;
typedef struct floor_generate_isolated_80285464_RecC {
    u8 pad00[6];
    u8 f6;
    u8 f7;
    s32 f8;
    u8 pad0C[12];
} floor_generate_isolated_80285464_RecC;
typedef struct floor_generate_isolated_80285464_RecD {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
} floor_generate_isolated_80285464_RecD;
#define floor_generate_isolated_80285464_ROOM_CELL(r, n) (*(floor_generate_isolated_80285464_RoomCell *)&generation_region_cell_entries[((n) << 2) + ((r) << 6)])
typedef struct {
    s32 seed;
    u16 flags;
    s16 field6;
    s16 field8;
    s16 fieldA;
    u8 padC[4];
    s8 field10;
    s8 field11;
} floor_generate_isolated_80285A70_State13710;
typedef struct {
    u8 pad0000[0x234];
    s32 level;
    u8 pad0238[0x2090 - 0x238];
    s32 mode;
} floor_generate_isolated_80285A70_Page8001;
typedef struct {
    u8 kind;
    u8 arg;
    u8 track;
    u8 table_index;
    u8 special;
} floor_generate_isolated_80285A70_TrackRecord;
typedef struct {
    u8 pad0000[0x296C];
    u32 flags;
} floor_generate_isolated_80285A70_Page800E;
typedef struct {
    s32 seed;
    u16 level;
    s16 ready;
} floor_generate_isolated_80285A70_SaveHead;
typedef struct {
    u8 pad0000[0x234];
    u16 level;
} floor_generate_isolated_80285A70_LevelPage;
typedef struct floor_generate_isolated_80285E80_DungeonRecord80285E80 {
    u8 value;
    u8 level;
} floor_generate_isolated_80285E80_DungeonRecord80285E80;
typedef struct floor_generate_isolated_80285E80_DungeonState80285E80 {
    u8 pad00[0x18];
    floor_generate_isolated_80285E80_DungeonRecord80285E80 *records;
} floor_generate_isolated_80285E80_DungeonState80285E80;
typedef struct floor_generate_isolated_80285E80_Packed16_80285E80 {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
} __attribute__((packed)) floor_generate_isolated_80285E80_Packed16_80285E80;
typedef struct floor_generate_isolated_80285E80_DungeonGlobals80285E80 {
    u8 pad022c[0x22C];
    s32 state_022c;
    u8 pad0230[4];
    s32 floor_0234;
    u8 pad0238[0x2090 - 0x238];
    s32 state_2090;
} floor_generate_isolated_80285E80_DungeonGlobals80285E80;
#define floor_generate_isolated_80285E80_DUNGEON_GLOBALS ((floor_generate_isolated_80285E80_DungeonGlobals80285E80 *)0x80010000)
typedef struct {
    u8 bytes[0x20];
} __attribute__((packed)) floor_generate_isolated_802864C4_Copy32;
typedef struct floor_generate_isolated_80286684_Object {
    s32 field_0;
} floor_generate_isolated_80286684_Object;
typedef struct floor_generate_isolated_80286894_S_80019894_0 {
    u16 unk_00;
    u8 pad_02[0x2];
    s32 unk_04;
    void * unk_08;
} floor_generate_isolated_80286894_S_80019894_0;
typedef struct {
    u16 active;
    s16 value;
    s16 unused;
} floor_generate_isolated_80286A84_DungeonCell;
typedef struct floor_generate_isolated_80286AF8_MapCell {
    s16 kind;
    s16 value;
    u16 flags;
} floor_generate_isolated_80286AF8_MapCell;
typedef struct floor_generate_isolated_80286AF8_DungeonCfg {
    floor_generate_isolated_80286AF8_MapCell *cells;
    u8 pad04[16];
    s16 shift_x;
    s16 shift_y;
    s16 mask_x;
    s16 mask_y;
    s16 span_x;
    s16 span_y;
} floor_generate_isolated_80286AF8_DungeonCfg;
typedef struct floor_generate_isolated_80286AF8_Room {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
    s16 tint;
    s16 active;
    u16 link;
    u8 pad0E[2];
    u8 *tiles;
} floor_generate_isolated_80286AF8_Room;
typedef struct floor_generate_isolated_80286AF8_Pair {
    u8 a;
    u8 b;
} floor_generate_isolated_80286AF8_Pair;
typedef struct {
    s16 x;
    s16 y;
    s16 unk4;
    s16 dir;
} floor_generate_isolated_80287C4C_Pos;
typedef floor_generate_isolated_80286AF8_MapCell floor_generate_isolated_80287C4C_DungeonCell;
typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
    u8 pad08[2];
    s16 active;
    u8 pad0C[8];
} floor_generate_isolated_80287C4C_Room;
typedef struct {
    s16 x;
    s16 y;
    s16 unk4;
    s16 dir;
} floor_generate_isolated_8028906C_Pos;
typedef struct {
    s16 unused[10];
    s16 stride;
} floor_generate_isolated_8028906C_DungeonState;
typedef struct {
    s16 kind;
    s16 value;
    s16 flags;
} floor_generate_isolated_8028906C_DungeonCell;
typedef u32 CoordPair __attribute__((aligned(2)));
typedef struct {
    s16 x;
    s16 y;
    s16 unk4;
    s16 dir;
} floor_generate_isolated_802895E4_Pos;
typedef struct {
    s16 kind;
    s16 value;
    s16 flags;
} floor_generate_isolated_802895E4_DungeonCell;
typedef struct {
    u16 unk0;
    u16 tile;
} floor_generate_isolated_802895E4_Walker;
typedef struct floor_generate_isolated_80289BD4_MapCell {
    u16 unk_00;
    u16 unk_02;
    u16 blocked;
} floor_generate_isolated_80289BD4_MapCell;
typedef struct {
    u8 pad0[4];
    u16 field4;
    u16 field6;
    u16 field8;
    s16 fieldA;
} floor_generate_isolated_80289CEC_Entry;
typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} floor_generate_isolated_80289EC0_Rect;
typedef struct {
    s16 height;
    u16 y;
    u16 flags;
} floor_generate_isolated_80289EC0_Tile;
typedef struct {
    u8 pad0[12];
    u8 *entries;
    u8 pad10[4];
} floor_generate_isolated_8028A0F4_DungeonGroup;
typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} floor_generate_isolated_8028A0F4_DungeonRect;
typedef struct {
    u8 pad0[6];
    u8 px;
    u8 py;
    u8 pad8[16];
} floor_generate_isolated_8028A0F4_DungeonSpot;
typedef struct {
    u8 kind;
    u8 f1;
    u8 f2;
    u8 f3;
} floor_generate_isolated_8028A0F4_DungeonSlot;
typedef struct floor_generate_isolated_8028A328_S_8001D328_0 {
    u8 unk_00;
    u8 pad_01[0x1];
    u8 unk_02;
    u8 pad_03[0x1];
    u16 unk_04;
    u16 unk_06;
} floor_generate_isolated_8028A328_S_8001D328_0;
typedef struct floor_generate_isolated_8028A328_S_8001D328_1 {
    u8 unk_00;
    u8 unk_01;
} floor_generate_isolated_8028A328_S_8001D328_1;
typedef struct floor_generate_isolated_8028A4AC_S_8001D4AC_1 {
    s32 unk_00;
} floor_generate_isolated_8028A4AC_S_8001D4AC_1;
typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 value;
} floor_generate_isolated_8028A5D8_DungeonRect;
typedef struct {
    s16 unused[10];
    s16 stride;
} floor_generate_isolated_8028A5D8_DungeonState;
typedef struct {
    s16 kind;
    s16 value;
    s16 flags;
} floor_generate_isolated_8028A5D8_DungeonCell;
typedef struct {
    u8 unused[0x146E];
    s16 level;
} floor_generate_isolated_8028A5D8_DungeonPage;
typedef struct floor_generate_isolated_8028AC34_S_8001DC34_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} floor_generate_isolated_8028AC34_S_8001DC34_0;
typedef struct floor_generate_isolated_8028AC34_S_8001DC34_1_pre {
    s16 unk_00;
} floor_generate_isolated_8028AC34_S_8001DC34_1_pre;
typedef struct floor_generate_isolated_8028AC34_S_8001DC34_1 {
    s16 unk_00;
} floor_generate_isolated_8028AC34_S_8001DC34_1;
typedef struct {
    s16 unk0;
    u16 value;
    s16 unk4;
} floor_generate_isolated_8028AD84_D_800EA000_Record;
#define M2C_SYNC() 0
typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    s16 unk8;
    s16 active;
    u8 pad[8];
} floor_generate_isolated_8028AE2C_DungeonArea;
extern u8 generation_region_cell_entries[];
extern u16 select_dungeon_spawn_tile(u8 *, u8 *);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern s32 generate_random_value(void);
s32 sample_terrain_surface_height();
extern s32 get_offset_map_cell_value_and_flags(s16, s16, s16, u16 *);
extern s32 check_diagonal_side_height(u16, s16, s16, s16);
extern void Control_CD(s32, s32, s32);
extern void drain_cd_command_queue(void);
extern s32 get_item_category_value(u8 *item);
extern void decompress_lz(u8 *, u8 *);
extern void func_8004068C(u8 *, u8 *);
extern s32 get_surface_height_at_coordinates(s32, s32);
extern s32 floor_layout_resource_descriptors[];
extern s16 floor_layout_loaded;
extern s32 floor_object_sprite_sources[];
extern s32 dungeon_floor_flags;
extern s32 floor_loaded_content_flags;
extern void apply_state_index_tile_masks(void);
extern void bind_view_triplet_source();
extern void runtime_load_packed_resource_chunks();
extern s32 bzero();
extern s32 rand(void);
extern s32 srand();
extern void store_random_nibble(void);
extern void clear_dungeon_cell_entries(void);
extern void clear_dungeon_object_entries(void);
extern void file_load_com();
extern floor_generate_isolated_80285A70_TrackRecord floor_track_configuration_records[];
extern s32 floor_track_resource_descriptors[];
extern u8 floor_generation_track_variant;
extern s32 floor_variant_resource_descriptors[];
extern u8 D_800F0000[];
extern s8 scene_music_hold[12];
extern u8 scene_mode_code[9];
extern s32 test_resident_bit(s32 value);
extern s32 func_80033BC0(s32 value);
extern void wait_until_sound_idle(void);
extern void func_80044698(void);
extern void load_and_upload_sprite_resource(s16 entity_type);
extern void SD_Call(s32 command, ...);
extern void drain_audio_commands_and_service_channels(void);
extern s32 random_dungeon_range_16(s32 lower, u16 upper);
extern void pack_tagged_resource_descriptor(s32, void *, s32 *, s32);
extern floor_generate_isolated_802864C4_Copy32 dungeon_resource_buffer;
extern s8 D_80012D52;
extern void audio_load_sound_effect_bank(s32);
extern void load_sound_set(s16);
extern void func_8004450C(s16);
extern floor_generate_isolated_80286684_Object *sound_stream_resource_entries[];
extern s8 sound_stream_state_index;
extern floor_generate_isolated_80286684_Object *sound_stream_buffer_entries[2];
extern s16 sound_stream_buffer_index;
extern s32 sound_stream_primary_marker_address[4];
extern s32 sound_stream_secondary_marker_address[4];
void set_sound_payload_slot();
s16 test_sound_channel_availability();
s32 VSync();
s32 DrawSync();
extern M2C_UNK sound_effect_bank_descriptors;
extern M2C_UNK sound_effect_loaded_record_ids;
extern s32 dungeon_mode_state[3];
extern s32 count_matching_packed_entity_keys(s32, s32);
extern s32 generation_room_columns;
extern s32 generation_room_rows;
extern u16 generation_unflagged_room_count;
extern u8 generation_search_forward_limit;
extern s8 generation_search_turn_offsets[];
extern void save_or_restore_random_seed(s32);
extern u32 calculate_planar_heading(s16, s16, s16, s16);
extern floor_generate_isolated_8028A0F4_DungeonGroup item_category_groups[];
extern u8 D_800E3549[];
extern s32 generation_special_feature_placed;
extern u8 resident_globals_page[];
extern u8 generation_border_cell_base_alias[];
void clear_generation_cell_grid(void);
void mask_generation_cell_rect(s16 start_x, s16 start_y, s16 rect_width, s16 rect_height, u16 mask);
void clear_generation_cell_masks(void);
void clear_thirty_six_table_fields(void);
s16 find_first_nonzero_rectangle_field(s16 start_x, s16 start_y, s16 width, s16 height);
void fill_generation_cell_marks(s16 start_x, s16 y, s16 width, s32 height, u16 fill_value);
void compact_generation_regions(void);
void clear_generation_region_entries(void);
void append_generation_region_entry(s16 row_index, s16 first_byte, s16 second_byte, s16 value);
void place_random_floor_elevators(void);
void initialize_grid_border_cells(void);
s32 mark_path_through_neighboring_tiles(s16 region_id);
s16 count_unblocked_cells_in_generation_region(s16 entry_index);
s16 find_highest_eligible_sample(s16 rect_index, s16 *out_x, s16 *out_y, s16 check_flags);
s16 find_first_qualifying_cell(s16 record_id, s16 *out_x, s16 *out_y, s32 search_mode);
s32 classify_directional_movement(s16 input_x, s16 input_y, s32 current_height, s16 direction);
void load_dungeon_layout(s16 layout_number);
s32 setup_dungeon_floor_encounters(void);
void load_floor_spawn_tables(s16 resource_index);
void convert_valid_entry_code_2_to_39(void);
s32 load_object_into_alternate_buffer(s16 object_index, s16 mode, s16 activate);
s32 load_generation_resource_slot(s16 resource_index);
s32 try_add_second_tower_entry(s16 entry_index);
void set_first_table_entry_active(void);
void fill_inactive_interior_cells(s16 value);
s32 generate_floor_layout(void);
void reset_generation_link_scratch(void);
s16 search_outward_for_eligible_tile(u16 *facing, s32 origin_x, s32 origin_y, s8 *tiles, s32 search_arg, s32 radius,
                  s32 filter_arg);
s32 has_generation_link_within_pair(s16 value_a, s16 value_b);
s16 connect_rooms_with_corridor(s16 src_dir, s16 dest_dir, s16 src_idx, s16 dest_idx, u8 *room_marks);
s32 choose_next_step_toward_destination(floor_generate_isolated_8028906C_Pos *start, floor_generate_isolated_8028906C_Pos *dest, s16 rnd, s16 *outX, s16 *outY);
s16 carve_corridor_toward_destination(floor_generate_isolated_802895E4_Pos *start, floor_generate_isolated_802895E4_Pos *dest, s16 rnd, s16 *out_x, s16 *out_y,
                  floor_generate_isolated_802895E4_Walker *walker, s32 *cost);
s16 choose_unblocked_cardinal_direction(s16 x, s16 y, s16 dir);
void pick_relative_room_edge_point(s16 side, s16 *out_x, s16 *out_y, floor_generate_isolated_80289CEC_Entry *room);
s32 is_value_within_inclusive_bounds(s16 value, s32 lower_bound, s16 upper_bound);
void update_region_until_complete(Rec_func_8001CE44_arg0 *region, s16 update_id);
void adjust_random_parity_tile_heights(floor_generate_isolated_80289EC0_Rect *rect, s32 rng_input_1);
void initialize_random_room_slot(void *room, s32 rng_arg1);
void place_room_trap_records(floor_generate_isolated_8028A0F4_DungeonRect *rect, s32 update_id);
void mark_random_eligible_region_tiles(floor_generate_isolated_8028A328_S_8001D328_0 *region, s32 setup_arg1);
void fill_region_with_random_patches(floor_generate_isolated_8028A5D8_DungeonRect *rect, s32 update_id);
void write_rectangular_border(s16 left_x, s16 top_y, s16 right_x, s16 bottom_y, s32 tile_value_base);
void clear_region_grid_rectangle(floor_generate_isolated_8028AC34_S_8001DC34_0 *region);
void advance_generation_step_pair(void *step_state, s32 update_id);
void retreat_generation_step_pair(void *step_state, s32 update_id);
s16 get_minimum_stepped_cell_value(s32 x, s32 y, s32 count, s16 x_step, s16 y_step);
void update_active_area_tiles(void);
extern floor_generate_isolated_80286AF8_MapCell generation_cells[];
extern u8 dungeon_room_count[];
extern u8 current_dungeon_floor[];
extern u8 floor_objects[];
extern u8 dungeon_ground_item_positions[];
extern u8 dungeon_floor_object_positions[12];
extern u8 dungeon_floor_marker_entries[];
extern u8 scene_geometry[];
extern u8 gpu_scratch_buffer_base[];
extern u8 gpu_scratch_write_pointer[];
extern u8 floor_generation_state[];
extern u8 floor_species_pool[];
extern u8 generation_room_link_count[];
extern u8 generation_room_link_pairs[];
extern u8 generation_blocked_direction_marks[];
extern u8 generation_search_side_marks_alias[];
void empty_dungeon_hook(s32 x, s32 y, s16 *tile, s32 kind, s32 amount);
#endif
