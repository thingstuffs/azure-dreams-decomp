#include "dungeon/level/floor_flags.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "dungeon/menu.h"

extern void create_map_marker(u8, u8, s32, s32, s32);

/* Create red markers at the owner positions of active list entries. */
void draw_monster_map_markers(void)
{
    u8 *node;
    u8 *owner;
    s32 marker_count;

    node = ((u8 *)dungeon_actor_ring_anchor);
    begin_map_marker_draw();
    marker_count = 0;
    while ((node = *(u8 **)(node + 0x5C) + 0x20) != ((u8 *)dungeon_actor_ring_anchor)) {
        if (*(s8 *)(node + 0x13) > 0) {
            owner = *(u8 * *)&((ObjectNodeHeader *)(node - 0x20))->sprite;
            create_map_marker(owner[0x24], owner[0x25], 0x202080, FLOOR_MONSTERS_VISIBLE,
                          marker_count++);
        }
    }
}
