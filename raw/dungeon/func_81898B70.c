#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80024264(void *arg0);
#ifndef NON_MATCHING
__asm__(".set func_80024264_returning, func_80024264");
extern void func_80024264_returning(void *arg0);
#else
#define func_80024264_returning func_80024264
#endif
extern void func_80024400(void) __attribute__((noreturn));
extern void func_800478B8(void *arg0);
extern s32 D_800814A0;

void func_80024370(void *arg0, s32 arg1, void *arg2)
{
    register void *saved_arg2 ASM_REG("$16");
    void *object;
    u16 count;

    saved_arg2 = arg2;
    object = FIELD(arg0, void *, 0);
    FIELD(object, u16, 0x14)++;

    count = FIELD(arg0, u16, 4) + 1;
    FIELD(arg0, u16, 4) = count;

    if ((s16)count == 8) {
        goto count_8;
    }
    if ((s16)count == 0x10) {
        goto count_16;
    }
    func_80024400();

count_8:
    func_80024264_returning(FIELD(arg0, void *, 0));
    func_80024400();

count_16:
    {
        register s32 *global_page ASM_REG("$3");

        global_page = (s32 *)0x80080000;
        ASM_KEEP(global_page);
        FIELD(arg0, u16, -2) |= 0x8000;
        FIELD(global_page, s32, 0x14A0) |= 0x8000;
        ASM_KEEP(saved_arg2);
        func_800478B8(saved_arg2);
    }
}

/* MECHANISM: Explicit labels preserve default -> count-8 -> count-16 emission order;
   the guarded arg2/$s0 hold gives the 0x18 frame and first-beq delay-slot move.
   A guarded $v1 page base yields the second-delay lui and 0x14A0 RMW, while the
   no-code returning-site alias keeps func_80024264 as jal despite stale LEAD-18 evidence. */
