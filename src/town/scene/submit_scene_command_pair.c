/* Submits a two-byte scene command and compares a stored value with the returned threshold. */
#include "town/scene/submit_scene_command_pair.h"
#include "town/scene.h"


u32 submit_scene_command_pair(s32 unused_query, s32 unused_param) {
    s8 command[2];

    command[1] = 0x17;
    command[0] = 0xA;
    return (u32)town_scene_root->services->callback_050(command);
}

s32 check_scene_value_threshold(s32 query_input, s32 query_param) {
    return (u32) town_scene_root->town_state->money >= submit_scene_command_pair(query_input, query_param);
}
