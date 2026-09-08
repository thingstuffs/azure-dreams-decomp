#include "common.h"

extern void func_8008CBA0(void *, s32, void *, void *);
extern void func_8008CF6C(void *, s32, void *, void *);
extern void func_80097898(void *);
extern void func_80097C50(void *, s32, void *, void *);

extern u16 D_80013714;
extern u8 D_8004F5F4[];
extern s32 D_80082EB0;
extern u8 D_80083160[];
extern s32 D_800E4940;

void func_80097C78(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    void *early_p2 = arg2;
    register void *p2 ASM_REG("$19") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *p3 ASM_REG("$17") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s16 direction = *(s16 *)((u8 *)p3 + 0x64);
    u8 *state = D_80083160;

    if (direction < 0) {
        *(u16 *)((u8 *)early_p2 + 0x14) &= 0xF7FF;
        func_80097898(arg0);
        return;
    }

    ASM_CLOBBER("$6");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    ASM_CLOBBER("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (direction > 0) {
        func_8008CBA0(arg0, arg1, p2, p3);
    }

    if (!(D_80013714 & 1) && (*(s32 *)(state + 8) & 0x80)) {
        *(s16 *)((u8 *)p3 + 0x8A) = 2;
        D_800E4940 = 2;
        func_8008CF6C(arg0, arg1, p2, D_8004F5F4);
        D_80082EB0 = 0;
        *(s32 *)((u8 *)arg0 + 0xC8) = 0;
        *(s32 *)((u8 *)arg0 + 0x104) = 0;
        return;
    }

    if (*(u8 *)((u8 *)arg0 + 0x9A) != 0x3A &&
        (*(s32 *)((u8 *)p3 + 0x1C) & 0x200)) {
        *(u16 *)((u8 *)p2 + 0x14) &= 0xF7FF;
        func_80097C50(arg0, arg1, p2, p3);
    }
}

/* MECHANISM: The 0x28 frame holds arg0/arg1/arg2/arg3 in s0/s2/s3/s1 and state in s4.
   A split entry-only a2 live range preserves retail's negative-path base, while guarded
   a2/a3 clobbers before the positive guard force all four call reloads in retail order. */
