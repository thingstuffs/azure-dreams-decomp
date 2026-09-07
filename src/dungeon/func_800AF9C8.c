#include "common.h"

extern u8 D_800E3648[];
extern void func_800B5160(u8 *) __attribute__((noreturn));

s32 func_800B5128(void) {
    u8 *entry;
    s32 i;
    u8 *page;

    i = 0;
    page = (u8 *)0x800E0000;
    ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
    entry = page + 0x3648;
    do {
        if (entry[1] == 0) {
            s32 index;

            index = (s16)i;
            ASM_TAILSLOT_PIN_TIED(index);   /* MATCH pin: retail delay-slot contents depend on it */
            func_800B5160(entry);
        }
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        i++;
        entry += 4;
    } while (i < 0x20);
    return -1;
}

/* MECHANISM: Frameless retail shape comes from the noreturn tail contract.
   A scheduling barrier keeps i++ out of the bnez delay so the pinned s16 index lands there.
   Short-lived $v0 page and index roles reproduce the split base load and tail-j delay. */
