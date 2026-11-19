#ifndef TOWN_MENU_POSITION_CALLBACKS_API_H
#define TOWN_MENU_POSITION_CALLBACKS_API_H
#include "town/menu/object.h"
struct LitMeshSprite;
#include "shared/entity.h"
#include "common.h"

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void initialize_lit_mesh_object_with_phase(DoorDisplayBody *object, ObjectPosition *position, struct LitMeshSprite *state);

struct S_func_800AA760_0;
void follow_linked_position_or_retire(struct S_func_800AA760_0 *object, ObjectPosition *position);

#endif
