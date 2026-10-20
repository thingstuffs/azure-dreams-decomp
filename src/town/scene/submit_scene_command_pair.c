#include "town/scene/submit_scene_command_pair.h"
#include "town/scene/submit_scene_command_pair.h"

u32 submit_scene_command_pair(s32 unused_query, s32 unused_param) {
    s8 command[2];

    command[1] = 0x17;
    command[0] = 0xA;
    return (u32)D_80016000->unk_20->callback_050(command);
}
#include "town/scene/submit_scene_command_pair.h"

s32 check_scene_value_threshold(s32 query_input, s32 query_param) {
    return (u32) D_80016000->unk_38->unk_2D5C >= submit_scene_command_pair(query_input, query_param);
}
