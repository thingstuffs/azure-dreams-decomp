#include "shared/record_ptrs.h"
#include "shared/town_root.h"

void play_event08_and_09_sound_d1(void) {
    town_scene_root->services->play_sound(0xD1);
}
