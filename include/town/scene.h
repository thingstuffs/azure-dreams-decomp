#ifndef TOWN_SCENE_H
#define TOWN_SCENE_H

#include "common.h"


/* process_town_records.c */
void process_town_records(s32 records_addr, s32 record_count);


/* is_next_entry_zero_after_skipping.c */
s32 is_next_entry_zero_after_skipping(s32 list_index);


/* check_progress_against_callback.c */
s32 check_progress_against_callback(void);


/* get_record_value_tier.c */
s32 get_record_value_tier(void);

#endif
