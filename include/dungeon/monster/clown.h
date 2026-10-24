#ifndef DUNGEON_RESOURCE16_SLOT0_H
#define DUNGEON_RESOURCE16_SLOT0_H
#include "common.h"
#include "dungeon/actor.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "m2c_compat.h"
#include "shared/def_table.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_func_8017360C_arg0.h"
#include "shared/object_flags.h"
#include "records/Rec_func_801732A4_arg0.h"
#include "shared/sprite_frame_state.h"
struct SpriteFrameState;
struct ObjectPosition;

#define NULL 0
typedef struct R16_80170878_S_80170878_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} R16_80170878_S_80170878_0;
typedef struct R16_80170878_S_80170878_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} R16_80170878_S_80170878_1;
typedef struct R16_80170878_S_80170878_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} R16_80170878_S_80170878_2;
typedef struct R16_80170878_S_80170878_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} R16_80170878_S_80170878_4;
typedef void (*R16_80170A58_Callback)(void *, void *, void *, void *);
typedef struct R16_80170A58_S_80170A58_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} R16_80170A58_S_80170A58_2;
typedef struct R16_80171014_S_80171014_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   
} R16_80171014_S_80171014_0;
typedef struct R16_80171014_S_80171014_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0x1E];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} R16_80171014_S_80171014_2;
typedef struct R16_80171574_S_80171FC8_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   
    u8 pad_72[0x16];
    u16 unk_88;
    union { s16 s; u16 u; } unk_8A;   
} R16_80171574_S_80171FC8_0;
typedef struct R16_80171574_S_80171FC8_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} R16_80171574_S_80171FC8_1;
typedef struct R16_80171574_S_80171FC8_2 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R16_80171574_S_80171FC8_2;
typedef struct R16_80171574_S_80171FC8_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x2];
    u16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
} R16_80171574_S_80171FC8_3;
typedef struct R16_80171574_S_80171FC8_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R16_80171574_S_80171FC8_4;
typedef struct R16_80171784_S_80171C34_1 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x1];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { s16 s; u16 u; } unk_2A;   
    u8 pad_2C[0x19];
    u8 unk_45;
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   
    u8 pad_6E[0x3];
    union { s8 s; u8 u; } unk_71;   
    u8 pad_72[0x16];
    union { u16 u; s16 s; } unk_88;   
} R16_80171784_S_80171C34_1;
typedef struct R16_80171784_S_80171C34_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   
    union { s8 s; u8 u; } unk_26;   
} R16_80171784_S_80171C34_2;
typedef struct R16_80171784_S_80171C34_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R16_80171784_S_80171C34_3_pre;
typedef struct R16_80171784_S_80171C34_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} R16_80171784_S_80171C34_3;
typedef struct R16_80171784_S_80171C34_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   
} R16_80171784_S_80171C34_5;
typedef struct R16_80171784_S_80171C34_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R16_80171784_S_80171C34_7;
typedef struct R16_80171784_S_80171C34_8 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R16_80171784_S_80171C34_8;
typedef struct R16_80171784_DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} R16_80171784_DungeonRecord;
typedef struct R16_80171ECC_S_80171ECC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R16_80171ECC_S_80171ECC_1;
typedef struct R16_801721B4_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} R16_801721B4_S_80172628_0;
typedef struct {
    u8 pad0[0x8C];
    void (*callback)(void *, void *, void *, void *);
} Resource16CallbackState;
typedef struct R16_801723F0_S_801723F0_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} R16_801723F0_S_801723F0_0;
typedef struct R16_801723F0_S_801723F0_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R16_801723F0_S_801723F0_3;
typedef struct R16_801725A4_S_801725A4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} R16_801725A4_S_801725A4_0;
typedef struct R16_801725A4_S_801725A4_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   
    union { u8 s; s8 u; } unk_73;   
} R16_801725A4_S_801725A4_1;

