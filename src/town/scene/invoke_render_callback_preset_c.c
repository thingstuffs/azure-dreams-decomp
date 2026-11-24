#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"

/* Set the speech balloon with settings (10, 1, 0, 15). */
void set_speech_balloon_preset_c(void) {
    town_scene_root->services->callback_278(10, 1, 0, 15);
}
