#include "common.h"

extern s32 D_80084D5C;

void func_808151F8(void *arg0) {
    /* retail reserves 8 bytes of frame and never touches them - no sw/lw/sh/sb with (sp) exists
       anywhere in the row's 39 words, and there is no `sw ra` (a leaf).  An unused local of frame
       size is the honest cause; without it the prologue/epilogue pair disappears (length-drift). */
    s32 unused_slot[2];
    u8 *inner;
    s16 state;
    register s32 call_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 value;

    state = *(s16 *)arg0;
    inner = *(u8 **)((u8 *)arg0 + 4);
    call_arg = state;
    if (state == 0) {
        goto state_0;
    }
    call_arg = 0xFFF70000;
    if (state == 1) {
        goto state_1;
    }
    return;

state_0:
    ASM_KEEP(call_arg);   /* SITE-FOR-PIN TRADE 2026-09-22: the two `func_8052FE88()` tail
                             pseudo-calls are gone; this holds the entry state in $4 across the
                             block.  Without it gcc folds `call_arg + 1` to `li 1` (it knows
                             call_arg == 0 on this edge) and drops the `move a0,v1` copy. */
    if (*(u16 *)(inner + 0x1A) & 8) {
        register s32 next ASM_REG("$2");   /* SITE-FOR-PIN TRADE 2026-09-22: one register
                                             colour - retail computes the stored value in $2, the
                                             free choice here is $4 (residue broad/2 without it) */

        next = call_arg + 1;
        *(s16 *)arg0 = next;
    }
    return;

state_1:
    value = *(s32 *)((u8 *)arg0 + 8) + (call_arg | 0xF7F8);
    *(s32 *)((u8 *)arg0 + 8) = value;
    if (value <= 0x80808) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_80084D5C |= 0x8000;
    }
}
