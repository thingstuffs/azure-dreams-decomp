#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"

extern s32 D_80174704[3];

extern void set_monster_data_pointer(void);
extern void func_8016E264(void);
extern void clear_entry_flag_and_link_owner(void *);

/* Leave the map screen and release the two attached objects. */
void leave_map_screen_and_release_objects(void)
{
    s32 i;
    void *object;
    u8 *ptr;

    ptr = (u8 *)(D_80174704[0] + 0x20);
    *(u16 *)(ptr + 0x46) &= 0x7FFF;
    D_800E296C &= 0xF7FFFFFF;
    D_80013714 &= 0xFFF6;
    set_monster_data_pointer();
    func_8016E264();

    i = 0;
    do {
        object = *(void **)(((u8 *)D_800E3D7C) + 0xAC + i * 4);
        if (object != 0) {
            clear_entry_flag_and_link_owner((u8 *)object - 0x20);
        }
        i++;
    } while (i < 2);
}
