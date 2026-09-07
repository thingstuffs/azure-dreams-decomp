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

void func_8009FAAC(void) {
    u8 *p;
    u16 t;

    p = (u8 *)0x80010000;
    PAGE_KEEP(p);
    t = *(u16 *)(p + 0x371A);
    *(s16 *)(p + 0x3718) = 0;
    *(s16 *)(p + 0x371A) = (s16)(t + 1);
}
