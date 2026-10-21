#include "common.h"

extern s32 scene_choice_index;

/* Returns whether D_80019BB4 equals 3. */
s32 get_equals_3(void) {
    return scene_choice_index == 3;
}
