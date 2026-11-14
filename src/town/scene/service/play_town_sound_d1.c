#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/service.h"

void play_town_sound_d1(void) {
    town_scene_root->services->play_sound(0xD1);
}
