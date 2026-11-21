#include "common.h"
#include "slus/gp_d92c_owned.h"
#include "town/scene.h"

/* set_no_change_seq: sets the flag that prevents sequence changes. */
void set_no_change_seq(void) {
    scene_music_hold = 1;
}
