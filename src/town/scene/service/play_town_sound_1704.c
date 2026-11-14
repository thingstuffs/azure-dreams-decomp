#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/service.h"

/* Request town sound 0x1704. */
void play_town_sound_1704(void) {
    town_scene_root->services->play_sound(0x1704);
}
