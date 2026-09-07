#include "common.h"

extern void func_80041E70(void *arg0);

void func_800AB9A0(void *arg0)
{
    u8 *obj = arg0;
    s32 i;

    for (i = 3; i >= 0; i--) {
        obj[0x2C + i * 2] = 0;
        obj[0x2D + i * 2] = 0;
    }

    *(u32 *)(obj + 0x1C) &= 0xFBFFE107;
    obj[0x24] = 0xFF;
    obj[0x28] = obj[0x29];
    obj[0x25] = obj[0x66];
    obj[0x26] = obj[0x68];
    obj[0x27] = obj[0x69];
    func_80041E70(obj);
}
