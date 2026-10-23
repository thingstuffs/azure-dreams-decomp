#ifndef TOWN_MENU_OBJECT_CREATE_POSITIONED_SPRITE_OBJECT_G01142_H
#define TOWN_MENU_OBJECT_CREATE_POSITIONED_SPRITE_OBJECT_G01142_H
/* Create positioned sprite object. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01142 - CL:town/func_800A9BA8. */

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/vector.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082D58.h"



typedef struct S_800A71F0_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800A71F0_3;

typedef struct S_800A71F0_4 {
    u8 pad_00[0x54];
    s32 unk_54;
    u8 pad_58[0x38];
    s16 unk_90;
} S_800A71F0_4;

struct Dst;

struct Elem;

struct ObjectNodeHeader;

struct S_800A7338_0;

typedef struct S_800A7338_0 {
    u8 pad_00[0x50];
    s32 (*unk_50)(struct S_800A7338_0 *, void *, s32);
} S_800A7338_0;

typedef struct S_800A7360_1 {
    u8 pad_00[0x50];
    s32 * unk_50;
} S_800A7360_1;

typedef void (*S_800A9C80_Callback)(void *, void *, s32);

void register_node_if_unregistered(void *block_data, s32 registration_id);
void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index);
void * allocate_list_node(s32, struct ObjectNodeHeader * *);
extern s32 D_800D0DF0;
extern void D_800A7360();
extern s32 D_800D0DF8[];
extern s16 query_lowered_transform_position();
extern void unlink_node_if_registered(void *);

/* Shared import declarations; data casts preserve each measured view. */
extern void add_hex_20000_s_signed_offset_hex_14(void *record);

/* Functions defined in this translation unit. */
s32 create_positioned_sprite_object(IntVector3 *position, s32 state_value, s32 graphic_id);
void copy_indexed_motion_value_and_advance(Rec_D_80082D58 *object, EntityRec *output, s32 unused);
void invoke_emote_object_callback(S_800A7338_0 *object, void *motion, s32 context);
void advance_emote_motion(S_800A7360_1 *object, EntityRec *motion);
void advance_position_and_handle_ground_contact(void *entity, void *motion, s32 context);

#endif
