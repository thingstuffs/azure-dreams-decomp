#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene.h"


/* Set the speech balloon with settings (1, 1, 0, 0x1E). */
void set_speech_balloon_preset_b(void) {
    town_scene_root->services->callback_278(1, 1, 0, 0x1E);
}
