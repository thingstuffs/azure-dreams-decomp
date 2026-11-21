#include "common.h"
#include "shared/game_work.h"
#include "engine/effect.h"
#include "engine/resource_type_list_layouts_data.h"

/* Bind the map's geometry blocks and relocate the packed face-list address words. */
void relocate_resource_type_lists(u8 *data_base, s16 type_index)
{
    GameWork *state = &g_game_work; /* BYTES: form the work base before adding the map offset. */
    MapGrid *map = &state->map;
    u32 *first_list;
    u32 *entry;
    s32 remaining;

    first_list = (u32 *)(data_base + resource_type_list_layouts[type_index]->off8 * 4);
    map->cell_faces = (void **)first_list;

    entry = first_list;
    remaining = resource_type_list_layouts[type_index]->relocation_count;
    if (remaining > 0) {
        do {
            remaining--;
            *entry += (u32)(unsigned long)data_base;
            entry++;
        } while (remaining > 0);
    }

    map->vertices = data_base + resource_type_list_layouts[type_index]->offA * 4;
    map->surface_planes = data_base + resource_type_list_layouts[type_index]->offC * 4;
    map->tile_kind_flags = data_base + resource_type_list_layouts[type_index]->offE * 4;
}
