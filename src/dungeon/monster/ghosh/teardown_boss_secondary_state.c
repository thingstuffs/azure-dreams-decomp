
struct ObjectNodeHeader;
#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"
#include "dungeon/item.h"


extern void func_80173ED0(void);
extern void clear_entry_flag_and_link_owner(struct ObjectNodeHeader *);

/* Dungeon teardown: clear the on-screen/status flag bits, run both shutdown hooks, and release the two objects held in the actor table. */
void teardown_boss_secondary_state(void) {
    s32 i;
    void *object;
    u8 *ptr;
    u16 *flags = ((u16 *)&system_update_flags);

    ptr = (u8 *)(ghosh_boss_node + 1);
    /*
     * BUG: the Ghosh dialogue script releases this companion (clearing ghosh_boss_node) before it calls
     * this teardown, so the node is null and the AND below reaches the halfword at 0x00000066. Harmless
     * on PS1: the low 64 KB is mapped kernel RAM, so the store does not fault and only clears bit 15.
     */
    *(u16 *)(ptr + 0x46) &= 0x7FFF;
    dungeon_floor_flags &= 0xF7FFFFFF;
    flags[0] &= 0xFFF6;
    set_monster_data_pointer();
    func_80173ED0();

    i = 0;
    do {
        object = *(void **)(((u8 *)dungeon_actor_ring_anchor) + 0xAC + i * 4);
        if (object != 0) {
            clear_entry_flag_and_link_owner((u8 *)object - 0x20);
        }
        i++;
    } while (i < 2);
}
