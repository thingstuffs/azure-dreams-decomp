#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern s32 D_80170F68;
extern u8 D_80173FB8[8];

extern s32 func_8003F270();
extern void func_80047784();
extern void *func_800A05A4();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern s32 func_800A94A0();
extern void func_800DA840();
extern void func_80172AE0(void) __attribute__((noreturn));
extern void func_80172AE8(void) __attribute__((noreturn));
extern void func_80172AF0(void) __attribute__((noreturn));
extern void func_80172AFC(void) __attribute__((noreturn));
extern void func_80172B9C(void) __attribute__((noreturn));


typedef struct S_801729D4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801729D4_0;   /* arg0 in func_801729D4 */

typedef struct S_801729D4_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x4];
    union { u8 u; s8 s; } unk_72;   /* accessed as both */
    union { u8 u; s8 s; } unk_73;   /* accessed as both */
} S_801729D4_1;   /* arg3 in func_801729D4 */

typedef struct S_801729D4_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801729D4_2_pre;   /* the 0x14 bytes before root in func_801729D4, addressed as root[-1] */

typedef struct S_801729D4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801729D4_3;   /* source in func_801729D4 */

typedef struct S_801729D4_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_801729D4_4;   /* arg2 in func_801729D4 */


typedef struct S_801729D4_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801729D4_6;   /* status in func_801729D4 */

void func_801729D4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&jt_1, &&jt_2, &&jt_3, &&jt_4, &&jt_5, &&jt_6, &&jt_7
    };
    u16 pos[3];
    u8 *anim;
    register s32 mode ASM_REG("$20");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 mode_test;
    s32 state;
    s32 kind;
    void *root;
    void *source;
    void *created;
    u8 *status;
    s32 x;
    s32 y;

    state = ((S_801729D4_0 *)arg0)->unk_9B;
    mode = 0;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    if (state == 2) {
        goto state_2;
    }
    return;

state_0:
    if (!(((S_801729D4_1 *)arg3)->unk_1C & 0x2000)) {
        goto no_special;
    }
    kind = (((S_801729D4_1 *)arg3)->unk_46 & 0x3FFF) - 1;
    if ((u32)kind >= 7U) {
        goto jt_4;
    }
    (void)jt_keep;
    goto *(((void **)D_80170838)[kind]);

jt_7:
    mode = 1;
    ASM_TAILSLOT_PIN(mode);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80172AE0();
jt_6:
    mode = 1;
    ASM_TAILSLOT_PIN(mode);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80172AE8();
jt_5:
    mode = 1;
    ASM_TAILSLOT_PIN(mode);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80172AF0();

no_special:
    kind = ((S_801729D4_1 *)arg3)->unk_46 & 0x3FFF;
    if (kind == 2) {
        goto no_2;
    }
    if (kind < 3) {
        if (kind == 1) {
            goto no_1;
        }
        anim = 0;
        ASM_KEEP(anim);   /* MATCH pin: retail delay-slot fill depends on it */
        func_80172AFC();
    }
    if (kind == 3) {
        goto no_3;
    }
    anim = 0;
    goto selected;

no_3:
jt_3:
    anim = (u8 *)arg3 + 0xE;
    ASM_TAILSLOT_PIN(anim);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80172AFC();
no_2:
jt_2:
    anim = (u8 *)arg3 + 0xB;
    ASM_TAILSLOT_PIN(anim);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80172AFC();
no_1:
jt_1:
    anim = (u8 *)arg3 + 8;
    ASM_TAILSLOT_PIN(anim);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80172AFC();
jt_4:
    anim = 0;

