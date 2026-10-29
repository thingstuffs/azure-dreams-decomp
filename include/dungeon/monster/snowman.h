#ifndef DUNGEON_RESOURCE10_SLOT0_H
#define DUNGEON_RESOURCE10_SLOT0_H
#include "shared/gpu_packets.h"
#include "dungeon/actor.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80171CD4_arg0.h"
#include "records/Rec_func_80171CD4_arg1.h"
#include "m2c_compat.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "records/Rec_D_80083460.h"
#include "records/Rec_func_80174800_arg0.h"
#include "sdk/libc.h"
#include "sdk/libgpu.h"
#include "dungeon/actor/animation.h"
#include "dungeon/actor/motion.h"
#include "dungeon/player/object.h"
#include "dungeon/system.h"
#include "engine/texture.h"
#include "dungeon/actor/status.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/state.h"
struct EntityLinkNode;
struct S_800AC480_0;
struct S_800AC480_3;
struct SpriteFrameState;
struct ObjectPosition;

#define NULL 0
typedef struct R10_8017092C_Scratch {
    u8 pad0[4];
    u16 in0;
    u16 in1;
    u16 in2;
    u8 pad0A[0x12];
    u8 *current;
    u8 pad20[4];
    u8 *table;
    u8 pad28[0xA8];
    s32 out0;
    s32 out1;
    u8 padD8[0x28];
    s32 index;
} R10_8017092C_Scratch;
typedef struct R10_8017092C_Packet {
    u8 pad0[3];
    u8 code;
    union {
        u32 link;
        struct {
            u8 r;
            u8 g;
            u8 b;
            u8 command;
        } color;
    } data;
    s32 screen;
} R10_8017092C_Packet;
typedef struct {
    u8 color[3];
    u8 pad03[0x2F];
    s16 scale;
    s16 divisor;
    s16 x;
    s16 y;
    u8 pad3A[6];
    s32 pos[3];
    s32 vel[3];
} R10_80170B0C_Actor;
typedef struct {
    s32 xyz[3];
} R10_80170B0C_Vec3;

typedef struct R10_80170CF8_S_80AC55DC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} R10_80170CF8_S_80AC55DC_0;
typedef struct R10_80170CF8_S_80AC55DC_1 {
    u8 pad_00[0x8];
    void * unk_08;
} R10_80170CF8_S_80AC55DC_1;
typedef struct R10_80170CF8_S_80AC55DC_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u16 unk_36;
    u16 unk_38;
    u16 unk_3A;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} R10_80170CF8_S_80AC55DC_2;

typedef struct R10_80170CF8_S_80AC55DC_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} R10_80170CF8_S_80AC55DC_6;

typedef struct R10_80170F3C_S_80170F3C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} R10_80170F3C_S_80170F3C_1;

typedef struct R10_80170F3C_S_80170F3C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} R10_80170F3C_S_80170F3C_4;
typedef void (*R10_80171104_ActorCallback)(void *, void *, void *, void *);

typedef struct R10_80171104_S_80171104_1 {
    u8 pad_00[0x1C];
    union { u32 u; s32 s; } unk_1C;   
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    union { u16 u; s16 s; } unk_88;   
} R10_80171104_S_80171104_1;
typedef struct R10_80171104_S_80171104_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R10_80171104_S_80171104_2;
typedef struct R10_80171D7C_S_80171CD4_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   
} R10_80171D7C_S_80171CD4_0;
typedef struct R10_80171D7C_S_80171CD4_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R10_80171D7C_S_80171CD4_4;
typedef struct R10_80172730_S_80172688_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} R10_80172730_S_80172688_1;

typedef struct R10_80172A94_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} R10_80172A94_S_80172628_0;
typedef struct R10_80172C54_S_80172C54_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   
    u8 pad_A0[0x4];
    s32 unk_A4;
} R10_80172C54_S_80172C54_0;

