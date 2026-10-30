#ifndef DUNGEON_RESOURCE08_SLOT0_H
#define DUNGEON_RESOURCE08_SLOT0_H
#include "common.h"
#include "dungeon/actor.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "m2c_compat.h"
#include "shared/def_table.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_func_801736F4_arg0.h"
#include "shared/object_flags.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "dungeon/system.h"
#include "engine/texture.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/state.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/status.h"
struct SpriteFrameState;
struct ObjectPosition;

#define NULL 0
typedef s32 R08_8017087C_M2C_UNK;




typedef void (*R08_80170A50_EntityCallback)(void *, void *, void *, void *);
typedef struct R08_80170A50_S_80170A28_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} R08_80170A50_S_80170A28_0;
typedef struct R08_80170A50_S_80170A28_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} R08_80170A50_S_80170A28_1;
typedef struct R08_80170A50_S_80170A28_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R08_80170A50_S_80170A28_2;
typedef struct R08_80170E7C_S_80170E7C_7 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    void * unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} R08_80170E7C_S_80170E7C_7;
typedef struct R08_80170E7C_S_80170E7C_8 {
    u8 pad_00[0x4];
    s32 unk_04;
} R08_80170E7C_S_80170E7C_8;
typedef struct R08_801715B4_S_80171570_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   
    u8 pad_72[0x18];
    s16 unk_8A;
} R08_801715B4_S_80171570_0;
typedef struct R08_801715B4_S_80171570_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} R08_801715B4_S_80171570_2;
typedef struct R08_801715B4_S_80171570_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R08_801715B4_S_80171570_3;

typedef struct R08_80172280_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} R08_80172280_S_80172628_0;
typedef struct R08_8017245C_S_80172478_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    union { s16 s; u16 u; } unk_A8;   
} R08_8017245C_S_80172478_0;
typedef struct R08_8017245C_S_80172478_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} R08_8017245C_S_80172478_2;

typedef struct R08_80172830_S_80172830_0 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x2];
    u16 timer;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 phase;
} R08_80172830_S_80172830_0;
typedef struct R08_80172CE8_S_80172CE8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} R08_80172CE8_S_80172CE8_0;
typedef struct R08_80172CE8_S_80172CE8_1_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} R08_80172CE8_S_80172CE8_1_pre;
typedef struct R08_80172CE8_S_80172CE8_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R08_80172CE8_S_80172CE8_2;
typedef struct R08_80172CE8_S_80172CE8_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} R08_80172CE8_S_80172CE8_3;
typedef struct R08_80173234_S_80173234_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } timer;   
    u8 pad_98[0x3];
    u8 phase;
} R08_80173234_S_80173234_0;
typedef struct R08_80173234_S_80173234_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R08_80173234_S_80173234_1;



typedef struct R08_801740F4_Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct R08_801740F4_Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} R08_801740F4_Entry;
typedef struct {
    u8 pad[0x13C];
    s32 value;
} R08_801740F4_Scratchpad;

typedef struct {
    u8 pad[0x1A];
    u16 field_1A;
    u16 field_1C;
    u16 field_1E;
} R08_80174180_Object;
typedef struct R08_801741D0_S_801741D0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s8 unk_20;
} R08_801741D0_S_801741D0_0;
typedef struct R08_801741D0_S_801741D0_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} R08_801741D0_S_801741D0_1;
typedef struct R08_801741D0_S_801741D0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} R08_801741D0_S_801741D0_2;
typedef struct R08_801741D0_S_801741D0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} R08_801741D0_S_801741D0_3;
typedef struct {
    u32 words[3];
} R08_801741D0_Packed12 __attribute__((packed));
typedef struct R08_801743BC_S_801743BC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x26];
    s16 unk_3A;
} R08_801743BC_S_801743BC_0;


typedef struct R08_80174648_S_80174648_0_pre {
    u16 unk_00;
} R08_80174648_S_80174648_0_pre;
typedef struct R08_80174648_S_80174648_0 {
    u8 pad_00[0x96];
    union { s16 s; u16 u; } timer;   
    u8 pad_98[0x3];
    u8 phase;
    u8 pad_9C[0x10];
    void * unk_AC;
    s16 unk_B0;
} R08_80174648_S_80174648_0;
typedef struct R08_80174648_S_80174648_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    union { u16 u; s16 s; } unk_2A;   
    u8 pad_2C[0x34];
    union { void * p; s32 i; } unk_60;   
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} R08_80174648_S_80174648_1;
typedef struct R08_80174648_S_80174648_2 {
    u8 pad_00[0x8];
    s32 * unk_08;
    union { void * p; s32 i; } unk_0C;   
    union { void * p; s32 i; } unk_10;   
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x88];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} R08_80174648_S_80174648_2;
typedef struct R08_80174648_S_80174648_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} R08_80174648_S_80174648_3;
typedef struct R08_80174648_S_80174648_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R08_80174648_S_80174648_6_pre;
typedef struct R08_80174648_S_80174648_6 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} R08_80174648_S_80174648_6;
typedef struct R08_80174648_S_80174648_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} R08_80174648_S_80174648_7;

