#ifndef TOWN_SCENE_FLAGS_H
#define TOWN_SCENE_FLAGS_H

#include "common.h"


/* clear_referenced_object_active_flag.c */
void clear_referenced_object_active_flag(void);


/* set_referenced_object_active_flag.c */
void set_referenced_object_active_flag(void);


/* clear_indexed_flag_bit_unless_index_one.c */
void clear_indexed_flag_bit_unless_index_one(s32 bit_index);


/* update_flag_test_target.c */
void update_flag_test_target(s16 sourceId, s16 targetId);


/* set_indexed_flag_bit.c */
void set_indexed_flag_bit(s32 flag_id);

/* Callback entry points. */
void clear_global_entry_flag(void);
void fade_panel_after_linked_flag(void *effect);

void update_dependent_entry_ids(s16 checked_id, s16 first_id, s16 second_id);

#endif
