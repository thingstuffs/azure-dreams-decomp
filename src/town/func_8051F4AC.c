#include "common.h"

extern s32 func_800162F8(void);
extern u8 D_8001D244[];

#ifndef NON_MATCHING
/* Value-returning tail call into func_80016CD4: retail emits a bare
 * `j func_80016CD4` (SN/ASPSX reuses $ra). maspsx's LEAD-18 pass rewrites the
 * gcc `jal`->`j` when the callee is in the source-derived zero-arg noreturn set,
 * so it is declared noreturn here (the pass, not gcc, owns the tail rewrite).
 * The fall-through arm also materialises a dead split address 0x8001C769 whose
 * page base (lui v0,0x8002) fills the preceding bnez delay slot and whose low
 * half (addiu v0,-14487) fills the converted j delay slot, while the taken arm
 * returns &D_8001D244 as its own self-contained lui/addiu. */
register u8 *dispatch_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
#else
#endif

void *func_80016CAC(void) {
#ifndef NON_MATCHING
    if (func_800162F8() == 0) {
        dispatch_result = (u8 *)0x80020000;
        __asm__ __volatile__("" : "=r"(dispatch_result) : "0"(dispatch_result));
        dispatch_result -= 0x3897;
        return;
    }
    return D_8001D244;
#else
    if (func_800162F8() == 0) {
        return;
    }
    return D_8001D244;
#endif
}
