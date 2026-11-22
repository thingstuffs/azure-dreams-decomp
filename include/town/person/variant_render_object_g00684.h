#ifndef TOWN_PERSON_VARIANT_RENDER_OBJECT_G00684_H
#define TOWN_PERSON_VARIANT_RENDER_OBJECT_G00684_H
/* shared declarations for variant render object. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800CE070, CL:town/func_800CE380, CL:town/func_800CE408, PD:town/engine:800D68B0. */

#include "common.h"
#include "town/person/object_setup.h"
#include "town/scene/list_setup.h"
#include "town/event/object_setup.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082D58.h"
#include "shared/object_payload.h"
#include "shared/vector.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "sdk/libgte.h"
#include "engine/node/allocation.h"
#include "town/person/position.h"
#include "engine/node.h"

typedef struct TownVariantSpriteBody {
    u8 pad_00[0x60];
    s32 slot;
    u8 pad_64[0x38];
    TownObjectRecord *owner;
} TownVariantSpriteBody;

/* extern */

/* arg1 in update_entity_relative_position */

/* ((Rec_D_80082D58 *)arg0)->unk_9C in update_entity_relative_position */
typedef struct S_800CB9B8_6 {
    u8 pad_00[0x3];
    s8 unk_03;
} S_800CB9B8_6;

typedef struct S_800CBAAC_0 {
    u8 pad_00[0x50];
    void (*unk_50)(void *, void *, ObjectPosition *, SpriteFrameState *);
} S_800CBAAC_0;

struct Rec_D_800CFCB4;

/* extern */
struct Rec_D_80082E80;

struct IntVector3;

/* extern (function symbol used as callback) */
/* extern */

void unlink_node_if_registered(void *block_data);
/* extern */
/* extern */
void clear_object_slot_and_mark_removed(void *);
s32 is_default_object_data(TownObjectRecord *);
/* extern */
extern void D_800CBAAC(S_800CBAAC_0 *, ObjectPosition *, SpriteFrameState *);

extern void *D_800D68B0[];

/* Functions defined in this translation unit. */
void update_entity_relative_position(TownVariantSpriteBody *entity, struct ObjectPosition *out_pos);
void invoke_object_handler(S_800CBAAC_0 *object, ObjectPosition *position, SpriteFrameState *sprite);
void allocate_variant_object(s32 variant, s32 x, s32 y);

#endif
