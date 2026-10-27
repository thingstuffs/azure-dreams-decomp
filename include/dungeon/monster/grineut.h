#ifndef DUNGEON_RESOURCE07_SLOT0_H
#define DUNGEON_RESOURCE07_SLOT0_H
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
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/def_table.h"
#include "records/Rec_func_80172CC0_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_func_801736F4_arg0.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "dungeon/system.h"
#include "engine/node/allocation.h"

typedef s32 R07_80170854_M2C_UNK;




typedef void (*R07_80170A28_EntityCallback)(void *, void *, void *, void *);
typedef struct R07_80170A28_S_80170A28_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} R07_80170A28_S_80170A28_0;
typedef struct R07_80170A28_S_80170A28_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} R07_80170A28_S_80170A28_1;
typedef struct R07_80170A28_S_80170A28_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R07_80170A28_S_80170A28_2;
typedef struct R07_80170E54_S_80170E54_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   
    u8 unk_26;
    u8 pad_27[0x5];
    union { void * p; u8 * p2; } unk_2C;   
    u8 pad_30[0x8B];
    u8 unk_BB;
} R07_80170E54_S_80170E54_2;
typedef struct R07_80170E54_S_80170E54_7 {
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
} R07_80170E54_S_80170E54_7;
typedef struct R07_80170E54_S_80170E54_8 {
    u8 pad_00[0x4];
    s32 unk_04;
} R07_80170E54_S_80170E54_8;
typedef struct R07_80170E54_S_80170E54_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} R07_80170E54_S_80170E54_9;
typedef struct R07_80171570_S_80171570_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   
    u8 pad_72[0x18];
    s16 unk_8A;
} R07_80171570_S_80171570_0;
typedef struct R07_80171570_S_80171570_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} R07_80171570_S_80171570_2;
typedef struct R07_80171570_S_80171570_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R07_80171570_S_80171570_3;

typedef struct R07_8017229C_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} R07_8017229C_S_80172628_0;
typedef struct R07_801723E0_S_801724A8_0 {
    u8 pad_00[0x8C];
    ActorActionHandler unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   
} R07_801723E0_S_801724A8_0;
typedef struct R07_80172478_S_80172478_0 {
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
} R07_80172478_S_80172478_0;
typedef struct R07_80172478_S_80172478_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} R07_80172478_S_80172478_2;


typedef struct R07_80172CC0_S_80172CC0_1_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} R07_80172CC0_S_80172CC0_1_pre;
typedef struct R07_80172CC0_S_80172CC0_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R07_80172CC0_S_80172CC0_2;
typedef struct R07_80173238_S_80173238_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } timer;   
    u8 pad_98[0x3];
    u8 phase;
} R07_80173238_S_80173238_1;
typedef struct R07_80173238_S_80173238_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R07_80173238_S_80173238_2;



