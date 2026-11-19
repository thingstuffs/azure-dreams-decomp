#ifndef INCLUDE_TOWN_MAP_OBJECT_CALLBACK_H
#define INCLUDE_TOWN_MAP_OBJECT_CALLBACK_H

#include "common.h"
#include "town/map/body.h"

typedef struct CallbackEntry CallbackEntry;
typedef s32 (*Callback)(CallbackEntry *);

struct CallbackEntry {
    Callback callback;
    u8 pad[20];
};

struct ObjectPosition;
extern CallbackEntry map_active_callbacks[];

void run_map_object_callback(TownMapBody *object, void *position, void *sprite);


void run_callbacks_unless_suppressed(void *object, struct ObjectPosition *position);
/* Registered code-address alias for run_callbacks_unless_suppressed. */


#endif
