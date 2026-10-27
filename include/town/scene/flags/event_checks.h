#ifndef INCLUDE_TOWN_SCENE_FLAGS_EVENT_CHECKS_H
#define INCLUDE_TOWN_SCENE_FLAGS_EVENT_CHECKS_H

#include "common.h"
#include "records/Rec_func_800165F4_arg0.h"

s32 update_and_test_pending_entry_flags(Rec_func_800165F4_arg0 *kind, s32 value);

s32 check_flag_test_record(void *record);
s32 check_record_flag_if_global_clear(void *record);

#endif
