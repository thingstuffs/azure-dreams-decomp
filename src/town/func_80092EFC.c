#include "common.h"

extern s16 D_8006ADD4[5];
extern u8 D_80083160[];
extern s32 D_80090A64;
extern s32 D_80091260;
extern s32 D_80091528;
extern s32 D_80097D2C[3];
extern s16 D_800D01F8[];
extern u8 D_80100D98[];
extern s32 D_80100DB0[3];
extern s32 D_80100E18[3];

extern s32 func_800352FC(void);
extern s32 func_8003BD84(s32, s32);
extern void func_800489F4(void *, u8, s8, s32);
extern void func_80048AC8(void *, s32);
extern void to_camera_zero_00(void);
extern void func_80090A04(void *);
extern s16 func_80094AA0(s16, s16, s32);
extern s32 func_80095360(s16);
extern void func_80095544(void *);
extern void func_80096868(void *, void *, void *);
extern void func_800A48B0(void *, void *);

void func_8009065C(void *arg0, void *arg1, void *arg2) {
    u8 *base = D_80083160;
    void *callback;
    s32 initial_flags;
    s32 flags;
    s32 movement;
    s32 index;

    func_80095544(arg1);

    if (D_80100DB0[0] != 0) {
        goto after_initial;
    }
    if (*(u16 *)(base + 0xC8) >= 0x800) {
        *(s16 *)(base + 0xC8) |= 0xF000;
    }

    callback = *(void **)arg0;
    if (callback == (void *)D_80097D2C) {
        goto active_callback;
    }
    if (callback == (void *)&D_80090A64) {
        goto active_callback;
    }
    /* garbage-passthru: a1/a2/a3 are caller-saved residue after func_80095544. */
    if (func_800352FC() == 0) {
        goto inactive_callback;
    }

active_callback:
    if (D_8006ADD4[0] != 12) {
        goto active_height;
    }
shared_exit:
    to_camera_zero_00();
    goto after_initial;

active_height:
    if (*(s16 *)((u8 *)arg1 + 6) < 0x400) {
        goto low_height;
    }
    goto after_initial;

inactive_callback:
    if (D_8006ADD4[0] != 12) {
        goto movement_path;
    }
    initial_flags = *(s32 *)(base + 8);
    if (initial_flags & 8) {
        *(s16 *)(base + 0xC8) -= 0x20;
        if (*(s16 *)(base + 0xC8) < -0x1E0) {
            *(s16 *)(base + 0xC8) = -0x1E0;
            goto after_initial;
        }
    } else if (initial_flags & 4) {
        *(s16 *)(base + 0xC8) += 0x20;
        if (*(s16 *)(base + 0xC8) > 0x1E0) {
            *(s16 *)(base + 0xC8) = 0x1E0;
            goto after_initial;
        }
    } else {
        goto shared_exit;
    }
    goto after_initial;

movement_path:
    if (*(s16 *)((u8 *)arg1 + 6) < 0x400) {
low_height:
        func_80090A04(arg1);
        goto after_initial;
    }
    movement = func_8003BD84(*(s32 *)((u8 *)arg1 + 0xC),
                             *(s32 *)((u8 *)arg1 + 0x10));
    if (movement == 0) {
        *(s16 *)(base + 0xC8) =
            (*(u16 *)(base + 0xC8) + 8) & 0xFFF0;
    }
    movement /= 0x10000;
    flags = *(s32 *)(base + 8);
    if (flags & 8) {
        *(s16 *)(base + 0xC8) -= 0x10 + movement;
    }
    if (flags & 4) {
        *(s16 *)(base + 0xC8) += 0x10 + movement;
    }

after_initial:

    callback = *(void **)arg0;
    if ((callback == (void *)&D_80091260) ||
        (callback == (void *)&D_80091528)) {
        *(s16 *)((u8 *)arg0 + 0x18) =
            func_80094AA0(*(s16 *)((u8 *)arg0 + 0x18),
                          *(s16 *)((u8 *)arg0 + 0x10), 0x200);
    } else {
        *(s16 *)((u8 *)arg0 + 0x18) = *(u16 *)((u8 *)arg0 + 0x10);
    }
    index = func_80095360(*(s16 *)((u8 *)arg0 + 0x18));
    if (*(s16 *)((u8 *)arg0 + 0x12) != index) {
        func_800489F4(arg2,
                      *(u8 *)(*(u8 **)((u8 *)arg0 + 0x1C) + index),
                      *(s8 *)((u8 *)arg2 + 4), 0);
        *(s16 *)((u8 *)arg0 + 0x12) = index;
    }

    {
        u16 bit_value;

        if (D_800D01F8[index] != 0) {
            bit_value = *(u16 *)((u8 *)arg2 + 0x14) | 1;
        } else {
            bit_value = *(u16 *)((u8 *)arg2 + 0x14) & 0xFFFE;
        }
        *(u16 *)((u8 *)arg2 + 0x14) = bit_value;
    }
    do {
        func_80096868(arg0, arg1, arg2);
    } while (0);
    func_80048AC8(arg2, 0);

    {
        u8 *state = D_80100D98;

        func_800A48B0(state, arg1);
    if (D_80100E18[0] == 0) {
        *(s32 *)(state + 8) = 0;
        return;
    }
    if (D_80100E18[0] == 2) {
        *(s32 *)(state + 8) /= 2;
        }
    }
}

/* MECHANISM: The three arguments stay in s1/s2/s3 and D_80083160 in s0, yielding the retail 0x28 frame.
   A one-sided schedule barrier preserves both clamp tails; ASM_TAILSLOT_PIN sinks the dead OR into its j slot.
   Memory fences retain the clear/store call sequence and force the post-store signed-halfword reload. */
