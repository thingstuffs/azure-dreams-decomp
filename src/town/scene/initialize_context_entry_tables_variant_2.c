#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"

/* Request town sound 0xB1. */
void play_town_sound_b1(void) {
    town_scene_root->services->play_sound(0xB1);
}
