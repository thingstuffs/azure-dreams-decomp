#include "common.h"

typedef struct S_80024370_0_pre {
    u16 unk_00;
} S_80024370_0_pre;   /* the 0x2 bytes before arg0 in func_80024370, addressed as arg0[-1] */

typedef struct S_80024370_0 {
    void * unk_00;
    u16 unk_04;
} S_80024370_0;   /* arg0 in func_80024370 */

typedef struct S_80024370_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80024370_1;   /* object in func_80024370 */

typedef struct S_80024370_2 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80024370_2;   /* global_page in func_80024370 */



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
    register void *saved_arg2 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    S_80024370_1 *object;
    u16 count;

    saved_arg2 = arg2;
    object = ((S_80024370_0 *)arg0)->unk_00;
    object->unk_14++;

    count = ((S_80024370_0 *)arg0)->unk_04 + 1;
    ((S_80024370_0 *)arg0)->unk_04 = count;

    if ((s16)count == 8) {
        goto count_8;
    }
    if ((s16)count == 0x10) {
        goto count_16;
    }
    func_80024400();

count_8:
    func_80024264_returning(((S_80024370_0 *)arg0)->unk_00);
    func_80024400();

count_16:
    {
        register s32 *global_page ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        global_page = (s32 *)0x80080000;
        ASM_KEEP(global_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ((S_80024370_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        ((S_80024370_2 *)global_page)->unk_14A0 |= 0x8000;
        ASM_KEEP(saved_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        func_800478B8(saved_arg2);
    }
}

/* MECHANISM: Explicit labels preserve default -> count-8 -> count-16 emission order;
   the guarded arg2/$s0 hold gives the 0x18 frame and first-beq delay-slot move.
   A guarded $v1 page base yields the second-delay lui and 0x14A0 RMW, while the
   no-code returning-site alias keeps func_80024264 as jal despite stale LEAD-18 evidence. */
