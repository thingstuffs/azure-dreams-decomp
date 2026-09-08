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
    register u8 *object_page ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 *height_table;
    u8 *height_page;

    if (func_800C07AC(&D_80083498) == 0) {
        return 0;
    }

    slot_index = 1;
    object_page = (u8 *)0x800E0000;
    ASM_KEEP(object_page);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    height_page = (u8 *)0x800E0000;
    ASM_KEEP(height_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    height_table = (s16 *)(height_page - 0x312C);
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
