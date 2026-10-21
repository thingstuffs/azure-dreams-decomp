#ifndef DUNGEON_RESOURCE07_SLOT0_H
#define DUNGEON_RESOURCE07_SLOT0_H
#include "common.h"
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

typedef s32 R07_80170854_M2C_UNK;
typedef struct R07_80170854_S_8016A854_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} R07_80170854_S_8016A854_0;
typedef struct R07_80170854_S_8016A854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} R07_80170854_S_8016A854_1;
typedef struct R07_80170854_S_8016A854_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} R07_80170854_S_8016A854_2;
typedef struct R07_80170854_S_8016A854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} R07_80170854_S_8016A854_4;
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
typedef struct R07_801717B4_S_80171C34_1 {
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
} R07_801717B4_S_80171C34_1;
typedef struct R07_801717B4_S_80171C34_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   
    union { s8 s; u8 u; } unk_26;   
} R07_801717B4_S_80171C34_2;
typedef struct R07_801717B4_S_80171C34_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R07_801717B4_S_80171C34_3_pre;
typedef struct R07_801717B4_S_80171C34_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} R07_801717B4_S_80171C34_3;
typedef struct R07_801717B4_S_80171C34_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   
} R07_801717B4_S_80171C34_5;
typedef struct R07_801717B4_S_80171C34_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R07_801717B4_S_80171C34_7;
typedef struct R07_801717B4_S_80171C34_8 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R07_801717B4_S_80171C34_8;
typedef struct R07_801717B4_DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} R07_801717B4_DungeonRecord;
typedef struct R07_80172184_Ent R07_80172184_Ent;
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
    M2C_UNK * unk_8C;
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
typedef struct {
    u8 pad0[0x8C];
    void (*callback)(void *, void *, void *, void *);
} Resource07CallbackState;
typedef struct R07_8017284C_S_8017284C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} R07_8017284C_S_8017284C_0;
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
    union { s16 s; u16 u; } unk_96;   
    u8 pad_98[0x3];
    u8 unk_9B;
} R07_80173238_S_80173238_1;
typedef struct R07_80173238_S_80173238_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R07_80173238_S_80173238_2;
typedef struct {
    s8 pad_00[0x8C];
    void *unk_8C;
} R07_80173EF4_Actor;
typedef struct {
    u8 pad_00[0x2C];
    u8 *unk_2C;
} R07_80173EF4_Entity;
typedef struct {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} R07_80173EF4_MapObject;
s32 allocate_list_node();
s32 func_8003FD64();
s32 register_node();
s32 func_8004491C();
s32 generate_random_value();
s32 set_or_clear_actor_status_slot();
void initialize_actor_sprite_and_animation();
s32 try_move_actor_to_valid_position();
void select_indirect_table_entry();
void advance_sprite_animation_and_textures();
void apply_monster_koyaw_data();
s32 refresh_actor_facing_and_lifecycle();
s16 sample_terrain_surface_height();
s32 resolve_record_orientation_or_fallback();
void select_sprite_entry();
void func_80047784();
s32 func_80069EF8();
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
void cycle_map_cell_flags();
void update_map_cell_flags_with_item_limit();
s32 check_movement_clearance_and_height();
s32 update_actor_proximity_flag();
s32 find_valid_monster_neighbor();
s32 probe_directional_neighbor();
s32 get_actor_height_difference();
s32 check_diagonal_side_height();
s32 rebuild_monster_reachable_tiles();
s32 prepare_directional_attack();
s32 try_claim_dungeon_action_slot();
u32 check_entity_interaction_compatibility();
s32 apply_camera_offset_and_select_target();
s32 has_pending_dungeon_activity();
s32 relink_entity_and_clear_high_flag();
s32 advance_status_timers();
s32 update_actor_movement_to_tile();
void spend_actor_mp();
s32 check_actor_floor_trap();
s32 func_800644B8();
void set_record_integer_tile_center();
void on_actor_status_updated();
void func_800A9A04();
s32 update_linked_actor_motion();
s32 resolve_attack_damage_and_effects();
s32 play_sound_if_enabled();
s32 get_cd_command_queue_depth();
s32 scan_monster_along_heading();
s32 create_actor_spell_effect();
void create_two_row_object_group();
void begin_actor_display_action();
void apply_clamped_actor_value_delta();
s32 update_actor_defeat_removal();
s32 update_actor_hop_and_shrink();
s32 advance_actor_removal();
s32 update_actor_hop_and_grow();
s32 get_entity_effect_value();
s32 func_80042900();
void clear_slots_of_type();
void func_80042B68();
s32 get_tile_chebyshev_distance();
s32 has_pending_actor_or_turn_action();
s32 update_actor_transform_from_parent();
s32 update_thrown_actor_travel();
s32 interpolate_actor_to_terrain_tile();
s32 update_spinning_actor_fall();
s32 update_actor_fade_in();
s32 resolve_actor_floor_trap_once();
s32 propagate_actor_action_flag();
extern u8 D_80174148[];
extern u8 D_80174190[];
extern u8 D_80174198[];
extern u8 D_800D79B0[];
extern u8 secondary_sprite[];
extern u8 D_80174140[];
extern u8 D_80174150[];
extern u8 D_80174188[];
extern u8 D_80174138[];
extern u8 actor_turn_angle_offsets[];
extern u8 D_80174158[];
extern u8 D_80174160[];
extern u8 D_80174168[];
extern u8 actor_update_node_cursor[];
extern u8 D_80174170[];
extern u8 D_80174180[];
extern u8 D_80174178[];
void *spawn_mode_dependent_112_object(s16 kind_flags, s16 byte_24, s16 byte_25, s16 value_0a);
void update_entity_facing_motion_and_ground(void *entity, R07_80170A28_S_80170A28_2 *motion, void *part);
void func_80170E54(void *record, EntityRec *entity, void *object, ActorRecord *other_entity);
void advance_stored_path_motion(void *action, s32 action_id, SpriteFrameState *entity, void *move_state);
void func_801717B4(void *move_data, void *context, void *position_data, void *actor_data);
void initialize_opposite_facing_effect(void *effect, s32 *position, SpriteFrameState *sprite, void *source);
s32 func_80171FC0(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, ActorRecord *actor);
void func_80172184(void *action_state, void *action_context, SpriteFrameState *sprite, ActorRecord *actor);
s32 func_8017229C(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void func_801723E0(R07_801723E0_S_801724A8_0 *state, s32 context, s32 source, s32 target);
void advance_target_hop(void *action, void *motion, void *sprite, void *actor);
void func_801727E8(Resource07CallbackState *state, void *entity, void *position, void *graphic);
void complete_staged_destination_movement(R07_8017284C_S_8017284C_0 *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void advance_actor_stored_path_2(void *action, ObjectPosition *motion, void *sprite, void *actor);
void settle_directional_motion_at_tile(void *motion_state, void *motion, void *sprite, void *entity);
void func_8017365C(void *state, void *motion, void *position, void *actor);
void func_8017367C(void *state, void *motion, void *position, void *actor);
void func_8017369C(void *state, void *motion, void *position, void *actor);
void func_801736BC(Resource07CallbackState *state, void *motion, void *position, void *actor);
void func_801736F4(void *controller, s32 actor_index, void *sprite, ActorRecord *actor);
void dim_and_clear_flagged_effect(void *controller, void *context, void *sprite, ActorRecord *entity);
void func_80173EF4(R07_80173EF4_Actor *actor, s32 action, R07_80173EF4_Entity *entity, R07_80173EF4_MapObject *map_object);
void func_80173FBC(Resource07CallbackState *state, void *entity, void *position, void *graphic);
void func_80174020(Resource07CallbackState *state, void *motion, void *position, void *actor);
void func_80174058(Resource07CallbackState *state, void *motion, void *position, void *actor);
void func_80174090(Resource07CallbackState *state, void *motion, void *position, void *actor);
void func_801740C8(Resource07CallbackState *state, void *motion, void *position, void *actor);
void func_80174100(Resource07CallbackState *state, void *motion, void *position, void *actor);
#endif
