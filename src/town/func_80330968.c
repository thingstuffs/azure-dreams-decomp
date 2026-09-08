#include "common.h"

extern void func_8001ACE8(s32);
extern void func_8001AD60(s32);

void func_8001B168(s32 base, s32 bits, s32 count)
{
    s32 held_base;
    s32 held_bits;
    s32 held_count;
    s32 i;

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
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
    ASM_KEEP(held_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(held_bits);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
}

/* MECHANISM: The counted loop pins the retail callee-saved argument/index roles,
   requiring the retail four saved registers and 0x28 outgoing-argument frame.
   Goto-shaped induction recomputes base+i; both call arms rejoin before shift/increment. */