typedef struct R10_80173080_S_80173080_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } timer;   
    u8 pad_98[0x3];
    u8 phase;
} R10_80173080_S_80173080_0;
typedef struct R10_80173080_S_80173080_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R10_80173080_S_80173080_3;
typedef struct R10_80173280_S_80173280_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } timer;   
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 phase;
    u8 pad_9C[0x2];
    u16 unk_9E;
} R10_80173280_S_80173280_0;


typedef struct R10_80173280_S_80173280_6 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} R10_80173280_S_80173280_6;
typedef struct R10_80173280_S_80173280_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} R10_80173280_S_80173280_7;
typedef struct R10_8017380C_S_8017380C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } timer;   
    u8 pad_98[0x3];
    u8 phase;
} R10_8017380C_S_8017380C_0;
typedef struct R10_80173BBC_S_80173D4C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} R10_80173BBC_S_80173D4C_0;


typedef struct R10_80173F4C_S_801740DC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} R10_80173F4C_S_801740DC_0;



typedef struct R10_8017442C_S_801745BC_0_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} R10_8017442C_S_801745BC_0_pre;
typedef struct R10_8017442C_S_801745BC_0 {
    u8 pad_00[0x5C];
    void * unk_5C;
} R10_8017442C_S_801745BC_0;
typedef struct R10_8017442C_S_801745BC_1_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} R10_8017442C_S_801745BC_1_pre;
typedef struct R10_8017442C_S_801745BC_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x14];
    s8 unk_28;
    u8 pad_29[0x33];
    void * unk_5C;
    u8 pad_60[0x4];
    s16 unk_64;
} R10_8017442C_S_801745BC_1;
typedef struct R10_8017442C_S_801745BC_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R10_8017442C_S_801745BC_2;
typedef struct R10_8017442C_S_801745BC_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
} R10_8017442C_S_801745BC_3;
typedef struct R10_8017442C_S_801745BC_4 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x14];
    u16 unk_2A;
} R10_8017442C_S_801745BC_4;
typedef struct R10_8017442C_S_801745BC_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} R10_8017442C_S_801745BC_5;
typedef struct R10_8017442C_OffsetPair {
    s16 x;
    u16 y;
} R10_8017442C_OffsetPair;
typedef struct R10_8017442C_OffsetTable {
    R10_8017442C_OffsetPair entries[8];
} R10_8017442C_OffsetTable;
typedef struct R10_80174670_S_80174800_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R10_80174670_S_80174800_0_pre;
typedef struct R10_80174670_S_80174800_0 {
    u8 pad_00[0x5C];
    void * unk_5C;
} R10_80174670_S_80174800_0;
typedef struct R10_80174670_S_80174800_1_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} R10_80174670_S_80174800_1_pre;
typedef struct R10_80174670_S_80174800_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R10_80174670_S_80174800_2;
typedef struct R10_80174670_S_80174800_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
} R10_80174670_S_80174800_3;
typedef struct R10_80174670_S_80174800_4 {
    u8 pad_00[0x26];
    u8 unk_26;
    u8 pad_27[0x3];
    s16 unk_2A;
    u8 pad_2C[0x58];
    s8 unk_84;
    s8 unk_85;
} R10_80174670_S_80174800_4;
typedef struct R10_80174898_S_80174898_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} R10_80174898_S_80174898_0;
typedef struct R10_80174898_S_80174898_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R10_80174898_S_80174898_1;

