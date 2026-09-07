#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_801744E0(void *);
extern void func_80047784(void *, s32, s32);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80174D98(void *, void *, void *, void *);

extern s16 D_80083228;
extern s32 D_80083460;
extern void *D_80170888[];
extern u8 D_801716F4[];
extern u8 D_8017555C[];
extern u8 D_801755BC[];
extern u8 D_801755C4[];
extern u8 D_801755CC[];

void func_801750F8(void *arg0_in, void *arg1_in, void *arg2_in, void *arg3_in)
{
    register void *arg0 ASM_REG("$18") = arg0_in;
    register void *arg1 ASM_REG("$16") = arg1_in;
    register void *arg2 ASM_REG("$17") = arg2_in;
    register void *arg3 ASM_REG("$19") = arg3_in;
    u8 state;
    static void *const sw_keep[] = { &&L0, &&L1, &&L2, &&L3, &&L4, &&L5 };

    state = FIELD(arg0, u8, 0x9B);
    if ((u32)state >= 6) {
        goto end;
    }
    (void)sw_keep;
    goto *D_80170888[state];

L0:
    {
    s32 x;
    s16 timer;
    u32 flags;

    x = func_801744E0(arg1);
    x = (x << 16) >> 7;
    FIELD(arg3, s16, 0x2A) = x;

    timer = ++FIELD(arg0, u16, 0x96);
    if (timer >= 0x78) {
        FIELD(arg0, u8, 0x9B) = 5;
        FIELD(arg0, u16, 0x96) = 0;
        goto end;
    }

    flags = FIELD(arg3, u32, 0x14);
    if (!(flags & 0x00800000)) {
        goto end;
    }
    FIELD(arg3, u32, 0x14) = flags & 0xFF7FFFFF;
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg2, u8 *, 0x2C) = D_801755BC;
    func_80047784(arg2,
        D_801755BC[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    func_800A56E0(0x51E);
    goto end;
    }

L1:
    if (!(FIELD(arg2, u16, 0x14) & 0x6000)) {
        goto end;
    }
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg2, u8 *, 0x2C) = D_801755CC;
    func_80047784(arg2,
        D_801755CC[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg2, u16, 0x14) |= 0x0800;
    goto end;

L2:
    {
    s16 timer;

    timer = ++FIELD(arg0, u16, 0x96);
    if (timer < 0xF) {
        goto end;
    }
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    goto end;
    }

L3:
    {
    s32 x;
    s32 y;
    s16 timer;

    timer = ++FIELD(arg0, u16, 0x96);
    if (timer < 3) {
        goto opposite_sound;
    }
    if (timer >= 7) {
        goto check_11;
    }
    x = FIELD(arg2, u16, 0x1C);
    y = FIELD(arg2, u16, 0x1E);
    ASM_KEEP(x);
    x += 0x258;
    y -= 0x258;
    goto store_xy;

check_11:
    if (timer >= 0xB) {
        goto timer_ge_11;
    }

opposite_sound:
    x = FIELD(arg2, u16, 0x1C) - 0x258;
    y = FIELD(arg2, u16, 0x1E) + 0x258;
    FIELD(arg2, u16, 0x1C) = x;
    FIELD(arg2, u16, 0x1E) = y;
    func_800A56E0(0x51F);
    goto after_xy;

timer_ge_11:
    if (timer >= 0xF) {
        goto check_17;
    }
    x = FIELD(arg2, u16, 0x1C);
    y = FIELD(arg2, u16, 0x1E);
    x += 0x258;
    ASM_KEEP(x);
    y -= 0x258;
    goto store_xy;

check_17:
    if (timer >= 0x11) {
        goto after_xy;
    }
    x = FIELD(arg2, u16, 0x1C) - 0x258;
    y = FIELD(arg2, u16, 0x1E) + 0x258;

store_xy:
    FIELD(arg2, u16, 0x1C) = x;
    FIELD(arg2, u16, 0x1E) = y;

after_xy:
    if (FIELD(arg0, s16, 0x96) < 0x14) {
        goto end;
    }
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg2, u16, 0x1E) = 0x1000;
    FIELD(arg2, u16, 0x1C) = 0x1000;
    FIELD(arg2, u8 *, 0x2C) = D_801755C4;
    func_80047784(arg2,
        D_801755C4[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    func_800A56E0(0x509);
    func_80174D98(arg0, arg1, arg2, arg3);
    goto end;
    }

L4:
    {
    s16 timer;

    timer = ++FIELD(arg0, u16, 0x96);
    if (timer < 9) {
        goto end;
    }
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    goto end;
    }

L5:
    {
        u8 *counter = (u8 *)&D_80083460;

        FIELD(counter, u16, 0xA)--;
        FIELD(arg2, u8 *, 0x2C) = D_8017555C;
        func_80047784(arg2,
            D_8017555C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        func_800AD594(arg3, 0x1000);
        FIELD(arg0, u8 *, 0x8C) = D_801716F4;
        FIELD(counter, s32, 0xC) = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
    }

end:
    return;
}

/* MECHANISM: frame is 4 param->callee-saved copies; all four MUST be declared as
   ASM_REG register locals in parameter order ($18,$16,$17,$19) so the copies emit
   a0,a1,a2,a3 and each sw pairs with its move (unpinned params emit via assign_parms
   and reorder to a1,a3,a0,a2).  L3's two identical "+0x258" arms are cross-jumped
   into one block unless each carries an ASM_KEEP at a DIFFERENT depth (after both
   lhu in arm A, after the first addiu in arm C): the volatile asm stops
   find_cross_jump's backward match while leaving the trailing addiu free to fill the
   `j` delay slot.  Config: 2.7.2-cdk-G0 -- 2.8.1-G0's dbr refuses a split-address
   %hi (HIGH) insn in a branch delay slot and steals `move a0,s1` instead (+1 word
   at each of the two table sites); cdk fills both slots with `lui a1,%hi(tbl)`. */
