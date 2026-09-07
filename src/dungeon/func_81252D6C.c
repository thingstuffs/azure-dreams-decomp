#include "common.h"


typedef s32 M2C_UNK;

extern s32 func_8003F270(void);
extern s32 func_80047784();
extern void *func_800A05A4();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern s32 func_800A94A0();
extern void func_80170E18();
extern void func_80172670(void) __attribute__((noreturn));
extern void func_80172678(void) __attribute__((noreturn));
extern void func_80172680(void) __attribute__((noreturn));
extern void func_8017268C(void) __attribute__((noreturn));
extern void func_80172700(void) __attribute__((noreturn));
extern void func_80172764(void) __attribute__((noreturn));
extern void func_80172998(void) __attribute__((noreturn));
extern void func_80172B24(void) __attribute__((noreturn));

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170838[];
extern void *D_80170860[];
extern M2C_UNK D_80171514;
extern u8 D_80173E8C[8];
extern u8 D_80173EDC[8];


typedef struct S_8017256C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
} S_8017256C_0;   /* arg0 in func_8017256C */

typedef struct S_8017256C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    union { void * p; u8 * p2; } unk_60;   /* accessed as both */
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 u; s8 s; } unk_72;   /* accessed as both */
    union { u8 u; s8 s; } unk_73;   /* accessed as both */
} S_8017256C_1;   /* arg3 in func_8017256C */

typedef struct S_8017256C_2_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_8017256C_2_pre;   /* the 0x14 bytes before linked in func_8017256C, addressed as linked[-1] */

typedef struct S_8017256C_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017256C_3;   /* src in func_8017256C */

typedef struct S_8017256C_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8017256C_4;   /* arg2 in func_8017256C */

typedef struct S_8017256C_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8017256C_5;   /* arg1 in func_8017256C */

typedef struct S_8017256C_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8017256C_6;   /* global in func_8017256C */

