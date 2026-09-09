#include "common.h"

#ifdef NON_MATCHING
#define KEEP_VALUE(v) ((void)0)
#else
#define KEEP_VALUE(v) __asm__("" : : "r"(v))
#endif

extern void func_800241D4(void *arg0, s32 arg1);
extern void func_80024274(void *arg0);
extern void func_80024F3C(void *arg0, s32 arg1, s32 arg2);

void func_80025DC8(void *arg0) {
    void *p;
    s32 i;

    i = 0;
    p = arg0;
loop:
    if (i == *(s32 *)((u8 *)arg0 + 0x2C)) {
        func_800241D4(*(void **)((u8 *)p + 0xC), 1);
        do { p = (u8 *)p + 4; } while (0);
    } else {
        func_80024274(*(void **)((u8 *)p + 0xC));
        do { p = (u8 *)p + 4; } while (0);
    }
    /* MATCH: Keep the pointer advance before the shared counter update. */
    KEEP_VALUE(p);
    i++;
    if (i >= 5) {
        func_80024F3C(*(void **)((u8 *)arg0 + 4), *(s32 *)((u8 *)arg0 + 0x2C), 3);
        return;
    }
    goto loop;
}
