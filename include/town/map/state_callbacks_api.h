#ifndef TOWN_MAP_STATE_CALLBACKS_API_H
#define TOWN_MAP_STATE_CALLBACKS_API_H

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct town_inactive_object;
struct SpriteFrameState;
void spin_object_until_flag_clears(struct town_inactive_object *obj, void *unused, struct SpriteFrameState *sprite);

#endif
