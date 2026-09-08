#include "common.h"

/* Port-guarded liveness barrier: keeps the 0x80010000 page base live in its
 * pinned register so gcc emits one shared `lui` + offset accesses instead of
 * folding each field back to an absolute address (which gas would expand into
 * a fresh `lui` per access). common.h's ASM_KEEP uses a `+r` constraint that
 * this TU's gcc-2.7.2 rejects, so define a local `=r`/`0` twin. On the
 * -DNON_MATCHING port build it drops to a no-op. */
#ifdef NON_MATCHING
#define PAGE_KEEP(v) ((void)0)
#else
#define PAGE_KEEP(v) __asm__ __volatile__("" : "=r"(v) : "0"(v))
#endif

/* Clears the value at 0x80013718 and increments the counter at 0x8001371A. */
void func_8009FAAC(void) {
    u8 *page_base;
    u16 counter;

    page_base = (u8 *)0x80010000;
    PAGE_KEEP(page_base);
    counter = *(u16 *)(page_base + 0x371A);
    *(s16 *)(page_base + 0x3718) = 0;
    *(s16 *)(page_base + 0x371A) = (s16)(counter + 1);
}