typedef struct R10_80174898_OffsetPair {
    s16 x;
    s16 y;
} R10_80174898_OffsetPair;
typedef struct R10_80174898_OffsetTable {
    R10_80174898_OffsetPair entries[8];
} R10_80174898_OffsetTable;
typedef struct R10_80174BE4_Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct R10_80174BE4_Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} R10_80174BE4_Entry;
typedef struct {
    u8 pad[0x13C];
    s32 value;
} R10_80174BE4_Scratchpad;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} R10_80174C70_LocalVector;
typedef struct {
    R10_80174C70_LocalVector vectors[4];
} __attribute__((packed)) R10_80174C70_LocalTable;
typedef struct R10_80174C70_S_80174C70_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    union { s16 s; u16 u; } unk_1A;   
    u8 pad_1C[0x46];
    s16 unk_62;
} R10_80174C70_S_80174C70_0;
typedef struct R10_80174C70_S_80174C70_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    union { s16 s; u16 u; } unk_1A;   
} R10_80174C70_S_80174C70_1;
typedef struct R10_80174C70_S_80174C70_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} R10_80174C70_S_80174C70_2;
typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} R10_80174F24_LocalVector;
typedef struct {
    u32 words[8];
} __attribute__((packed)) R10_80174F24_LocalTable;
typedef struct {
    u32 words[3];
} __attribute__((packed)) R10_80174F24_LocalPacket;
typedef struct R10_80174F24_S_func_80AF3724_0 {
    u8 pad_00[2];
    u16 unk_02;
    u8 pad_04[2];
    u16 unk_06;
    u8 pad_08[2];
    u16 unk_0A;
} R10_80174F24_S_func_80AF3724_0;

typedef struct R10_80174F24_S_func_80AF3724_2 {
    u16 unk_00;
    u16 unk_02;
} R10_80174F24_S_func_80AF3724_2;

typedef struct R10_80174F24_S_func_80AF3724_4 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0xC];
    R10_80174F24_LocalPacket unk_28;
} R10_80174F24_S_func_80AF3724_4;



typedef struct R10_80175398_DungeonCopy3 {
    s32 x;
    s32 y;
    s32 z;
} R10_80175398_DungeonCopy3;
typedef struct R10_80175398_DungeonChild {
    s32 x;
    s32 y;
    s32 z;
} R10_80175398_DungeonChild;
typedef struct R10_80175398_DungeonTail {
    u8 pad0[0x0C];
    u32 color;
    u8 pad10[4];
    u16 flags;
    u8 pad16[6];
    u16 value1c;
    u16 value1e;
} R10_80175398_DungeonTail;
typedef struct R10_80175398_DungeonEffect {
    u8 pad0[8];
    R10_80175398_DungeonChild *child;
    R10_80175398_DungeonTail *tail;
    void *resource;
} R10_80175398_DungeonEffect;
typedef struct R10_80175398_S_80175398_0_pre {
    u16 unk_00;
} R10_80175398_S_80175398_0_pre;
typedef struct R10_80175398_S_80175398_0 {
    u8 pad_00[0x96];
    union { u16 u; s16 s; } timer;   
    u8 pad_98[0x3];
    u8 phase;
    u8 pad_9C[0xC];
    union { void * p; u8 * p2; } unk_A8;   
    s16 unk_AC;
} R10_80175398_S_80175398_0;
typedef struct R10_80175398_S_80175398_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    union { u16 u; s16 s; } unk_2A;   
    u8 pad_2C[0x34];
    u8 * unk_60;
    u8 pad_64[0x9];
    s8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} R10_80175398_S_80175398_1;
typedef struct R10_80175398_S_80175398_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    u8 * unk_0C;
    u32 unk_10;
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
    u8 pad_30[0x78];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} R10_80175398_S_80175398_2;
typedef struct R10_80175398_S_80175398_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} R10_80175398_S_80175398_3;
typedef struct R10_80175398_S_80175398_5_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} R10_80175398_S_80175398_5_pre;
typedef struct R10_80175398_S_80175398_5 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} R10_80175398_S_80175398_5;

