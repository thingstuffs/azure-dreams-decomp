#ifndef TOWN_MENU_OBJECT_CREATE_POSITIONED_SPRITE_OBJECT_G01142_H
#define TOWN_MENU_OBJECT_CREATE_POSITIONED_SPRITE_OBJECT_G01142_H
/* Create positioned sprite object. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01142 - CL:town/func_800A9BA8. */

#include "common.h"
#include "shared/sprite_source.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/vector.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082D58.h"
#include "town/person/position.h"

struct EmoteCallbackObject;

/* Body shared by the positioned-emote creator and callback dispatcher. */
typedef struct EmoteCallbackObject {
    /* 0x00 */ u8 pad_00[0x50];
    /* 0x50 */ s32 (*callback)(struct EmoteCallbackObject *, void *, s32);
    /* 0x54 */ s32 state_value;
    /* 0x58 */ u8 pad_58[0x38];
    /* 0x90 */ s16 frame;
} EmoteCallbackObject;


typedef struct S_800A71F0_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800A71F0_3;


struct Dst;

struct Elem;

struct ObjectNodeHeader;



typedef struct S_800A7360_1 {
    u8 pad_00[0x50];
    void (*unk_50)(void *, void *, s32);
} S_800A7360_1;

typedef void (*S_800A9C80_Callback)(void *, void *, s32);

void select_record_entry_and_value(void *state,void *entries, short index);
void * allocate_list_node(s32, struct ObjectNodeHeader * *);
extern s32 D_800D0DF0;
extern void D_800A7360();
extern s32 D_800D0DF8[];
extern void unlink_node_if_registered(void *);

/* Shared import declarations; data casts preserve each measured view. */

/* Functions defined in this translation unit. */
ObjectNodeHeader *create_positioned_sprite_object(IntVector3 *position, s32 state_value, SpriteSourceEntry *graphic_id);
ObjectNodeHeader *create_preset_sprite_object(IntVector3 *position);
void copy_indexed_motion_value_and_advance(Rec_D_80082D58 *object, EntityRec *output, s32 unused);
void invoke_emote_object_callback(EmoteCallbackObject *object, void *motion, s32 context);
void advance_emote_motion(S_800A7360_1 *object, EntityRec *motion);
void advance_position_and_handle_ground_contact(void *entity, void *motion, s32 context);

#endif
