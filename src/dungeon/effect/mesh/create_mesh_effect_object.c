#include "shared/object_node.h"
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef int s32;

extern void register_node(void *object, void *data);
extern s16 tile_key_pair_count;
extern void *tile_coordinate_records;
extern s32 D_800D1824;

/* Creates an object, attaches its data, and clears the shared state. */
void create_mesh_effect_object(void)
{
    void *object;

    object = allocate_flagged_object_node(0);
    register_node(object, &D_800D1824);
    tile_coordinate_records = ((u8 *)object) + 0x20;
    *((s8 *)(((u8 *)object) + 0x20)) = 0;
    tile_key_pair_count = 0;
}
