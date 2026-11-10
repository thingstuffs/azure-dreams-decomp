#ifndef DUNGEON_ITEM_GET_ACTOR_HEIGHT_DIFFERENCE_API_H
#define DUNGEON_ITEM_GET_ACTOR_HEIGHT_DIFFERENCE_API_H

#include "common.h"

struct ActorRecord;
s16 get_actor_height_difference(struct ActorRecord *left_record, struct ActorRecord *right_record);

#endif
