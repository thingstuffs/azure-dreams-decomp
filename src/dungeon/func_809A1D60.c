#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 D_8006CD58[];
extern u8 D_8006DE24[];
extern u8 D_80080A84;
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800DCF50;
extern s32 D_800DDAB8[];
extern void *D_80170880[];
extern void *D_80170898[];
extern u8 D_801710EC[];
extern u8 D_80175E40[];
extern u8 D_80175F40[];
extern u16 D_80175F6E;

extern s32 func_8003E4FC();
extern s32 func_8003F270();
extern s32 func_8003F540();
extern s32 func_800445E0();
extern s32 func_80047784();
extern void *func_800A05A4();
extern s32 func_800A2B04();
extern s32 func_800A4ACC();
extern s32 func_800A56E0();
extern s32 func_800A9400();
extern s32 func_800A94A0();
extern s32 func_800BB044();
extern void func_80173624() __attribute__((noreturn));
extern void func_80173698() __attribute__((noreturn));
extern void func_801736FC() __attribute__((noreturn));
extern void func_801737D4() __attribute__((noreturn));
extern void func_80173AB0() __attribute__((noreturn));
extern s32 func_80175814();
extern s32 func_80175D7C();


typedef struct S_80173560_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    union { u8 n; volatile u8 v; } unk_9B;   /* accessed as both */
} S_80173560_0;   /* arg0 in func_80173560 */

typedef struct S_80173560_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 u; s8 s; } unk_72;   /* accessed as both */
    union { u8 u; s8 s; } unk_73;   /* accessed as both */
} S_80173560_1;   /* arg3 in func_80173560 */

typedef struct S_80173560_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80173560_2_pre;   /* the 0x14 bytes before outer in func_80173560, addressed as outer[-1] */

typedef struct S_80173560_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173560_3;   /* inner in func_80173560 */

typedef struct S_80173560_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80173560_4;   /* arg2 in func_80173560 */


