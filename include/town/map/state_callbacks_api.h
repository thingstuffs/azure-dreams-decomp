#ifndef TOWN_MAP_STATE_CALLBACKS_API_H
#define TOWN_MAP_STATE_CALLBACKS_API_H

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct town_inactive_object;
struct town_inactive_state;
void update_inactive_object_state(struct town_inactive_object *obj, void *unused, struct town_inactive_state *state);

#endif
