#include "common.h"

#include "common.h"

extern void func_80043458(void);

#if !defined(NON_MATCHING) && __GNUC__ < 3
#define ASM_KEEP(value) \
    __asm__ __volatile__("" : "=r"(value) : "0"(value))
#else
#define LEGACY_ASM_KEEP(value) ASM_KEEP(value)
#endif

/* Reset global state and initialize default parameters. */
void func_800434E4(void)
{
    u8 *globals_base = (u8 *)0x80010000;

    *(u8 *)(globals_base + 0x3185) = 1;
    ASM_KEEP(globals_base);
    *(s32 *)(globals_base + 0x2D5C) = 0;
    *(s32 *)(globals_base + 0x2D68) = 0;
    *(s32 *)(globals_base + 0x2D58) = 0;
    *(s32 *)(globals_base + 0x022C) = 0;
    func_80043458();
    *(s16 *)(globals_base + 0x3630) = 0xD5;
    *(s16 *)(globals_base + 0x3632) = 0x38;
    *(s16 *)(globals_base + 0x3634) = 0x6B;
    *(s16 *)(globals_base + 0x3636) = 0x70;
    *(s16 *)(globals_base + 0x3638) = 0x100;
    *(s16 *)(globals_base + 0x363A) = 0x78;
    *(s32 *)(globals_base + 0x363C) = 0x4000;
    *(s16 *)(globals_base + 0x20A0) = 0;
    *(s16 *)(globals_base + 0x20A2) = 0;
    *(s16 *)(globals_base + 0x20A4) = 0;
}
