#include "shared/entity.h"
#ifndef TOWN_MENU_OBJECT_ALLOCATE_AND_INITIALIZE_DISPLAY_OBJECT_G01137_H
#define TOWN_MENU_OBJECT_ALLOCATE_AND_INITIALIZE_DISPLAY_OBJECT_G01137_H
#include "town/menu/object.h"
struct LitMeshSprite;
struct TownObjectRecord;
#include "engine/node/registration.h"

/* Allocate and initialize display object. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_800A48A0. */

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"
#include "shared/vector.h"
struct ObjectNodeHeader;

/* payload in allocate_and_initialize_display_object */
extern void *allocate_list_node();
extern void D_800A2180(DoorDisplayBody *, ObjectPosition *, struct LitMeshSprite *);
extern void D_800A21EC(DoorDisplayBody *, ObjectPosition *, struct LitMeshSprite *);
/* arg0 in initialize_directional_object_state */
extern u8 lit_mesh_renderer_address[];
extern s32 D_800A2338;
extern s32 D_800A23D0;

/* Shared import declarations; data casts preserve each measured view. */

/* Functions defined in this translation unit. */
struct ObjectNodeHeader *allocate_and_initialize_display_object(struct TownObjectRecord *owner, u8 *active_flag, ObjectPosition *origin, s32 part_index, DoorDisplayCallback update,
    DoorDisplayCallback initialize);
void run_callback_until_state_clears(DoorDisplayBody *object, ObjectPosition *position, struct LitMeshSprite *mesh);
void initialize_directional_object_state(DoorDisplayBody *object, ObjectPosition *placement, struct LitMeshSprite *state);
void copy_directional_value(DoorDisplayBody *object, ObjectPosition *unused, struct LitMeshSprite *mesh);

#endif
