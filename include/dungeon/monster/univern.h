#ifndef DUNGEON_RESOURCE17_SLOT0_H
#define DUNGEON_RESOURCE17_SLOT0_H
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
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/def_table.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/actor_status.h"
#include "shared/position_views.h"
#include "sdk/libgte.h"
#include "dungeon/actor/animation.h"
#include "dungeon/actor/motion.h"
#include "dungeon/system.h"
#include "dungeon/actor/status.h"
struct S_800AC480_0;
struct S_800AC480_3;
struct S_800AD594_0;
struct SpriteFrameState;

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
#define F8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define FS8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define F16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define FS16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define F32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define FPTR(p, o) (*(void **)((u8 *)(p) + (o)))
typedef unsigned long R17_8017089C_uptr;

typedef struct R17_8017089C_S_8017089C_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} R17_8017089C_S_8017089C_1;
typedef struct R17_8017089C_S_8017089C_2 {
    u8 pad_00[0x8];
    union { struct { void * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   
    void * unk_0C;
} R17_8017089C_S_8017089C_2;
typedef struct R17_8017089C_S_8017089C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x1];
    s16 unk_9E;
    u8 pad_A0[0x8];
    s16 unk_A8;
} R17_8017089C_S_8017089C_4;
typedef struct R17_8017089C_S_8017089C_5 {
    u8 pad_00[0xA4];
    void * unk_A4;
} R17_8017089C_S_8017089C_5;
typedef struct R17_8017089C_S_8017089C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    s16 unk_06;
    u8 pad_08[0x90];
    void * unk_98;
} R17_8017089C_S_8017089C_6;

typedef struct R17_8017089C_S_8017089C_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} R17_8017089C_S_8017089C_8;

typedef void (*R17_80170BB8_EntityCallback)(void *, void *, void *, void *);
typedef struct R17_80170BB8_S_80170BB8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R17_80170BB8_S_80170BB8_0;

typedef struct R17_80170BB8_S_80170BB8_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    union { u16 u; s16 s; } unk_88;   
} R17_80170BB8_S_80170BB8_2;
typedef struct R17_80170BB8_S_if_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} R17_80170BB8_S_if_0;

typedef struct R17_801718D0_S_801718D0_0 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   
} R17_801718D0_S_801718D0_0;




typedef struct R17_801724C4_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} R17_801724C4_S_80172628_0;

typedef struct {
    u8 pad00[4];
    u16 flags4;
} R17_80172C18_SubActor;
typedef struct {
    u8 pad00[0x2C];
    void (*f2C)(void);
} R17_80172C18_ActorBase;
typedef struct {
    u8 pad00[0x8C];
    void (*f8C)(void);
    union {
        u32 word90;
        struct {
            u16 half90;
            u16 half92;
        } h;
    } u90;
    u8 pad94[2];
    u16 f96;
    u16 flags98;
    u8 pad9A;
    u8 state9B;
    u8 pad9C[8];
    u8 *fA4;
    s16 fA8;
} R17_80172C18_State;
typedef struct {
    u8 pad00[0xC];
    u32 fC;
    u32 f10;
    u32 f14;
} R17_80172C18_Position;

typedef struct {
    u8 pad00[8];
    u8 slots[9];
    u8 pad11[11];
    u32 flags1C;
    u8 pad20[10];
    s16 f2A;
    u8 pad2C[26];
    u16 f46;
    u8 pad48[24];
    void *f60;
    u8 pad64[9];
    s8 f6D;
    u8 pad6E[4];
    s8 f72;
    s8 f73;
} R17_80172C18_Entity;
typedef struct {
    u8 pad00[0xA6];
    u16 fA6;
} R17_80172C18_MainObj;
typedef struct R17_80173244_S_80173354_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } timer;   
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 phase;
} R17_80173244_S_80173354_1;
typedef struct R17_80173614_S_func_80C17E14_0 {
    u8 pad_00[0x96];
    union {
        u8 unk_00_u8;
        u16 unk_00_u16;
    } unk_96;
    u16 unk_98;
    u8 pad_9A[1];
    u8 unk_9B;
} R17_80173614_S_func_80C17E14_0;

