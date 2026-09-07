#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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
    register void *arg0 ASM_REG("$18") = in0;
    register void *arg1 ASM_REG("$20") = in1;
    register void *arg2 ASM_REG("$19") = in2;
    register void *arg3 ASM_REG("$16") = in3;
    register s32 special ASM_REG("$21");
    register u8 *kind_ptr ASM_REG("$17");
    u32 state;
    register u32 increment_state_value ASM_REG("$2");
    s32 kind;
    u32 kind_index;
    register u16 count ASM_REG("$2");
    register u16 next_count ASM_REG("$3");

    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    ASM_KEEP(arg3);

    state = FIELD(arg0, u8, 0x9B);
    if (state >= 9) {
        return;
    }
    special = 0;
    ASM_KEEP(special);
    (void)state_labels;
    goto *D_80170838[state];

state0:
    if (!(FIELD(arg3, s32, 0x1C) & 0x2000)) {
        goto kind_normal;
    }
    kind_index = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
    if (kind_index >= 7) {
        goto kind_default;
    }
    (void)kind_labels;
    goto *D_80170860[kind_index];

kind14_special:
    special = 1;
    ASM_TAILSLOT_PIN(special);
    func_80172670();
kind11_special:
    special = 1;
    ASM_TAILSLOT_PIN(special);
    func_80172678();
kind8_special:
    special = 1;
    ASM_TAILSLOT_PIN(special);
    func_80172680();

kind_normal:
    kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
    if (kind == 2) {
        goto kind2;
    }
    if (kind < 3) {
        if (kind == 1) {
            goto kind1;
        }
        kind_ptr = 0;
        ASM_KEEP(kind_ptr);
        func_8017268C();
    }
    if (kind != 3) {
        kind_ptr = 0;
        goto kind_chosen;
    }

kind3:
    kind_ptr = (u8 *)arg3 + 0xE;
    ASM_TAILSLOT_PIN(kind_ptr);
    func_8017268C();
kind2:
    kind_ptr = (u8 *)arg3 + 0xB;
    ASM_TAILSLOT_PIN(kind_ptr);
    func_8017268C();
kind1:
    kind_ptr = (u8 *)arg3 + 8;
    ASM_TAILSLOT_PIN(kind_ptr);
    func_8017268C();

kind_default:
    kind_ptr = 0;
kind_chosen:
    ASM_KEEP(kind_ptr);
    if (*kind_ptr == 0) {
        goto state0_empty;
    }

    FIELD(arg0, u16, 0x98) &= 0xFF7F;
    ASM_KEEP(special);
    {
        register s32 special_copy ASM_REG("$2") = special;

        ASM_KEEP(special_copy);
        if (special_copy) {
            FIELD(arg3, void *, 0x60) = D_800814A8;
            func_80172700();
        }
    }

    ASM_SCHED_BARRIER();
    if (D_8006DE24[*kind_ptr * 20 + 0x12] == 2) {
        u8 *linked = FIELD(arg3, u8 *, 0x60);
        if (linked != 0) {
            register u8 *src ASM_REG("$3") = FIELD(linked, u8 *, -0x14);

            ASM_KEEP(src);
            FIELD(arg3, u8, 0x72) = FIELD(src, u8, 0x24);
            FIELD(arg3, u8, 0x73) = FIELD(src, u8, 0x25);
            func_80172764();
        }
    } else {
        register s32 x ASM_REG("$2");
        register s32 y ASM_REG("$3");

        FIELD(arg3, void *, 0x60) = func_800A05A4(
            arg3,
            FIELD(arg2, u8, 0x24),
            FIELD(arg2, u8, 0x25),
            FIELD(arg3, s16, 0x2A),
            0x10);
        x = FIELD(arg3, s8, 0x72);
        y = FIELD(arg3, s8, 0x73);
        ASM_KEEP(x);
        ASM_KEEP(y);
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        FIELD(arg3, u8, 0x72) = x;
        FIELD(arg3, u8, 0x73) = y;
    }

