#ifndef DUNGEON_ACTOR_CALLBACK_H
#define DUNGEON_ACTOR_CALLBACK_H

/* Actor +0x8C callbacks receive action, motion, sprite and actor context. */
typedef void (*ActorCallback)(void *, void *, void *, void *);

#endif
