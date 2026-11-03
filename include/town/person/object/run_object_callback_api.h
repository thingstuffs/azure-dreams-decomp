#ifndef TOWN_PERSON_OBJECT_RUN_OBJECT_CALLBACK_API_H
#define TOWN_PERSON_OBJECT_RUN_OBJECT_CALLBACK_API_H

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct ObjectPosition;
struct SpriteFrameState;
struct TownObjectRecord;
void run_object_callback(struct TownObjectRecord *object, struct ObjectPosition *context, struct SpriteFrameState *record);

#endif
