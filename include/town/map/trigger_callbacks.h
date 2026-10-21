#ifndef TOWN_MAP_TRIGGER_CALLBACKS_H
#define TOWN_MAP_TRIGGER_CALLBACKS_H

#include "common.h"

typedef struct map_trigger_record map_trigger_record;
typedef void (*map_trigger_callback_fn)(map_trigger_record *record);

/* The invoker advances six pointer words (0x18 bytes) per record. */
struct map_trigger_record {
    map_trigger_callback_fn handler;
    s16 x;
    s16 y;
    s16 limit_x;
    s16 limit_y;
    s16 reset_limit_x;
    s16 reset_limit_y;
    u16 argument;
    s16 predicate_arg;
    s16 mode;
    u8 pad_16[2];
};

extern map_trigger_record D_800D4668[];
void trigger_entity_action_when_allowed(map_trigger_record *record);
void trigger_action_when_position_limit_exceeded(map_trigger_record *record);

#endif
