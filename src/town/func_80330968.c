#include "common.h"

extern void func_8001ACE8(s32);
extern void func_8001AD60(s32);

void func_8001B168(s32 base, s32 bits, s32 count)
{
    s32 held_base;
    s32 held_bits;
    s32 held_count;
    s32 i;

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    held_base = base;
    held_bits = bits;
    held_count = count;
    i = 0;
    if (held_count > 0) {
loop:
        if (held_bits & 1) {
            func_8001ACE8(held_base + i);
        } else {
            func_8001AD60(held_base + i);
        }
        held_bits >>= 1;
        i++;
        if (i < held_count) {
            goto loop;
        }
    }
    ASM_KEEP(held_base);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ASM_KEEP(held_bits);   /* MATCH pin: retail register colouring depends on it */
}

/* MECHANISM: The counted loop pins the retail callee-saved argument/index roles,
   requiring the retail four saved registers and 0x28 outgoing-argument frame.
   Goto-shaped induction recomputes base+i; both call arms rejoin before shift/increment. */
