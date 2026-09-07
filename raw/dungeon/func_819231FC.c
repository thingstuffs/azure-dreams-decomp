#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern s32 func_8002406C(s32 arg0);
extern void func_80024A60(void) __attribute__((noreturn));
extern s16 D_80025B60[5];
extern s32 D_800814A0[3];

static void *const keepalive[] = { (void *)func_80024A60 };

void func_800249FC(void *arg0, s32 arg1, void *arg2) {
    s32 state;
    s16 timer;
    s32 result;
    u16 flags;
    u16 value;

    FIELD(arg2, u16, 0x1A) += 0x2BC;
    state = FIELD(arg0, s16, 0x5A);
    D_80025B60[0] = 1;

    if (state >= 0x29) {
        u32 tail_v0;

        tail_v0 = FIELD(arg2, u16, 0x1E) + 0xC8;
        ASM_TAILSLOT_PIN(tail_v0);
        func_80024A60();
    }

    ASM_SCHED_BARRIER();
    if (state < 0x15) {
        value = FIELD(arg2, u16, 0x1E) - 0xBE;
        FIELD(arg2, u16, 0x1E) = value;
        FIELD(arg2, u16, 0x1C) = value;
    }

    result = func_8002406C(3);
    flags = FIELD(arg2, u16, 0x14);
    if (flags & 0x80) {
        FIELD(arg2, u16, 0x14) = flags & 0xFF7F;
    } else if ((result << 16) != 0) {
        FIELD(arg2, u16, 0x14) = flags & 0xFF7F;
    } else {
        FIELD(arg2, u16, 0x14) = flags | 0x80;
    }

    timer = FIELD(arg0, u16, 0x5A) - 1;
    FIELD(arg0, s16, 0x5A) = timer;
    if ((timer << 16) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

/* MECHANISM: The natural body holds arg0/arg2 in s1/s0 across the helper call,
   producing the retail 0x20 frame and save order; s32 state keeps the direct lh.
   A block barrier retains the first branch nop, while a guarded v0 tail-slot
   pin preserves the dead +0xC8 value; per-arm stores merge at the v0 join. */
