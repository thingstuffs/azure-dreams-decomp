#ifndef DUNGEON_TOWN_MAP_H
#define DUNGEON_TOWN_MAP_H

struct ObjectNodeHeader;
#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
typedef void (*Callback)(void *);
typedef struct town_map_7FFEE278_S_8008B9D8_0 {
    u8 pad_00[0x68];
    void (*unk_68)(struct Struct_7FFEE2A0 *object, void *position, void *sprite);
} town_map_7FFEE278_S_8008B9D8_0;
struct Struct_7FFEE2A0;
typedef struct town_map_7FFEE2A0_Struct_7FFEE2A0 {
    char pad0[0x64];
    s16 unk64;
    void (*unk68)(void *state, void *position, void *sprite);
    void (*unk6C)(void *state, void *position, void *sprite);
} town_map_7FFEE2A0_Struct_7FFEE2A0;
typedef struct town_map_7FFEE2E4_S_8008BA44_0 {
    void * unk_00;
    u8 pad_04[0x60];
    union { s16 s; s16 u; } town_map_7FFEE2E4_unk_64;   
    s16 unk_66;
    M2C_UNK * unk_68;
    s32 unk_6C;
} town_map_7FFEE2E4_S_8008BA44_0;
typedef struct town_map_7FFEE2E4_S_8008BA44_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} town_map_7FFEE2E4_S_8008BA44_1;
typedef struct town_map_7FFEE2E4_S_8008BA44_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} town_map_7FFEE2E4_S_8008BA44_2;
typedef struct {
    u16 pad0[5];
    u16 unkA;
} town_map_7FFEE36C_SubStruct;
typedef struct {
    town_map_7FFEE36C_SubStruct *sub;
    u8 pad4[96];
    s16 unk64;
    s16 unk66;
    void *unk68;
    void *unk6C;
} town_map_7FFEE36C_MainStruct;
typedef struct town_map_7FFEE3F0_SubStruct {
    u8 pad0[8];
    u16 unk8;
} town_map_7FFEE3F0_SubStruct;
typedef struct town_map_7FFEE3F0_Actor {
    town_map_7FFEE3F0_SubStruct *sub;
    u8 pad4[0x64 - 4];
    s16 unk64;
    s16 unk66;
    void *unk68;
    s32 unk6C;
} town_map_7FFEE3F0_Actor;
typedef struct town_map_7FFEE474_SubStruct {
    u8 pad0[8];
    u16 unk8;
} town_map_7FFEE474_SubStruct;
typedef struct town_map_7FFEE474_MainStruct {
    town_map_7FFEE474_SubStruct *sub;
    u8 pad4[0x60];
    s16 unk64;
    s16 unk66;
    void *unk68;
    s32 unk6c;
} town_map_7FFEE474_MainStruct;
typedef struct town_map_7FFEE4F8_S_8008BC58_0 {
    u8 pad_00[0x64];
    u16 unk_64;
    s16 unk_66;
    void * unk_68;
    u8 pad_6C[0x8];
    s32 unk_74;
    s32 unk_78;
    u8 * unk_7C;
} town_map_7FFEE4F8_S_8008BC58_0;
typedef struct town_map_7FFEE4F8_S_8008BC58_1 {
    u8 pad_00[0x10];
    s32 unk_10;
} town_map_7FFEE4F8_S_8008BC58_1;
typedef struct town_map_7FFEE4F8_S_8008BC58_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} town_map_7FFEE4F8_S_8008BC58_2;
typedef struct town_map_7FFEE4F8_S_8008BC58_3 {
    u8 pad_00[0x30];
    s32 unk_30;
    s32 unk_34;
} town_map_7FFEE4F8_S_8008BC58_3;
typedef struct town_map_7FFEE778_S_8008BED8_0 {
    u8 pad_00[0x68];
    M2C_UNK * unk_68;
} town_map_7FFEE778_S_8008BED8_0;
extern u32 loaded_town_resource_attributes[];
extern s32 town_resource_descriptors[218];
extern s32 town_resource_request[203];
extern void DrawSync(s32 control_value);
extern s32 load_cd_resource(s32 entry_value);
extern s32 func_80047E78(s32 entry_value);
extern void call_script();
extern void func_80035208(s32 value);
extern s8 town_resource_command[12];
extern s32 town_map_resource_ids[];
extern void *runtime_find_unused_pool_slot(void);
extern void runtime_initialize_state_value(void *, s32);
extern void runtime_clear_value(void *);
extern void unlink_active_node(void *);
extern void push_node_onto_free_list(struct ObjectNodeHeader *);
extern s8 town_map_link_slots;
extern u8 town_map_status;
extern void *register_node(void *, void *);
extern void *func_8004491C(void *, void *);
extern void copy_window_params(void *, u32);
extern void func_800375C0(void *, u32);
extern void select_record_entry_and_value(void *state, void *entries, short index);
extern void unlink_node_if_registered(void *);
extern void func_80033D08(void *);
extern u8 town_map_tag;
extern u8 D_80037714;
extern u8 D_800794AC;
extern u32 town_map_selection;
extern u32 D_800CFB74[];
extern u8 D_800CFC38[];
extern u32 D_800CFC44[];
extern s8 town_map_state_ids[];
extern s32 town_map_state_values[];
extern void advance_sprite_animation_and_textures(void *entity);
extern u8 D_80072210[];
extern u8 D_80072214[];
extern u8 town_building_slot_rectangles[];
void process_pending_resource_load(void);
void write_resource_command(s32 value, s32 command);
void send_resource_command_23(s32 entry_index);
s32 town_map_set(s32 value_7c, s32 value_78);
s32 town_map_del(void);
s32 clear_town_map_status(void);
void initialize_town_map_object_state(s32 mode, s32 *list, u8 *init_context, u8 *target_object);
void run_map_object_callback(town_map_7FFEE278_S_8008B9D8_0 *object, void *position, void *sprite);
void advance_town_map_countdown_callback(town_map_7FFEE2A0_Struct_7FFEE2A0 *state, void *position, void *sprite);
void decrease_town_map_object_field_0a_and_transition(town_map_7FFEE2E4_S_8008BA44_0 *state);
void decrease_inner_value_and_load_indexed_state(town_map_7FFEE36C_MainStruct *state);
void advance_inner_value_and_load_indexed_state(town_map_7FFEE3F0_Actor *actor);
void decrease_substructure_value_and_reset(town_map_7FFEE474_MainStruct *object);
void handle_town_map_input(u8 *object, town_map_7FFEE4F8_S_8008BC58_2 *view_params, void *update_context);
void restore_town_map_input_state(town_map_7FFEE778_S_8008BED8_0 *state);
void release_town_map_record(void *record);
#endif
