#include "common.h"

extern s8 scene_music_hold;

/* set_no_change_seq: sets the flag that prevents sequence changes. */
void set_no_change_seq(void) {
    scene_music_hold = 1;
}
