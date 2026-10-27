#ifndef DUNGEON_RESOURCE03_SLOT0_H
#define DUNGEON_RESOURCE03_SLOT0_H
#include "common.h"
#include "dungeon/actor.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "m2c_compat.h"
#include "shared/def_table.h"
#include "records/Rec_func_801736F4_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/sprite_frame_state.h"
#include "shared/actor_status.h"
#include "shared/object_links.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/actor/animation.h"
#include "dungeon/actor/motion.h"
#include "dungeon/player/object.h"
#include "dungeon/system.h"
#include "engine/node/allocation.h"
struct S_800AC480_0;
struct S_800AC480_3;

typedef s32 R03_80170854_M2C_UNK;
typedef struct R03_80170854_S_8016A854_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} R03_80170854_S_8016A854_0;
typedef struct R03_80170854_S_8016A854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} R03_80170854_S_8016A854_1;
typedef struct R03_80170854_S_8016A854_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} R03_80170854_S_8016A854_2;
typedef struct R03_80170854_S_8016A854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} R03_80170854_S_8016A854_4;
typedef void (*R03_80170A28_EntityCallback)(void *, void *, void *, void *);

typedef struct R03_80170A28_S_80170A28_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} R03_80170A28_S_80170A28_1;
typedef struct R03_80170A28_S_80170A28_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R03_80170A28_S_80170A28_2;

typedef struct R03_8017139C_S_8017139C_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   
} R03_8017139C_S_8017139C_0;
typedef struct R03_8017139C_S_8017139C_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    u8 unk_9A;
} R03_8017139C_S_8017139C_2;

typedef struct R03_80171DA0_S_80171DA0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} R03_80171DA0_S_80171DA0_1;

typedef struct R03_8017207C_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} R03_8017207C_S_80172628_0;
typedef struct R03_801721C0_S_801721C0_0 {
    u8 pad_00[0x8C];
    ActorActionHandler unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   
} R03_801721C0_S_801721C0_0;
typedef struct R03_80172258_S_80172258_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
} R03_80172258_S_80172258_0;

typedef struct R03_80172620_S_80172620_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 phase;
    u8 pad_9C[0x8];
    union { void * s; s32 u; } unk_A4;   
} R03_80172620_S_80172620_0;
typedef struct R03_80172620_S_80172620_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 * unk_10;
    u8 pad_14[0x36];
    u16 unk_4A;
    u8 pad_4C[0x6F];
    u8 unk_BB;
} R03_80172620_S_80172620_3;

typedef struct R03_80172620_S_80172620_5 {
    u8 pad_00[0xBB];
    u8 unk_BB;
} R03_80172620_S_80172620_5;
typedef struct R03_80172620_Copy24 {
    s32 word[6];
} R03_80172620_Copy24;
typedef struct R03_80172A24_S_80172A24_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} R03_80172A24_S_80172A24_0;

typedef struct R03_80172A24_S_80172A24_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} R03_80172A24_S_80172A24_7;
typedef struct R03_80172F14_S_80172F14_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } timer;   
    u8 pad_98[0x3];
    u8 phase;
} R03_80172F14_S_80172F14_1;
typedef struct R03_80173358_S_80173358_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} R03_80173358_S_80173358_0;
typedef struct R03_80173358_S_80173358_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} R03_80173358_S_80173358_1;
typedef struct R03_80173358_S_80173358_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} R03_80173358_S_80173358_2;



extern s32 rand(void);
extern int abs(int);
void * func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
s32 register_node(struct ObjectNodeHeader *entry, void *registration_id);
s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
s32 set_or_clear_actor_status_slot();
void select_indirect_table_entry(struct S_80047738 *state, s16 table_index, s16 entry_index);
void advance_sprite_animation_and_textures(void *entity);
void apply_monster_koyaw_data(s32 flags, s8 *dst);
s32 refresh_actor_facing_and_lifecycle();
s16 sample_terrain_surface_height();
void select_sprite_entry(void *object_data, s16 table_index, s16 entry_index);
void func_80047784(SpriteFrameState *object, s16 table_index, s16 entry_index);
s32 check_entity_relation();
s32 find_active_rect_containing_point(s32 point_x, s32 point_y);
s32 test_neighbor_position_relation(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y);
s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
s32 can_entity_gain_level(void *entity);
void update_actor_status_and_mp(ActorRecord *entity);
s32 begin_ready_actor_directional_action();
s32 advance_actor_pending_action(void *actor_state, void *action, void *status, void *actor);
void begin_actor_move_to_target_facing();
s32 reset_actor_action_state(void *actor, void *unused, SpriteFrameState *sprite, u8 *direction_frames);
s32 process_selected_actor_record();
void begin_actor_spell_action(void *actor, void *effect_param, SpriteFrameState *target, u8 *direction_table, void *next_state);
void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
s32 check_movement_clearance_and_height();
s32 update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
void * find_adjacent_actor(void *entity, u16 x, u16 y);
s32 probe_directional_neighbor();
s32 get_actor_height_difference();
s32 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
s32 select_actor_route_target(u8 *actor_held, s32 kind, u8 *work_p, u16 *out);
s32 prepare_directional_attack();
s32 try_claim_dungeon_action_slot();
u32 check_entity_interaction_compatibility();
s32 apply_camera_offset_and_select_target(void *object_addr, void *source_pos, s32 helper_arg, s32 slot_value);
#include "dungeon/player/object/action_state.h"
struct ObjectNodeHeader;
struct S_80047738;
s32 relink_entity_and_clear_high_flag();
void advance_status_timers(void *record);
s32 update_actor_movement_to_tile(void *move_state, void *motion, void *target_tile, ActorRecord *actor);
void spend_actor_mp();

