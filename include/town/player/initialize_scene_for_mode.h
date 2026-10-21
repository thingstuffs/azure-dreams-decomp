#ifndef MODULES_TOWN_PLAYER_INIT_H
#define MODULES_TOWN_PLAYER_INIT_H

#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/object_node.h"
#include "shared/position_query.h"
#include "shared/tile_object.h"

typedef struct func_80092868_ScenePos {
    s16 pad0;
    u16 x;
    s16 pad4;
    u16 y;
    s16 pad8;
    s16 angle;
} func_80092868_ScenePos;

typedef struct func_80092868_RenderState {
    u8 pad0[0xC];
    s32 color;
    u8 pad10[0xC];
    s16 scale0;
    s16 scale1;
    u8 pad20[8];
    s32 source;
} func_80092868_RenderState;

typedef struct func_80092868_TownState {
    u8 pad0[0xC];
    u16 frame;
    s16 alternate;
    u16 *coords;
    u16 x_offset;
    u16 y_offset;
    s32 mode;
} func_80092868_TownState;

typedef struct func_80092868_TownObject {
    void *next;
    void *prev;
    func_80092868_ScenePos *scene;
    func_80092868_RenderState *render;
    void *callback;
} func_80092868_TownObject;

typedef struct func_80092868_TownWork {
    u8 pad0[0x10];
    u16 frame0;
    s16 field12;
    u8 pad14[2];
    s16 active;
    u16 frame1;
} func_80092868_TownWork;

typedef struct func_80092AB0_S_80090210_0 {
    s32 unk_00;
    u8 pad_04[0x10];
    s32 * unk_14;
    u8 pad_18[0x2];
    s16 unk_1A;
    u8 pad_1C[0xA];
    s16 unk_26;
} func_80092AB0_S_80090210_0;

typedef struct func_80092AB0_S_80090210_1 {
    u8 pad_00[0x28];
    s32 unk_28;
} func_80092AB0_S_80090210_1;

typedef struct func_80092AB0_S_80090210_2 {
    u8 pad_00[0x438];
    union { s32 (*s)(); s32 u; } unk_438;                         
} func_80092AB0_S_80090210_2;

typedef struct func_80092C18_S_80090378_0 {
    s32 unk_00;
} func_80092C18_S_80090378_0;

typedef void (*func_80092C9C_ObjectCallback)(void *, s32, s32);

typedef void (*func_80092C9C_ActorCallback)(void *, void *, s32);

typedef struct func_80092C9C_S_800903FC_1 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0x2];
    u16 unk_16;
} func_80092C9C_S_800903FC_1;

typedef struct func_80092C9C_S_800903FC_2 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x17];
    u8 unk_3B;
} func_80092C9C_S_800903FC_2;

typedef struct func_80092C9C_S_800903FC_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} func_80092C9C_S_800903FC_3;

typedef struct func_80092C9C_S_800903FC_4 {
    u8 pad_00[0x8];
    void * unk_08;
} func_80092C9C_S_800903FC_4;

void initialize_scene_for_mode(void);
void synchronize_mode_and_pending_callback(void);
void initialize_global_scene_record(void);
void plt_init_sleep_set(void);
void initialize_scene_render_state(void);
void initialize_scene_render_object(void);
void rebuild_menu_node_list(void *owner, ObjectPosition *node_in, s32 mode);
void process_scene_record_update(void *context, void *input, void *record);
s32 func_800909A0();
void clear_record_state_or_update(void *record);
void func_80090A64(void);
void no_op_scene_callback_b(void);

extern void clear_resident_bitmap_bit(s32 flag_id);
extern s32 test_resident_bitmap_bit(s32 bit_id);
extern void zero_words(void *ptr, s32 count);
extern func_80092868_TownObject *initialize_scene_object_in_buffer(s32 flags, void *storage, s16 size);
extern void register_node(func_80092868_TownObject *object, void *data);
extern void func_8004491C(func_80092868_TownObject *object, void *data);
extern void initialize_circular_list_head(void);
extern void handle_insert_initialize_two_values_status_flags(void *node, func_80092868_ScenePos *scene, void *value_0c);
extern void initialize_pointer_table_self_links(void);
extern void initialize_the_store_two_values_set_state_flags(void *record, func_80092868_ScenePos *scene, void *value_0c);
extern void initialize_six_global_pointers_corresponding_storage_blocks(void);
extern void run_the_three_update_routines_context(void *owner);
extern s32 find_item_by_kind_and_type(s32 first_value, s32 second_value);
extern void copy_entity_record_fields(void *, void *);
extern void create_person_object(void);
extern void initialize_object_at_current_position(void);
extern s16 query_lowered_transform_position(func_80092868_ScenePos *scene);
void set_resident_bitmap_bit();
s32 load_town_sprite_bundle();
s32 load_alternate_town_sprite_bundle();
void call_the_handler_selects_nonzero_entry();
extern void initialize_record_and_select_active_data(void *owner, void *node_in, s32 mode);
void initialize_record_with_handler_table();
void initialize_player_object();
extern s32 service_script_controller(void);
extern s32 func_800352FC(void);
extern void submit_object_resource_data(void *owner);
extern s32 read_map_cell_at_world_position(s16 owner, s16 node_in);
extern void handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(void *owner, void *node_in);
extern void add_motion_deltas_to_position(void *owner);
extern void apply_the_enabled_movement_offsets_adding_z_offset_only_positive(void *owner);
extern void store_position_and_compute_delta(void *owner);
extern void update_the_s_field_10_using_callee_8008_fe_90(void *owner);
extern s32 get_whether_has_attached_state_type_n_1_n_3(void *owner);
extern s16 select_the_smaller_position_query_result_capped_n_64_writes_associated(void *owner, void *node_in);
extern void compute_and_clamps_vector_based_adjustment_updates_town(void *owner, s16 node_in, void *mode);
extern void update_object_and_clear_status_fields(void *owner);
extern void turn_entity_toward_target(void *owner, void *node_in, s32 mode);
extern s32 check_masked_value_in_current_range(u16 owner);
extern s32 runtime_estimate_vector_length(s32, s32);
extern void texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(void *, u8, s8, s32);
extern void step_actor_animation(void *, s32);
extern void func_80048AC8(void *, s32);
extern s16 step_angle_12_toward(s16, s16, s32);
extern s32 view_relative_angle_sector(s16);
extern void clear_motion_along_blocked_directions_update_affected_axes(void *);
extern void dispatch_to_matching_fallback_handler_using_sentinel_terminated_key_lists(void *, void *, void *);

extern func_80092868_TownState D_8006ADBC;
extern s16 D_8006ADD4[];
extern s32 D_80080A80;
extern u8 D_8008FFC0[];
extern u8 D_800970FC[];
extern u8 D_800CFCB4[];
extern u8 D_800D0420[];
extern u8 D_800FE490[];
extern u8 D_80100D98[];
extern s32 D_80100DB0[];
extern s32 D_80100E18[];
extern s32 D_800834B8;
extern s32 D_80097D54;
extern u8 D_800D0078[];
extern s32 D_800D0438;
extern s32 D_800D0178;
extern u8 D_80082BC0[];
extern s32 D_80097D2C[3];
extern u8 D_800A5638[];
extern s32 D_80091260;
extern s32 D_80091528;
extern s16 D_800D01F8[];

#endif
