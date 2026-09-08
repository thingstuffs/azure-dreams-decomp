#include "common.h"

#ifdef NON_MATCHING
#define READ_ZERO(var) ((var) = 0)
#else
#define READ_ZERO(var) __asm__("" : "=r"(var))
#endif

extern s32 func_80700D20();
extern u8 D_80700638[];
extern u8 D_8070063A[];

void func_808813CC(void) {
    register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 i;
    u16 value;

    READ_ZERO(zero);
    i = zero | 4;
    do {
        func_80700D20(*(u16 *)(D_80700638 + i));
        value = *(u16 *)(D_8070063A + i);
        i += 4;
        func_80700D20(value);
    } while (i < 8);
}