typedef struct R08_80174648_S_80174648_9 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} R08_80174648_S_80174648_9;
typedef struct R08_80174648_S_80174648_10 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} R08_80174648_S_80174648_10;
typedef struct R08_80174648_S_80174648_11 {
    u8 unk_00;
} R08_80174648_S_80174648_11;
extern int abs(int);
extern s32 Control_CD();
void * func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
s32 register_node(ObjectNodeHeader *entry, void *registration_id);
s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
s32 generate_random_value(void);
s16 set_or_clear_actor_status_slot(ActorRecord *owner, s8 id, s8 value);
void initialize_actor_sprite_and_animation(void *entity, void *position, SpriteFrameState *sprite, s32 init_flags);
void advance_sprite_animation_and_textures(void *entity);
s32 refresh_actor_facing_and_lifecycle();
s16 sample_terrain_surface_height();
s32 resolve_record_orientation_or_fallback();
void select_sprite_entry();
void func_80047784(void *object_data, s16 table_index, s16 entry_index);
s32 check_entity_relation();
s32 find_active_rect_containing_point(s32 point_x, s32 point_y);
s32 can_entity_gain_level(void *entity);
void update_actor_status_and_mp(ActorRecord *entity);
void begin_pushed_actor_move(void *state_in, void *unused, void *position_in, void *actor_in);
s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
s32 reset_actor_action_state(void *actor, void *unused, SpriteFrameState *sprite, u8 *direction_frames);
void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
s32 check_movement_clearance_and_height();
s32 update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
s16 get_actor_height_difference(ActorRecord *left_record, ActorRecord *right_record);
s16 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
s32 prepare_directional_attack();
s16 try_claim_dungeon_action_slot(ActorRecord *actor);
u32 check_entity_interaction_compatibility();
s32 apply_camera_offset_and_select_target(void *object_addr, void *source_pos, s32 helper_arg, s32 slot_value);
#include "dungeon/player/object/action_state.h"
struct Entry;
struct ObjectNodeHeader;
struct ObjectNodeHeader;
s32 relink_entity_and_clear_high_flag();
s32 update_actor_movement_to_tile(void *move_state, void *motion, void *target_tile, ActorRecord *actor);
void spend_actor_mp(ActorRecord *entity, s32 base_reduction);

void func_800A9A04(void *actor);
s32 update_linked_actor_motion(void *state, void *transform, void *config, void *object);
void * resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
s32 get_cd_command_queue_depth(void);
void create_two_row_object_group(void *payload, s16 value_scale);
s32 update_actor_hop_and_shrink(void *animation, void *motion, SpriteFrameState *scale, void *render);

s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
s32 func_80042900(ActorRecord *entry, s32 effect_id);
void clear_slots_of_type(ActorRecord *owner, s8 match_type);
void func_80042B68(ActorRecord *owner, s8 match_type);
s32 get_tile_chebyshev_distance();