typedef struct R17_80173614_S_func_80C17E14_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} R17_80173614_S_func_80C17E14_2;
typedef struct R17_80173614_S_func_80C17E14_3 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[4];
    u32 unk_1C;
    u8 pad_20[0x4A];
    u16 unk_6A;
} R17_80173614_S_func_80C17E14_3;
typedef struct R17_801738E0_S_801738E0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 phase;
    u8 pad_9C[0xC];
    s16 unk_A8;
} R17_801738E0_S_801738E0_0;

typedef struct R17_801738E0_S_801738E0_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} R17_801738E0_S_801738E0_2;
typedef struct R17_801738E0_S_801738E0_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} R17_801738E0_S_801738E0_3;
struct R17_801738E0_GlobalStruct {
    u16 unk0;
    u16 flags;
    u8 unk4[6];
    u16 counter;
};
typedef struct R17_80173F10_S_80173ED8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
} R17_80173F10_S_80173ED8_0;
typedef struct R17_80173F10_S_80173ED8_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} R17_80173F10_S_80173ED8_2;
typedef struct R17_80173F10_S_80173ED8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} R17_80173F10_S_80173ED8_4;
typedef struct R17_80173F10_S_80173ED8_5 {
    u8 pad_00[0x58];
    void * unk_58;
} R17_80173F10_S_80173ED8_5;



void *allocate_list_node();
void * func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
void select_sprite_entry(void *object, s16 table_index, s16 entry_index);
void func_80047784(SpriteFrameState *object, s16 table_index, s16 entry_index);
void texture_set_the_active_entries_matching_id_in_type_n_2_table_slots();
void select_indirect_table_entry();
void advance_sprite_animation_and_textures(void *entity);
void apply_monster_koyaw_data(s32 flags, s8 *dst);
s32 refresh_actor_facing_and_lifecycle();
s16 sample_terrain_surface_height();
s32 check_entity_relation();
s32 find_active_rect_containing_point(s32 point_x, s32 point_y);
s32 test_neighbor_position_relation(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y);
s32 get_rounded_facing_and_rounding_flag();
s32 can_entity_gain_level(void *entity);
void update_actor_status_and_mp(ActorRecord *entity);
s32 begin_ready_actor_directional_action();
s32 advance_actor_pending_action(void *actor_state, void *action, void *status, void *actor);
void begin_actor_move_to_target_facing();
s32 reset_actor_action_state(void *actor, void *unused, SpriteFrameState *sprite, u8 *direction_frames);
s32 process_selected_actor_record();
void begin_actor_spell_action(void *actor, void *effect_param, SpriteFrameState *target, u8 *direction_table, void *next_state);
s32 cycle_map_cell_flags();
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
s32 update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
void * find_adjacent_actor();
s32 probe_directional_neighbor();
s32 get_actor_height_difference();
s32 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
s32 select_actor_route_target();
s32 check_directional_move_and_terrain();
s32 prepare_directional_attack();
s32 try_claim_dungeon_action_slot();
u32 check_entity_interaction_compatibility();
s32 apply_camera_offset_and_select_target();
#include "dungeon/player/object/action_state.h"
struct ObjectNodeHeader;
s32 relink_entity_and_clear_high_flag();
s32 update_actor_movement_to_tile(void *move_state, void *motion, void *target_tile, ActorRecord *actor);
void spend_actor_mp(struct S_800AD594_0 *entity, s32 base_reduction);

s32 update_linked_actor_motion(void *state, void *transform, void *config, void *object);
void * resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
void set_record_integer_tile_center();
void * scan_actor_along_heading();
void * create_actor_spell_effect(void *actor, void *record_data, s16 mode, void *context);
s32 get_cd_command_queue_depth(void);
void create_source_positioned_object();
void begin_actor_display_action(void *actor, void *unused, SpriteFrameState *display, u8 *facing_variants);
void unlink_entity_node();
void distribute_experience_and_report_gains();
void * detach_record_and_update_slot_state(void *record);

s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
s32 func_80042900(ActorRecord *entry, s32 effect_id);
void clear_slots_of_type(ActorRecord *owner, s8 match_type);
void func_80042B68(ActorRecord *owner, s8 match_type);
s32 get_tile_chebyshev_distance();

