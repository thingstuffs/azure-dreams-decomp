#ifndef DUNGEON_MONSTER_DRAGON_DISPLAY_ORIENTATION_H
#define DUNGEON_MONSTER_DRAGON_DISPLAY_ORIENTATION_H

struct ActorRecord;
struct ObjectPosition;
struct SpriteFrameState;

void copy_display_orientation_state(struct ActorRecord *body, struct ObjectPosition *position, struct SpriteFrameState *sprite, void *orientation);

#endif
