#ifndef DUNGEON_EFFECT_MESH_CALLBACKS_API_H
#define DUNGEON_EFFECT_MESH_CALLBACKS_API_H

#include "common.h"

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct ObjectPosition;
struct PointRecord;
struct dungeon_mesh_chain_payload;
s32 draw_linked_brightness_points(struct PointRecord *start_node, struct ObjectPosition *start_coords);
int draw_linked_mesh_chain(void *body, struct ObjectPosition *value, struct dungeon_mesh_chain_payload *payload);

void raise_entity_to_ground(struct PointRecord *state, struct ObjectPosition *position);

#endif