void on_actor_status_updated(void *actor);
void func_800A9A04(void *actor);
s32 update_actor_transform_from_parent(Rec_func_800A9E70_arg0 *state, ObjectPosition *position, Rec_D_80082E80 *tile, void *actor);
s32 update_thrown_actor_travel(void *move_state, ObjectPosition *motion, SpriteFrameState *tile_pos, ActorRecord *actor);
s32 interpolate_actor_to_terrain_tile(struct S_800AC480_0 *move_state, ObjectPosition *motion, MovingTile *target_tile, struct S_800AC480_3 *height_state);
s32 update_spinning_actor_fall();
s32 update_actor_fade_in();
s32 resolve_actor_floor_trap_once();
s32 propagate_actor_action_flag();
extern u8 univern_frame_set[];
extern u8 view_facing_angle_alias[];
extern u8 child_texture_entries[];
extern u8 child_object_update_address[];
extern u8 univern_direction_frames[];
extern u8 univern_alt_spawn_direction_frames[];
extern u8 univern_alt_direction_frames[];
extern u8 D_80174504[];
extern u8 D_801744A4[];
extern u8 D_801744D4[];
extern u8 univern_frame_set_1[];
extern u8 actor_turn_angle_offsets[];
extern u8 actor_update_node_cursor[];
extern u8 D_801744B4[];
extern u8 D_801744BC[];
extern u8 D_801744C4[];
extern u8 D_801744CC[];
extern u8 D_801744DC[];
extern u8 D_801744AC[];
extern u8 univern_frame_set_2[];
void *spawn_univern_actor(s32 kind, s32 tile_x, s32 tile_y, s32 copy_value);
void create_anchored_directional_object(void *actor, void *motion, struct SpriteFrameState *object);
void update_entity_movement_and_ground_height(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *status);
void advance_entity_along_path_2(void *motion, s32 unused, struct SpriteFrameState *entity, void *path_state);
void choose_univern_move(Rec_func_800A9E70_arg0 *move_data, void *context, SpriteFrameState *position_data, ActorRecord *actor_data);
s32 try_univern_attack(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, void *sprite_arg, ActorRecord *actor);
void begin_univern_attack(Rec_func_800A9E70_arg0 *action_state, void *context, struct SpriteFrameState *animation,
    ActorRecord *entity);
s32 relink_univern_path(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void finish_actor_tile_move_then_resume_ground_movement(void *state, void *motion, void *source, void *target);
void finish_linked_actor_motion_and_floor_trap_then_resume_ground_movement(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic);
void update_staged_movement_and_direction(void *action, void *motion, struct SpriteFrameState *sprite, void *actor);
void update_entity_item_action_and_idle_return(R17_80172C18_State *state, R17_80172C18_Position *pos, struct SpriteFrameState *actor, R17_80172C18_Entity *ent);
void advance_univern_flight(void *action, void *motion, struct SpriteFrameState *sprite, void *actor);
void advance_familiar_defeat_sequence(R17_80173614_S_func_80C17E14_0 *action, MotionDeltaView *motion, R17_80173614_S_func_80C17E14_2 *sprite,
    R17_80173614_S_func_80C17E14_3 *entity);
void shrink_hopping_univern(void *state, void *motion, void *position, void *actor);
void advance_univern_removal(void *state, void *motion, void *position, void *actor);
void finish_actor_hop_and_grow_then_resume_ground_movement(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void update_sleeping_univern(void *actor_arg, void *motion_arg, void *sprite_arg, void *entity_arg);
void advance_univern_status_action(void *action, void *context, struct SpriteFrameState *sprite, void *entity);
void update_univern_parent_motion(ActorRecord *actor, ObjectPosition *action, SpriteFrameState *entity, ActorRecord *map_object);
void update_timed_effect_and_expire(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic);
void finish_actor_terrain_interpolation_then_resume_ground_movement(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void finish_spinning_actor_fall_then_resume_ground_movement(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void update_effect_trajectory_and_sprite(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void blend_animation_palette_and_complete(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void finish_actor_action_flag_propagation_then_resume_ground_movement(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
#endif
