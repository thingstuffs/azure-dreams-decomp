#ifndef INCLUDE_TOWN_DEVKIT_STAGE_DISPATCH_H
#define INCLUDE_TOWN_DEVKIT_STAGE_DISPATCH_H

#include "common.h"

s32 dispatch_scene_stage_if_counter_positive(s32 fallback_result);
s32 set_stage_flag_one_if_ready(s32 fallback_result);
s32 set_stage_flag_two_if_ready(s32 fallback_result);

#endif
