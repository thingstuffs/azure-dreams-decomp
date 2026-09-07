#include "common.h"

typedef struct S_801750F8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801750F8_0;   /* arg0 in func_801750F8 */

typedef struct S_801750F8_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801750F8_1;   /* arg3 in func_801750F8 */

typedef struct S_801750F8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_801750F8_2;   /* arg2 in func_801750F8 */

typedef struct S_801750F8_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801750F8_3;   /* counter in func_801750F8 */



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
    void *arg0 = arg0_in;
    void *arg1 = arg1_in;
    register void *arg2 ASM_REG("$17") = arg2_in;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *arg3 = arg3_in;
    u8 state;
    static void *const sw_keep[] = { &&L0, &&L1, &&L2, &&L3, &&L4, &&L5 };

    state = ((S_801750F8_0 *)arg0)->unk_9B;
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
    ((S_801750F8_1 *)arg3)->unk_2A = x;

    timer = ++((S_801750F8_0 *)arg0)->unk_96.s;
    if (timer >= 0x78) {
        ((S_801750F8_0 *)arg0)->unk_9B = 5;
        ((S_801750F8_0 *)arg0)->unk_96.s = 0;
        goto end;
    }

    flags = ((S_801750F8_1 *)arg3)->unk_14;
    if (!(flags & 0x00800000)) {
        goto end;
    }
    ((S_801750F8_1 *)arg3)->unk_14 = flags & 0xFF7FFFFF;
    ((S_801750F8_0 *)arg0)->unk_96.s = 0;
    ((S_801750F8_0 *)arg0)->unk_9B++;
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801755BC;
    func_80047784(arg2,
        D_801755BC[((D_80083228 + ((S_801750F8_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    func_800A56E0(0x51E);
    goto end;
    }

L1:
    if (!(((S_801750F8_2 *)arg2)->unk_14 & 0x6000)) {
        goto end;
    }
    ((S_801750F8_0 *)arg0)->unk_96.s = 0;
    ((S_801750F8_0 *)arg0)->unk_9B++;
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801755CC;
    func_80047784(arg2,
        D_801755CC[((D_80083228 + ((S_801750F8_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_801750F8_2 *)arg2)->unk_14 |= 0x0800;
    goto end;

L2:
    {
    s16 timer;

    timer = ++((S_801750F8_0 *)arg0)->unk_96.s;
    if (timer < 0xF) {
        goto end;
    }
    ((S_801750F8_0 *)arg0)->unk_96.s = 0;
    ((S_801750F8_0 *)arg0)->unk_9B++;
    ((S_801750F8_2 *)arg2)->unk_14 &= 0xF7FF;
    goto end;
    }

L3:
    {
    s32 x;
    s32 y;
    s16 timer;

    timer = ++((S_801750F8_0 *)arg0)->unk_96.s;
    if (timer < 3) {
        goto opposite_sound;
    }
    if (timer >= 7) {
        goto check_11;
    }
    x = ((S_801750F8_2 *)arg2)->unk_1C;
    y = ((S_801750F8_2 *)arg2)->unk_1E;
    x += 0x258;
    y -= 0x258;
    goto store_xy;

check_11:
    if (timer >= 0xB) {
        goto timer_ge_11;
    }

opposite_sound:
    x = ((S_801750F8_2 *)arg2)->unk_1C - 0x258;
    y = ((S_801750F8_2 *)arg2)->unk_1E + 0x258;
    ((S_801750F8_2 *)arg2)->unk_1C = x;
    ((S_801750F8_2 *)arg2)->unk_1E = y;
    func_800A56E0(0x51F);
    goto after_xy;

timer_ge_11:
    if (timer >= 0xF) {
        goto check_17;
    }
    x = ((S_801750F8_2 *)arg2)->unk_1C;
    y = ((S_801750F8_2 *)arg2)->unk_1E;
    x += 0x258;
    ASM_KEEP(x);   /* MATCH pin: retail branch polarity depends on it */
    y -= 0x258;
    goto store_xy;

check_17:
    if (timer >= 0x11) {
        goto after_xy;
    }
    x = ((S_801750F8_2 *)arg2)->unk_1C - 0x258;
    y = ((S_801750F8_2 *)arg2)->unk_1E + 0x258;

store_xy:
    ((S_801750F8_2 *)arg2)->unk_1C = x;
    ((S_801750F8_2 *)arg2)->unk_1E = y;

after_xy:
    if (((S_801750F8_0 *)arg0)->unk_96.u < 0x14) {
        goto end;
    }
    ((S_801750F8_0 *)arg0)->unk_96.s = 0;
    ((S_801750F8_0 *)arg0)->unk_9B++;
    ((S_801750F8_2 *)arg2)->unk_1E = 0x1000;
    ((S_801750F8_2 *)arg2)->unk_1C = 0x1000;
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801755C4;
    func_80047784(arg2,
        D_801755C4[((D_80083228 + ((S_801750F8_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    func_800A56E0(0x509);
    func_80174D98(arg0, arg1, arg2, arg3);
    goto end;
    }

L4:
    {
    s16 timer;

    timer = ++((S_801750F8_0 *)arg0)->unk_96.s;
    if (timer < 9) {
        goto end;
    }
    ((S_801750F8_0 *)arg0)->unk_96.s = 0;
    ((S_801750F8_0 *)arg0)->unk_9B++;
    goto end;
    }

L5:
    {
        u8 *counter = (u8 *)&D_80083460;

        ((S_801750F8_3 *)counter)->unk_0A--;
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8017555C;
        func_80047784(arg2,
            D_8017555C[((D_80083228 + ((S_801750F8_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        func_800AD594(arg3, 0x1000);
        ((S_801750F8_0 *)arg0)->unk_8C = D_801716F4;
        ((S_801750F8_3 *)counter)->unk_0C = 0;
        ((S_801750F8_1 *)arg3)->unk_46 &= 0x7FFF;
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
