#include "common.h"

extern void func_80099088() __attribute__((noreturn));

s32 func_8009904C(s32 arg0) {
    s32 *entry;
    s32 value;
    s32 i;

    i = 0;
    entry = (s32 *)0x80010000;
loop:
    value = entry[0xA7];
    if (value != 0) {
        if (value == arg0) {
            s32 index = (s16)i;
            ASM_TAILSLOT_PIN_TIED(index);
            func_80099088(arg0, entry);
        }
        ASM_SCHED_BARRIER();
        i++;
        entry++;
        if (i < 20) {
            goto loop;
        }
    }
    return -1;
}

/* MECHANISM: The a1 cursor holds 0x80010000; indexed +0x29c loads D_8001029C.
   The continuation consumes a signed index through its nonstandard v0 ABI, so
   a guarded tail-slot pin exposes the sll/sra pair around the frameless jump;
   a zero-word boundary keeps the other path's increment out of that delay slot. */
