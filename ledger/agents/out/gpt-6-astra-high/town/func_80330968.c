#include "common.h"

extern void func_8001ACE8(s32);
extern void func_8001AD60(s32);

/* Dispatches consecutive indices to one of two handlers according to successive mask bits. */
void func_8001B168(s32 base, s32 bits, s32 count)
{
    s32 first_index;
    s32 remaining_bits;
    s32 index_count;
    s32 offset;

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    first_index = base;
    remaining_bits = bits;
    index_count = count;
    offset = 0;
    if (index_count > 0) {
loop:
        if (remaining_bits & 1) {
            func_8001ACE8(first_index + offset);
        } else {
            func_8001AD60(first_index + offset);
        }
        remaining_bits >>= 1;
        offset++;
        if (offset < index_count) {
            goto loop;
        }
    }
    ASM_KEEP(first_index);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ASM_KEEP(remaining_bits);   /* MATCH pin: retail register colouring depends on it */
}
