#include "common.h"

extern s32 func_8004A658(s32, s32);
extern void func_800A7A6C(void *);

void func_800A7A38(u8 *item)
{
    if (item[1] == 0x12) {
        u32 value = 0x80070000;

        ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        value -= 0x1DC0;
        ASM_TAILSLOT_PIN(value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800A7A6C(item);
        return;
    }
    func_8004A658(item[1], item[0]);
}
