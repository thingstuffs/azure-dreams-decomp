#include "common.h"

extern s32 func_8004A658(s32, s32);
extern void func_800A7A6C(void *);

void func_800A7A38(u8 *item)
{
    if (item[1] == 0x12) {
        register u32 value ASM_REG("$2") = 0x80070000;

        ASM_KEEP(value);
        value -= 0x1DC0;
        ASM_TAILSLOT_PIN(value);
        func_800A7A6C(item);
        return;
    }
    func_8004A658(item[1], item[0]);
}