void * func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
s16 set_or_clear_actor_status_slot(ActorRecord *owner, s8 id, s8 value);
void initialize_actor_sprite_and_animation(void *entity, void *position, SpriteFrameState *sprite, s32 init_flags);
void select_indirect_table_entry(struct S_80047738 *state, s16 table_index, s16 entry_index);
void advance_sprite_animation_and_textures(void *entity);
void apply_monster_koyaw_data(s32 flags, s8 *dst);
s32 refresh_actor_facing_and_lifecycle();
s16 sample_terrain_surface_height();
s32 resolve_record_orientation_or_fallback();
void select_sprite_entry();
void func_80047784(SpriteFrameState *object, s16 table_index, s16 entry_index);
s32 check_entity_relation();
s32 find_active_rect_containing_point(s32 point_x, s32 point_y);
s32 test_neighbor_position_relation(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y);
s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
s32 can_entity_gain_level(void *entity);
void update_actor_status_and_mp(ActorRecord *entity);
void begin_pushed_actor_move(void *state_in, void *unused, void *position_in, void *actor_in);
s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
s32 advance_actor_pending_action(void *actor_state, void *action, void *status, void *actor);
void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
s32 reset_actor_action_state(void *actor, void *unused, SpriteFrameState *sprite, u8 *direction_frames);
s32 process_selected_actor_record(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
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
s16 try_claim_dungeon_action_slot(ActorRecord *actor);
u32 check_entity_interaction_compatibility();
s32 apply_camera_offset_and_select_target(void *object_addr, void *source_pos, s32 helper_arg, s32 slot_value);
#include "dungeon/player/object/action_state.h"
struct ObjectNodeHeader;
struct S_80047738;
s32 relink_entity_and_clear_high_flag();
void advance_status_timers();
s32 update_actor_movement_to_tile();
void spend_actor_mp();

void set_record_integer_tile_center();
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
s32 update_actor_hop_and_shrink(void *animation, void *motion, SpriteFrameState *scale, void *render);

s32 update_actor_hop_and_grow();
s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
s32 func_80042900(ActorRecord *entry, s32 effect_id);
void clear_slots_of_type(ActorRecord *owner, s8 match_type);
void func_80042B68(ActorRecord *owner, s8 match_type);
s32 get_tile_chebyshev_distance();

s32 update_actor_transform_from_parent();
s32 update_thrown_actor_travel(void *move_state, ObjectPosition *motion, SpriteFrameState *tile_pos, ActorRecord *actor);
s32 interpolate_actor_to_terrain_tile();
s32 update_spinning_actor_fall();
s32 update_actor_fade_in();
s32 resolve_actor_floor_trap_once(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
s32 propagate_actor_action_flag(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern u8 grineut_frame_set_1[];
extern u8 grineut_alt_direction_frames[];
extern u8 D_80174198[];
extern u8 D_800D79B0[];
extern u8 secondary_sprite[];
extern u8 grineut_frame_set_3[];
extern u8 grineut_frame_set_4[];
extern u8 grineut_frame_set_2[];
extern u8 grineut_move_direction_frames[];
extern u8 actor_turn_angle_offsets[];
extern u8 grineut_frame_set_5[];
extern u8 grineut_frame_set_6[];
extern u8 grineut_frame_set[];
extern u8 actor_update_node_cursor[];
extern u8 D_80174170[];
extern u8 D_80174180[];
extern u8 D_80174178[];
void *spawn_mode_dependent_112_object(s16 kind_flags, s16 byte_24, s16 byte_25, s16 value_0a);
void update_entity_facing_motion_and_ground(void *entity, R07_80170A28_S_80170A28_2 *motion, void *part);
void dispatch_monster_move_attack_spell(ActorRecord *record, ObjectPosition *entity, SpriteFrameState *object, ActorRecord *other_entity);
void advance_stored_path_motion(ActorRecord *action, ObjectPosition *action_id, SpriteFrameState *entity, ActorRecord *move_state);
void choose_grineut_move(ActorRecord *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data);
void initialize_opposite_facing_effect(ActorRecord *effect, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *source);
s32 try_grineut_attack(ActorRecord *action_state, ObjectPosition *motion_param, SpriteFrameState *sprite, ActorRecord *actor);
void begin_grineut_attack(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);
s32 relink_grineut_path(void *entity_arg, ObjectPosition *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void move_grineut_to_tile(R07_801723E0_S_801724A8_0 *state, s32 context, s32 source, s32 target);
void advance_target_hop(void *action, void *motion, void *sprite, void *actor);
void update_grineut_linked_motion(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic);
void complete_staged_destination_movement(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void advance_actor_stored_path_2(void *action, ObjectPosition *motion, void *sprite, void *actor);
void settle_directional_motion_at_tile(void *motion_state, void *motion, void *sprite, void *entity);
void remove_defeated_grineut(void *state, void *motion, void *position, void *actor);
void shrink_hopping_grineut(void *state, void *motion, void *position, void *actor);
void advance_grineut_removal(void *state, void *motion, void *position, void *actor);
void grow_hopping_grineut(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void update_sleeping_grineut(ActorRecord *controller, ObjectPosition *actor_index, SpriteFrameState *sprite, ActorRecord *actor);
void dim_and_clear_flagged_effect(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
void update_grineut_parent_motion(ActorRecord *actor, ObjectPosition *action, SpriteFrameState *entity, ActorRecord *map_object);
void update_thrown_grineut(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic);
void settle_grineut_on_tile(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void update_spinning_grineut_fall(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void fade_in_grineut(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void resolve_grineut_floor_trap(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void propagate_grineut_action_flag(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);




void settle_directional_motion_variant(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);


void update_directional_movement_and_center(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *actor, ActorRecord *entity);



void decelerate_directional_motion_and_center(void *action, ObjectPosition *motion, SpriteFrameState *sprite, void *entity);
void settle_directional_actor_motion(void *motion_state, ObjectPosition *motion, SpriteFrameState *map_actor, void *actor);
void settle_entity_after_directional_motion(void *action, ObjectPosition *motion, SpriteFrameState *sprite, void *entity);
void update_directional_motion_and_tile_alignment(void *action, ObjectPosition *motion, SpriteFrameState *actor, void *entity);

void *spawn_grineut(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height);

#endif
