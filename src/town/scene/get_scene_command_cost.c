/* Submits a two-byte scene command and compares a stored value with the returned threshold. */
#include "town/scene/get_scene_command_cost.h"
#include "town/scene.h"


u32 get_scene_command_cost(s32 unused_query, s32 unused_param) {
    s8 command[2];

    command[1] = 0x17;
    command[0] = 0xA;
    return (u32)town_scene_root->services->callback_050(command);
}

s32 can_afford_scene_command(s32 query_input, s32 query_param) {
    return (u32) town_scene_root->town_state->money >= get_scene_command_cost(query_input, query_param);
}
