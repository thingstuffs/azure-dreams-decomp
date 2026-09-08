#include "common.h"

extern s32 func_8009D218(s32, s32);
extern s32 func_800A48F0(s32, s32, s32);
extern void func_80099844(s32, void *);
extern u8 D_800E1D01[9];

/*
 * Register-priority permutation closer (portable, guarded pins only):
 *  - arg1 pinned to $16 (s0) forces arg0 to fall into $17 (s1) naturally,
 *    reproducing retail's arg0->s1 / arg1->s0 callee-saved roles (gcc's
 *    natural priority allocates arg0 into $16, giving the swapped roles).
 *  - the (arg1&0xff)>>2 partial index pinned to $6 (a2) forces the list
 *    scheduler to emit the andi/srl into the arg register BEFORE the
 *    move a0,s1 / li a1,0x15 arg setup, matching retail's schedule; the
 *    +2 folds into the jal delay slot exactly as retail.
 * (u32) cast makes the >>2 a logical srl (matches retail), not sra.
 */
void func_800262B8(s32 arg0, s32 arg1) {
    register s32 b ASM_REG("$16") = arg1;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    if (func_8009D218(arg0, 2) == 0) {
        register s32 c ASM_REG("$6") = (u32)(b & 0xFF) >> 2;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        if ((func_800A48F0(arg0, 0x16, c + 4) << 16) != 0) {
            func_80099844(arg0, D_800E1D01);
        }
    }
}