state0_copy:
    if (func_800A94A0(arg3, kind_ptr, special, (u8 *)arg0 + 0x98) == 0) {
        return;
    }
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_80172B24();

state0_empty:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    D_8008346C = 0;
    FIELD(D_800814A8, u16, 0xA6)--;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = &D_80171514;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    func_80172B24();

state1:
    if (func_8003F270() != 0) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        func_80172B24();
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x703);
    count = FIELD(arg0, u16, 0x96);
    next_count = count + 1;
    ASM_KEEP(count);
    ASM_KEEP(next_count);
    FIELD(arg0, u16, 0x96) = next_count;
    if ((s16)count < 8 && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
        return;
    }
    increment_state_value = FIELD(arg0, u8, 0x9B);
    ASM_KEEP(increment_state_value);
    FIELD(arg0, u16, 0x96) = 0;
    func_80172998();

state2:
    if (FIELD(arg0, s16, 0xA2) != 0) {
        count = FIELD(arg0, u16, 0x96);
        next_count = count + 1;
        ASM_KEEP(count);
        ASM_KEEP(next_count);
        FIELD(arg0, u16, 0x96) = next_count;
        if ((s16)count < 15 && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
            return;
        }
    }
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x703);
    FIELD(arg2, u8 *, 0x2C) = D_80173EDC;
    func_80047784(
        arg2,
        D_80173EDC[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    func_80172B24();

state3:
    func_80170E18(arg0, arg1, arg2, arg3);
    count = FIELD(arg0, u16, 0x96);
    next_count = count + 1;
    ASM_KEEP(count);
    ASM_KEEP(next_count);
    FIELD(arg0, u16, 0x96) = next_count;
    if ((s16)count < 3 && !(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    FIELD(arg2, u16, 0x14) |= 0x800;
    increment_state_value = FIELD(arg0, u8, 0x9B);
    ASM_KEEP(increment_state_value);
increment_state:
    FIELD(arg0, u8, 0x9B) = increment_state_value + 1;
    func_80172B24();

state4:
    FIELD(arg2, u16, 0x14) |= 0x800;
    count = FIELD(arg0, u16, 0x96);
    next_count = count + 1;
    ASM_KEEP(count);
    ASM_KEEP(next_count);
    FIELD(arg0, u16, 0x96) = next_count;
    if ((s16)count < 10 && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
        return;
    }
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    func_80172B24();

state5:
state6:
    FIELD(arg0, u16, 0x98) |= 0x80;
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    func_80172B24();

state7:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg0, u8, 0x9B)++;
    if (FIELD(arg2, u8 *, 0x2C) == D_80173E8C) {
        return;
    }
    FIELD(arg2, u8 *, 0x2C) = D_80173E8C;
    func_80047784(
        arg2,
        D_80173E8C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x9E) = 0;
    FIELD(arg0, s16, 0x92) = -0x20;
    func_80172B24();

state8:
    {
        u8 *global = (u8 *)&D_80083460;

        if (FIELD(global, s32, 0x0C) != 0) {
            return;
        }
        FIELD(global, u16, 0x0A)--;
        FIELD(arg0, void *, 0x8C) = &D_80171514;
        func_800A4ACC(arg3);
        FIELD(arg3, u8, 0x6D)--;
        FIELD(arg3, u8, 0x73) = 0;
        FIELD(arg3, u8, 0x72) = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A56E0(0xB4);
    }
}

/* MECHANISM: The 0x38 frame holds s2/s4/s3/s0 args plus s5 special and s1 kind, with v0 pinned only for the shared increment.
   Named noreturn continuations recover all 18 retail absolute jumps; LEAD28 pins retain the s5/s1 delay-slot values.
   A scheduling barrier keeps the D_8006DE24 page load below the special-path branch. */
