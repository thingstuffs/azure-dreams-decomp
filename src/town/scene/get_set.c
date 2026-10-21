#include "common.h"

extern s32 scene_choice_index;

/* Returns whether D_80019BB4 is set to 1. */
s32 get_set_1(void) {
    return scene_choice_index == 1;
}