typedef struct R16_801725A4_S_801725A4_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R16_801725A4_S_801725A4_3;
typedef struct R16_801729D8_S_80173294_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; s16 p; } timer;   
    u8 pad_98[0x3];
    u8 phase;
} R16_801729D8_S_80173294_0;
typedef struct R16_80172CCC_S_80173588_0 {
    u8 pad_00[0xA2];
    s16 unk_A2;
} R16_80172CCC_S_80173588_0;
typedef struct R16_80172D50_S_80173E50_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} R16_80172D50_S_80173E50_0;
typedef struct {
    s8 pad_00[0x8C];
    void *unk_8C;
} R16_80173468_Actor;
typedef struct {
    u8 pad_00[0x2C];
    u8 *unk_2C;
} R16_80173468_Entity;
typedef struct {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} R16_80173468_MapObject;
typedef struct R16_801736AC_Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct R16_801736AC_Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} R16_801736AC_Entry;
typedef struct {
    u8 pad[0x13C];
    s32 value;
} R16_801736AC_Scratchpad;
typedef struct {
    u8 pad[0x5218];
    s16 value;
} R16_801736AC_GlobalPage;
typedef struct R16_80173738_S_80173738_0_pre {
    u16 unk_00;
} R16_80173738_S_80173738_0_pre;
typedef struct R16_80173738_S_80173738_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x2];
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x1E];
    s32 unk_40;
    s32 unk_44;
} R16_80173738_S_80173738_0;
typedef struct R16_80173738_S_80173738_2 {
    s32 unk_00;
} R16_80173738_S_80173738_2;
typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
} R16_80173738_FuncArg1;
typedef struct R16_80173904_S_80173904_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x2];
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0x1E];
    s32 unk_40;
    s32 unk_44;
} R16_80173904_S_80173904_0;
typedef struct R16_80173904_S_80173904_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} R16_80173904_S_80173904_1;
typedef struct R16_80173904_S_80173904_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} R16_80173904_S_80173904_2;
typedef struct R16_80173904_S_80173904_3 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} R16_80173904_S_80173904_3;
typedef struct R16_80173904_S_80173904_4 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} R16_80173904_S_80173904_4;
typedef struct {
    u8 pad0[2];
    u16 flags;
    u8 pad4[6];
    u16 count;
} R16_80173AE8_DungeonState;
typedef struct R16_80173CEC_S_80173CEC_11 {
    u8 pad_00[0x8];
    void * unk_08;
} R16_80173CEC_S_80173CEC_11;
typedef struct R16_80173CEC_S_80173CEC_12 {
    s32 unk_00;
    s32 unk_04;
} R16_80173CEC_S_80173CEC_12;
typedef struct R16_80173CEC_S_80173CEC_2 {
    u8 unk_00;
} R16_80173CEC_S_80173CEC_2;
typedef struct R16_80173CEC_S_80173CEC_3 {
    u8 pad_00[0xA8];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} R16_80173CEC_S_80173CEC_3;
typedef struct R16_80173CEC_S_80173CEC_4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} R16_80173CEC_S_80173CEC_4;
typedef struct R16_80173CEC_S_80173CEC_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} R16_80173CEC_S_80173CEC_5;
typedef struct R16_80173CEC_S_80173CEC_8 {
    u8 pad_00[0x8];
    s32 unk_08;
} R16_80173CEC_S_80173CEC_8;
typedef struct R16_80173CEC_S_80173CEC_9 {
    u8 pad_00[0xC];
    union { s32 s; void * u; } unk_0C;   
    s32 unk_10;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} R16_80173CEC_S_80173CEC_9;
