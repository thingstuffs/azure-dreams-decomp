
struct ObjectNodeHeader;
#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"
#include "dungeon/item.h"


extern void func_8016E264(void);
extern void clear_entry_flag_and_link_owner(struct ObjectNodeHeader *);

/* Leave the map screen and release the two attached objects. */
void leave_map_screen_and_release_objects(void)
{
    s32 i;
    void *object;
    u8 *ptr;

    ptr = (u8 *)(ghosh_actor_node + 1);
    *(u16 *)(ptr + 0x46) &= 0x7FFF;
    dungeon_floor_flags &= 0xF7FFFFFF;
    system_update_flags &= 0xFFF6;
    set_monster_data_pointer();
    func_8016E264();

    i = 0;
    do {
        object = *(void **)(((u8 *)dungeon_actor_ring_anchor) + 0xAC + i * 4);
        if (object != 0) {
            clear_entry_flag_and_link_owner((u8 *)object - 0x20);
        }
        i++;
    } while (i < 2);
}
