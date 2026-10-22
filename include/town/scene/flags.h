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

#endif