extern s32 abs(s32);
extern s32 rand(void);
s32 Control_CD();
s32 allocate_list_node();
s32 func_8003FD64();
s32 register_node();
s32 func_8004491C();
s32 set_or_clear_actor_status_slot();
s32 generate_random_value();
void initialize_actor_sprite_and_animation();
s32 try_move_actor_to_valid_position();
void select_indirect_table_entry();
s32 advance_sprite_animation_and_textures();
s32 rsin();
void apply_monster_koyaw_data();
s32 refresh_actor_facing_and_lifecycle();
s16 sample_terrain_surface_height();
s32 select_sprite_entry();
s32 func_80047784();
s32 check_entity_relation();
s32 find_active_rect_containing_point();
s32 test_neighbor_position_relation();
s32 get_rounded_facing_and_rounding_flag();
s32 can_entity_gain_level();
void update_actor_status_and_mp();
void begin_pushed_actor_move();
s32 begin_ready_actor_directional_action();
s32 advance_actor_pending_action();
void begin_actor_move_to_target_facing();
s32 reset_actor_action_state();
s32 process_selected_actor_record();
void begin_actor_spell_action();
s32 cycle_map_cell_flags();
s32 update_map_cell_flags_with_item_limit();
s32 update_actor_proximity_flag();
s32 find_adjacent_actor();
s32 probe_directional_neighbor();
s32 get_actor_height_difference();
s32 check_diagonal_side_height();
s32 select_actor_route_target();
s32 check_directional_move_and_terrain();
s32 prepare_directional_attack();
s32 try_claim_dungeon_action_slot();
u32 check_entity_interaction_compatibility();
s32 apply_camera_offset_and_select_target();
s32 has_pending_dungeon_activity();
s32 relink_entity_and_clear_high_flag();
s32 advance_status_timers();
s32 update_actor_movement_to_tile();
s32 spend_actor_mp();

s32 update_linked_actor_motion();
s32 resolve_attack_damage_and_effects();
s32 play_sound_if_enabled();
s32 get_cd_command_queue_depth();
s32 scan_actor_along_heading();
void set_record_integer_tile_center();
s32 create_actor_spell_effect();
void create_actor_linked_effect();
void begin_actor_display_action();
void apply_clamped_actor_value_delta();
s32 update_actor_defeat_removal();
s32 update_actor_hop_and_shrink();

