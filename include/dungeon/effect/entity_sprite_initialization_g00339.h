#ifndef DUNGEON_EFFECT_ENTITY_SPRITE_INITIALIZATION_G00339_H
#define DUNGEON_EFFECT_ENTITY_SPRITE_INITIALIZATION_G00339_H
/* Entity sprite initialization shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800ACB90. */

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"

typedef struct S_800B22F0_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800B22F0_0;

/* arg2 in initialize_entity_sprite_effect */
typedef struct S_800B22F0_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x51];
    u8 unk_71;
    u8 pad_72[0x16];
    s16 unk_88;
    u8 pad_8A[0x23];
    u8 unk_AD;
} S_800B22F0_1;

typedef s32 M2C_UNK;

typedef struct S_800B23F8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800B23F8_0;

/* obj in create_mode_configured_object */
typedef struct S_800B23F8_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_800B23F8_1;

/* work in create_mode_configured_object */
typedef struct S_800B23F8_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800B23F8_2;

/* part_a in create_mode_configured_object */
typedef struct S_800B23F8_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_800B23F8_4;

/* state in initialize_entity_sprite_effect */
extern s8 find_active_rect_containing_point(u8, u8);
extern void set_record_integer_tile_center(void *, u8, u8);
extern s16 sample_terrain_surface_height(u16, u16, s16);
extern void clear_entry_flag_and_link_owner(void *);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void create_tracked_effect(void *, s32, void *, void *);
/* (void *)reg_s3 in create_mode_configured_object */
extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern s32 D_80083498;
extern M2C_UNK D_800B274C;
extern M2C_UNK D_800B2A60;

/* Functions defined in this translation unit. */
void initialize_entity_sprite_effect(void *entity, EntityRec *position, void *sprite, s16 unused);
void *create_mode_configured_object(s16 mode, s32 part_b_byte_24, s32 part_b_byte_25, s32 part_a_value, s32 part_b_value);

#endif
