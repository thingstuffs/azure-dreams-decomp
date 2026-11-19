#ifndef TOWN_PERSON_MOTION_CALLBACKS_API_H
#define TOWN_PERSON_MOTION_CALLBACKS_API_H

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct ObjectPosition;
struct TownObjectRecord;
struct SpriteFrameState;
void move_toward_offset_target(struct TownObjectRecord *object, struct ObjectPosition *position, struct SpriteFrameState *finish_arg);

#endif
