#include "common.h"

#ifdef NON_MATCHING
#define READ_ZERO(var) ((var) = 0)
#else
#define READ_ZERO(var) __asm__("" : "=r"(var))
#endif

extern s32 func_807010E0();
extern u8 D_807009B8[];
extern u8 D_807009BA[];

/* Process six pairs of 16-bit table entries starting at byte offset four. */
void func_8087FE98(void) {
    register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 byte_offset;
    u16 second_entry;

    READ_ZERO(zero);
    byte_offset = zero | 4;
    do {
        func_807010E0(*(u16 *)(D_807009B8 + byte_offset));
        second_entry = *(u16 *)(D_807009BA + byte_offset);
        byte_offset += 4;
        func_807010E0(second_entry);
    } while (byte_offset < 0x1C);
}