typedef struct R10_80175398_S_80175398_7 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} R10_80175398_S_80175398_7;
extern s32 Control_CD();
typedef struct { s16 x; u16 y; } Resource10DirectionOffset;
extern const Resource10DirectionOffset D_80170854[8];
extern const Resource10DirectionOffset D_80170874[8];
s32 RotTransPers(void *vertex, s32 *screen, s32 *p, s32 *flag);
void advance_sprite_animation_and_textures(void *entity);
s32 register_node(ObjectNodeHeader *entry, void *registration_id);
s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
void select_record_entry_and_value(void *state, void *entries, short index);
void * func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
void select_sprite_entry(void *object_data, s16 table_index, s16 entry_index);
void func_80047784(void *object_data, s16 table_index, s16 entry_index);
void apply_monster_koyaw_data(s32 flags, s8 *dst);
s32 refresh_actor_facing_and_lifecycle();
s16 sample_terrain_surface_height();
s32 check_entity_relation();
s32 find_active_rect_containing_point(s32 point_x, s32 point_y);
s16 test_neighbor_position_relation(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y);
s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
s32 can_entity_gain_level(void *entity);
void update_actor_status_and_mp(ActorRecord *entity);
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
void *probe_directional_neighbor(void *entity, s32 x, s32 y, u32 direction);
s16 get_actor_height_difference(ActorRecord *left_record, ActorRecord *right_record);
s16 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
s32 select_actor_route_target(u8 *actor_held, s32 kind, u8 *work_p, u16 *out);
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