void func_8017256C(void *in0, void *in1, void *in2, void *in3)
{
    static void *const state_labels[] = {
        &&state0, &&state1, &&state2, &&state3, &&state4,
        &&state5, &&state6, &&state7, &&state8
    };
    static void *const kind_labels[] = {
        &&kind8_special, &&kind11_special, &&kind14_special,
        &&kind8_special, &&kind11_special, &&kind14_special,
        &&kind8_special
    };
    register void *arg0 ASM_REG("$18") = in0;   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *arg1 = in1;
    void *arg2 = in2;
    void *arg3 = in3;
    register s32 special ASM_REG("$21");   /* MATCH pin: keeps a constant in a register as retail does */
    register u8 *kind_ptr ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u32 state;
    u32 increment_state_value;
    s32 kind;
    u32 kind_index;
    u16 count;
    u16 next_count;

    ASM_KEEP(arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */

    state = ((S_8017256C_0 *)arg0)->unk_9B;
    if (state >= 9) {
        return;
    }
    special = 0;
    ASM_KEEP(special);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    (void)state_labels;
    goto *D_80170838[state];

state0:
    if (!(((S_8017256C_1 *)arg3)->unk_1C & 0x2000)) {
        goto kind_normal;
    }
    kind_index = (((S_8017256C_1 *)arg3)->unk_46 & 0x3FFF) - 1;
    if (kind_index >= 7) {
        goto kind_default;
    }
    (void)kind_labels;
    goto *D_80170860[kind_index];

kind14_special:
    special = 1;
    ASM_TAILSLOT_PIN(special);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80172670();
kind11_special:
    special = 1;
    ASM_TAILSLOT_PIN(special);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80172678();
kind8_special:
    special = 1;
    ASM_TAILSLOT_PIN(special);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80172680();

kind_normal:
    kind = ((S_8017256C_1 *)arg3)->unk_46 & 0x3FFF;
    if (kind == 2) {
        goto kind2;
    }
    if (kind < 3) {
        if (kind == 1) {
            goto kind1;
        }
        kind_ptr = 0;
        ASM_KEEP(kind_ptr);   /* MATCH pin: load-bearing for the whole function shape */
        func_8017268C();
    }
    if (kind != 3) {
        kind_ptr = 0;
        goto kind_chosen;
    }

kind3:
    kind_ptr = (u8 *)arg3 + 0xE;
    ASM_TAILSLOT_PIN(kind_ptr);   /* MATCH pin: retail delay-slot fill depends on it */
    func_8017268C();
kind2:
    kind_ptr = (u8 *)arg3 + 0xB;
    ASM_TAILSLOT_PIN(kind_ptr);   /* MATCH pin: retail delay-slot fill depends on it */
    func_8017268C();
kind1:
    kind_ptr = (u8 *)arg3 + 8;
    ASM_TAILSLOT_PIN(kind_ptr);   /* MATCH pin: retail delay-slot fill depends on it */
    func_8017268C();

kind_default:
    kind_ptr = 0;
kind_chosen:
    if (*kind_ptr == 0) {
        goto state0_empty;
    }

    ((S_8017256C_0 *)arg0)->unk_98 &= 0xFF7F;
    {
        s32 special_copy = special;

        ASM_KEEP(special_copy);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        if (special_copy) {
            ((S_8017256C_1 *)arg3)->unk_60.p = D_800814A8;
            func_80172700();
        }
    }

    ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    if (D_8006DE24[*kind_ptr * 20 + 0x12] == 2) {
        u8 *linked = ((S_8017256C_1 *)arg3)->unk_60.p2;
        if (linked != 0) {
            register u8 *src ASM_REG("$3") = ((S_8017256C_2_pre *)linked)[-1].unk_00;   /* MATCH pin: load-bearing for the whole function shape */

            ((S_8017256C_1 *)arg3)->unk_72.u = ((S_8017256C_3 *)src)->unk_24;
            ((S_8017256C_1 *)arg3)->unk_73.u = ((S_8017256C_3 *)src)->unk_25;
            func_80172764();
        }
    } else {
        register s32 x ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        s32 y;

        ((S_8017256C_1 *)arg3)->unk_60.p = func_800A05A4(
            arg3,
            ((S_8017256C_4 *)arg2)->unk_24,
            ((S_8017256C_4 *)arg2)->unk_25,
            ((S_8017256C_1 *)arg3)->unk_2A,
            0x10);
        x = ((S_8017256C_1 *)arg3)->unk_72.s;
        y = ((S_8017256C_1 *)arg3)->unk_73.s;
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        ((S_8017256C_1 *)arg3)->unk_72.u = x;
        ((S_8017256C_1 *)arg3)->unk_73.u = y;
    }

state0_copy:
    if (func_800A94A0(arg3, kind_ptr, special, (u8 *)arg0 + 0x98) == 0) {
        return;
    }
    ((S_8017256C_0 *)arg0)->unk_96 = 0;
    ((S_8017256C_0 *)arg0)->unk_9B++;
    ((S_8017256C_5 *)arg1)->unk_14 = 0;
    ((S_8017256C_5 *)arg1)->unk_10 = 0;
    ((S_8017256C_5 *)arg1)->unk_0C = 0;
    func_80172B24();

state0_empty:
    ((S_8017256C_5 *)arg1)->unk_14 = 0;
    ((S_8017256C_5 *)arg1)->unk_10 = 0;
    ((S_8017256C_5 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_8017256C_4 *)arg2)->unk_24, ((S_8017256C_4 *)arg2)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + (0xA6)))--;
    func_800A4ACC(arg3);
    ((S_8017256C_1 *)arg3)->unk_6D--;
    ((S_8017256C_0 *)arg0)->unk_8C = &D_80171514;
    ((S_8017256C_1 *)arg3)->unk_73.u = 0;
    ((S_8017256C_1 *)arg3)->unk_72.u = 0;
    ((S_8017256C_1 *)arg3)->unk_46 &= 0x7FFF;
    func_80172B24();

state1:
    if (func_8003F270() != 0) {
        ((S_8017256C_4 *)arg2)->unk_14 |= 0x800;
        func_80172B24();
    }
    ((S_8017256C_4 *)arg2)->unk_14 &= 0xF7FF;
    ((S_8017256C_0 *)arg0)->unk_9B++;
    func_800A56E0(0x703);
    count = ((S_8017256C_0 *)arg0)->unk_96;
    next_count = count + 1;
    ASM_KEEP(next_count);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ((S_8017256C_0 *)arg0)->unk_96 = next_count;
    if ((s16)count < 8 && !(((S_8017256C_4 *)arg2)->unk_14 & 0x8000)) {
        return;
    }
    increment_state_value = ((S_8017256C_0 *)arg0)->unk_9B;
    ASM_KEEP(increment_state_value);   /* MATCH pin: retail basic-block layout depends on it */
    ((S_8017256C_0 *)arg0)->unk_96 = 0;
    func_80172998();

