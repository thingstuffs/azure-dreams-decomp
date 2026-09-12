#include "common.h"

extern s32 D_80083498;
extern s16 D_800DCED4[];
extern u8 *D_800E3D7C;

extern s32 func_800429E4(void *);
extern s32 func_800C07AC(s32 *);
extern void func_800C542C(void *, s16, s32, s32);

/* Update the two occupied object slots using their table heights when enabled. */
s32 func_800C0180(void)
{
    s32 slot_index;
    void *object;
    u8 *object_page;
    s16 *height_table;

    if (func_800C07AC(&D_80083498) == 0) {
        return 0;
    }

    slot_index = 1;
    object_page = (u8 *)0x800E0000;
    height_table = D_800DCED4;
    do {
        object = *(void **)(*(u8 **)(object_page + 0x3D7C) + 0xAC + slot_index * 4);
        if (object != 0) {
            func_800C542C(object, height_table[func_800429E4(object)],
                          (s16)slot_index, 0);
        }
        slot_index--;
    } while (slot_index >= 0);

    return 1;
}
