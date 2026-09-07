#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef s32 M2C_UNK;

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80173768(void) __attribute__((noreturn));
extern void func_80173894(void) __attribute__((noreturn));
extern s32 func_8017589C(void *, void *, void *);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80170850[20];
extern M2C_UNK D_80170E94;
extern u8 D_80175F10[8];
extern u8 D_80175F40[8];
extern u8 D_80175F68[8];

void func_801735BC(void *arg0, void *arg1, void *arg2, void *arg3)
{
    void *actor = arg3;
    u8 state;
    u16 flags;
    u16 flags3;
    u16 timer;
    s32 gate;
    static void *const keepalive[] = { &&L0, &&L1, &&L2, &&L3, &&L4 };

    state = FIELD(arg0, u8, 0x9B);
    if ((u32)state >= 5) {
        return;
    }
    goto *(((void **)D_80170850)[state]);

L0:
    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((s16)timer > 0) {
        return;
    }
    FIELD(arg2, u8 *, 0x2C) = D_80175F40;
    func_80047784(arg2,
        D_80175F40[((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_80173768();
    return;

L1:
    flags = FIELD(arg2, u16, 0x14);
    if (flags & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 4;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        if (FIELD(arg0, u8, 0xAE) != 2) {
            return;
        }
        func_8009C12C(actor, arg2, FIELD(actor, s16, 0x2A), 1);
        func_80173894();
        return;
    }
    if (FIELD(arg2, s8, 4) != 2) {
        return;
    }
    if (!(flags & 0x1000)) {
        return;
    }
    func_800A56E0(0x808);
    FIELD(arg0, s32, 0xB0) = func_8017589C(arg0, arg1, arg2);
    FIELD(arg0, u8, 0x9B)++;
    func_80173894();
    return;

L2:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    FIELD(arg2, u8 *, 0x2C) = D_80175F68;
    func_80047784(arg2,
        D_80175F68[((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg2, u16, 0x14) |= 0x0800;
    FIELD(arg0, u8, 0x9B)++;
    func_80173894();
    return;

L3:
    flags3 = FIELD(arg2, u16, 0x14);
    if (flags3 & 0x8000) {
        FIELD(arg2, u8 *, 0x2C) = D_80175F68;
        func_80047784(arg2,
            D_80175F68[((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg2, u16, 0x14) |= 0x0800;
        func_80173894();
        return;
    }
    gate = flags3 & 0x6000;
    goto Lgate;

L4:
    gate = FIELD(arg2, u16, 0x14) & 0xE000;
Lgate:
    if (gate == 0) {
        return;
    }
    FIELD(arg2, u8 *, 0x2C) = D_80175F10;
    func_80047784(arg2,
        D_80175F10[((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u8, 0xAE) = 0;
    FIELD(actor, u32, 0x14) &= ~0x40000000;
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    func_800AD594(actor, 0x800);
    FIELD(actor, u16, 0x46) &= 0x7FFF;
    FIELD(arg0, M2C_UNK *, 0x8C) = &D_80170E94;
    D_8008346C = 0;
}

/* MECHANISM: two edits closed this from the prior aligned-3 plateau.
   (1) LOCAL JOIN, not a phantom noreturn sibcall: retail's `j 0x801737F0` out of
   case 3 lands on the SHARED `beqz` of case 4, so the `andi v0,v1,0x6000` in that
   j-delay is a live gate value, not dead code — written as `gate = flags3 & 0x6000;
   goto Lgate;` with `Lgate:` between case 4's mask and the shared test.
   (2) SPLIT (one name per live range): case 1 and case 3 must NOT share one `flags`
   local — case 1's copy is live across `lb $v1,4($s0)`, so the shared pseudo inherits
   that $v1 conflict and case 3's load colors $a0 instead of retail's $v1.
   Frame/dispatch unchanged: extern jtbl computed goto through D_80170850 + keepalive,
   args (arg0,arg1,arg2,arg3) -> s2,s3,s0,s1, tail joins via noreturn func_80173768/894. */
