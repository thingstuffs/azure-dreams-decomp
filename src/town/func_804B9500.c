#include "common.h"

extern s32 select_scene_choice_by_mode(s32, s32);
s32 check_scene_selection_result_present(s32 arg0, s32 arg1) { return (select_scene_choice_by_mode(arg0, arg1) != -1); }
