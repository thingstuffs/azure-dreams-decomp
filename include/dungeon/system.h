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

s16 get_maximum_sampled_offset_value(s32 base_position, s32 offsets, s32 offset_count);
s32 check_four_vector_half_turn_gaps(s16 x_a, s16 y_a, s16 x_b, s16 y_b, u16 x_c, u16 y_c, u16 x_d, u16 y_d);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
s32 display_text_with_fullwidth_adjustment(s8 *text);

s32 find_and_clear_empty_item_slot(void);
s32 find_last_zero_entry_run_start(void);

#endif
