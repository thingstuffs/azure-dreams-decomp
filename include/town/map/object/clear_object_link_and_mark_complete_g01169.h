#ifndef TOWN_MAP_OBJECT_CLEAR_OBJECT_LINK_AND_MARK_COMPLETE_G01169_H
#define TOWN_MAP_OBJECT_CLEAR_OBJECT_LINK_AND_MARK_COMPLETE_G01169_H
struct LitMeshSprite;
/* Clear object link and mark complete. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_800BDDA8, CL:town/func_800BDE1C. */

#include "common.h"
#include "town/scene/list_setup.h"
#include "shared/object_flags.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 classify_object_against_bounds(void *, struct ObjectPosition *position);
extern void unlink_node_if_registered(void *object);
#include "engine/node.h"
#include "shared/town_object.h"
extern u8 lit_mesh_renderer_address[];
extern u8 D_800D1BDC[];
extern u8 D_800BB640[];
extern u8 D_800BB6C4[];

/* Shared import declarations; data casts preserve each measured view. */


/* Functions defined in this translation unit. */
void retire_object_when_out_of_bounds(TownObjectRecord *object, ObjectPosition *context);
void init_lit_mesh_object(void *object_id, ObjectPosition *object, struct LitMeshSprite *sprite);
void update_spinning_object(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *state);
void update_static_object(TownObjectRecord *object, ObjectPosition *position);
void init_static_object_long_delay(void *object, ObjectPosition *context, struct LitMeshSprite *state);
void init_static_object_short_delay(void *object, ObjectPosition *context, struct LitMeshSprite *state);

#endif
