#ifndef DUNGEON_MONSTER_GRINEUT_PATH_MOTION_H
#define DUNGEON_MONSTER_GRINEUT_PATH_MOTION_H

struct ActorRecord;
struct ObjectPosition;
struct SpriteFrameState;

void advance_grineut_stored_path(struct ActorRecord *action, struct ObjectPosition *action_id, struct SpriteFrameState *entity, struct ActorRecord *move_state);

#endif
