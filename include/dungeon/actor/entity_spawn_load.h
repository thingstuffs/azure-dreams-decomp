#ifndef DUNGEON_ACTOR_ENTITY_SPAWN_LOAD_H
#define DUNGEON_ACTOR_ENTITY_SPAWN_LOAD_H
/* Select dungeon spawn tiles and advance staged entity loading. */

#include "common.h"
#include "dungeon/item/monster_resource_slots_g00325.h"
#include "shared/dungeon_floor.h"
#include "shared/slus_cd_callback.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_effect_status.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "dungeon/item/actor_target.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct DungeonArea {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 unk8;
    s16 enabled;
    u8 pad[8];
} DungeonArea;

typedef struct DungeonState {
    u8 pad0[0xA];
    s16 count;
} DungeonState;

typedef struct EntityCopyBlock {
    s32 words[4];
} EntityCopyBlock;

typedef struct EntityCopyTail {
    s32 words[3];
} EntityCopyTail;

typedef struct Table4Entry {
    u8 value;
    u8 pad[3];
} Table4Entry;

typedef struct Table84Entry {
    u8 value;
    u8 pad[0x53];
} Table84Entry;

typedef struct TablePage {
    u8 pad0[0x980];
    Table4Entry table4[64];
    u8 gap[0x13];
    Table84Entry table84[64];
} TablePage;

typedef MonsterFactory SpawnFunc;

typedef struct S_800A504C_0 {
    u8 pad_00[0xA];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x80];
    s32 unk_8C;
    s32 unk_90;
    u16 unk_94;
    u8 pad_96[0x2];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_800A504C_0;

/* base in advance_staged_entity_load */
typedef struct S_800A504C_1_pre {
    u8 * unk_00;
    u8 pad_04[0xE];
    u16 unk_12;
} S_800A504C_1_pre;

/* the 0x14 bytes before entity in advance_staged_entity_load, addressed as entity[-1] */
typedef struct S_800A504C_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
    u8 pad_8A[0x6];
    s32 unk_90;
} S_800A504C_1;

/* entity in advance_staged_entity_load */
typedef struct S_800A504C_2_pre {
    s16 unk_00;
    u8 pad_02[0x30A0];
} S_800A504C_2_pre;

/* the 0x30A2 bytes before role1 in advance_staged_entity_load, addressed as role1[-1] */
typedef struct S_800A504C_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_800A504C_2;

/* role1 in advance_staged_entity_load */
typedef struct S_800A504C_3 {
    u8 pad_00[0x58];
    s32 unk_58;
    s32 unk_5C;
    u8 pad_60[0x2C];
    s32 unk_8C;
    s32 unk_90;
    u16 unk_94;
    u8 pad_96[0x2];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_800A504C_3;

/* tail_dst in advance_staged_entity_load */
typedef struct S_800A504C_4_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_800A504C_4_pre;

/* the 0x14 bytes before spawned in advance_staged_entity_load, addressed as spawned[-1] */
typedef struct S_800A504C_4 {
    u8 pad_00[0x10];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_10;   /* overlapping accesses */
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x23];
    u8 unk_43;
    u8 pad_44[0x8];
    s32 unk_4C;
    s32 unk_50;
    u8 pad_54[0x4];
    s32 unk_58;
    s32 unk_5C;
} S_800A504C_4;

/* spawned in advance_staged_entity_load */
typedef struct S_800A504C_5 {
    u8 pad_00[0xAC];
    u8 * unk_AC;
    u8 pad_B0[0x20];
    u8 * unk_D0;
} S_800A504C_5;

/* record in advance_staged_entity_load */
typedef struct S_800A504C_6 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800A504C_6;

/* global_page in advance_staged_entity_load */
typedef struct S_800A504C_7_pre {
    s16 unk_00;
    u8 pad_02[0x30A0];
} S_800A504C_7_pre;

s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
extern s32 generate_random_value(void);
extern s16 floor_generation_state[3];
/* the 0x30A2 bytes before D_800E0000 in advance_staged_entity_load, addressed as D_800E0000[-1] */
extern s32 func_8003E188();
extern s32 Control_CD();
extern s32 has_enough_available_runtime_nodes(s32 limit);
extern s32 apply_actor_template_and_class();
extern s32 replay_actor_status_slots();
extern s32 func_80042640();
extern s32 copy_entity_record();
#include "engine/node.h"
extern void select_indirect_table_entry(void *state_data, s16 table_index, s16 entry_index);
extern s32 queue_cd_resource();
extern s32 func_80047E30();
extern s32 register_and_upload_sprite_resource();
extern s32 begin_sprite_resource_load_with_completion_flag();
extern s32 read_sound_mode_blocking_status(s32 mode);
struct EntityLinkNode;
void unlink_entity_node(struct EntityLinkNode *node);
extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern u8 * find_or_retain_sprite_resource_slot(s32 requested_id, s32 requested_type);
extern u8 D_80023000[];
extern u8 *sprite_resource_base;
extern s32 loaded_entity_sprite_resource;
extern u8 sprite_resource_completion_flag[];
extern u8 familiar_record_slots[];
extern u8 entity_resource_read_complete[];
#include "shared/dungeon_image_buffer.h"
extern u8 D_800E0000[];

/* Functions defined in this translation unit. */
s32 select_dungeon_spawn_tile(u8 *x_out, u8 *y_out);
s32 advance_staged_entity_load(s32 unused, u8 *entity);

#endif
