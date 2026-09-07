#include "common.h"

typedef struct S_800249FC_0 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_800249FC_0;   /* arg2 in func_800249FC */

typedef struct S_800249FC_1_pre {
    u16 unk_00;
} S_800249FC_1_pre;   /* the 0x2 bytes before arg0 in func_800249FC, addressed as arg0[-1] */

typedef struct S_800249FC_1 {
    u8 pad_00[0x5A];
    union { s16 s; u16 u; } unk_5A;   /* accessed as both */
} S_800249FC_1;   /* arg0 in func_800249FC */



extern s32 func_8002406C(s32 arg0);
extern void func_80024A60(void) __attribute__((noreturn));
extern s16 D_80025B60[5];
extern s32 D_800814A0[3];

static void *const keepalive[] = { (void *)func_80024A60 };

void func_800249FC(void *arg0, s32 arg1, S_800249FC_0 *arg2) {
    s32 state;
    s16 timer;
    s32 result;
    u16 flags;
    u16 value;

    arg2->unk_1A += 0x2BC;
    state = ((S_800249FC_1 *)arg0)->unk_5A.s;
    D_80025B60[0] = 1;

    if (state >= 0x29) {
        u32 tail_v0;

        tail_v0 = arg2->unk_1E + 0xC8;
        ASM_TAILSLOT_PIN(tail_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_80024A60();
    }

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    if (state < 0x15) {
        value = arg2->unk_1E - 0xBE;
        arg2->unk_1E = value;
        arg2->unk_1C = value;
    }

    result = func_8002406C(3);
    flags = arg2->unk_14;
    if (flags & 0x80) {
        arg2->unk_14 = flags & 0xFF7F;
    } else if ((result << 16) != 0) {
        arg2->unk_14 = flags & 0xFF7F;
    } else {
        arg2->unk_14 = flags | 0x80;
    }

    timer = ((S_800249FC_1 *)arg0)->unk_5A.u - 1;
    ((S_800249FC_1 *)arg0)->unk_5A.s = timer;
    if ((timer << 16) <= 0) {
        ((S_800249FC_1_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

/* MECHANISM: The natural body holds arg0/arg2 in s1/s0 across the helper call,
   producing the retail 0x20 frame and save order; s32 state keeps the direct lh.
   A block barrier retains the first branch nop, while a guarded v0 tail-slot
   pin preserves the dead +0xC8 value; per-arm stores merge at the v0 join. */
