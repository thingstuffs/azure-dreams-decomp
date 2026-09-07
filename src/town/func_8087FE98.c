#include "common.h"

#ifdef NON_MATCHING
#define READ_ZERO(var) ((var) = 0)
#else
#define READ_ZERO(var) __asm__("" : "=r"(var))
#endif

extern s32 func_807010E0();
extern u8 D_807009B8[];
extern u8 D_807009BA[];

void func_8087FE98(void) {
    register s32 zero ASM_REG("$0");   /* MATCH pin: retail immediate-load split depends on it */
    s32 i;
    u16 value;

    READ_ZERO(zero);
    i = zero | 4;
    do {
        func_807010E0(*(u16 *)(D_807009B8 + i));
        value = *(u16 *)(D_807009BA + i);
        i += 4;
        func_807010E0(value);
    } while (i < 0x1C);
}
