
struct ObjectNodeHeader;
#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"
#include "dungeon/item.h"
#include "dungeon/level.h"


extern void func_8016E264(void);

/* Leave the map screen and release the two attached objects. */
void leave_map_screen_and_release_objects(void)
{
    s32 i;
    void *object;
    u8 *ptr;

    ptr = NODE_BODY(ghosh_actor_node);
    *(u16 *)(ptr + 0x46) &= 0x7FFF;
    dungeon_floor_flags &= 0xF7FFFFFF;
    system_update_flags &= 0xFFF6;
    reset_timed_sequence_data();
    func_8016E264();

    i = 0;
    do {
        object = *(void **)(((u8 *)dungeon_actor_ring_anchor) + 0xAC + i * 4);
        if (object != 0) {
            insert_node_before_primary_actor(NODE_HEADER(object));
        }
        i++;
    } while (i < 2);
}
