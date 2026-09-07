#include "common.h"

extern u8 D_800E3548[];
extern void func_800A722C(u8 *) __attribute__((noreturn));

s32 func_800A71F4(void) {
    u8 *entry;
    s32 i;
    register u8 *page ASM_REG("$2");

    i = 0;
    page = (u8 *)0x800E0000;
    ASM_KEEP(page);
    entry = page + 0x3548;
    do {
        if (entry[1] == 0) {
            register s32 index ASM_REG("$2");

            index = (s16)i;
            ASM_TAILSLOT_PIN_TIED(index);
            func_800A722C(entry);
        }
        ASM_SCHED_BARRIER();
        i++;
        entry += 4;
    } while (i < 0x40);
    return -1;
}

/* MECHANISM: Frameless retail shape comes from the noreturn tail contract.
   A scheduling barrier keeps i++ out of the bnez delay so the pinned s16 index lands there.
   Short-lived $v0 page and index roles reproduce the split base load and tail-j delay. */
