#ifndef INCLUDE_TOWN_MAP_OBJECT_CALLBACK_H
#define INCLUDE_TOWN_MAP_OBJECT_CALLBACK_H

#include "common.h"
#include "town/map/body.h"

void run_map_object_callback(TownMapBody *object, void *position, void *sprite);


void run_callbacks_unless_suppressed(void *object, void *check_data);
/* Registered code-address alias for run_callbacks_unless_suppressed. */


#endif
