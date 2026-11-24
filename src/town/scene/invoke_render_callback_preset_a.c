#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene.h"


/* Set the speech balloon with settings (1, 2, 0, 0x50). */
void set_speech_balloon_preset_a(void) {
    town_scene_root->services->callback_278(1, 2, 0, 0x50);
}
