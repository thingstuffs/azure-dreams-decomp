#include "common.h"

extern s32 scene_choice_index;

/* Returns whether D_80019BB4 equals 6. */
s32 get_equals_6(void) {
    return scene_choice_index == 6;
}
