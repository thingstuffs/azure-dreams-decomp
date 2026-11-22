#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

void load_event08_sound_sequence_28_mode_200(void)
{
    town_scene_root->services->callback_238(0x28, 0x200);
}
