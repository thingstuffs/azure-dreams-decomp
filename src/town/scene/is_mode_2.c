#include "common.h"

extern s32 scene_choice_index;

/* Returns whether D_80019BB4 is 2. */
s32 get_2(void) {
    return scene_choice_index == 2;
}
