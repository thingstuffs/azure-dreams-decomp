#ifndef INCLUDE_TOWN_SCENE_MILESTONE_REWARDS_H
#define INCLUDE_TOWN_SCENE_MILESTONE_REWARDS_H

#include "common.h"

extern s16 milestone_flag_ids[];
extern void *milestone_response_table[][5];

void *award_next_unearned_milestone(s32 counter_id);
char *select_response_selector_status_flags(long long unused, s32 selection);

#endif