s32 update_actor_transform_from_parent();
s32 interpolate_actor_to_terrain_tile();
s32 update_spinning_actor_fall();
s32 update_actor_fade_in();
void project_sprite_commands(void *context, void *position, struct Entry *entry, s16 depth_bias);
void func_800453E0(void *context, void *position, struct Entry *entry, s16 depth_bias);
void unlink_node();
void func_80044A50(struct ObjectNodeHeader *node);
void select_record_entry_and_value(void *state, void *entries, short index);
void sound_set_cd_cue_parameters(int value_0, int value_1, int value_2, int value_3);
void run_cd_image_commands(u32 *stream_ref, u8 *state, s32 execute);
void func_80041588(u32 *stream_ref, u8 *state, s32 execute);
s32 read_stream_cue_start_offset(void);
s32 lookup_masked_byte_table();
void unlink_entity_node();
void decrement_monster_entry_count(s16 requested_id, s16 requested_type);
s32 create_status_linked_render_effect();
s32 select_nearby_target_and_initialize_slot(void * slot_id,void *target, s32 target_id, s32 slot_value);
s32 propagate_actor_action_flag(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern u8 griffon_direction_frames[];
extern u8 griffon_frame_set_3[];
extern u8 griffon_behavior_handlers[];
extern u8 griffon_object_callback[];
extern u8 secondary_sprite[];
extern u8 griffon_frame_set_4[];
extern u8 griffon_frame_set_6[];
extern u8 griffon_frame_set_1[];
extern u8 griffon_move_direction_frames[];
extern u8 actor_turn_angle_offsets[];
extern u8 D_80174C4C[];
extern u8 D_80174C54[];
extern u8 griffon_frame_set[];
extern u8 actor_update_node_cursor[];
extern u8 griffon_frame_set_5[];
extern u8 griffon_frame_set_2[];
extern u8 griffon_frame_set_14[];
extern u8 griffon_frame_set_13[];
extern u8 D_80174D14[];
extern u8 D_80174D08[];
extern u8 actor_action_reset_value[];
extern u8 griffon_transition_sprite_source[];
extern u8 resource_completion_callback_address[];
extern u8 cd_cue_base[];
extern u8 actor_effect_color_targets[];
extern u8 staged_spawn_count[];
extern u8 dungeon_resource_buffer[];
extern u8 D_80174CF4[];
extern u8 D_80174CFC[];
extern u8 D_80174D18[];
extern u8 griffon_effect_load_done[];
void *spawn_animated_monster(s16 kind_flags, s16 tile_x, s16 tile_y, s16 part_id);
void update_griffon_motion_and_facing(void *entity, R08_80170A50_S_80170A28_2 *motion, void *part);
void update_actor_behavior_and_effect(ActorRecord *actor, ObjectPosition *position, SpriteFrameState *object, ActorRecord *actor_data);
void advance_griffon_stored_path(ActorRecord *action, ObjectPosition *action_id, SpriteFrameState *entity, ActorRecord *move_state);
void choose_griffon_move(ActorRecord *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data);
void begin_griffon_step_animation(void *object, void *unused, void *display, void *orientation);
s32 update_actor_animation_behavior_and_facing(ActorRecord *action_state, ObjectPosition *motion_param, SpriteFrameState *sprite, ActorRecord *actor);
void begin_griffon_attack(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);
s32 relink_griffon_path(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void finish_actor_tile_move_then_resume_effect_behavior(ActorRecord *state, ObjectPosition *context, SpriteFrameState *source, ActorRecord *target);
void hop_griffon_to_tile(void *action, void *motion,struct SpriteFrameState *sprite, void *actor);
void advance_a_timed_actor_animation_applies_completion_effects(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic);
void update_staged_movement_and_return_to_tile(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_item_activation_and_cleanup(void *action, ObjectPosition *motion, void *actor, ActorRecord *object);
void advance_action_phase_and_process_actor(void *action, void *motion,struct SpriteFrameState *sprite, void *entity);
void remove_defeated_griffon(void *state, void *motion, void *position, void *actor);
void shrink_hopping_griffon(void *state, void *motion, void *position, void *actor);
void advance_griffon_removal(void *state, void *motion, void *position, void *actor);
void finish_actor_hop_and_grow_then_resume_effect_behavior(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void update_object_or_select_directional_data(ActorRecord *controller, ObjectPosition *actor_index, SpriteFrameState *sprite, ActorRecord *actor);
void resume_actor_effect_behavior_after_status_animation(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
void update_griffon_parent_motion(ActorRecord *actor, ObjectPosition *action, SpriteFrameState *entity, ActorRecord *map_object);
void finish_thrown_actor_travel_and_floor_trap_then_resume_effect_behavior(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic);
void finish_actor_terrain_interpolation_then_resume_effect_behavior(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void create_four_directional_effects(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void finish_actor_fade_in_then_resume_effect_behavior(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
s32 start_bank_actor_hit_reaction(void *initial_payload, s32 entry_data, R08_801740F4_Entry *entry, s32 unused);
void advance_object_angle_and_height(u16 *record_data, s32 unused, R08_80174180_Object *object);
void create_tinted_rotated_sprite(s32 unused_0, R08_801741D0_S_801741D0_3 *source_pos, s32 unused_2, s8 green, u8 red_blue);
void update_timed_effect_and_expire(void *effect, s32 x, s32 y);
void create_positioned_sprite_effect(M2C_UNK unused, EntityRec *source_pos, void *unused_context);
void wait_for_griffon_action_slot(void *entity_data, s32 unused_1, s32 unused_2, void *other_data);
void finish_griffon_effect_and_tint(u8 *task, void *context, u8 *input);
void advance_effect_and_child_animation(ActorRecord *effect_state, ObjectPosition *position, SpriteFrameState *entity, ActorRecord *actor);
void finish_actor_floor_trap_then_resume_effect_behavior(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void finish_actor_action_flag_propagation_then_resume_effect_behavior(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void *spawn_griffon_actor(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);




void advance_entity_movement_and_settle_tile(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity);
void update_actor_directional_movement(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void update_directional_motion_and_center_variant(ActorRecord *controller, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity);




void advance_directional_motion_to_center(void *motion_state, ObjectPosition *motion, SpriteFrameState *sprite, void *actor);
void update_directional_motion(void *action, ObjectPosition *motion, SpriteFrameState *sprite, void *entity);
void update_griffon_recoil(void *action, ObjectPosition *motion, SpriteFrameState *sprite, void *entity);

#endif
