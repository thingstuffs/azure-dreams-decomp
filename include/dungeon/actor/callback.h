#ifndef DUNGEON_ACTOR_CALLBACK_H
#define DUNGEON_ACTOR_CALLBACK_H

/* Actor +0x8C callbacks receive action, motion, sprite and actor context. */
typedef void (*ActorCallback)(void *, void *, void *, void *);

struct ActorRecord;
struct ObjectPosition;
struct SpriteFrameState;

/* Movement entry points called by monster action dispatchers. */
void select_zu_movement(struct ActorRecord *move_data, struct ObjectPosition *context, struct SpriteFrameState *position_data, struct ActorRecord *actor_data);
void advance_stored_entity_path(struct ActorRecord *body, struct ObjectPosition *position, struct SpriteFrameState *sprite, struct ActorRecord *actor);

#endif
