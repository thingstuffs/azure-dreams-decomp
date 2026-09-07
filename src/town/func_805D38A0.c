#include "common.h"

typedef s32 (*Callback)(void *);

extern s8 D_80016000[];
extern s32 D_80019B00;
extern u8 D_80019B8C;

void func_805D38A0(void) {
    u8 sp10[2];
    s8 *slot;
    s32 ret;
    u8 kind;

    slot = *(s8 **)(*(s8 **)D_80016000 + 0x40) +
           (*(s32 *)(*(s8 **)D_80016000 + 8) * 8);
    kind = D_80019B8C;
    sp10[1] = 0x19;
    sp10[0] = kind;
    *(u8 *)(slot + 6) = kind;
    ret = (*(Callback *)(*(s8 **)(*(s8 **)D_80016000 + 0x20) + 0x50))(sp10);
    D_80019B00 = ret;
    *(s32 *)slot = ret;
}

/* MECHANISM
 * - GLOBAL DECL FORM: D_80016000 as `extern s8 D_80016000[]` deref'd twice as
 *   *(s8**)D_80016000 gives retail's single held `lui $a1,0x8001` + two
 *   `lw 0x6000($a1)`; the intervening `sb 6($s0)` store kills the CSE, which
 *   is exactly why retail reloads. D_80019B8C declared u8 (not the s32 sibling
 *   decl) is what emits `lbu`, not `lw`+trunc.
 * - STATEMENT ORDER IS THE LEVER: computing `slot` BEFORE `kind = D_80019B8C`
 *   puts %hi(D_80016000) in $a1 ahead of %hi(D_80019B8C) and lets gcc color the
 *   D_80019B8C hi-base and the lbu destination onto the same $a0 (retail words
 *   0/1/3). The reverse order costs a third lui register ($v1) and swaps them.
 * - FRAME: two sibling u8 stack bytes as a u8[2] passed by address gives the
 *   0x20 frame (16 arg + 8 local + ra/s0) and `addiu $a0,$sp,0x10` in the jalr
 *   delay slot; a wrapper struct would not.
 */
