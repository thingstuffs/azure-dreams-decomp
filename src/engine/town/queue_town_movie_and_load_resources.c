#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void move_vram_rect(); /* extern */
void append_town_movie_list_node();        /* extern */
void file_load_com(void *packed_data);                   /* extern */
void load_shared_resource_once(void);                            /* extern */
void load_bin_nametwin(void);                            /* extern */
extern M2C_UNK town_movie_resource_descriptor;
extern M2C_UNK town_movie_callback_list;
extern M2C_UNK town_movie_primary_resource;
extern M2C_UNK town_movie_secondary_resource;

/* Append the runtime entry, copy two VRAM strips, and run the associated updates. */
void queue_town_movie_and_load_resources(void) {
    append_town_movie_list_node(&town_movie_callback_list, &town_movie_resource_descriptor);
    move_vram_rect(0, 0x1F2, 0x10, 1, 0x90, 0x1F2);
    move_vram_rect(0x80, 0x1F2, 0x10, 1, 0, 0x1F2);
    file_load_com(&town_movie_primary_resource);
    file_load_com(&town_movie_secondary_resource);
    load_bin_nametwin();
    load_shared_resource_once();
}
