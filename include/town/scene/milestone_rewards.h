#ifndef INCLUDE_TOWN_SCENE_MILESTONE_REWARDS_H
#define INCLUDE_TOWN_SCENE_MILESTONE_REWARDS_H

#include "common.h"

extern s16 milestone_flag_ids[];
extern void *milestone_response_table[][5];

void *award_next_unearned_milestone(s32 counter_id);
s32 get_cycled_four_entry_value(void);
void *select_response_and_set_sbs32_flags(void);
void get_local_global_table(void);
extern void *scene_event_results[];
char *select_response_selector_status_flags(long long unused, s32 selection);

#endif
