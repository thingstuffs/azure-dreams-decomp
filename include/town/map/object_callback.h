#ifndef INCLUDE_TOWN_MAP_OBJECT_CALLBACK_H
#define INCLUDE_TOWN_MAP_OBJECT_CALLBACK_H

#include "common.h"

struct S_8008B9D8_0;
void run_map_object_callback(struct S_8008B9D8_0 *object, void *position, void *sprite);


void run_callbacks_unless_suppressed(void *object, void *check_data);
/* Registered code-address alias for run_callbacks_unless_suppressed. */
void map_active_node_key(void *object, void *check_data);

#endif
