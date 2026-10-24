#ifndef TOWN_MAP_TRIGGER_CALLBACKS_H
#define TOWN_MAP_TRIGGER_CALLBACKS_H

#include "common.h"

typedef struct map_trigger_record map_trigger_record;
/* Town proximity-trigger callback receiving its own trigger record.
 * The callback-table walker passes the entry address and advances by 0x18 bytes. */
typedef void (*map_trigger_callback_fn)(map_trigger_record *record);

/* The invoker advances six pointer words (0x18 bytes) per record. */
/* One town proximity trigger in the scene callback table, terminated by a null handler.
 * Trigger callbacks replace handler to alternate between entry and reset-distance tests. */
struct map_trigger_record {
    map_trigger_callback_fn handler; /* current trigger callback; null terminates the table */
    s16 x; /* trigger center X, compared with the player position integer half */
    s16 y; /* trigger center Y, compared with the player position integer half */
    s16 limit_x; /* maximum absolute X distance that permits the entry action, in world units */
    s16 limit_y; /* maximum absolute Y distance that permits the entry action, in world units */
    s16 reset_limit_x; /* X distance threshold; exceeding either reset limit re-arms the trigger */
    s16 reset_limit_y; /* Y distance threshold; exceeding either reset limit re-arms the trigger */
    u16 argument; /* SD_Call argument for entry; the reset action ORs it with 0x1000 */
    s16 predicate_arg; /* resident bitmap flag id tested before entering the trigger */
    s16 mode; /* predicate polarity: zero requires the flag set, nonzero requires it clear */
    u8 pad_16[2];
};

extern map_trigger_record town_map_callback_entries[];
void trigger_entity_action_when_allowed(map_trigger_record *record);
void trigger_action_when_position_limit_exceeded(map_trigger_record *record);

#endif