s32 rsin(s32);
void on_actor_status_updated(void *actor);
void func_800A9A04(void *actor);
s32 update_linked_actor_motion(void *state, void *transform, void *config, void *object);
void * resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
s32 get_cd_command_queue_depth(void);
void *scan_actor_along_heading();
void *create_actor_spell_effect(void *actor, void *record_data, s16 mode, void *context);
void begin_actor_display_action(void *actor, void *unused, SpriteFrameState *display, u8 *facing_variants);

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
void initialize_timed_motion_step(unsigned short countdown, unsigned int amount);
void spawn_radial_particle_burst();
void project_sprite_commands();
void func_800453E0(void *context, void *position, struct Entry *entry, s16 depth_bias);
s32 rcos(s32);
void unlink_node();
void func_80044A50(struct ObjectNodeHeader *node);
void sound_set_cd_cue_parameters(int value_0, int value_1, int value_2, int value_3);
s32 run_cd_image_commands();
void func_80041588(u32 *stream_ref, u8 *state, s32 execute);
s32 read_stream_cue_start_offset(void);
s32 lookup_masked_byte_table();
void unlink_entity_node(struct EntityLinkNode *node);
void decrement_monster_entry_count(s16 requested_id, s16 requested_type);
s32 advance_staged_entity_load();
s32 create_status_linked_render_effect();
s32 select_nearby_target_and_initialize_slot(void * slot_id,void *target, s32 target_id, s32 slot_value);
s32 resolve_actor_floor_trap_once(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
s32 propagate_actor_action_flag(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern u8 shared_sprite_entries[];
extern u8 snowman_direction_frames[];
extern u8 snowman_alt_direction_frames[];
extern u8 snowman_frame_set_2[];
extern u8 snowman_frame_set[];
extern u8 snowman_frame_set_3[];
extern u8 D_80175A1C[];
extern u8 D_80175998[];
extern u8 D_801759D0[];
extern u8 D_801759E0[];
extern u8 snowman_move_direction_frames[];
extern u8 actor_turn_angle_offsets[];
extern u8 D_801759A8[];
extern u8 snowman_attack_frames[];
extern u8 D_801759C8[];
extern u8 snowman_frame_set_1[];
extern u8 D_801759D8[];
extern u8 D_80175A18[];
extern u8 D_80175A0C[];
extern u8 actor_action_reset_value[];
extern u8 D_80175A84[];
extern u8 resource_completion_callback_address[];
extern u8 cd_cue_base[];
extern u8 actor_effect_color_targets[];
extern u8 staged_spawn_count[];
extern u8 dungeon_resource_buffer[];
extern u8 snowman_image_commands[];
extern u8 D_80175A00[];
extern u8 snowman_image_load_done[];
extern u8 snowman_effect_load_done[];
s32 draw_snowman_point_chain(u8 *node_data, u16 *position);
void move_and_shrink_fading_effect(R10_80170B0C_Actor *actor, R10_80170B0C_Vec3 *vec, struct SpriteFrameState *sprite);
void create_converging_fading_sprite(
    R10_80170CF8_S_80AC55DC_1 *origin, s16 effect_id, s32 effect_value, s16 duration,
    s32 offset_x, s32 offset_y, s32 offset_z);
void *create_actor_with_optional_status(s16 flags, s16 kind_id, s16 variant, s32 spawn_value);
void update_actor_callbacks_animation_and_ground(u8 *actor, u8 *motion, u8 *object);
void update_snowman_behavior(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *sprite_arg, ActorRecord *entity_arg);
void advance_snowman_stored_path(void *movement, void *motion, SpriteFrameState *entity, void *path_state);
void choose_snowman_move(ActorRecord *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data);
void begin_snowman_step_animation(void *actor_state, void *action_state, SpriteFrameState *sprite, void *orientation);
s32 try_snowman_attack(ActorRecord *action_state, ObjectPosition *motion_param, SpriteFrameState *sprite, ActorRecord *actor);
void begin_snowman_attack(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);
s32 relink_snowman_path(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void move_snowman_to_tile(void *entity_arg, void *motion, void *check_arg, void *actor_arg);
void hop_snowman_to_tile(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_snowman_linked_motion(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic);
void advance_timed_attack_animation_and_damage(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void advance_actor_spell_effect_sequence(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *tile_arg, ActorRecord *action);
void displace_actor_then_recenter(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *entity, ActorRecord *actor);
void remove_defeated_snowman(void *state, void *motion, void *position, void *actor);
void shrink_hopping_snowman(void *state, void *motion, void *position, void *actor);
void advance_snowman_removal(void *state, void *motion, void *position, void *actor);
void grow_hopping_snowman(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void advance_snowman_status_action(ActorRecord *action, ObjectPosition *context, SpriteFrameState *sprite_in, ActorRecord *actor_in);
void advance_snowman_mp_action(ActorRecord *actor_in, ObjectPosition *actor_index, SpriteFrameState *target, ActorRecord *entity_in);
void update_snowman_parent_motion(ActorRecord *actor, ObjectPosition *action, SpriteFrameState *entity, ActorRecord *map_object);
void advance_boss_command_stream(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic);
void settle_snowman_on_tile(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void create_positioned_sprite_effect(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void fade_in_snowman(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void resolve_linked_attack_hits_and_particle_bursts(void *node, s32 target_x, s32 target_y, s32 target_height);
void prepare_directional_attacks_for_neighbor_entities(void *node, s32 tile_x, s32 tile_y, s16 target_height);
void select_actor_target_and_advance_status(ActorRecord *action_state, ObjectPosition *effect_arg, SpriteFrameState *anim_state, ActorRecord *actor);
void advance_directional_attack_sequence(ActorRecord *action, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *entity);
s32 project_snowman_sprite_chain(void *initial_payload, s32 entry_data, R10_80174BE4_Entry *entry, s32 unused);
void update_effect_motion_and_brightness(void *effect, void *motion, void *render);
void spawn_randomized_oscillating_effect(s32 unused, R10_80174F24_S_func_80AF3724_0 *origin, void *unused_record, void *unused_actor);
void wait_for_snowman_action_slot(void *entity_data, s32 unused_1, s32 unused_2, void *other_data);
void restore_snowman_scene_tint(u8 *task, void *context, struct SpriteFrameState *input);
void advance_actor_transition_and_restore_facing(void *transition, void *position, struct SpriteFrameState *record, void *actor);
void resolve_snowman_floor_trap(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void propagate_snowman_action_flag(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void finish_snowman_tile_hop(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor);

#endif
