#ifndef MODULES_TOWN_DOOR_H
#define MODULES_TOWN_DOOR_H

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A0668_arg0.h"
#include "shared/object_flags.h"
#include "shared/runtime_dispatch.h"
#include "shared/sys_flags.h"

typedef struct S_800A0668_1 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A0668_1;

typedef struct S_800A06A4_0 {
    s32 * unk_00;
    u8 pad_04[0x14];
    s32 unk_18;
    s32 * unk_1C;
    u8 pad_20[0x40];
    s32 * unk_60;
    u8 pad_64[0x14];
    s16 unk_78;
    u8 pad_7A[0x4];
    s16 unk_7E;
    u8 pad_80[0x20];
    s16 unk_A0;
    u8 pad_A2[0x2];
    u8 unk_A4;
} S_800A06A4_0;

typedef struct S_func_800A0708_0 {
    u8 pad_00[0x50];
    void (*unk_50)(void *, void *, void *, s32);
    u8 pad_54[0x44];
    s8 *unk_98;
} S_func_800A0708_0;

typedef struct S_func_800A0708_1 {
    u16 unk_00;
} S_func_800A0708_1;

typedef struct {
    u8 pad00[0x50];
    void *unk50;
    u8 pad54[0x68 - 0x54];
    s16 unk68;
    u8 pad6A[0x72 - 0x6A];
    s16 unk72;
} S800A3088Arg0;

typedef struct {
    u8 pad0[2];
    s16 unk2;
    u8 pad4[2];
    s16 unk6;
} S800A3088Arg2;

typedef struct S_800A08F0_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x1A];
    u16 unk_6E;
} S_800A08F0_0;

typedef struct S_800A092C_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x18];
    u16 unk_6C;
} S_800A092C_0;

typedef struct S_800A0958_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x1A];
    u16 unk_6E;
} S_800A0958_0;

typedef struct Node {
    struct Node *next;
    u8 pad_04[0xC];
    s32 field_10;
    u8 pad_14[0xA];
    u16 flags;
} Node;

typedef struct {
    Node *head;
    s32 pad[2];
} ListHead;

typedef struct {
    u8 pad_00[0x48];
    s32 field_48;
} NodeData;

typedef struct {
    s8 pad[0x50];
    void *unk50;
    s8 pad2[0x18];
    s16 unk6C;
} EntityStruct;

typedef struct S_800A0A54_0 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800A0A54_0;

typedef struct S_800A0A88_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x3C];
    s16 unk_90;
} S_800A0A88_0;

typedef struct S_800A0C30_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x1E];
    s16 unk_72;
    u8 pad_74[0x1C];
    s16 unk_90;
} S_800A0C30_0;

typedef struct S_800A0C30_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800A0C30_1;

typedef struct S_800A0CC0_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
} S_800A0CC0_0;

typedef struct S_800A0DAC_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
    u16 unk_6E;
} S_800A0DAC_0;

typedef struct S_800A0E3C_1 {
    u8 pad_00[0x48];
    s32 unk_48;
} S_800A0E3C_1;

typedef struct S_800A0F10_0 {
    u8 pad_00[0x10];
    u16 unk_10;
} S_800A0F10_0;

s32 check_door_status_inverted(void *object);
void initialize_door_variant(void *record_data, s32 initial_value);
void handle_door_check_result(S_func_800A0708_0 *object, void *callback_arg, s32 callback_data);
void install_next_door_handler(void *object, s32 unused_value, s32 update_context, u8 unused_flags);
void emit_door_position_effect(S800A3088Arg0 *entity, s32 action, S800A3088Arg2 *position);
void open_door_to_target(void *object, void *context);
void door_no_op(void);
void advance_door_open_angle(S_800A08F0_0 *door);
void tick_door_open_countdown(S_800A092C_0 *state);
void advance_door_close_angle(S_800A0958_0 *door);
void *find_door_keyed_node(s32 requested_value);
void door_open_demo_set_sub(s32 door_id, s16 demo_angle);
void door_open_demo_set(s32 script_context);
void door_atari_on_off(s32 door_id, s16 collision_enabled);
void into_dn_door_demo_set(void);
void trigger_door_interaction_effect(void *actor, void *target, void *position);
void change_door_map(void *map_source, s32 *map_table);
void advance_door_step(void *entity);
void select_tower_entry_handler_by_item_count(S_800A0C30_0 *script_state, void *unused_context, S_800A0C30_1 *event_params);
void set_door_handler_if_ready(S_800A0CC0_0 *object, s32 value_1, s32 value_2, s32 value_3);
void update_door_completion_state(u8 *object, s32 unused, s32 state_id, s32 state_arg);
void advance_door_state_counter(S_800A0DAC_0 *state, s32 unused, s32 context_a, s32 context_b);
void tick_door_countdown(Rec_func_800A0668_arg0 *object, S_800A0E3C_1 *source, s32 update_arg_a, s32 update_arg_b);
void into_dn_door_jobs(void);
s32 check_door_input_and_angle(Rec_func_800A0668_arg0 *object, s32 test_value);

extern void unlink_node_if_registered(void *);
extern void func_80033D08(void *);
extern s32 classify_object_against_bounds(void *, void *);
extern s32 create_object_with_shared_data(void *input_first, s32 input_second, s32 input_third, u8 input_fourth);
extern void initialize_player_entity_callbacks(s32 entity_id, s32 x, s32 y);
extern void initialize_entity_handlers_and_position(s16 actor_value, s16 position_value_1, s16 position_value_2);
extern s32 change_map();
extern s32 get_player_homerank();
extern s32 find_target_byte_index_in_list();
extern s16 create_objects_descending_by_count();
s32 count_consecutive_nonzero_entries_up_twenty();
void set_player_block_value();
s32 service_script_controller(void);
s32 func_800352FC(void);
s16 initialize_object_items_in_reverse(void *ptr, s32 stateId, s16 currentState);
void no_op_callback_a(void *ptr, s32 stateId, s32 stateArg);
void load_indexed_resource_package(s32 value);
void sound_set_cd_cue_parameters(s32 value0, s32 value1, s32 value2, s32 value3);
void SD_Call(s32 value);
extern void decrease_value_and_advance_counter();
extern void process_terminated_shop_ids(void);
extern void clear_resident_bitmap_bit(s32 a0);
extern void apply_building_pending_updates(void);
extern void dispatch_conditional_table_pairs(void);
s32 get_smallest_signed_overlap_axis_amount_two_intersecting_boxes();

extern s32 D_800D09E0;
extern ListHead active_node_list_head;
extern s32 D_800D4404;
extern u8 door_transition_state[];
extern s32 cd_cue_base[];
extern s16 current_dungeon_floor;
extern s32 scene_object_payload_alias;
extern s32 D_80091260;
extern s32 D_80091528;
extern s32 D_800CFCB4;

#endif
