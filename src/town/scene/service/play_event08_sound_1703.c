#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

void play_event08_sound_1703(void)
{
    town_scene_root->services->play_sound(0x1703);
}
