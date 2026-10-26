#ifndef DUNGEON_EFFECT_ENTITY_SPRITE_INITIALIZATION_G00339_H
#define DUNGEON_EFFECT_ENTITY_SPRITE_INITIALIZATION_G00339_H
#include "dungeon/level.h"


struct ObjectNodeHeader;
struct SpriteFrameState;
/* Entity sprite initialization shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800ACB90. */

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"

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
    void (*unk_10)();
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
extern void clear_entry_flag_and_link_owner(struct ObjectNodeHeader *);
extern void create_tracked_effect(void *, s32, void *, void *);
/* (void *)reg_s3 in create_mode_configured_object */
extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern s32 scene_object_list_anchor;
extern void D_800B274C();
extern void slow_target_action_callback();

/* Functions defined in this translation unit. */
void initialize_entity_sprite_effect(void *entity, EntityRec *position,struct SpriteFrameState *sprite, s16 unused);

#endif
