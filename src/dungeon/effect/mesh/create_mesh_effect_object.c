#include "shared/object_node.h"
#include "dungeon/effect/mesh.h"

extern void register_node(void *object, void *data);
extern s16 tile_key_pair_count;
extern void *tile_coordinate_records;

/* Creates an object, attaches its data, and clears the shared state. */
void create_mesh_effect_object(void)
{
    void *object;

    object = allocate_flagged_object_node(0);
    register_node(object, build_visible_tile_quads);
    tile_coordinate_records = ((u8 *)object) + 0x20;
    *((s8 *)(((u8 *)object) + 0x20)) = 0;
    tile_key_pair_count = 0;
}
