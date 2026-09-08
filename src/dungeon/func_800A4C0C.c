#include "common.h"

extern u32 func_800A2BDC(void *arg0);
extern s32 func_800A41F0(void *arg0);
extern s32 func_8009B7E4(void *arg0, void *arg1);
extern void func_8009A3D0(s32 arg0, s32 arg1, s32 arg2);
extern void func_8009A21C(s32 arg0, s32 arg1, s32 arg2);
extern void func_800AA508(void *arg0, void *arg1, void *arg2, void *arg3);
extern void func_800AA5E4(void *arg0, void *arg1, void *arg2, void *arg3);
extern void *D_800814A8[4];

s32 func_800AA36C(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 result;
    register s32 old_x ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 old_y;
    s32 mode;
    u32 flags;
    u8 state;

    if (((func_800A2BDC(arg3) << 16) == 0) &&
        ((*(u16 *)((u8 *)arg0 - 2) & 0x8000) == 0) &&
        ((*(volatile u32 *)((u8 *)arg3 + 0x1C) & 0x80000) == 0) &&
        ((*(u32 *)((u8 *)arg3 + 0x14) & 0x100000) == 0) &&
        ((state = *(u8 *)((u8 *)D_800814A8[0] + 0x9A)) != 0x18) &&
        (state != 0x11) &&
        ((func_800A41F0(arg3) << 16) != 0)) {
        old_x = *(u8 *)((u8 *)arg2 + 0x24);
        old_y = *(u8 *)((u8 *)arg2 + 0x25);
        result = (s16)func_8009B7E4(arg2, arg3);
        mode = 0x3000;
        if (result != 0) {
            register u32 mask ASM_REG("$3") = 0x40000000;   /* MATCH pin: load-bearing for the whole function shape */
            s32 sound_x = old_x;
            s32 sound_y;
            ASM_KEEP(mask);   /* MATCH pin: retail schedule: same instructions, different order without it */
            ASM_KEEP(sound_x);   /* MATCH pin: retail keeps a computation the compiler would drop */
            flags = *(u32 *)((u8 *)arg3 + 0x1C) | mask;
            *(u32 *)((u8 *)arg3 + 0x1C) = flags;
            if (flags & 0x2000) {
                mode = 0x300;
            }
            sound_y = old_y;
            ASM_KEEP(sound_y);   /* MATCH pin: retail delay-slot contents depend on it */
            func_8009A3D0(sound_x, sound_y, mode);
            flags = *(u32 *)((u8 *)arg3 + 0x1C);
            func_8009A21C(*(u8 *)((u8 *)arg2 + 0x24),
                          *(u8 *)((u8 *)arg2 + 0x25),
                          (flags & 0x2000) ? 0x300 : 0x3000);

            if (result == 1) {
                func_800AA508(arg0, arg1, arg2, arg3);
                return 1;
                ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot contents depend on it */
                return 1;
            } else {
                func_800AA5E4(arg0, arg1, arg2, arg3);
                return 1;
            }
        }
    }
    return 0;
}

/* MECHANISM: The short-circuit success region yields the retail 0x30 frame and
   shared zero epilogue; s2/s3 plus v1/a0/a1 pins preserve full-width lbu roles.
   Duplicated cleanup calls and a one-sided barrier retain both j/li tail sites. */
