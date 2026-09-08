#include "common.h"

extern void func_80041E70(void *arg0);

/* Clears object entries and flags, restores saved fields, and updates the object. */
void func_800AB9A0(void *object)
{
    u8 *obj = object;
    s32 entry_index;

    for (entry_index = 3; entry_index >= 0; entry_index--) {
        obj[0x2C + entry_index * 2] = 0;
        obj[0x2D + entry_index * 2] = 0;
    }

    *(u32 *)(obj + 0x1C) &= 0xFBFFE107;
    obj[0x24] = 0xFF;
    obj[0x28] = obj[0x29];
    obj[0x25] = obj[0x66];
    obj[0x26] = obj[0x68];
    obj[0x27] = obj[0x69];
    func_80041E70(obj);
}