void func_80173560(void *arg0, void *arg1, void *raw_arg2, void *raw_arg3) {
    static void *const state_labels[] = {
        &&state0, &&state1, &&state2, &&state3, &&state4
    };
    static void *const item_labels[] = {
        &&item_a, &&item_b, &&item_c, &&item_default
    };
    void *arg2 = raw_arg2;
    void *arg3 = raw_arg3;
    s32 state;
    register s32 key ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 cond;
    register s32 sound_arg ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 s0;
    register s32 s1 ASM_REG("$17");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 temp;
    s32 index;
    s32 value;
    s32 tval;
    s32 vidx;
    s32 sv;
    register s32 raw ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    void *ptr;

    state = ((S_80173560_0 *)arg0)->unk_9B.n;
    ASM_KEEP(state);   /* MATCH pin: keeps a statement from moving across a call/branch */
    if ((u32)state >= 5) {
        return;
    }
    s1 = 0;
    ASM_KEEP(s1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    (void)state_labels;
    goto *D_80170880[state];

state0:
    key = ((S_80173560_1 *)arg3)->unk_46 & 0x3FFF;
    state = key - 1;
    if ((u32)state >= 7) {
        goto item_default;
    }
    (void)item_labels;
    goto *D_80170898[state];

item_a:
    s1 = 1;
    s0 = (s32)((u8 *)arg3 + 0xE);
    ASM_KEEP(s1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_TAILSLOT_PIN(s0);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80173624();

item_b:
    s1 = 1;
    s0 = (s32)((u8 *)arg3 + 0xB);
    ASM_KEEP(s1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_TAILSLOT_PIN(s0);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80173624();

item_c:
    s1 = 1;
    s0 = (s32)((u8 *)arg3 + 8);
    ASM_KEEP(s1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_TAILSLOT_PIN(s0);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80173624();

item_default:
    s0 = 0;
    ASM_KEEP(s0);   /* MATCH pin: retail basic-block layout depends on it */
    key = ((S_80173560_0 *)arg0)->unk_98;
    cond = s1;
    ((S_80173560_0 *)arg0)->unk_98 = key & 0xFF7F;
    state = *(u8 *)s0;
    if (cond != 0) {
        state |= 0x80;
    }
    D_80175F6E = state;
    if (cond != 0) {
        ((S_80173560_1 *)arg3)->unk_60 = D_800814A8;
        func_80173698();
    }

    vidx = *(u8 *)s0;
    tval = D_8006DE24[vidx * 20 + 0x12];
    if (tval == 2) {
        register void *a0v ASM_REG("$4") = arg3;   /* MATCH pin: retail delay-slot fill depends on it */
        void *outer = ((S_80173560_1 *)arg3)->unk_60;
        if (outer != 0) {
            register void *inner ASM_REG("$3") = ((S_80173560_2_pre *)outer)[-1].unk_00;   /* MATCH pin: load-bearing for the whole function shape */
            ((S_80173560_1 *)arg3)->unk_72.u = ((S_80173560_3 *)inner)->unk_24;
            ((S_80173560_1 *)arg3)->unk_73.u = ((S_80173560_3 *)inner)->unk_25;
            func_801736FC(a0v, (void *)s0);
        }
    } else {
        register s32 abs_value ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
        s32 abs_temp;
        ptr = func_800A05A4(arg3, ((S_80173560_4 *)arg2)->unk_24,
                            ((S_80173560_4 *)arg2)->unk_25, ((S_80173560_1 *)arg3)->unk_2A, 0x10);
        ((S_80173560_1 *)arg3)->unk_60 = ptr;
        abs_value = ((S_80173560_1 *)arg3)->unk_72.s;
        abs_temp = ((S_80173560_1 *)arg3)->unk_73.s;
        if (abs_value < 0) {
            abs_value = -abs_value;
        }
        if (abs_temp < 0) {
            abs_temp = -abs_temp;
        }
        ((S_80173560_1 *)arg3)->unk_72.u = abs_value;
        ((S_80173560_1 *)arg3)->unk_73.u = abs_temp;
    }

    if (func_800A94A0(arg3, (void *)s0, s1, (u8 *)arg0 + 0x98) == 0) {
        return;
    }
    if (s1 != 0) {
        D_800DCF50 = *(u8 *)s0;
        ((S_80173560_1 *)arg3)->unk_13 |= 0x80;
    }
    index = ((D_80083228 + ((S_80173560_1 *)arg3)->unk_2A + 0x100) >> 9) & 7;
    func_80047784(arg2, ((u8 *)((S_80173560_4 *)arg2)->unk_2C)[index], 2);
    ((S_80173560_4 *)arg2)->unk_14 |= 0x800;
    if (s1 != 0 && !(((S_80173560_1 *)arg3)->unk_13 & 0x80)) {
        func_80175814(arg3);
        func_80175D7C(arg3);
        func_801737D4();
    }
    ((S_80173560_1 *)arg3)->unk_13 &= 0x7F;
    *(u16 *)&D_80175E40[0x12E] &= 0xFF7F;
    func_800BB044(arg3);
    ((S_80173560_0 *)arg0)->unk_9B.n++;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    s0 = (s32)&D_80175F6E;
    if (*(u16 *)s0 & 0x80) {
        if (func_8003F270() != 0) {
            return;
        }
        func_800A56E0(0x300);
        key = (s16)func_800A9400(*(u16 *)s0 & 0x7F);
        ((S_80173560_0 *)arg0)->unk_96.s = D_80175F40[key] - 0x10;
        ((S_80173560_0 *)arg0)->unk_9B.n++;
        func_80173AB0();
    }
    key = ((S_80173560_0 *)arg0)->unk_9B.v;
    key += 2;
    ((S_80173560_0 *)arg0)->unk_9B.n = key;
    func_80173AB0();

state1:
    ((S_80173560_0 *)arg0)->unk_96.u -= D_80080A84;
    if (((S_80173560_0 *)arg0)->unk_96.s < 3) {
        ((S_80173560_4 *)arg2)->unk_14 &= 0xF7FF;
    }
    if (((S_80173560_0 *)arg0)->unk_96.s > 0) {
        return;
    }
    temp = D_80175F6E & 0x7F;
    s1 = (s32)D_800DDAB8;
    raw = func_800A9400(temp);
    sound_arg = 0x1300;
    ASM_USE(sound_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
    sv = raw << 16;
    sv >>= 16;
    func_800A56E0(sound_arg);
    func_8003F540(0, D_8006CD58[0],
                  ((s32 *)(((sv << 17) >> 14) + s1))[0],
                  ((s32 *)(((sv << 17) >> 14) + s1))[1]);
    value = func_800445E0();
    func_8003E4FC(0x15, value, 0);
    ((S_80173560_0 *)arg0)->unk_9B.n++;

state2:
    if (func_8003F270() != 0) {
        ((S_80173560_4 *)arg2)->unk_14 |= 0x800;
        func_80173AB0();
    }
    ((S_80173560_4 *)arg2)->unk_14 &= 0xF7FF;
    ((S_80173560_0 *)arg0)->unk_9B.n++;

state3:
    if (!(((S_80173560_0 *)arg0)->unk_98 & 0x80)) {
        ((S_80173560_4 *)arg2)->unk_05--;
    }

state4:
    if (((S_80173560_4 *)arg2)->unk_04 == 4) {
        if (!(((S_80173560_4 *)arg2)->unk_14 & 0x1000)) {
            goto check_high_flags;
        }
    } else {
check_high_flags:
        if (!(((S_80173560_4 *)arg2)->unk_14 & 0xE000)) {
            return;
        }
    }
    ((S_80173560_0 *)arg0)->unk_98 |= 0x80;
    if (!(((S_80173560_4 *)arg2)->unk_14 & 0xE000)) {
        return;
    }
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((S_80173560_4 *)arg2)->unk_24, ((S_80173560_4 *)arg2)->unk_25);
    ptr = D_80175E40;
    if (((S_80173560_4 *)arg2)->unk_2C != ptr) {
        (*(void * *)((u8 *)arg2 + (0x2C))) = ptr;
        index = ((D_80083228 + ((S_80173560_1 *)arg3)->unk_2A + 0x100) >> 9) & 7;
        func_80047784(arg2, D_80175E40[index], 0);
    }
    {
        s32 *blk = &D_80083460;
        if (blk[3] != 0) {
            return;
        }
        ((u16 *)blk)[5]--;
    }
    ((S_80173560_0 *)arg0)->unk_8C = D_801710EC;
    func_800A4ACC(arg3);
    ((S_80173560_1 *)arg3)->unk_6D--;
    ((S_80173560_1 *)arg3)->unk_46 &= 0x7FFF;
    ((S_80173560_0 *)arg0)->unk_98 &= 0xFFBF;
    ((S_80173560_1 *)arg3)->unk_73.u = 0;
    ((S_80173560_1 *)arg3)->unk_72.u = 0;
    func_800A56E0(0xB4);
}

/* MECHANISM: computed-goto dispatch through the RETAIL jtbls D_80170880/D_80170898
   (local label arrays are keepalive only). Four levers closed this row, each proven in a
   <=20-line /tmp microprobe before a metered eval: (1) $a0 ROLE SPLIT -- the shared
   `move a0,s2` is a BLOCK-SCOPED `void *a0v = arg3;` declared at the
   head of the ==2 arm (function-scope or a plain local both fail: a pseudo copy makes cse
   canonicalize the 0x72/0x73 store base onto $a0, and a function-scope hard-reg local steals
   $a0 from the D_8006DE24 index temp); (2) the pre-call D_80175F6E RMW is written through the
   neighbour symbol D_80175E40[0x12E] (same address) so gcc cannot CSE its %hi with the held
   post-call base in $s0, and ASM_SCHED_BARRIER() keeps that base's lui out of the 0x9B++
   load-delay; (3) state1 pins the func_800A9400 result in $v0 (`raw`) so `sll s0,v0,16` needs
   no copy, with ASM_USE(sound_arg) holding `li a0,0x1300` above the shifts; (4) the
   D_800DDAB8 row address is written INLINE in the func_8003F540 arg list (arg1's lui is then
   emitted first and the scheduler sinks its lw past the shift chain) with a state1-LOCAL `sv`
   so local-alloc can recycle $s0 for the address temp. `&D_80083460` is held in a plain
   pointer (DEPIN) -- a hard-reg pin fuses lui/addiu into one register, retail splits v0/v1. */
