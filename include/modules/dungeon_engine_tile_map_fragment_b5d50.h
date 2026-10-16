#ifndef MORE_FRAGMENT_B5D50_H
#define MORE_FRAGMENT_B5D50_H
#include "common.h"
struct Node;
extern void * findEligibleActorAtTileAndHeight(struct Node *node, s16 x, s16 y_in, s16 value);
s32 dungeonFindValidNearbyPosition(u8 *entry, s16 x, s16 y, s16 *out_x, s16 *out_y);
#endif
