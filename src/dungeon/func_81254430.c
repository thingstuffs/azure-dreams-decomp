#include "common.h"

typedef struct {
    u32 value;
    s32 pad[2];
} S_80173F90;

extern S_80173F90 D_80173F90;

#ifdef NON_MATCHING
#define KEEP_PAGE(var) ((void)0)
#else
#define KEEP_PAGE(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

/* Resets global state fields and flags and loads the configured value. */
void func_81254430(void) {
    u8 *page = (u8 *)0x80010000;
    register u16 flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    KEEP_PAGE(page);
    flags = *(u16 *)(page + 0x3714);
    *(s16 *)(page + 0x371A) = 0;
    *(s16 *)(page + 0x3718) = 0;
    *(s16 *)(page + 0x3716) = 0;
    value = D_80173F90.value;
    *(s16 *)(page + 0x3714) = (flags | 9) & 0xFFEF;
    *(s32 *)(page + 0x371C) = value;
}
