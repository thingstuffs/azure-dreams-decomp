#include "common.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"

extern void allocate_and_initialize_object(void);
extern void set_monster_data_pointer();
extern void select_sprite_entry();
extern void clear_entry_flag_and_link_owner();

extern u8 *ghosh_actor_node;
extern u8 D_80174684[];

/* Resets the Ghosh actor action and animation, updates system flags, and relinks up to two attached
 * objects. */
void dispatch_map_exit_callback(s32 unused0, s32 unused1, s32 unused2, s32 unused3)
{
    s32 i;
    s32 object;
    u8 *base;
    u8 *linked;

    allocate_and_initialize_object();
    base = ghosh_actor_node + 0x20;
    linked = *(u8 **)(ghosh_actor_node + 0xC);
    *(u16 *)(base + 0x46) &= 0x7FFF;
    system_update_flags &= 0xFFF6;
    set_monster_data_pointer();
    base[0xB3] = 1;
    base[0xB2] = 0;
    if (*(u8 **)(linked + 0x2C) != D_80174684) {
        *(u8 **)(linked + 0x2C) = D_80174684;
        select_sprite_entry(linked,
            D_80174684[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)(base + 0x2A) + 0x100) >> 9) & 7],
            0);
    }

    i = 0;
    do {
        object = *(s32 *)(((u8 *)dungeon_actor_ring_anchor) + (i * 4) + 0xAC);
        if (object != 0) {
            clear_entry_flag_and_link_owner(object - 0x20);
        }
        i++;
    } while (i < 2);
}
