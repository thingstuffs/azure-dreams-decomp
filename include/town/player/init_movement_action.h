#ifndef TOWN_PLAYER_INIT_MOVEMENT_ACTION_H
#define TOWN_PLAYER_INIT_MOVEMENT_ACTION_H

struct ObjectPosition;

struct TownObjectRecord;
struct SpriteFrameState;

void init_movement_action(struct TownObjectRecord *record, struct ObjectPosition *unused, struct SpriteFrameState *sprite);

#endif
