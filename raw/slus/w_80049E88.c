#include "common.h"

#include "common.h"

extern s32 func_80042900(void *, s8);
extern s8 D_800712E4[];
extern u8 D_800712F0[];

u8 func_80049E88(void *arg0) {
    register s32 i ASM_REG("$16");
    s32 base;
    register void *arg ASM_REG("$18");
    register u8 *table ASM_REG("$2");
    s32 temp;
    u8 value;

    arg = arg0;
    i = 0xB;
    temp = (s32) D_800712E4;
    base = temp;
    do {
        if ((func_80042900(arg, *(s8 *) (i + base)) << 0x10) != 0) {
            break;
        }
        i--;
    } while (i > 0);

    value = *(u8 *) (i + base);
    __asm__ volatile("" : "=r"(base) : "0"(base));
    if ((value == 7) && ((func_80042900(arg, (s8) value) << 0x10) > 0)) {
        i--;
    }

    table = D_800712F0;
    table += i;
    return *table;
}