s32 update_actor_hop_and_grow();
s32 get_entity_effect_value();
s32 func_80042900();
void clear_slots_of_type();
void func_80042B68();
s32 get_tile_chebyshev_distance();
s32 has_pending_actor_or_turn_action();
void on_actor_status_updated();
void func_800A9A04();
s32 create_randomized_motion_object();
s32 update_actor_transform_from_parent();
s32 update_thrown_actor_travel();
s32 interpolate_actor_to_terrain_tile();
s32 update_spinning_actor_fall();
s32 propagate_actor_action_flag();
s32 update_actor_fade_in();
s32 resolve_actor_floor_trap_once();
void project_sprite_commands();
void func_800453E0();
s32 select_record_entry_and_value();
s32 rcos();
void unlink_node();
void func_80044A50();
void sound_set_cd_cue_parameters();
void run_cd_image_commands();
void func_80041588();
int read_stream_cue_start_offset();
s32 lookup_masked_byte_table();
s32 rand();
void unlink_entity_node();
void decrement_monster_entry_count();
s32 advance_staged_entity_load();
s32 create_status_linked_render_effect();
s32 select_nearby_target_and_initialize_slot(s32 slot_id,struct ObjectPosition *target, s32 target_id, s32 slot_value);
extern u8 clown_direction_frames[];
extern u8 clown_alt_direction_frames[];
extern u8 D_8017426C[];
extern u8 D_8017421C[];
extern u8 D_8017424C[];
extern u8 D_80174254[];
extern u8 actor_turn_angle_offsets[];
extern u8 D_80174214[];
extern u8 clown_frame_set[];
extern u8 D_80174244[];
extern u8 clown_frame_set_1[];
extern u8 clown_fade_count[];
extern u8 shared_sprite_entries[];
extern u8 actor_action_reset_value[];
extern u8 D_801742E8[];
extern u8 resource_completion_callback_address[];
extern u8 cd_cue_base[];
extern u8 actor_effect_color_targets[];
extern u8 staged_spawn_count[];
extern u8 dungeon_resource_buffer[];
extern u8 D_801742CC[];
extern u8 D_801742D4[];
extern u8 clown_image_load_done[];
extern u8 clown_effect_load_done[];
void *spawn_clown_actor(s16 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c);
void update_entity_facing_and_ground(void *entity, struct ObjectPosition *motion, struct SpriteFrameState *sprite);
void update_actor_state_and_dispatch_transition(void *actor, void *actor_context, struct SpriteFrameState *map_object, ActorRecord *creature);
void advance_actor_path_step_and_update_counters(void *motion_state, s32 unused, struct SpriteFrameState *entity, void *path_state);
void choose_clown_move(void *move_data, void *context, void *position_data, void *actor_data);
s32 initialize_transition_action(void *action_state, s32 action_id, void *source_obj, ActorRecord *actor);
void begin_eligible_actor_action(Rec_func_800A9E70_arg0 *action_state, s32 context, struct SpriteFrameState *animation, ActorRecord *actor);
s32 relink_clown_path(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void finish_actor_tile_move_then_dispatch_transition(void *state, s32 unused, s32 source, s32 target);
void finish_linked_actor_motion_and_floor_trap_then_dispatch_transition(Resource16CallbackState *state, void *entity, void *position, void *graphic);

void update_overlay_object_action(void *owner, void *motion, struct SpriteFrameState *actor, void *object_in);
void damp_actor_motion_then_recenter(R16_801729D8_S_80173294_0 *motion_state, ObjectPosition *motion, SpriteFrameState *tile_state, void *entity);
void remove_defeated_clown(void *state, void *motion, void *position, void *actor);
void shrink_hopping_clown(R16_80172CCC_S_80173588_0 *state, void *context, SpriteFrameState *data, void *render);
void advance_clown_removal(void *state, void *motion, void *position, void *actor);
void finish_actor_hop_and_grow_then_dispatch_transition(Resource16CallbackState *state, void *motion, void *position, void *actor);
void advance_clown_status_action(void *actor, void *context, struct SpriteFrameState *render_record, ActorRecord *actor_state);
void advance_clown_mp_action(void *actor, void *context, struct SpriteFrameState *animation, ActorRecord *entity);
void update_clown_parent_motion(R16_80173468_Actor *actor, s32 action, struct SpriteFrameState *entity, R16_80173468_MapObject *map_object);
void finish_thrown_actor_travel_and_floor_trap_then_dispatch_transition(Resource16CallbackState *state, void *entity, void *position, void *graphic);
void finish_actor_terrain_interpolation_then_dispatch_transition(Resource16CallbackState *state, void *motion, void *position, void *actor);
void finish_spinning_actor_fall_then_dispatch_transition(Resource16CallbackState *state, void *motion, void *position, void *actor);
void finish_actor_action_flag_propagation_then_dispatch_transition(Resource16CallbackState *state, void *motion, void *position, void *actor);
void finish_actor_fade_in_then_dispatch_transition(Resource16CallbackState *state, void *motion, void *position, void *actor);
void finish_actor_floor_trap_then_dispatch_transition(Resource16CallbackState *state, void *motion, void *position, void *actor);
s32 project_clown_sprite_chain(void *initial_payload, s32 entry_data, R16_801736AC_Entry *entry, s32 unused);
void update_expanding_spiral_effect(void *effect, R16_80173738_FuncArg1 *position, struct SpriteFrameState *primitive);
void create_angled_source_effect(
    s32 unused_0, R16_80173904_S_80173904_3 *origin, s32 unused_2, s32 unused_3, s16 angle, u16 depth_offset);
void wait_for_clown_action_slot(void *entity_data, s32 unused_1, s32 unused_2, void *other_data);
void fade_entity_colors_to_neutral(void *entity_data, void *unused, void *source_data);
void advance_actor_effect_sequence(Rec_func_801732A4_arg0 *state, EntityRec *position, struct SpriteFrameState *actor, void *model);


void finish_actor_action_animation(void *action, void *motion, SpriteFrameState *anim, ActorRecord *actor);

#endif