state2:
    if (((S_8017256C_0 *)arg0)->unk_A2 != 0) {
        count = ((S_8017256C_0 *)arg0)->unk_96;
        next_count = count + 1;
        ASM_KEEP(next_count);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ((S_8017256C_0 *)arg0)->unk_96 = next_count;
        if ((s16)count < 15 && !(((S_8017256C_4 *)arg2)->unk_14 & 0x8000)) {
            return;
        }
    }
    ((S_8017256C_0 *)arg0)->unk_96 = 0;
    ((S_8017256C_0 *)arg0)->unk_9B++;
    func_800A56E0(0x703);
    (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80173EDC;
    func_80047784(
        arg2,
        D_80173EDC[((D_80083228 + ((S_8017256C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    func_80172B24();

state3:
    func_80170E18(arg0, arg1, arg2, arg3);
    count = ((S_8017256C_0 *)arg0)->unk_96;
    next_count = count + 1;
    ASM_KEEP(next_count);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ((S_8017256C_0 *)arg0)->unk_96 = next_count;
    if ((s16)count < 3 && !(((S_8017256C_4 *)arg2)->unk_14 & 0xE000)) {
        return;
    }
    ((S_8017256C_4 *)arg2)->unk_14 |= 0x800;
    increment_state_value = ((S_8017256C_0 *)arg0)->unk_9B;
increment_state:
    ((S_8017256C_0 *)arg0)->unk_9B = increment_state_value + 1;
    func_80172B24();

state4:
    ((S_8017256C_4 *)arg2)->unk_14 |= 0x800;
    count = ((S_8017256C_0 *)arg0)->unk_96;
    next_count = count + 1;
    ASM_KEEP(next_count);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ((S_8017256C_0 *)arg0)->unk_96 = next_count;
    if ((s16)count < 10 && !(((S_8017256C_4 *)arg2)->unk_14 & 0x8000)) {
        return;
    }
    ((S_8017256C_0 *)arg0)->unk_96 = 0;
    ((S_8017256C_0 *)arg0)->unk_9B++;
    ((S_8017256C_4 *)arg2)->unk_14 &= 0xF7FF;
    func_80172B24();

state5:
state6:
    ((S_8017256C_0 *)arg0)->unk_98 |= 0x80;
    ((S_8017256C_0 *)arg0)->unk_96 = 0;
    ((S_8017256C_0 *)arg0)->unk_9B++;
    func_80172B24();

state7:
    if (!(((S_8017256C_4 *)arg2)->unk_14 & 0xE000)) {
        return;
    }
    ((S_8017256C_5 *)arg1)->unk_14 = 0;
    ((S_8017256C_5 *)arg1)->unk_10 = 0;
    ((S_8017256C_5 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_8017256C_4 *)arg2)->unk_24, ((S_8017256C_4 *)arg2)->unk_25);
    ((S_8017256C_0 *)arg0)->unk_9B++;
    if (((S_8017256C_4 *)arg2)->unk_2C == D_80173E8C) {
        return;
    }
    (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80173E8C;
    func_80047784(
        arg2,
        D_80173E8C[((D_80083228 + ((S_8017256C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_8017256C_0 *)arg0)->unk_9E = 0;
    ((S_8017256C_0 *)arg0)->unk_92 = -0x20;
    func_80172B24();

state8:
    {
        u8 *global = (u8 *)&D_80083460;

        if (((S_8017256C_6 *)global)->unk_0C != 0) {
            return;
        }
        ((S_8017256C_6 *)global)->unk_0A--;
        ((S_8017256C_0 *)arg0)->unk_8C = &D_80171514;
        func_800A4ACC(arg3);
        ((S_8017256C_1 *)arg3)->unk_6D--;
        ((S_8017256C_1 *)arg3)->unk_73.u = 0;
        ((S_8017256C_1 *)arg3)->unk_72.u = 0;
        ((S_8017256C_1 *)arg3)->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
    }
}

/* MECHANISM: The 0x38 frame holds s2/s4/s3/s0 args plus s5 special and s1 kind, with v0 pinned only for the shared increment.
   Named noreturn continuations recover all 18 retail absolute jumps; LEAD28 pins retain the s5/s1 delay-slot values.
   A scheduling barrier keeps the D_8006DE24 page load below the special-path branch. */
