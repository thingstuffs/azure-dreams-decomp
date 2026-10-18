#include "modules/town_ovl_65b134.h"

u32 submit_scene_command_pair(s32 unused_query, s32 unused_param) {
    s8 command[2];

    command[1] = 0x17;
    command[0] = 0xA;
    return (u32)D_80016000->unk_20->callback_050(command);
}