selected:
    if (*anim == 0) {
        goto empty_anim;
    }
    ((S_801729D4_0 *)arg0)->unk_98 &= 0xFF7F;
    ASM_KEEP(mode);   /* MATCH pin: retail delay-slot fill depends on it */
    mode_test = mode;
    ASM_KEEP(mode_test);   /* MATCH pin: retail delay-slot fill depends on it */
    if (mode_test != 0) {
        root = D_800814A8;
        ((S_801729D4_1 *)arg3)->unk_60 = root;
        source = ((S_801729D4_2_pre *)root)[-1].unk_00;
        ((S_801729D4_1 *)arg3)->unk_72.u = ((S_801729D4_3 *)source)->unk_24;
        ((S_801729D4_1 *)arg3)->unk_73.u = ((S_801729D4_3 *)source)->unk_25;
        func_80172B9C();
    }

    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    created = func_800A05A4(
        arg3, ((S_801729D4_4 *)arg2)->unk_24, ((S_801729D4_4 *)arg2)->unk_25,
        ((S_801729D4_1 *)arg3)->unk_2A, 0x10);
    ((S_801729D4_1 *)arg3)->unk_60 = created;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    x = ((S_801729D4_1 *)arg3)->unk_72.s;
    y = ((S_801729D4_1 *)arg3)->unk_73.s;
    if (x < 0) {
        x = -x;
    }
    if (y < 0) {
        y = -y;
    }
    ((S_801729D4_1 *)arg3)->unk_72.u = x;
    ((S_801729D4_1 *)arg3)->unk_73.u = y;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */

    pos[0] = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_u16.v;
    pos[1] = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_u16.v;
    pos[2] = ((Rec_D_800E3D7C *)arg1)->unk_08.at02_u16.v;
    if (func_800A94A0(arg3, anim, mode, (u8 *)arg0 + 0x98) != 0) {
        ((S_801729D4_4 *)arg2)->unk_14 &= 0xF7FF;
        func_800A56E0(0x703);
        func_800DA840(pos, (s16)((*anim - 1) % 3));
        ((S_801729D4_0 *)arg0)->unk_9B++;
        return;
    }
    goto done;

empty_anim:
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((S_801729D4_4 *)arg2)->unk_24, ((S_801729D4_4 *)arg2)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + (0xA6)))--;
    func_800A4ACC(arg3);
    ((S_801729D4_1 *)arg3)->unk_6D.u--;
    ((S_801729D4_0 *)arg0)->unk_8C = &D_80170F68;
    ((S_801729D4_1 *)arg3)->unk_73.u = 0;
    ((S_801729D4_1 *)arg3)->unk_72.u = 0;
    ((S_801729D4_1 *)arg3)->unk_46 &= 0x7FFF;
    return;

state_1:
    if (func_8003F270() != 0) {
        ((S_801729D4_4 *)arg2)->unk_14 |= 0x800;
        return;
    }
    ((S_801729D4_4 *)arg2)->unk_14 &= 0xF7FF;
    ((S_801729D4_0 *)arg0)->unk_9B++;

state_2:
    if ((((S_801729D4_4 *)arg2)->unk_04 == 8 &&
         (((S_801729D4_4 *)arg2)->unk_14 & 0x1000)) ||
        (((S_801729D4_4 *)arg2)->unk_14 & 0xE000)) {
        ((S_801729D4_4 *)arg2)->unk_14 |= 0x800;
        ((S_801729D4_0 *)arg0)->unk_96 = 3;
        ((S_801729D4_0 *)arg0)->unk_98 |= 0x80;
    }
    ((S_801729D4_0 *)arg0)->unk_96--;
    if ((s16)((S_801729D4_0 *)arg0)->unk_96 <= 0) {
        ((S_801729D4_0 *)arg0)->unk_96 = 0;
        ((S_801729D4_4 *)arg2)->unk_14 &= 0xF7FF;
    }
    if (((S_801729D4_4 *)arg2)->unk_14 & 0xE000) {
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((S_801729D4_4 *)arg2)->unk_24, ((S_801729D4_4 *)arg2)->unk_25);
        if (((S_801729D4_4 *)arg2)->unk_2C != D_80173FB8) {
            (*(void * *)((u8 *)arg2 + (0x2C))) = D_80173FB8;
            func_80047784(
                arg2,
                D_80173FB8[((D_80083228 + ((S_801729D4_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        status = (u8 *)&D_80083460;
        if (((S_801729D4_6 *)status)->unk_0C == 0) {
            ((S_801729D4_6 *)status)->unk_0A--;
            ((S_801729D4_4 *)arg2)->unk_14 &= 0xF7FF;
            ((S_801729D4_0 *)arg0)->unk_8C = &D_80170F68;
            func_800A4ACC(arg3);
            if (((S_801729D4_1 *)arg3)->unk_6D.s > 0) {
                ((S_801729D4_1 *)arg3)->unk_6D.u--;
            }
            ((S_801729D4_1 *)arg3)->unk_73.u = 0;
            ((S_801729D4_1 *)arg3)->unk_72.u = 0;
            ((S_801729D4_1 *)arg3)->unk_46 &= 0x7FFF;
            func_800A56E0(0xB4);
        }
    }

done:
    return;
}

/* MECHANISM: The s4 guard is delayed until its body use so the entry assignment
   can fill retail's state-dispatch branch slot without splitting the save block.
   Fences stop slot theft; distinct root/source/call ranges preserve v0/v1 roles. */
