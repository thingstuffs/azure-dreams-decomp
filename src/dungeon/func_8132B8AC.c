#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_8016A8B4[];
typedef struct {
    s16 x;
    u16 y;
} InitPair;
typedef struct {
    InitPair pair[8];
} __attribute__((packed)) InitBlock;
void func_800419EC();            /* extern */
void func_80047738();              /* extern */
void func_80047784();         /* extern */
void func_800478B8();  /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80069EF8();                                /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_80170C3C();                            /* extern */
M2C_UNK func_80171A10(); /* extern */
M2C_UNK func_80172A14();      /* extern */
M2C_UNK func_80172B00();      /* extern */
M2C_UNK func_80172CC8(); /* extern */
M2C_UNK func_80172F44(); /* extern */
void func_80173240() __attribute__((noreturn));      /* extern */
void func_801735B0() __attribute__((noreturn));      /* extern */
void func_8017378C() __attribute__((noreturn));      /* extern */
void func_80173C7C() __attribute__((noreturn));      /* extern */
void func_80173CE8() __attribute__((noreturn));      /* extern */
void func_80173CF8() __attribute__((noreturn));      /* extern */
void func_80173D34() __attribute__((noreturn));      /* extern */
void func_80173D38() __attribute__((noreturn));      /* extern */
void func_80173DC4() __attribute__((noreturn));      /* extern */
extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern InitBlock D_8016A894;
extern u8 D_80174C64[];
extern u8 D_80174C6C[];
extern u8 D_80174C7C[];
extern u8 D_80174C84[];
extern u8 D_80174C8C[];
extern u8 D_80174C94[];
extern s32 D_80174CE0;

void func_801730AC(void *in0, void *in1, void *in2) {
    void *arg0 = in0;
    void *arg1 = in1;
    void *arg2 = in2;
    InitBlock sp18;
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19, &&jt_c20 };
    s32 temp_a2;
    s16 temp_s2;
    s16 temp_v0_10;
    s16 temp_v1_5;
    s16 sprite_angle_base;
    s16 sprite_angle_delta;
    s32 *temp_v1_2;
    s32 *temp_v1_3;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1_2;
    s32 temp_pos_x;
    s32 temp_pos_y;
    s32 var_a0;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 one;
    s32 one_2;
    u16 temp_v0;
    u16 temp_v0_11;
    u16 temp_v0_12;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_8;
    u16 temp_v0_9;
    u16 temp_v1_4;
    u16 temp_v1_6;
    u8 temp_v1;
    u8 *case11_current;
    u8 *state_row;
    u8 *state_base;
    u8 *state_table;
    void *temp_s3;
    s32 tail_test;
    register s32 tail_state ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register u8 *tail_sprite ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    register void *particle_a0 ASM_REG("$4");   /* MATCH pin: retail keeps a computation the compiler would drop */
    s32 particle_a2;
    s32 particle_a3;
    s32 particle_random;

    sp18 = D_8016A894;
    ASM_KEEP(arg1);   /* MATCH pin: load-bearing for the whole function shape */
    temp_s3 = D_80174CE0 + 0x20;
    func_800478B8(arg2);
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9A);
    if (temp_v1 >= 0x15U) {
        goto block_97;
    }
    (void)jt_keep; goto *D_8016A8B4[(u32)(temp_v1)];
jt_c0:
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x96);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0 + 1);
    if ((s16) temp_v0 < 0x1E) {
        goto block_97;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
    M2C_FIELD(arg1, s32 *, 0xC) = 0xFFF80000;
    func_80173D34();
    return;
jt_c1:
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    tail_test = M2C_FIELD(arg0, u16 *, 0x96) + 1;
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) tail_test;
    tail_test = (s16) tail_test < 0x28;
    ASM_TAILSLOT_PIN(tail_test);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    func_80173240();
    return;
