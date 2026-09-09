#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"



extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern s32 func_8017589C(void *, void *, void *);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80170850[20];
extern M2C_UNK D_80170E94;
extern u8 D_80175F10[8];
extern u8 D_80175F40[8];
extern u8 D_80175F68[8];


typedef struct S_801735BC_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x12];
    u8 unk_AE;
    u8 pad_AF[0x1];
    s32 unk_B0;
} S_801735BC_0;   /* arg0 in func_801735BC */

typedef struct S_801735BC_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801735BC_1;   /* actor in func_801735BC */



void func_801735BC(void *incoming_arg0, void *incoming_arg1, void *incoming_arg2, void *arg3)
{
    /* MATCH: the local state join must retain arg0 in retail's s2. */
    register void *arg0 ASM_REG("$18") = incoming_arg0;
    void *arg1 = incoming_arg1;
    void *arg2 = incoming_arg2;
    void *actor = arg3;
    u8 state;
    u16 flags;
    u16 flags3;
    u16 timer;
    s32 gate;
    static void *const keepalive[] = { &&L0, &&L1, &&L2, &&L3, &&L4 };

    state = ((S_801735BC_0 *)arg0)->unk_9B;
    if ((u32)state >= 5) {
        return;
    }
    goto *(((void **)D_80170850)[state]);

L0:
    timer = ((S_801735BC_0 *)arg0)->unk_96 - 1;
    ((S_801735BC_0 *)arg0)->unk_96 = timer;
    if ((s16)timer > 0) {
        return;
    }
    (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80175F40;
    func_80047784(arg2,
        D_80175F40[((D_80083228 + ((S_801735BC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    goto Ladvance;

L1:
    flags = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v;
    if (flags & 0x8000) {
        ((S_801735BC_0 *)arg0)->unk_9B = 4;
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x6000;
        if (((S_801735BC_0 *)arg0)->unk_AE != 2) {
            return;
        }
        func_8009C12C(actor, arg2, ((S_801735BC_1 *)actor)->unk_2A, 1);
        return;
    }
    if (((Rec_D_80082E80 *)arg2)->unk_04.as_s8 != 2) {
        return;
    }
    if (!(flags & 0x1000)) {
        return;
    }
    func_800A56E0(0x808);
    ((S_801735BC_0 *)arg0)->unk_B0 = func_8017589C(arg0, arg1, arg2);
    ((S_801735BC_0 *)arg0)->unk_9B++;
    return;

L2:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80175F68;
    func_80047784(arg2,
        D_80175F68[((D_80083228 + ((S_801735BC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x0800;
Ladvance:
    ((S_801735BC_0 *)arg0)->unk_9B++;
    return;

L3:
    flags3 = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v;
    if (flags3 & 0x8000) {
        (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80175F68;
        func_80047784(arg2,
            D_80175F68[((D_80083228 + ((S_801735BC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x0800;
        return;
    }
    gate = flags3 & 0x6000;
    goto Lgate;

L4:
    gate = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000;
Lgate:
    if (gate == 0) {
        return;
    }
    (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80175F10;
    func_80047784(arg2,
        D_80175F10[((D_80083228 + ((S_801735BC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_801735BC_0 *)arg0)->unk_AE = 0;
    ((S_801735BC_1 *)actor)->unk_14 &= ~0x40000000;
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    func_800AD594(actor, 0x800);
    ((S_801735BC_1 *)actor)->unk_46 &= 0x7FFF;
    (*(M2C_UNK * *)((u8 *)arg0 + (0x8C))) = &D_80170E94;
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
