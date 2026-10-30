#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/cd.h"
#include "engine/scene.h"
#include "slus.h"
#include "slus/data.h"

/* Read the movie overlay code (the first read descriptor) from disc once and mark it loaded. */
void load_movie_overlay_once(void) {
    if (movie_overlay_loaded == 0) {
        Control_CD(6, resource_read_descriptors, 0);
        drain_cd_command_queue();
        movie_overlay_loaded = 1;
    }
}
