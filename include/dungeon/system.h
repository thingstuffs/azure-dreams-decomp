#ifndef DUNGEON_SYSTEM_H
#define DUNGEON_SYSTEM_H

/* Function contracts owned by src/dungeon/system/ (decision 74; maintained by tools/headers). */
#include "common.h"
s32 check_action_available_without_nearby_actor(void);
void clear_pending_item_action_state(void);
void * create_expanding_screen_rectangle(void);
void *create_fullscreen_quad_updater(s16 initialValue);
void decrement_bounded_counter(void);
void display_fixed_item_action_message(void);
struct DungeonItemEntry;
void display_item_status_message(void *entity, struct DungeonItemEntry *item, s32 message_kind);
void display_actor_item_status_message(void *actor, struct DungeonItemEntry *item);
s32 increment_bounded_counter(void);
void restore_dungeon_random_seed(s32 saved_seed);
void restore_item_flag_400_bitmap(void);
void store_unique_text_record(char *text, s32 type, s32 value);


/* dungeon/system/util.c */
s32 play_sound_if_enabled(s32 query_value);

/* dungeon/system/util.c */
void place_actor_item(void *object_context, struct DungeonItemEntry *target);

#endif
