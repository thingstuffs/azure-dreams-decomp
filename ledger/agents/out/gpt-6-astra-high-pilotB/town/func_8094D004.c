#include "common.h"

extern u8 D_80016038[16];
extern u8 *D_80016D08[3];

#ifdef __mips__
static const u32 data_bank[6] __asm__("func_8094D004")
    __attribute__((section(".text.func_8094D004"), aligned(4))) = {
    [0] = 0x4c070707,
    [1] = 0x80016af4,
    [2] = 0x00000001,
    [3] = 0x4c070707,
    [4] = 0x80016a94,
    [5] = 0x00010f48,
};
__asm__(".globl func_8094D004\n"
        ".size func_8094D004, 48");
#define BODY_NAME func_8094D01C
#else
#define BODY_NAME func_8094D004
#endif

/* Point the first buffer slot at D_80016038. */
void BODY_NAME(void) {
    D_80016D08[0] = D_80016038;
}
