#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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

void func_80173560(void *arg0, void *arg1, void *raw_arg2, void *raw_arg3) {
    static void *const state_labels[] = {
        &&state0, &&state1, &&state2, &&state3, &&state4
    };
    static void *const item_labels[] = {
        &&item_a, &&item_b, &&item_c, &&item_default
    };
    register void *arg2 ASM_REG("$19") = raw_arg2;
    register void *arg3 ASM_REG("$18") = raw_arg3;
    register s32 state ASM_REG("$3");
    register s32 key ASM_REG("$2");
    register s32 cond ASM_REG("$4");
    register s32 sound_arg ASM_REG("$4");
    s32 s0;
    register s32 s1 ASM_REG("$17");
    s32 temp;
    s32 index;
    s32 value;
    s32 tval;
    s32 vidx;
    s32 sv;
    register s32 raw ASM_REG("$2");
    void *ptr;

    ASM_KEEP(arg2);
    ASM_KEEP(arg3);
    state = FIELD(arg0, u8, 0x9B);
    ASM_KEEP(state);
    if ((u32)state >= 5) {
        return;
    }
    s1 = 0;
    ASM_KEEP(s1);
    (void)state_labels;
    goto *D_80170880[state];

state0:
    key = FIELD(arg3, u16, 0x46) & 0x3FFF;
    ASM_KEEP(key);
    state = key - 1;
    ASM_KEEP(state);
    if ((u32)state >= 7) {
        goto item_default;
    }
    (void)item_labels;
    goto *D_80170898[state];

item_a:
    s1 = 1;
    s0 = (s32)((u8 *)arg3 + 0xE);
    ASM_KEEP(s1);
    ASM_TAILSLOT_PIN(s0);
    func_80173624();

item_b:
    s1 = 1;
    s0 = (s32)((u8 *)arg3 + 0xB);
    ASM_KEEP(s1);
    ASM_TAILSLOT_PIN(s0);
    func_80173624();

item_c:
    s1 = 1;
    s0 = (s32)((u8 *)arg3 + 8);
    ASM_KEEP(s1);
    ASM_TAILSLOT_PIN(s0);
    func_80173624();

item_default:
    s0 = 0;
    ASM_KEEP(s0);
    key = FIELD(arg0, u16, 0x98);
    cond = s1;
    FIELD(arg0, u16, 0x98) = key & 0xFF7F;
    state = *(u8 *)s0;
    if (cond != 0) {
        state |= 0x80;
    }
    D_80175F6E = state;
    if (cond != 0) {
        FIELD(arg3, void *, 0x60) = D_800814A8;
        func_80173698();
    }

    vidx = *(u8 *)s0;
    tval = D_8006DE24[vidx * 20 + 0x12];
    if (tval == 2) {
        register void *a0v ASM_REG("$4") = arg3;
        register void *outer ASM_REG("$2") = FIELD(arg3, void *, 0x60);
        if (outer != 0) {
            register void *inner ASM_REG("$3") = FIELD(outer, void *, -0x14);
            FIELD(arg3, u8, 0x72) = FIELD(inner, u8, 0x24);
            FIELD(arg3, u8, 0x73) = FIELD(inner, u8, 0x25);
            func_801736FC(a0v, (void *)s0);
        }
    } else {
        register s32 abs_value ASM_REG("$2");
        register s32 abs_temp ASM_REG("$3");
        ptr = func_800A05A4(arg3, FIELD(arg2, u8, 0x24),
                            FIELD(arg2, u8, 0x25), FIELD(arg3, s16, 0x2A), 0x10);
        FIELD(arg3, void *, 0x60) = ptr;
        abs_value = FIELD(arg3, s8, 0x72);
        abs_temp = FIELD(arg3, s8, 0x73);
        if (abs_value < 0) {
            abs_value = -abs_value;
        }
        if (abs_temp < 0) {
            abs_temp = -abs_temp;
        }
        FIELD(arg3, u8, 0x72) = abs_value;
        FIELD(arg3, u8, 0x73) = abs_temp;
    }

    if (func_800A94A0(arg3, (void *)s0, s1, (u8 *)arg0 + 0x98) == 0) {
        return;
    }
    if (s1 != 0) {
        D_800DCF50 = *(u8 *)s0;
        FIELD(arg3, u8, 0x13) |= 0x80;
    }
    index = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
    func_80047784(arg2, ((u8 *)FIELD(arg2, void *, 0x2C))[index], 2);
    FIELD(arg2, u16, 0x14) |= 0x800;
    if (s1 != 0 && !(FIELD(arg3, u8, 0x13) & 0x80)) {
        func_80175814(arg3);
        func_80175D7C(arg3);
        func_801737D4();
    }
    FIELD(arg3, u8, 0x13) &= 0x7F;
    *(u16 *)&D_80175E40[0x12E] &= 0xFF7F;
    func_800BB044(arg3);
    FIELD(arg0, u8, 0x9B)++;
    ASM_SCHED_BARRIER();
    s0 = (s32)&D_80175F6E;
    if (*(u16 *)s0 & 0x80) {
        if (func_8003F270() != 0) {
            return;
        }
        func_800A56E0(0x300);
        key = (s16)func_800A9400(*(u16 *)s0 & 0x7F);
        ASM_KEEP(key);
        FIELD(arg0, s16, 0x96) = D_80175F40[key] - 0x10;
        FIELD(arg0, u8, 0x9B)++;
        func_80173AB0();
    }
    key = FIELD(arg0, volatile u8, 0x9B);
    key += 2;
    FIELD(arg0, u8, 0x9B) = key;
    func_80173AB0();

state1:
    FIELD(arg0, u16, 0x96) -= D_80080A84;
    if (FIELD(arg0, s16, 0x96) < 3) {
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
    }
    if (FIELD(arg0, s16, 0x96) > 0) {
        return;
    }
    temp = D_80175F6E & 0x7F;
    s1 = (s32)D_800DDAB8;
    raw = func_800A9400(temp);
    sound_arg = 0x1300;
    ASM_USE(sound_arg);
    sv = raw << 16;
    sv >>= 16;
    func_800A56E0(sound_arg);
    func_8003F540(0, D_8006CD58[0],
                  ((s32 *)(((sv << 17) >> 14) + s1))[0],
                  ((s32 *)(((sv << 17) >> 14) + s1))[1]);
    value = func_800445E0();
    func_8003E4FC(0x15, value, 0);
    FIELD(arg0, u8, 0x9B)++;

state2:
    if (func_8003F270() != 0) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        func_80173AB0();
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;

state3:
    if (!(FIELD(arg0, u16, 0x98) & 0x80)) {
        FIELD(arg2, u8, 5)--;
    }

state4:
    if (FIELD(arg2, s8, 4) == 4) {
        if (!(FIELD(arg2, u16, 0x14) & 0x1000)) {
            goto check_high_flags;
        }
    } else {
check_high_flags:
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            return;
        }
    }
    FIELD(arg0, u16, 0x98) |= 0x80;
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    ptr = D_80175E40;
    if (FIELD(arg2, void *, 0x2C) != ptr) {
        FIELD(arg2, void *, 0x2C) = ptr;
        index = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
        func_80047784(arg2, D_80175E40[index], 0);
    }
    {
        s32 *blk = &D_80083460;
        if (blk[3] != 0) {
            return;
        }
        ((u16 *)blk)[5]--;
    }
    FIELD(arg0, void *, 0x8C) = D_801710EC;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    FIELD(arg0, u16, 0x98) &= 0xFFBF;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    func_800A56E0(0xB4);
}

/* MECHANISM: computed-goto dispatch through the RETAIL jtbls D_80170880/D_80170898
   (local label arrays are keepalive only). Four levers closed this row, each proven in a
   <=20-line /tmp microprobe before a metered eval: (1) $a0 ROLE SPLIT -- the shared
   `move a0,s2` is a BLOCK-SCOPED `register void *a0v ASM_REG("$4") = arg3;` declared at the
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
