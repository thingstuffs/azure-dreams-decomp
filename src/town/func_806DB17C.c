#include "modules/town_ovl_65b134.h"

s32 check_scene_value_threshold(s32 query_input, s32 query_param) {
    return (u32) D_80016000->unk_38->unk_2D5C >= submit_scene_command_pair(query_input, query_param);
}
