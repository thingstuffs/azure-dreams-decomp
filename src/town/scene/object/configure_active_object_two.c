#include "modules/town_ovl_3fe0d0_p00.h"
#include "town/scene/object.h"

/* Request town sound 0x1700. */
void play_town_sound_1700(void) {
    town_scene_root->services->play_sound(0x1700);
}
