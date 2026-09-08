#include "common.h"

extern s32 func_8009A350(s16, s16, s32, s32 *);
extern s16 func_800BCB04(u16, u16, s16);
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];

s32 func_8009A540(s32 arg0, s16 arg1, s16 arg2, s16 arg3)
{
    s32 local;
    s32 i;
    s32 first_row;
    s32 second_row;
    register s32 in_range ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 x;
    s32 y;
    register u16 *first ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 *first_at;
    u16 *second;
    u32 index;
    u32 first_value;
    u32 second_value;
    s32 third;
    register s32 held_arg0 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 held_arg3 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u32 page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    held_arg0 = arg0;
    held_arg3 = arg3;
    arg0 &= 1;
    if (arg0) {
        ASM_KEEP(held_arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(held_arg3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        i = -1;
        x = (s16)arg1;
        first_row = (x << 6) + 0x20;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        page = 0x800E0000;
        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        first = (u16 *)(page - 0x3154);
        y = (s16)arg2;
        second_row = (y << 6) + 0x20;
loop:
        if ((func_8009A350(x, y, (held_arg0 + i) & 7, &local) << 16) == 0) {
            goto next;
        }
        index = ((u16)held_arg0 + i) & 7;
        first_at = (u16 *)((index << 1) + (u32)first);
        third = (s16)held_arg3;
        first_value = *first_at;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        second = D_800DCEBC;
        ASM_KEEP(second);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        second_value = second[index];
        if (func_800BCB04(
                (first_value + first_row) & 0xFFFF,
                (second_value + second_row) & 0xFFFF,
                third) >= 0x201) {
            in_range = i < 2;
            goto decision;
        } else {
next:
            i += 2;
            if (i < 2) {
                goto loop;
            }
            ASM_KEEP(i);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            in_range = i < 2;
        }
decision:
        if (in_range) {
            return 0;
        }
    }
    return 1;
}

/* MECHANISM: True-name rowbase uses a 0x40 frame with one local and s0-s7/ra.
   Raw arg0/arg3 holds plus signed row values reproduce the callee ABI lifetimes.
   A rewritten v0 page builds s7; a byte-scaled v1 index orders both table loads.
   Post-loop ASM_KEEP(i) preserves retail's redundant slti v1 instead of zero-folding. */
