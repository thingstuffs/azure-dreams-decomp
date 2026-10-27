#ifndef INCLUDE_TOWN_SCENE_RECORD_QUERIES_H
#define INCLUDE_TOWN_SCENE_RECORD_QUERIES_H

#include "common.h"

s32 town_table_contains_first_byte(s32 target_value);
s32 town_table_contains_first_byte_b(s32 target_value);
s32 town_table_contains_first_byte_c(s32 target_value);
s32 town_table_contains_first_byte_d(s32 target_value);
s32 test_town_counter_threshold(void);
s32 test_town_counter_threshold_b(void);

s32 get_current_nested_record_value(void);
s32 func_8001A220(void);

#endif
