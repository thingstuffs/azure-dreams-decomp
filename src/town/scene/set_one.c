#include "common.h"

extern s32 scene_response_enabled;

/* Sets D_8001C360 to one. */
void set_one(void) {
    scene_response_enabled = 1;
}
