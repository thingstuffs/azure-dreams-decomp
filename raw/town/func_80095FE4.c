#include "common.h"

extern u32 func_8009368C(void *arg0, s32 arg1, s32 arg2);
extern void func_80098868(void *arg0, s32 arg1, s32 arg2);

extern s32 D_800834B8;
extern s32 D_8009C340;

void func_80093744(void) {
    u8 *base;
    void *values;
    s32 value1;
    s32 value2;
    u8 *object;
    register void *arg0 ASM_REG("$4");

    base = (u8 *)&D_800834B8;
    arg0 = base;
    values = base - 0x20;
    value1 = *(s32 *)((u8 *)values + 8);
    value2 = *(s32 *)((u8 *)values + 0xC);
    object = *(u8 **)(base + 0x2C);
    ASM_KEEP(arg0);
    ASM_KEEP(base);

    if (func_8009368C(arg0, value1, value2) != 0) {
        u8 *current;

        func_80098868(base, value1, value2);
        current = *(u8 **)(base + 0x2C);
        if (current != 0 && (current[0x14] == 4 || current[0x4D] == 0xD)) {
            *(s32 **)(object + 0x50) = &D_8009C340;
            *(u8 **)(base + 0x2C) = 0;
        }
    }
}
