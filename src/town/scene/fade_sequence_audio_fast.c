#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"

/* Request town sound 0xB1. */
void fade_sequence_audio_fast(void) {
    town_scene_root->services->play_sound(0xB1);
}
