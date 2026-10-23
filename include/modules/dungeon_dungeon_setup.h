#ifndef DUNGEON_DUNGEON_SETUP_H
#define DUNGEON_DUNGEON_SETUP_H

struct ObjectPosition;
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_item_entries.h"
#include "shared/dungeon_floor.h"
#include "m2c_compat.h"
#include "records/Rec_D_80083460.h"
#include "shared/runtime_dispatch.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
typedef struct {
    u8 pad_00[0x19];
    s8 red;
    s8 green;
    s8 blue;
} dungeon_setup_80283000_ColorState;
typedef struct {
    u32 unk00;
    u8 pad04[0x10];
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    u16 unk1C;
    u16 unk1E;
} dungeon_setup_802831D8_InitBlock;
typedef struct {
    u8 pad00[0xA8];
    u32 unkA8;
    u8 padAC[0x130];
    dungeon_setup_802831D8_InitBlock unk1DC;
} dungeon_setup_802831D8_GlobalState;
typedef struct dungeon_setup_8028325C_S_8001625C_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    s16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
} dungeon_setup_8028325C_S_8001625C_0;
typedef struct dungeon_setup_8028325C_S_8001625C_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} dungeon_setup_8028325C_S_8001625C_2;
typedef struct dungeon_setup_8028325C_S_8001625C_3 {
    s8 unk_00;
} dungeon_setup_8028325C_S_8001625C_3;
typedef struct dungeon_setup_802835B8_S_800165B8_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u8 pad_14[0x86];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x5];
    u16 unk_A2;
    u8 pad_A4[0x38];
    s32 unk_DC;
    s32 unk_E0;
} dungeon_setup_802835B8_S_800165B8_1;
typedef struct dungeon_setup_802835B8_S_800165B8_2 {
    u8 pad_00[0x10];
    u8 unk_10;
    u8 pad_11[0x1];
    u8 unk_12;
    u8 pad_13[0x3];
    u16 unk_16;
} dungeon_setup_802835B8_S_800165B8_2;
typedef struct dungeon_setup_802835B8_S_800165B8_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
    u8 pad_27[0x1];
    s32 unk_28;
    void * unk_2C;
} dungeon_setup_802835B8_S_800165B8_3;
typedef struct dungeon_setup_802835B8_S_800165B8_5 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x14];
    s8 unk_40;
    s8 unk_41;
    s8 unk_42;
    u8 pad_43[0x15];
    void * unk_58;
    void * unk_5C;
    u8 pad_60[0x28];
    s16 unk_88;
} dungeon_setup_802835B8_S_800165B8_5;
typedef struct dungeon_setup_802835B8_S_800165B8_6 {
    u8 pad_00[0xFA];
    u8 unk_FA;
} dungeon_setup_802835B8_S_800165B8_6;
typedef struct dungeon_setup_802835B8_S_800165B8_8 {
    u8 pad_00[0x4];
    s16 unk_04;
    union { u16 s; s16 u; } dungeon_setup_802835B8_unk_06;   
} dungeon_setup_802835B8_S_800165B8_8;
typedef struct dungeon_setup_802835B8_S_800165B8_10 {
    u8 pad_00[0x3714];
    u16 unk_3714;
} dungeon_setup_802835B8_S_800165B8_10;
typedef struct {
    u8 bytes[13];
} __attribute__((packed)) dungeon_setup_802835B8_Copy13;
typedef struct {
    u8 bytes[12];
} __attribute__((packed)) dungeon_setup_802835B8_Copy12;
typedef struct dungeon_setup_80283BF0_S_80016BF0_0 {
    u8 pad_00[0x10];
    u8 * unk_10;
    s16 unk_14;
    s16 unk_16;
} dungeon_setup_80283BF0_S_80016BF0_0;
typedef struct dungeon_setup_80283BF0_S_80016BF0_2_pre {
    u16 unk_00;
} dungeon_setup_80283BF0_S_80016BF0_2_pre;
typedef struct dungeon_setup_80283BF0_S_80016BF0_2 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
    u8 pad_06[0x4];
    u16 unk_0A;
} dungeon_setup_80283BF0_S_80016BF0_2;
typedef struct dungeon_setup_80283BF0_S_80016BF0_3 {
    u8 pad_00[0x4];
    u16 unk_04;
} dungeon_setup_80283BF0_S_80016BF0_3;
typedef struct dungeon_setup_80283BF0_S_80016BF0_4 {
    u8 pad_00[0x4];
    u16 unk_04;
} dungeon_setup_80283BF0_S_80016BF0_4;
typedef struct dungeon_setup_80283F70_S_80016F70_0 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    s8 unk_03;
    s32 unk_04;
} dungeon_setup_80283F70_S_80016F70_0;
typedef struct dungeon_setup_8028403C_S_8001703C_0 {
    s32 unk_00;
} dungeon_setup_8028403C_S_8001703C_0;
typedef struct dungeon_setup_8028403C_S_8001703C_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x2];
    s32 unk_08;
    s16 unk_0C;
    u8 pad_0E[0x2];
    s32 unk_10;
    s16 unk_14;
    u8 pad_16[0x2];
    s32 unk_18;
    s16 unk_1C;
} dungeon_setup_8028403C_S_8001703C_1;
typedef struct
{
    u8 value[4];
}
dungeon_setup_80284068_UnalignedWord;
typedef struct
{
    u32 words[0x23];
}
dungeon_setup_80284068_Entry;
typedef struct
{
    u8 pad0000[0x244];
    dungeon_setup_80284068_UnalignedWord src;
    u8 pad0248[0x50];
    void *arg;
    u8 pad029C[0x1F48];
    dungeon_setup_80284068_UnalignedWord dest;
}
dungeon_setup_80284068_Cursor;
typedef union
{
    u8 *raw;
    dungeon_setup_80284068_Cursor *entry;
}
dungeon_setup_80284068_CursorPtr;
typedef struct dungeon_setup_802842A0_S_800172A0_2 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} dungeon_setup_802842A0_S_800172A0_2;
typedef struct dungeon_setup_802842A0_S_800172A0_3 {
    void * unk_00;
    u8 pad_04[0x8];
    void * unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[0x8];
    s16 unk_24;
    s16 unk_26;
} dungeon_setup_802842A0_S_800172A0_3;
extern void SetFogFar(s32, s32);
extern void SetLightMatrix(void *);
extern void SetColorMatrix(void *);
extern void SetBackColor(s32, s32, s32);
extern void SetFarColor(s32, s32, s32);
extern void SetGeomOffset(s32, s32);
extern void SetGeomScreen(s32);
extern u8 monster_spawn_records;
extern dungeon_setup_80283000_ColorState upper_draw_context;
extern dungeon_setup_80283000_ColorState lower_draw_context;
extern u8 D_80080AA0[16];
extern u8 generation_cells[16];
extern u8 camera_transition_timer[];
extern void set_continuation_value(void *);
void file_load_com(void *);
s32 load_dungeon_sprite_bundle();
void bzero(void *, s32);
extern s32 D_80012D60;
extern s32 loaded_sprite_bundle_attributes;
extern u8 *sprite_resource_base;
extern M2C_UNK D_80080AE0;
extern M2C_UNK D_80080AE8;
extern M2C_UNK D_80080E18;
extern M2C_UNK D_80080E20;
extern M2C_UNK D_80080E30;
extern M2C_UNK D_80080EE8;
extern s16 floor_generation_state[3];
extern u8 scene_mode_code;
extern s16 pending_marked_actor_count;
extern s8 dungeon_event_pending_flag;
extern s8 D_800DCF58;
extern s8 scripted_boundary_active;
extern DungeonItemPosition dungeon_ground_item_positions[64];
extern s16 pickup_event_latch;
extern s16 bounded_runtime_counter;
extern s32 player_turn_fraction;
extern s8 entity_resource_read_complete;
extern u8 dungeon_resource_buffer[];
extern void clear_floor_resource_state_table(void);
extern s32 rand(void);
extern void mark_category_items_flag_400(s32);
extern void shuffle_enabled_item_category_pointers(void);
extern void request_scene_dispatch_state(s32);
extern void pack_tagged_resource_descriptor(s32, void *, void *, s32);
extern void Control_CD(s32, void *, s32);
extern void drain_cd_command_queue(void);
extern void invalidate_four_sprite_resource_slots(void);
extern s32 D_8001022C;
extern s8 scene_music_hold;
extern s16 current_dungeon_floor;
extern s8 sprite_bundle_loaded;
extern u8 dungeon_button_latch;
extern s32 D_800E3D1C;
extern u8 familiar_record_storage[];
extern void *initialize_scene_object_in_buffer(s32, void *, s32);
extern void register_node(void *, void *);
extern void func_8004491C(void *, void *);
extern void zero_words(void *, s32);
extern s16 select_dungeon_spawn_tile(u8 *, u8 *);
extern s32 test_resident_bit(s32);
extern s32 func_80033BC0(s32);
extern s16 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);
extern void get_offset_map_cell_value_and_flags(u8, u8, s16, u16 *);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void restore_inventory_and_familiars(void *, void *, u8, u8);
extern void texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(void *, u8, s32, s32);
extern s32 get_entity_effect_value(void *, s32);
extern s32 func_80042900(void *, s32);
extern void select_record_entry_and_value(void *, void *, s32);
extern void create_tracked_effect(void *, s32, void *, void *);
extern void restore_player_control_callback(void *, void *);
extern s8 find_active_rect_containing_point(s32, s32, void *, u16);
extern void process_global_buffer_and_submit(void);
extern void *create_pulsing_effect_object(void);
extern s32 dungeon_mode_state;
extern s8 random_pickup_enabled;
extern s8 D_80082A3B;
extern s32 saved_held_item_word;
extern s32 held_item_record;
extern s32 temporary_item_record;
extern void *actor_direction_sprites;
extern u8 D_80089AA0[];
extern u8 D_800DD078;
extern u8 player_attack_followup_frames;
extern u8 D_800DD0A8;
extern s32 equipped_actor_sprite_sources[];
extern s32 unequipped_actor_sprite_sources[];
extern s32 D_800E3D48[];
extern void *actor_default_frames[];
extern u8 player_wait_frames[];
extern u16 camera_pitch_presets[];
extern u16 camera_depth_presets[];
extern u8 dungeon_camera_targets[];
extern s32 dungeon_menu_action_state[];
extern u8 monster_resource_cache_slots[];
extern void restore_actor_stats_from_snapshot(void *object, void *table);
extern s8 get_bounded_stride_index(void *object, void *table, s32 value2, s32 value3);
extern u8 familiar_record_slots[];
s32 rsin();
s32 rcos();
extern void D_800C7B38();
static __inline__ void set_light_vectors(u8 *view_state, s16 x, s16 y);
void initialize_floor_generation_state(void);
void reset_dungeon_runtime_state(void);
void initialize_dungeon_floor_state(void);
void initialize_dungeon_actor(void);
void apply_tile_flags_to_rectangle(s16 start_x, s16 start_y, s16 width, s16 height);
void apply_state_index_tile_masks(void);
void initialize_dungeon_record_kinds(void);
void initialize_dungeon_region_records(void);
void clear_dungeon_state_bytes(void);
void clear_shared_state_values(void);
void init_koh_properties_and_entry_tables(void);
void clear_dungeon_progress_state(void);
void initialize_random_effect_position(struct ObjectPosition *source, s16 base_offset);
#endif
