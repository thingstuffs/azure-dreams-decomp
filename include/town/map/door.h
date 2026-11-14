#ifndef MODULES_TOWN_DOOR_H
#define MODULES_TOWN_DOOR_H
#include "engine/scene.h"
#include "town/scene/collision.h"
#include "town/menu/motion.h"
#include "town/map/object_setup.h"
#include "shared/sprite_frame_state.h"

struct S_800A092C_0;
struct S_800A0958_0;
struct S_800A0C30_0;
struct S_800A0C30_1;
struct S_800A0E3C_1;

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A0668_arg0.h"
#include "shared/object_flags.h"
#include "shared/runtime_dispatch.h"
#include "shared/sys_flags.h"
#include "town/shop.h"
#include "shared/town_object.h"
#include "shared/entity.h"
struct InputRecord;

typedef struct S_800A0668_1 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A0668_1;

typedef struct S_800A06A4_0 {
    s32 * unk_00;
    u8 pad_04[0x14];
    void *position;
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
    void (*unk_50)(struct S_800A092C_0 *);
    u8 pad_54[0x1A];
    u16 unk_6E;
} S_800A08F0_0;

typedef struct S_800A092C_0 {
    u8 pad_00[0x50];
    void (*unk_50)(struct S_800A0958_0 *);
    u8 pad_54[0x18];
    u16 unk_6C;
} S_800A092C_0;

typedef struct S_800A0958_0 {
    u8 pad_00[0x50];
    void (*unk_50)(S800A3088Arg0 *, void *, S800A3088Arg2 *);
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
    void (*unk_50)(u8 *, s32,  s32,  s32);
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
    void (*unk_50)(struct S_800A0C30_0 *, void *, struct S_800A0C30_1 *);
} S_800A0CC0_0;

typedef struct S_800A0DAC_0 {
    u8 pad_00[0x50];
    void (*unk_50)(Rec_func_800A0668_arg0 *, struct S_800A0E3C_1 *, s32,  s32);
    u8 pad_54[0x18];
    s16 unk_6C;
    u16 unk_6E;
} S_800A0DAC_0;

typedef struct S_800A0E3C_1 {
    u8 pad_00[0x48];
    s32 unk_48;
} S_800A0E3C_1;


s32 check_door_status_inverted(void *object);

void update_door_object(S_func_800A0708_0 *object, void *callback_arg, s32 callback_data);
void create_door_shared_object(TownObjectRecord *object, TownObjectRecord *unused_context, void *update_context, SpriteFrameState *unused_data);
void check_door_entry_and_open(S800A3088Arg0 *entity, void *action, S800A3088Arg2 *position);
void open_door_to_target(TownObjectRecord *object, void *context);
void door_no_op(void);
void advance_door_open_angle(S_800A08F0_0 *door);
void tick_door_open_countdown(S_800A092C_0 *state);
void advance_door_close_angle(S_800A0958_0 *door);
void *find_door_keyed_node(s32 requested_value);
void door_open_demo_set_sub(s32 door_id, s16 demo_angle);
void door_open_demo_set(s32 script_context);
void door_atari_on_off(s32 door_id, s16 collision_enabled);
void into_dn_door_demo_set(void);
void check_door_entry_and_change_map(void *actor, void *target, void *position);
void change_door_map(void *map_source, s32 *map_table);
void create_door_transition_objects(void *entity, TownObjectRecord *unused_context, void *update_context, SpriteFrameState *unused_data);
void start_door_entry_or_wait(S_800A0C30_0 *script_state, void *unused_context, S_800A0C30_1 *event_params);
void resume_door_entry_when_script_idle(S_800A0CC0_0 *object, s32 value_1, s32 value_2, s32 value_3);
void start_door_transition_effect(u8 *object, s32 unused, s32 state_id, s32 state_arg);
void update_door_transition_spin(S_800A0DAC_0 *state, s32 unused, s32 context_a, s32 context_b);
void tick_door_countdown(Rec_func_800A0668_arg0 *object, S_800A0E3C_1 *source, s32 update_arg_a, s32 update_arg_b);
void into_dn_door_jobs(void);
s32 check_door_input_and_angle(Rec_func_800A0668_arg0 *object, void *test_value);

extern void unlink_node_if_registered(void *);
extern void func_80033D08(void *);
extern s32 classify_object_against_bounds(void *, void *);
extern void * create_default_display_object(void *input_first, s32 input_second, s32 input_third, u8 input_fourth); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void initialize_player_entity_callbacks(s32 entity_id, s32 x, s32 y);
extern void change_map(struct InputRecord *input);
extern s32 create_display_object_series(s32 object_key, s32 payload_value, s32 payload_param, s32 count);
s32 count_used_item_slots(void);
void set_player_block_value(s32 value);
s32 func_800352FC(void);
s16 initialize_object_items_in_reverse(void *ptr, s32 stateId, s16 currentState);
void no_op_callback_a(void *unused_ptr, s32 unused_state_id, s32 unused_state_arg); /* Unprototyped: retail call passes more arguments than the callee reads */
void sound_set_cd_cue_parameters(s32 value0, s32 value1, s32 value2, s32 value3);
void SD_Call(s32 value);
extern void clear_resident_bit_patterns(void);
extern void clear_resident_bitmap_bit(s32 a0);
extern void apply_building_pending_updates(void);
extern void sync_resident_flag_pairs(void);

extern s32 D_800D09E0;
extern ListHead active_node_list_head;
extern s32 D_800D4404;
extern Rec_D_80100B70 door_transition_state;
extern s32 cd_cue_base[];
extern s16 current_dungeon_floor;
extern s32 scene_object_payload_alias;


extern ColliderView town_actor_control;

#endif
