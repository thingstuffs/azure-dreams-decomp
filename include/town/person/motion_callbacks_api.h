#ifndef TOWN_PERSON_MOTION_CALLBACKS_API_H
#define TOWN_PERSON_MOTION_CALLBACKS_API_H

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct town_offset_target_object;
struct town_offset_target_position;
void move_toward_offset_target(struct town_offset_target_object *object, struct town_offset_target_position *position, void *finish_arg);

#endif
