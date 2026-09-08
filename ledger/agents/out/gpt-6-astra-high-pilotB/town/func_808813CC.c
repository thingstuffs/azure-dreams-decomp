#include "common.h"

#ifdef NON_MATCHING
#define READ_ZERO(var) ((var) = 0)
#else
#define READ_ZERO(var) __asm__("" : "=r"(var))
#endif

extern s32 func_80700D20();
extern u8 D_80700638[];
extern u8 D_8070063A[];

/* Pass paired 16-bit values at four-byte offsets to func_80700D20. */
void func_808813CC(void) {
    register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 byte_offset;
    u16 second_value;

    READ_ZERO(zero);
    byte_offset = zero | 4;
    do {
        func_80700D20(*(u16 *)(D_80700638 + byte_offset));
        second_value = *(u16 *)(D_8070063A + byte_offset);
        byte_offset += 4;
        func_80700D20(second_value);
    } while (byte_offset < 8);
}
