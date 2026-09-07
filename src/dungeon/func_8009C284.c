#include "common.h"
#define F(p,t,o) (*(t *)((u8 *)(p) + (o)))
extern s16 func_8009FD40(void *, void *);
extern void func_800A1B14(void) __attribute__((noreturn));
extern u8 D_80082E80[];
extern s8 D_80082EA6;
s32 func_800A19E4(void *a, void *b, s32 lo, s32 hi, s8 *out) {
    u32 flags = F(b, u32, 0x1C); s8 v;
    if (flags & 0x20000) {
        if (flags & 0x10) { F(b,u32,0x1C) = flags & ~0x20000; F(b,s8,0x73)=0; F(b,s8,0x72)=0; *out=-1; func_800A1B14(); }
        v = F(a,s8,0x26);
        if (v >= 0) {
            u8 *page = (u8 *)0x80080000;
            ASM_KEEP(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
            if (v == F(page,s8,0x2EA6)) goto done;
        }
        if ((func_8009FD40(D_80082E80,a) << 16) >= (hi << 16)) { F(b,s8,0x73)=0; F(b,s8,0x72)=0; F(b,u32,0x1C) &= ~0x20000; *out=-1; func_800A1B14(); }
        goto done;
    }
    if (!(flags & 0x10)) {
        v=F(a,s8,0x26);
        if (v >= 0) {
            u8 *page = (u8 *)0x80080000;
            ASM_KEEP(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
            if (v == F(page,s8,0x2EA6)) goto set_flag;
        }
        if ((func_8009FD40(D_80082E80,a) << 16) >= (lo << 16)) goto done;
set_flag:
        F(b,u32,0x1C) |= 0x20000;
    }
done:
    return (F(b,u32,0x1C) >> 17) & 1;
}
/* MECHANISM: The 0x28 frame naturally holds b/lo/hi/out in s0/s1/s2/s3; noreturn
   typing preserves both distinct func_800A1B14 tail jumps. Per-path 0x80080000
   bases plus ASM_KEEP put each page lui in the bltz slot; the high test is >=. */
