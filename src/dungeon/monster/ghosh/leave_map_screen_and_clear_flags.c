#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"

extern s32 ghosh_actor_node[3];

extern void set_monster_data_pointer(void);
extern void func_8016E264(void);

/* Leave the map screen: clear the three display flags and tear the screen down. */
void leave_map_screen_and_clear_flags(void) {
    u8 *ptr;
    u16 *h = ((u16 *)&system_update_flags);

    ptr = (u8 *)(ghosh_actor_node[0] + 0x20);
    *(u16 *)(ptr + 0x46) &= 0x7FFF;
    dungeon_floor_flags &= 0xF7FFFFFF;
    h[0] &= 0xFFF6;
    set_monster_data_pointer();
    func_8016E264();
}
