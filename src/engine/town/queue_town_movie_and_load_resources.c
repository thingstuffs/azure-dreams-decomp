#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/graphics.h"
#include "engine/movie.h"
#include "engine/scene.h"
#include "engine/town.h"
#include "slus.h"
#include "slus/data.h"

extern MovieListNode town_movie_callback_list;

/* Append the runtime entry, copy two VRAM strips, and run the associated updates. */
void queue_town_movie_and_load_resources(void) {
    append_list_tail(&town_movie_callback_list, &town_movie_resource_descriptor);
    move_vram_rect(0, 0x1F2, 0x10, 1, 0x90, 0x1F2);
    move_vram_rect(0x80, 0x1F2, 0x10, 1, 0, 0x1F2);
    file_load_com(town_movie_primary_resource);
    file_load_com(town_movie_secondary_resource);
    load_bin_nametwin();
    load_shared_resource_once();
}
