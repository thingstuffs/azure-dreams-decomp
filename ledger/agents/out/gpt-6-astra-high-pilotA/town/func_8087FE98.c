#include "common.h"

#ifdef NON_MATCHING
#define READ_ZERO(var) ((var) = 0)
#else
#define READ_ZERO(var) __asm__("" : "=r"(var))
#endif

extern s32 func_807010E0();
extern u8 D_807009B8[];
extern u8 D_807009BA[];

/* Passes six pairs of 16-bit table entries to func_807010E0. */
void func_8087FE98(void) {
    register s32 zero ASM_REG("$0");
    s32 offset;
    u16 second_value;

    READ_ZERO(zero);
    offset = zero | 4;
    do {
        func_807010E0(*(u16 *)(D_807009B8 + offset));
        second_value = *(u16 *)(D_807009BA + offset);
        offset += 4;
        func_807010E0(second_value);
    } while (offset < 0x1C);
}