jt_c3:
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFF7F);
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
    if ((s16) temp_v0_2 < 0xA) {
        goto block_98;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    func_80173D34();
    return;
jt_c5:
    M2C_FIELD(arg2, u8 **, 0x2C) = D_80174C8C;
    func_80047784(arg2, D_80174C8C[((s32) (D_80083228 + M2C_FIELD(temp_s3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    func_800A56E0(0x801);
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
    func_80173D34();
    return;
jt_c6:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x6000)) {
        goto block_98;
    }
    M2C_FIELD(arg0, s8 *, 0xB6) = 0;
    M2C_FIELD(temp_s3, u16 *, 0x88) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
    if (M2C_FIELD(arg2, u8 **, 0x2C) == D_80174C64) {
        goto block_97;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_80174C64;
    func_80047784(arg2, D_80174C64[((s32) (D_80083228 + M2C_FIELD(temp_s3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    {
        register void *case6_a0 ASM_REG("$4") = arg0;   /* MATCH pin: retail keeps a computation the compiler would drop */
        void *case6_a1 = arg1;
        void *case6_a2;
        u8 case6_state;

        ASM_SET(arg0);   /* MATCH pin: load-bearing for the whole function shape */
        case6_state = M2C_FIELD(arg0, u8 *, 0x9A);
        case6_a2 = arg2;
        M2C_FIELD(arg0, u16 *, 0x96) = 0U;
        M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (case6_state + 1);
        func_80172B00(case6_a0, case6_a1, case6_a2);
    }
    tail_test = 0x80170000;
    ASM_PAGEBASE_PIN(tail_test);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80173D38();
    return;
jt_c7:
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) (M2C_FIELD(arg1, u16 *, 0xA) - 8);
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_3;
    if ((s16) temp_v0_3 < 4) {
        goto block_98;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, u16 *, 0x9E) = 0U;
    M2C_FIELD(arg0, u16 *, 0xA2) = 0U;
    M2C_FIELD(arg0, s16 *, 0x92) = -0x20;
    func_80173D34();
    return;
jt_c9:
    temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x96);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_4 + 1);
    if ((s16) temp_v0_4 < 7) {
        goto block_97;
    }
    M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
    M2C_FIELD(arg2, u8 **, 0x2C) = D_80174C6C;
    func_80047784(arg2, D_80174C6C[((s32) (D_80083228 + M2C_FIELD(temp_s3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(arg1, s32 *, 0xC) = 0xFFF80000;
    M2C_FIELD(arg0, s16 *, 0xB4) = 5;
    M2C_FIELD(arg0, u16 *, 0x96) = 0x10U;
    state_base = D_80174C94;
    state_row = state_base + M2C_FIELD(arg0, s16 *, 0xB4) * 2;
    temp_a0 = state_row[1] & 7;
    temp_v1_2 = (s32 *) &sp18.pair[temp_a0];
    M2C_FIELD(arg1, s16 *, 0xE) = (s16) (M2C_FIELD(temp_v1_2, s16 *, 0) * 0x10);
    M2C_FIELD(arg1, s16 *, 0x12) = (s16) (M2C_FIELD(temp_v1_2, u16 *, 2) * 0x10);
    M2C_FIELD(temp_s3, s16 *, 0x2A) = (s16) (temp_a0 << 9);
    func_80173D34();
    return;
jt_c10:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x96) > 0) {
        goto block_29;
    }
    state_table = D_80174C94;
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) ((state_table[M2C_FIELD(arg0, s16 *, 0xB4) * 2] * 4) + 1);
    var_a0 = state_table[M2C_FIELD(arg0, s16 *, 0xB4) * 2 + 1] & 7;
    temp_v1_3 = (s32 *) &sp18.pair[var_a0];
    M2C_FIELD(arg1, s16 *, 0xE) = (s16) (M2C_FIELD(temp_v1_3, s16 *, 0) * 0x10);
    M2C_FIELD(arg1, s16 *, 0x12) = (s16) (M2C_FIELD(temp_v1_3, u16 *, 2) * 0x10);
    temp_a2 = var_a0 << 9;
    if (temp_a2 != M2C_FIELD(temp_s3, s16 *, 0x2A)) {
        goto block_25;
    }
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (M2C_FIELD(arg0, u16 *, 0x96) - 1);
block_25:
    M2C_FIELD(temp_s3, s16 *, 0x2A) = temp_a2;
    if ((state_table[M2C_FIELD(arg0, s16 *, 0xB4) * 2 + 1] & 0xF8) != 0xF8) {
        goto block_27;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0x13U;
    M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
block_27:
    M2C_FIELD(arg0, u16 *, 0xB4) = (u16) (M2C_FIELD(arg0, u16 *, 0xB4) + 1);
    func_801735B0();
    return;
block_29:
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    if (M2C_FIELD(arg2, s8 *, 4) != 5) {
        goto block_32;
    }
    particle_a0 = arg2;
    ASM_SET(arg2);   /* MATCH pin: retail register colouring depends on it */
    M2C_FIELD(arg2, u8 **, 0x2C) = D_80174C6C;
    func_80047784(particle_a0, D_80174C6C[((s32) (D_80083228 + M2C_FIELD(temp_s3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    var_s0 = 0;
    func_800A56E0(0x706);
loop_31:
    var_s0 += 1;
    particle_random = func_80069EF8();
    particle_a0 = arg0 - 0x20;
    particle_a2 = 0x8080FF;
    particle_a3 = (particle_random & 0xFF) | 0x80;
    ASM_KEEP4(particle_a0, particle_a2, particle_a3, temp_s3);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    func_80171A10(particle_a0, M2C_FIELD(temp_s3, s16 *, 0x2A), particle_a2, particle_a3, 0);
    if (var_s0 < 0x14) {
        goto loop_31;
    }
block_32:
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (M2C_FIELD(arg0, u16 *, 0x96) - 1);
    func_80173D34();
    return;
jt_c11:
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    if (M2C_FIELD(arg2, s8 *, 4) != 5) {
        goto block_37;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_80174C6C;
    func_80047784(arg2, D_80174C6C[((s32) (D_80083228 + M2C_FIELD(temp_s3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    var_s0_2 = 0;
    func_800A56E0(0x706);
loop_36:
    var_s0_2 += 1;
    particle_random = func_80069EF8();
    particle_a0 = arg0 - 0x20;
    particle_a2 = 0x8080FF;
    particle_a3 = (particle_random & 0xFF) | 0x80;
    ASM_KEEP4(particle_a0, particle_a2, particle_a3, temp_s3);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    func_80171A10(particle_a0, M2C_FIELD(temp_s3, s16 *, 0x2A), particle_a2, particle_a3, 0);
    if (var_s0_2 < 0x14) {
        goto loop_36;
    }
block_37:
    temp_v0_5 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_5;
    if ((temp_v0_5 << 0x10) > 0) {
        goto block_98;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0x2EU;
    M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
#ifndef NON_MATCHING
    tail_state = 0x80170000;
#endif
    case11_current = M2C_FIELD(arg2, u8 **, 0x2C);
#ifdef NON_MATCHING
    tail_sprite = D_80174C64;
#else
    ASM_KEEP(tail_state);   /* MATCH pin: keeps a constant in a register as retail does */
    tail_sprite = (u8 *)tail_state + 0x4C64;
#endif
    if (case11_current == tail_sprite) {
        goto block_97;
    }
#ifndef NON_MATCHING
    tail_state = 0x80080000;
    ASM_KEEP(tail_state);   /* MATCH pin: keeps a constant in a register as retail does */
#endif
    M2C_FIELD(arg2, u8 **, 0x2C) = tail_sprite;
    func_80173CF8();
    return;
jt_c12:
    temp_v0_6 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_6;
    if ((temp_v0_6 << 0x10) > 0) {
        goto block_46;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 6U;
    if (M2C_FIELD(temp_s3, s16 *, 0x2A) >= 0x800) {
        goto block_45;
    }
    M2C_FIELD(temp_s3, s16 *, 0x2A) = (s16) (M2C_FIELD(temp_s3, u16 *, 0x2A) + 0x200);
    func_8017378C();
    return;
block_45:
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
block_46:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x96) != 0x28) {
        goto block_48;
    }
    M2C_FIELD(temp_s3, s16 *, 0x2A) = 0xE00;
block_48:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x96) != 0x1E) {
        goto block_50;
    }
    M2C_FIELD(temp_s3, s16 *, 0x2A) = 0;
block_50:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x96) != 0x1D) {
        goto block_52;
    }
    M2C_FIELD(temp_s3, s16 *, 0x2A) = 0x200;
block_52:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x96) != 0x12) {
        goto block_54;
    }
    M2C_FIELD(temp_s3, s16 *, 0x2A) = 0;
block_54:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x96) != 0x11) {
        goto block_56;
    }
    M2C_FIELD(temp_s3, s16 *, 0x2A) = 0xE00;
block_56:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x96) != 0xA) {
        goto block_98;
    }
    M2C_FIELD(temp_s3, s16 *, 0x2A) = 0;
    func_80173D38();
    return;
jt_c8:
jt_c13:
    temp_v1_4 = M2C_FIELD(arg0, u16 *, 0x9E);
    M2C_FIELD(arg0, u16 *, 0x9E) = (u16) (temp_v1_4 + 1);
    M2C_FIELD(arg0, s32 *, 0xA0) = (s32) (M2C_FIELD(arg0, s32 *, 0xA0) + (func_800644B8((s16) temp_v1_4 * 0x55) * 0x10));
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) (M2C_FIELD(temp_s3, u16 *, 0x88)
        + M2C_FIELD(arg0, u16 *, 0x92) - M2C_FIELD(arg0, u16 *, 0xA2));
    func_80173D34();
    return;
jt_c14:
    temp_v0_7 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_7;
    if ((s16) temp_v0_7 < 3) {
        goto block_98;
    }
    tail_sprite = (u8 *)0x80170000;
    ASM_KEEP(tail_sprite);   /* MATCH pin: retail immediate-load split depends on it */
    tail_state = M2C_FIELD(arg0, u8 *, 0x9A);
    ASM_KEEP(tail_state);   /* MATCH pin: keeps a constant in a register as retail does */
    tail_sprite += 0x4C6C;
    ASM_KEEP(tail_sprite);   /* MATCH pin: retail immediate-load split depends on it */
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    func_80173CE8();
    return;
jt_c15:
    if (M2C_FIELD(arg2, s8 *, 4) != 5) {
        goto block_67;
    }
    particle_a0 = arg2;
    particle_a2 = 0;
    M2C_FIELD(arg2, u8 **, 0x2C) = D_80174C6C;
    sprite_angle_base = D_80083228;
    sprite_angle_delta = M2C_FIELD(temp_s3, s16 *, 0x2A);
    var_s0_3 = particle_a2;
    ASM_KEEP_NV(var_s0_3);   /* MATCH pin: keeps a statement from moving across a call/branch */
    one = 1;
    func_80047784(particle_a0, D_80174C6C[((s32) (sprite_angle_base + sprite_angle_delta + 0x100) >> 9) & 7], particle_a2);
    func_800A56E0(0x706);
loop_66:
    var_s0_3 += 1;
    particle_random = func_80069EF8();
    particle_a0 = arg0 - 0x20;
    particle_a2 = 0x8080FF;
    particle_a3 = (particle_random & 0xFF) | 0x80;
    ASM_KEEP4(particle_a0, particle_a2, particle_a3, temp_s3);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    func_80171A10(particle_a0, M2C_FIELD(temp_s3, s16 *, 0x2A), particle_a2, particle_a3, one);
    if (var_s0_3 < 0x14) {
        goto loop_66;
    }
block_67:
    temp_v0_8 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_8;
    if ((s16) temp_v0_8 < 0x19) {
        goto block_98;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
    M2C_FIELD(arg1, s16 *, 0xE) = -0x10;
    M2C_FIELD(arg1, s16 *, 0x12) = 0;
    func_80173D34();
    return;
jt_c16:
    temp_v0_9 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_9;
    if ((s16) temp_v0_9 < 0xA) {
        goto block_72;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
    M2C_FIELD(arg1, s16 *, 0xE) = 4;
    M2C_FIELD(arg1, s16 *, 0x12) = 0;
    func_80172CC8(arg1, -0x50, 0, -0x10, 0);
    func_80172CC8(arg1, -0x28, 0, -8, 0);
    func_80172CC8(arg1, -0x1C, 0, -0x1E, 0);
    func_800419EC(6, 0xC);
    func_800A56E0(0x601);
block_72:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x96) != 8) {
        goto block_74;
    }
    func_80172CC8(arg1, -0x30, 0, -0xA, 1);
    func_80172CC8(arg1, -0x18, 0, -0x18, 1);
    func_80172CC8(arg1, 0, 0, -0x10, 1);
    func_800419EC(6, 0xC);
    func_800A56E0(0x601);
block_74:
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    if (M2C_FIELD(arg2, s8 *, 4) != 5) {
        goto block_98;
    }
    particle_a0 = arg2;
    ASM_SET(arg2);   /* MATCH pin: retail register colouring depends on it */
    particle_a2 = 0;
    ASM_KEEP_NV(particle_a2);   /* MATCH pin: retail delay-slot fill depends on it */
    M2C_FIELD(arg2, u8 **, 0x2C) = D_80174C6C;
    sprite_angle_base = D_80083228;
    sprite_angle_delta = M2C_FIELD(temp_s3, s16 *, 0x2A);
    var_s0_4 = particle_a2;
    ASM_KEEP_NV(var_s0_4);   /* MATCH pin: retail delay-slot fill depends on it */
    one_2 = 1;
    func_80047784(particle_a0, D_80174C6C[((s32) (sprite_angle_base + sprite_angle_delta + 0x100) >> 9) & 7], particle_a2);
    func_800A56E0(0x706);
loop_76:
    var_s0_4 += 1;
    particle_random = func_80069EF8();
    particle_a0 = arg0 - 0x20;
    particle_a2 = 0x8080FF;
    particle_a3 = (particle_random & 0xFF) | 0x80;
    ASM_KEEP4(particle_a0, particle_a2, particle_a3, temp_s3);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    func_80171A10(particle_a0, M2C_FIELD(temp_s3, s16 *, 0x2A), particle_a2, particle_a3, one_2);
    if (var_s0_4 < 0x14) {
        goto loop_76;
    }
    tail_test = 0x80170000;
    ASM_KEEP(tail_test);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80173D38();
    return;
jt_c17:
    temp_v1_5 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) temp_v1_5;
    if (temp_v1_5 >= 0xE) {
        goto block_83;
    }
    if (temp_v1_5 & 1) {
        goto block_83;
    }
    temp_v1_6 = (u16) M2C_FIELD(temp_s3, s16 *, 0x2A);
    temp_v0_10 = temp_v1_6 + 0x200;
    M2C_FIELD(temp_s3, s16 *, 0x2A) = temp_v0_10;
    if (temp_v0_10 < 0x1000) {
        goto block_83;
    }
    M2C_FIELD(temp_s3, s16 *, 0x2A) = (s16) (temp_v1_6 - 0xE00);
block_83:
    temp_pos_x = M2C_FIELD(arg1, s32 *, 0);
    temp_a0_2 = M2C_FIELD(arg1, s32 *, 0xC);
    temp_pos_y = M2C_FIELD(arg1, s32 *, 4);
    temp_a1_2 = M2C_FIELD(arg1, s32 *, 0x10);
    M2C_FIELD(arg1, s32 *, 0) = temp_pos_x + temp_a0_2;
    M2C_FIELD(arg1, s32 *, 4) = temp_pos_y + temp_a1_2;
    if ((s16) M2C_FIELD(arg1, u16 *, 0xA) >= (s16) M2C_FIELD(temp_s3, u16 *, 0x88)) {
        goto block_85;
    }
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) (M2C_FIELD(arg1, u16 *, 0xA) + 6);
block_85:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x96) < 0x13) {
        goto block_90;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
    M2C_FIELD(arg1, s16 *, 0x12) = 0;
    M2C_FIELD(arg1, s16 *, 0xE) = 0;
    func_80173C7C(temp_a0_2, temp_a1_2);
    return;
jt_c18:
    temp_v0_11 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_11;
    if ((s16) temp_v0_11 < 0x3C) {
        goto block_90;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 4U;
    M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
    func_80172A14(arg0, arg1, arg2);
    M2C_FIELD(arg2, u8 **, 0x2C) = D_80174C7C;
    func_80047784(arg2, D_80174C7C[((s32) (D_80083228 + M2C_FIELD(temp_s3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    func_800A56E0(0x800);
block_90:
    if ((M2C_FIELD(arg0, u16 *, 0x96) & 3) != 1) {
        goto block_98;
    }
    func_80172F44(arg1, -0x10, 0, -4);
    func_80172F44(arg1, 0xC, 0, -0xC);
    tail_test = 0x80170000;
    ASM_PAGEBASE_PIN(tail_test);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80173D38();
    return;
jt_c19:
    temp_v0_12 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_12;
    if ((temp_v0_12 << 0x10) > 0) {
        goto block_98;
    }
    M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
    M2C_FIELD(arg2, u8 **, 0x2C) = D_80174C84;
    func_80047784(arg2, D_80174C84[((s32) (D_80083228 + M2C_FIELD(temp_s3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    tail_test = 0x80170000;
    ASM_PAGEBASE_PIN(tail_test);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80173D38();
    return;
jt_c20:
    func_80170C3C();
jt_c2:
jt_c4:
block_97:
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
block_98:
    if (D_80174CE0 == 0) {
        goto block_105;
    }
    temp_s2 = ((s32) (D_80083228 + M2C_FIELD(temp_s3, s16 *, 0x2A) + 0x100) >> 9) & 7;
    if (M2C_FIELD(arg0, s16 *, 0x94) == temp_s2) {
        goto block_101;
    }
    func_80047738(arg2, M2C_FIELD(arg2, u8 **, 0x2C)[temp_s2], M2C_FIELD(arg2, s8 *, 4));
    M2C_FIELD(arg0, s16 *, 0x94) = temp_s2;
block_101:
    if (D_8006CCF8[temp_s2] == 0) {
        goto block_104;
    }
    tail_test = M2C_FIELD(arg2, u16 *, 0x14) | 1;
    ASM_TAILSLOT_PIN(tail_test);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    func_80173DC4();
    return;
block_104:
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFFFE);
block_105:
    return;
}