void on_actor_status_updated(void *actor);
void func_800A9A04(void *actor);
s32 update_linked_actor_motion(void *state, void *transform, void *config, void *object);
void * resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
s32 get_cd_command_queue_depth(void);
void * scan_actor_along_heading();
void * create_actor_spell_effect(void *actor, void *record_data, s16 mode, void *context);
void create_two_row_object_group(void *payload, s16 value_scale);
void begin_actor_display_action();
s32 update_actor_defeat_removal(u8 *state, s32 *position, u8 *sprite, u8 *entity_data);

s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
s32 func_80042900(ActorRecord *entry, s32 effect_id);
void clear_slots_of_type(ActorRecord *owner, s8 match_type);
void func_80042B68(ActorRecord *owner, s8 match_type);
s32 get_tile_chebyshev_distance();

s32 update_actor_transform_from_parent(Rec_func_800A9E70_arg0 *state, ObjectPosition *position, Rec_D_80082E80 *tile, void *actor);
s32 update_thrown_actor_travel(void *move_state, ObjectPosition *motion, SpriteFrameState *tile_pos, ActorRecord *actor);
s32 interpolate_actor_to_terrain_tile(struct S_800AC480_0 *move_state, ObjectPosition *motion, MovingTile *target_tile, struct S_800AC480_3 *height_state);
s32 update_spinning_actor_fall();
s32 update_actor_fade_in();
s32 resolve_actor_floor_trap_once();
s32 propagate_actor_action_flag();
extern u8 dragon_direction_frames[];
extern u8 dragon_alt_direction_frames[];
extern u8 D_80173CEC[];
extern u8 dragon_frame_set[];
extern u8 D_80173CCC[];
extern u8 dragon_reset_frames[];
extern u8 dragon_frame_set_5[];
extern u8 actor_turn_angle_offsets[];
extern u8 D_80173C8C[];
extern u8 dragon_frame_set_2[];
extern u8 dragon_frame_set_3[];
extern u8 effect_update_tag[];
extern u8 actor_update_node_cursor[];
extern u8 dragon_frame_set_1[];
extern u8 D_80173CAC[];
extern u8 D_80173CB4[];
extern u8 dragon_frame_set_4[];
extern u8 D_80173CC4[];
extern u8 D_80173CE4[];
void *spawn_mode_dependent_112_object(s16 kind_flags, s16 byte_24, s16 byte_25, s16 value_0a);
void update_entity_facing_motion_and_ground(void *entity, R03_80170A28_S_80170A28_2 *motion, void *part);
void dispatch_monster_move_attack_spell(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *entity, ActorRecord *actor_state);
void advance_stored_entity_path(void *controller, ObjectPosition *context, void *entity, void *path_state);
void advance_actor_path_with_item_search(Rec_func_800A9E70_arg0 *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data);
void copy_display_orientation_state(void *object, ObjectPosition *unused, void *display, void *orientation);
s32 check_actor_transition_and_start_effect(Rec_func_800A9E70_arg0 *action_state, ObjectPosition *motion_param, void *sprite_arg, ActorRecord *actor);
void start_directional_actor_effect(void *action_state, ObjectPosition *action_context, void *sprite, ActorRecord *actor);
s32 dispatch_actor_path_state_and_relink_entity(void *entity_arg, ObjectPosition *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void finish_actor_tile_move_and_check_trap(R03_801721C0_S_801721C0_0 *object, void *motion, void *check_data, void *target);
void complete_actor_jump_to_destination(void *jump, void *motion, void *map_entity, void *actor);
void update_dragon_linked_motion(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic);
void advance_actor_attack_and_resolve_damage(void *action, void *transform, void *sprite, ActorRecord *actor);
void finish_timed_actor_movement(void *action_state, void *transform, void *sprite, ActorRecord *actor);
void slow_directional_movement_to_tile(R03_80172F14_S_80172F14_1 *controller, ObjectPosition *motion, SpriteFrameState *entity, void *source);
void remove_defeated_dragon(void *state, void *motion, void *position, void *actor);
void shrink_hopping_dragon(void *state, void *motion, void *position, void *actor);
void advance_dragon_removal(void *state, void *motion, void *position, void *actor);
void grow_hopping_dragon(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void update_actor_status_and_restore_handler(void *in_controller, ObjectPosition *in_context, void *sprite, void *in_actor);
void wait_for_dragon_mp(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
void update_dragon_parent_motion(ActorRecord *actor, ObjectPosition *action, SpriteFrameState *entity, ActorRecord *map_object);
void update_thrown_dragon(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic);
void settle_dragon_on_tile(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void fade_entity_colors_to_neutral(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void fade_in_dragon(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void resolve_dragon_floor_trap(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void propagate_dragon_action_flag(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
/* Compatibility for registered relink copies pending LL4 deletion.
 * Production home members use the shared concept directly. */

#endif
