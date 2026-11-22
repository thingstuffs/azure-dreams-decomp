#ifndef ENGINE_SCENE_REMOVAL_COUNTER_H
#define ENGINE_SCENE_REMOVAL_COUNTER_H

#include "common.h"

/* The installed update decrements the first word and tests the value addressed
 * by the second word. The factory writes both through the node's +8 slot. */
typedef struct NodeRemovalCounter {
    s32 count;
    s32 *watched_value;
} NodeRemovalCounter;

void *create_node_with_record_pair(s32 *watched_value, s32 initial_count, unsigned long unused_value);

#endif
