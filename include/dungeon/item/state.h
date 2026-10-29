#ifndef DUNGEON_ITEM_STATE_H
#define DUNGEON_ITEM_STATE_H
/* Prototypes of the functions defined in src/dungeon/item/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/dungeon_item_entries.h"

/* apply_item_and_update_matching_actor_state.c */
s32 apply_item_and_update_matching_actor_state(void *entity, DungeonItemEntry *action_id, s16 action_arg);

/* create_timed_region_flag_expiry.c */
void *create_timed_region_flag_expiry(s32 unused0, s32 unused1, s32 unused2, s16 payloadValueA, s16 payloadValueC);

/* set_monster_reachability_flag.c */
s32 set_monster_reachability_flag(void);

/* tick_region_flag_expiry.c */
void tick_region_flag_expiry(void *state);

/* update_actor_proximity_flag.c */
s32 update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);

/* write_status_prefix_bytes.c */
void *write_status_prefix_bytes(void *dst);

#endif
