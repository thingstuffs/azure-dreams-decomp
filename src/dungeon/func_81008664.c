#include "common.h"
typedef long long s64;
typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *const D_80170878[];
void func_80047784();
void func_8009A21C();
s32 func_8009A2B8();
void func_8009A3D0();
s32 func_800A4ACC();
s32 func_800A4E2C();
s32 func_800A56E0();
void func_800AA53C();
void func_800AD594();
s16 func_800BCB04();
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s16 D_8008146E;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern u8 D_800DDC40[];
extern M2C_UNK D_80171058;
extern u8 D_80174888[];
extern u8 D_801748F0[];
extern u8 D_801748F8[];

void func_81008664(void *_arg0, void *_arg1, void *_arg2, void *volatile arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    struct {
        void *sp10;
        s16 sp14;
        s16 sp16;
        s32 sp18;
        u8 *sp1C;
    } locals;
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    M2C_UNK var_a2_3;
    M2C_UNK var_a2_4;
    s16 *temp_a0_4;
    s16 temp_v0;
    s16 temp_v0_2;
    s32 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_8;
    s16 temp_v0_9;
    s32 temp_a0;
    s32 temp_a0_3;
    s32 temp_s3;
    register s32 temp_t0 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 temp_v0_10;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_selector_v0;
    register s32 var_s6 ASM_REG("$22");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u16 temp_v0_5;
    u32 temp_v1;
    u32 temp_angle;
    u32 temp_flags1;
    u32 temp_flags2;
    u32 temp_flags16;
    u32 temp_mask;
    u32 temp_rm;
    u32 temp_arg2_flag;
    u32 call1_x;
    u32 call1_y;
    u32 call2_x;
    u32 call2_y;
    s32 temp_divisor;
    s32 temp_numer1;   /* MATCH pin: keeps a constant in a register as retail does */
    s32 temp_numer2;
    u8 *temp_table_c0a;
    u8 *temp_table_c0b;   /* MATCH pin: keeps a constant in a register as retail does */
    s16 *temp_ptr_c0b;
    u32 case4_x;
    u32 case4_y;
    void *case4_a0;
    void *case4_a0b;
    u32 case4_saved;
    M2C_UNK *case4_handler;
    u8 *case4_global;
    u32 case4_count;
    register u32 case1_v0 ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u32 case1_v1;
    register u32 case1_t0 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 case1_a0;
    register u32 temp_stack14 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u32 temp_stack16 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u8 *case2_state_table;
    u32 case2_state_idx;
    register u32 case2_y ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u8 *case2_step_table;
    register u8 *case2_obj_table ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u8 *case2_sp1c ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u32 case2_cce8;
    register u32 case2_sp18 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u32 case2_v1_y;
    u32 case2_a0_x;
    register void *block_sp10 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 block_v0;
    u8 next_state;
    u8 *temp_table;
    u8 *temp_table2;
    register u8 *temp_callback ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
    u32 temp_cb_idx1;
    u32 temp_cb_idx2;
    u32 temp_cb_idx3;
    u32 temp_cb_idx4;
    s16 *temp_global16;
    void *temp_a0_2;
    register void *temp_sp10 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_arg3_1 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_arg3_2 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_arg3_3 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    void *temp_arg3_4;
    register void *temp_arg3_5 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_arg3_6 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_arg3_7 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_arg3_8 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_arg3_9 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_arg3_10 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_arg3_11 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_arg3_12 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_arg3_13 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    void *temp_s1;
    register void *temp_s4 ASM_REG("$20");   /* MATCH pin: keeps a constant in a register as retail does */
    register void *temp_s5 ASM_REG("$21");   /* MATCH pin: keeps a constant in a register as retail does */
    register void *arg0 ASM_REG("$18") = _arg0;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *arg1 = _arg1;
    register void *arg2 = _arg2;

       /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_s4 = M2C_FIELD(arg0, void **, 0xA8);
    ASM_KEEP(temp_s4);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    ASM_KEEP_NV(temp_v1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_s5 = temp_s4;
    temp_s1 = M2C_FIELD(temp_s4, void **, -0x14);
    temp_sp10 = M2C_FIELD(temp_s4, void **, -0x18);
    locals.sp10 = temp_sp10;
    if (temp_v1 >= 5U) {
        goto block_59;
    }
    (void) jt_keep;
    goto *D_80170878[temp_v1];
jt_c0:
    M2C_FIELD(arg0, s32 *, 0xAC) = (s32) M2C_FIELD(temp_s5, s32 *, 0x8C);
    if (M2C_FIELD(temp_s4, s32 *, 0x1C) & 0x40000) {
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x1000);
    } else {
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xEFFF);
    }
    if (M2C_FIELD(temp_s5, u16 *, 0x98) & 8) {
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x4000);
    } else {
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xBFFF);
    }
    if (M2C_FIELD(temp_s5, u16 *, 0x98) & 4) {
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x2000);
    } else {
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xDFFF);
    }
    M2C_FIELD(temp_s5, s32 *, 0x8C) = 0;
    temp_flags1 = M2C_FIELD(temp_s4, s32 *, 0x1C);
    ASM_KEEP_NV(temp_flags1);   /* MATCH pin: keeps a statement from moving across a call/branch */
    temp_s1 = M2C_FIELD(temp_s4, void **, -0x14);
    ASM_KEEP(temp_s1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    temp_flags1 &= 0x2000;
    call1_x = M2C_FIELD(temp_s1, u8 *, 0x24);
    call1_y = M2C_FIELD(temp_s1, u8 *, 0x25);
    var_a2 = 0x3000;
    if (!temp_flags1) {
        goto block_13;
    }
    var_a2 = 0x300;
block_13:
    func_8009A3D0(call1_x, call1_y, var_a2);
    temp_arg3_1 = arg3;
    ASM_KEEP_NV(temp_arg3_1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    call2_x = M2C_FIELD(arg2, u8 *, 0x24);
    ASM_KEEP_NV(call2_x);   /* MATCH pin: keeps a statement from moving across a call/branch */
    temp_flags2 = M2C_FIELD(temp_arg3_1, s32 *, 0x1C);
    ASM_KEEP_NV(temp_flags2);   /* MATCH pin: retail basic-block layout depends on it */
    call2_y = M2C_FIELD(arg2, u8 *, 0x25);
    ASM_KEEP_NV(call2_y);   /* MATCH pin: keeps a statement from moving across a call/branch */
    temp_flags2 &= 0x2000;
    var_a2_2 = 0x3000;
    if (!temp_flags2) {
        goto block_15;
    }
    var_a2_2 = 0x300;
block_15:
    func_8009A3D0(call2_x, call2_y, var_a2_2);
    temp_arg3_2 = arg3;
    ASM_KEEP_NV(temp_arg3_2);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    temp_mask = 0xFFFB0000;
    ASM_KEEP_NV(temp_mask);   /* MATCH pin: keeps a statement from moving across a call/branch */
    temp_rm = M2C_FIELD(temp_arg3_2, s32 *, 0x1C);
    ASM_KEEP_NV(temp_rm);   /* MATCH pin: retail register colouring depends on it */
    temp_mask |= 0xFFFF;
    temp_rm &= temp_mask;
    M2C_FIELD(temp_arg3_2, s32 *, 0x1C) = temp_rm;
    temp_flags16 = M2C_FIELD(arg0, u16 *, 0x98);
    ASM_KEEP(temp_flags16);   /* MATCH pin: load-bearing for the whole function shape */
    temp_angle = M2C_FIELD(temp_arg3_2, u16 *, 0x2A);
    ASM_KEEP_NV(temp_angle);
    temp_flags16 |= 0xC;
    temp_angle >>= 9;
    M2C_FIELD(arg0, u16 *, 0x98) = temp_flags16;
    temp_arg2_flag = M2C_FIELD(arg2, u16 *, 0x14);
    temp_arg2_flag &= 0x8000;
    temp_s3 = temp_angle & 7;
    if (!temp_arg2_flag) {
        goto block_19;
    }
    if (!(M2C_FIELD(temp_s1, u16 *, 0x14) & 0x8000)) {
        goto block_19;
    }
    next_state = 2;
    M2C_FIELD(arg0, s16 *, 0x96) = 0;
    goto block_store_state;
block_19:
    M2C_FIELD(arg0, s16 *, 0x96) = 0xC;
    ASM_SCHED_BARRIER();
    temp_table_c0a = D_8006CCD8;
    temp_a0 = temp_s3 * 2;
    temp_table_c0a = (u8 *) (temp_a0 + (u32) temp_table_c0a);
    temp_numer1 = * (s16 *) temp_table_c0a;
    ASM_KEEP_NV(temp_numer1);
    temp_divisor = 0xC;
    ASM_KEEP_NV(temp_divisor);
    temp_numer1 <<= 0x16;
    temp_numer1 = temp_numer1 / temp_divisor;
    M2C_FIELD(arg1, s32 *, 0xC) = temp_numer1;
    temp_table_c0b = D_8006CCE8;
    temp_ptr_c0b = (s16 *) (temp_a0 + (u32) temp_table_c0b);
    temp_numer2 = *temp_ptr_c0b;
    temp_numer2 <<= 0x16;
    temp_numer2 = temp_numer2 / (s16) M2C_FIELD(arg0, s16 *, 0x96);
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = temp_numer2;
    M2C_FIELD(temp_s4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_s4, s32 *, 0x1C) & 0xFFFBFFFF);
    M2C_FIELD(temp_s5, u16 *, 0x98) = (u16) (M2C_FIELD(temp_s5, u16 *, 0x98) | 0xC);
    temp_callback = D_801748F0;
    temp_global16 = &D_80083228;
    M2C_FIELD(arg2, u8 **, 0x2C) = temp_callback;
    {
        u32 case0_zero;

        temp_arg3_3 = arg3;
        temp_cb_idx1 = (s16) *temp_global16;
        temp_angle = (s16) M2C_FIELD(temp_arg3_3, u16 *, 0x2A);
        ASM_USE(temp_angle);
        case0_zero = 0;
        ASM_KEEP_NV(case0_zero);
        temp_cb_idx1 = ((s32) (temp_cb_idx1 + temp_angle + 0x100) >> 9) & 7;
        temp_cb_idx1 = temp_cb_idx1 + (u32) temp_callback;
        func_80047784(arg2, M2C_FIELD((void *) temp_cb_idx1, u8 *, 0), case0_zero);
    }
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
jt_c1:
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v0;
    if (temp_v0 != 8) {
        goto block_22;
    }
    case1_v0 = (u32) D_800DDC40;
    case1_v1 = M2C_FIELD(temp_s4, u8 *, 0x13);
    case1_t0 = (u32) locals.sp10;
    case1_v1 += case1_v0;
    case1_v0 = M2C_FIELD((void *) case1_t0, s16 *, 0xA);
    case1_t0 = (u32) arg3;
    ASM_KEEP_NV(case1_t0);
    case1_a0 = M2C_FIELD((void *) case1_t0, s16 *, 0x88);
    ASM_KEEP_NV(case1_a0);
    case1_v1 = M2C_FIELD((void *) case1_v1, u8 *, 0);
    ASM_KEEP_NV(case1_v1);
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) ((s32) ((((case1_v0 - case1_a0) - case1_v1) + 0x10) << 0x10) / temp_v0);
    M2C_FIELD(temp_s5, u16 *, 0x92) = (u16) (M2C_FIELD(temp_s5, u16 *, 0x92) + M2C_FIELD(temp_s4, u16 *, 0x88));
    M2C_FIELD(temp_s4, u16 *, 0x88) = 0U;
block_22:
    if (M2C_FIELD(arg0, s16 *, 0x96) > 0) {
        goto block_59;
    }
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    M2C_FIELD(arg1, s32 *, 0x14) = -0x40000;
    func_800A56E0(0x802, temp_v0);
    {
        s32 case1_state;
        case1_state = 0x10;
        ASM_KEEP_NV(case1_state);
        temp_callback = D_801748F8;
        M2C_FIELD(arg0, s16 *, 0x96) = case1_state;
    }
    temp_global16 = &D_80083228;
    M2C_FIELD(arg2, u8 **, 0x2C) = temp_callback;
    temp_arg3_5 = arg3;
    temp_cb_idx2 = ((s32) (*temp_global16 + (s16) M2C_FIELD(temp_arg3_5, u16 *, 0x2A) + 0x100) >> 9) & 7;
    temp_cb_idx2 = temp_cb_idx2 + (u32) temp_callback;
    func_80047784(arg2, M2C_FIELD((void *) temp_cb_idx2, u8 *, 0), 0);
    goto block_state_inc;
block_25:
    temp_stack14 = (u8) locals.sp14;
    M2C_FIELD(temp_s1, u8 *, 0x24) = temp_stack14;
    temp_stack16 = (u8) locals.sp16;
    M2C_FIELD(temp_s1, u8 *, 0x25) = temp_stack16;
    goto block_success;
jt_c2:
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0xFFFE0000);
    case2_state_idx = D_800DDC40[M2C_FIELD(temp_s4, u8 *, 0x13)];
    M2C_FIELD(temp_s5, u16 *, 0x92) = (u16) ((M2C_FIELD(arg1, u16 *, 0xA) + case2_state_idx) - 0x10);
    temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        goto block_29;
    }
    if (!(M2C_FIELD(temp_s1, u16 *, 0x14) & 0x8000)) {
        goto block_59;
    }
block_29:
    case2_y = M2C_FIELD(temp_s1, u8 *, 0x24);
    ASM_KEEP_NV(case2_y);
    locals.sp14 = (s16) case2_y;
    temp_arg3_6 = arg3;
    ASM_KEEP_NV(temp_arg3_6);
    var_s6 = 0x40;
    ASM_KEEP(var_s6);
    temp_selector_v0 = (s16) M2C_FIELD(temp_arg3_6, u16 *, 0x2A);
    case2_y = M2C_FIELD(temp_s1, u8 *, 0x25);
    temp_selector_v0 = (temp_selector_v0 + 0x800) & 0xFFF;
    temp_s3 = temp_selector_v0 >> 9;
    ASM_KEEP(temp_s3);
    case2_step_table = D_8006CCD8;
    locals.sp16 = (s16) case2_y;
    temp_t0 = temp_s3 * 2;
    locals.sp18 = temp_t0;
    case2_step_table = (u8 *) (temp_t0 + (u32) case2_step_table);
    locals.sp1C = case2_step_table;
    ASM_SCHED_BARRIER();
loop_30:
    var_s6 -= 1;
loop_check:
    temp_a0_2 = temp_s1 + 0x24;
    if (var_s6 <= 0) {
        goto block_25;
    }
    temp_v0_3 = (s16) func_800A4E2C(temp_a0_2, temp_s1 + 0x25);
    var_s6 -= 1;
    if (temp_v0_3 < 0) {
        goto loop_check;
    }
    var_s6 += 1;
    ASM_KEEP(var_s6);
    case2_obj_table = D_80082E80;
    ASM_KEEP_NV(case2_obj_table);
    if (temp_v0_3 != M2C_FIELD(case2_obj_table, s8 *, 0x26)) {
        goto block_35;
    }
    temp_global16 = &D_8008146E;
    var_s6 -= 1;
    if (*temp_global16 >= 2) {
        goto loop_check;
    }
    var_s6 += 1;
block_35:
    temp_v0_10 = func_8009A2B8(M2C_FIELD(temp_s1, u8 *, 0x24), M2C_FIELD(temp_s1, u8 *, 0x25), temp_s3);
    var_s6 -= 1;
    if ((temp_v0_10 << 0x10) != 0) {
        goto loop_check;
    }
    var_s6 += 1;
    ASM_KEEP(var_s6);
    M2C_FIELD(temp_s1, s8 *, 0x26) = (s8) temp_v0_3;
    M2C_FIELD(arg2, s8 *, 0x26) = (s8) temp_v0_3;
    case2_sp1c = locals.sp1C;
    M2C_FIELD(arg2, u8 *, 0x24) = (u8) (M2C_FIELD(temp_s1, u8 *, 0x24) + *case2_sp1c);
    ASM_SCHED_BARRIER();
    case2_cce8 = (u32) D_8006CCE8;
    case2_sp18 = (u32) locals.sp18;
    ASM_KEEP_NV(case2_sp18);
    case2_v1_y = M2C_FIELD(temp_s1, u8 *, 0x25);
    ASM_KEEP_NV(case2_v1_y);
    case2_a0_x = M2C_FIELD(arg2, u8 *, 0x24);
    ASM_KEEP_NV(case2_a0_x);
    case2_cce8 = case2_sp18 + case2_cce8;
    case2_a0_x <<= 6;
    case2_cce8 = M2C_FIELD((void *) case2_cce8, u8 *, 0);
    ASM_KEEP_NV(case2_cce8);
    case2_a0_x |= 0x20;
    ASM_KEEP_NV(case2_a0_x);
    case2_v1_y += case2_cce8;
    M2C_FIELD(arg2, u8 *, 0x25) = (u8) case2_v1_y;
    temp_v0_4 = func_800BCB04(case2_a0_x, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x80));
    temp_arg3_7 = arg3;
    M2C_FIELD(temp_arg3_7, s16 *, 0x88) = temp_v0_4;
    var_s6 -= 1;
    if (temp_v0_4 >= 0x201) {
        goto loop_check;
    }
    var_s6 += 1;
    temp_v0_5 = func_800BCB04((M2C_FIELD(temp_s1, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(temp_s1, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x80));
    M2C_FIELD(temp_s4, u16 *, 0x88) = temp_v0_5;
    var_s6 -= 1;
    if ((s16) temp_v0_5 >= 0x201) {
        goto loop_check;
    }
    var_s6 += 1;
    ASM_KEEP(var_s6);
    var_s6 -= 1;
    temp_arg3_8 = arg3;
    if (M2C_FIELD(temp_arg3_8, s16 *, 0x88) != (s16) temp_v0_5) {
        goto loop_check;
    }
block_success:
    block_v0 = M2C_FIELD(temp_s1, u8 *, 0x24);
    block_sp10 = locals.sp10;
    block_v0 = ((block_v0 << 6) + 0x20) << 0x10;
    M2C_FIELD(block_sp10, s32 *, 0) = block_v0;
    M2C_FIELD(arg1, s32 *, 0) = block_v0;
    block_v0 = M2C_FIELD(temp_s1, u8 *, 0x25);
    block_v0 = ((block_v0 << 6) + 0x20) << 0x10;
    M2C_FIELD(block_sp10, s32 *, 4) = block_v0;
    M2C_FIELD(arg1, s32 *, 4) = block_v0;
    M2C_FIELD(arg1, s32 *, 8) = (s32) (((s16) M2C_FIELD(temp_s4, u16 *, 0x88) - 0x100) << 0x10);
    M2C_FIELD(temp_s5, s32 *, 0x90) = (s32) M2C_FIELD(arg0, s32 *, 0x90);
    M2C_FIELD(arg0, s16 *, 0x96) = 8;
    temp_arg3_9 = arg3;
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) ((s32) ((M2C_FIELD(temp_arg3_9, s16 *, 0x88) << 0x10) - M2C_FIELD(arg1, s32 *, 8)) / (s16) M2C_FIELD(arg0, s16 *, 0x96));
    temp_callback = D_801748F8;
    temp_global16 = &D_80083228;
    M2C_FIELD(arg2, u8 **, 0x2C) = temp_callback;
    temp_cb_idx3 = ((s32) (*temp_global16 + (s16) M2C_FIELD(temp_arg3_9, u16 *, 0x2A) + 0x100) >> 9) & 7;
    temp_cb_idx3 = temp_cb_idx3 + (u32) temp_callback;
    func_80047784(arg2, M2C_FIELD((void *) temp_cb_idx3, u8 *, 0), 0);
    func_800AA53C(arg3);
    func_800AA53C(temp_s4);
    goto block_state_inc;
jt_c3:
    M2C_FIELD(temp_s5, u16 *, 0x92) = (u16) (M2C_FIELD(arg0, u16 *, 0x92) + 0x40);
    if ((s16) M2C_FIELD(arg0, u16 *, 0x92) >= 0) {
        goto block_44;
    }
    temp_v0_8 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v0_8;
    if ((temp_v0_8 << 0x10) > 0) {
        goto block_59;
    }
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        goto block_59;
    }
block_44:
    M2C_FIELD(arg0, s32 *, 0x90) = 0;
    M2C_FIELD(temp_s5, s32 *, 0x90) = 0;
    if (!(M2C_FIELD(arg0, u16 *, 0x98) & 0x1000)) {
        goto block_46;
    }
    M2C_FIELD(temp_s4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_s4, s32 *, 0x1C) | 0x40000);
block_46:
    if (M2C_FIELD(arg0, u16 *, 0x98) & 0x4000) {
        goto block_48;
    }
    M2C_FIELD(temp_s5, u16 *, 0x98) = (u16) (M2C_FIELD(temp_s5, u16 *, 0x98) & 0xFFF7);
block_48:
    if (M2C_FIELD(arg0, u16 *, 0x98) & 0x2000) {
        goto block_50;
    }
    M2C_FIELD(temp_s5, u16 *, 0x98) = (u16) (M2C_FIELD(temp_s5, u16 *, 0x98) & 0xFFFB);
block_50:
    temp_arg3_10 = arg3;
    M2C_FIELD(temp_arg3_10, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_arg3_10, s32 *, 0x1C) | 0x40000000);
    M2C_FIELD(temp_s4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_s4, s32 *, 0x1C) | 0x40000000);
    {
        register s32 case3_v0 ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
        register u32 case3_v1 ASM_REG("$3");
        s32 case3_a0;
        register u32 case3_t0 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */

        case3_v1 = M2C_FIELD(temp_arg3_10, u16 *, 0x2A);
        case3_v0 = 8;
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg0, s16 *, 0x96) = case3_v0;
        case3_v0 = (u32) D_8006CCD8;
        temp_s3 = case3_v1 >> 8;
        ASM_KEEP(temp_s3);
        case3_a0 = temp_s3 & 0xE;
        case3_v0 = case3_a0 + case3_v0;
        case3_v0 = M2C_FIELD((void *) case3_v0, s16 *, 0);
        case3_v1 = 8;
        case3_v0 <<= 0x16;
        case3_v0 = 0 - case3_v0;
        case3_v0 /= (s32) case3_v1;
        M2C_FIELD(arg1, s32 *, 0xC) = case3_v0;
        case3_v0 = (u32) D_8006CCE8;
        case3_a0 += case3_v0;
        case3_v0 = M2C_FIELD((void *) case3_a0, s16 *, 0);
        case3_v1 = M2C_FIELD(arg0, s16 *, 0x96);
        case3_v0 <<= 0x16;
        case3_v0 = 0 - case3_v0;
        case3_v0 /= (s32) case3_v1;
        M2C_FIELD(arg1, s32 *, 0x10) = case3_v0;
        case3_t0 = (u32) locals.sp10;
        M2C_FIELD((void *) case3_t0, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        goto block_state_inc;
    }
jt_c4:
    temp_v0_9 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v0_9;
    if ((temp_v0_9 << 0x10) <= 0) {
        goto block_54;
    }
    if (!(M2C_FIELD(temp_s1, u16 *, 0x14) & 0x8000)) {
        goto block_59;
    }
block_54:
    case4_x = M2C_FIELD(arg2, u8 *, 0x24);
    case4_x = ((case4_x << 6) + 0x20) << 0x10;
    M2C_FIELD(arg1, s32 *, 0) = case4_x;
    case4_y = M2C_FIELD(arg2, u8 *, 0x25);
    case4_a0 = arg3;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    case4_y = ((case4_y << 6) + 0x20) << 0x10;
    M2C_FIELD(arg1, s32 *, 4) = case4_y;
    case4_saved = M2C_FIELD(arg0, s32 *, 0xAC);
    M2C_FIELD(temp_s5, s32 *, 0x8C) = case4_saved;
    func_800AD594(case4_a0, 0x100);
    case4_handler = &D_80171058;
    case4_global = D_80083460;
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = case4_handler;
    case4_count = M2C_FIELD(case4_global, u16 *, 0xA);
    case4_a0b = arg3;
    case4_count -= 1;
    M2C_FIELD(case4_global, u16 *, 0xA) = case4_count;
    func_800A4ACC(case4_a0b);
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF3);
    temp_arg3_11 = arg3;
    ASM_KEEP_NV(temp_arg3_11);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    {
        u32 case4_flags;
        u32 case4_mask;
        u32 case4_call_x;
        u32 case4_call_y;

        ASM_SCHED_BARRIER();
        case4_flags = M2C_FIELD(temp_arg3_11, s32 *, 0x1C);
        case4_mask = 0x40000;
        case4_flags |= case4_mask;
        M2C_FIELD(temp_arg3_11, s32 *, 0x1C) = case4_flags;
        case4_flags &= 0x2000;
        case4_call_x = M2C_FIELD(arg2, u8 *, 0x24);
        case4_call_y = M2C_FIELD(arg2, u8 *, 0x25);
        var_a2_3 = 0x3000;
        if (!case4_flags) {
            goto block_56;
        }
        var_a2_3 = 0x300;
block_56:
        func_8009A21C(case4_call_x, case4_call_y, var_a2_3);
    }
    {
        u32 case4_flags;
        u32 case4_call_x;
        u32 case4_call_y;

        case4_flags = M2C_FIELD(temp_s4, s32 *, 0x1C);
        ASM_KEEP_NV(case4_flags);
        case4_call_x = M2C_FIELD(temp_s1, u8 *, 0x24);
        ASM_KEEP_NV(case4_call_x);
        case4_call_y = M2C_FIELD(temp_s1, u8 *, 0x25);
        ASM_KEEP_NV(case4_call_y);
        case4_flags &= 0x2000;
        var_a2_4 = 0x3000;
        if (!case4_flags) {
            goto block_58;
        }
        var_a2_4 = 0x300;
block_58:
        func_8009A21C(case4_call_x, case4_call_y, var_a2_4);
    }
    temp_callback = D_80174888;
    temp_global16 = &D_80083228;
    M2C_FIELD(arg2, u8 **, 0x2C) = temp_callback;
    temp_arg3_12 = arg3;
    temp_cb_idx4 = ((s32) (*temp_global16 + (s16) M2C_FIELD(temp_arg3_12, u16 *, 0x2A) + 0x100) >> 9) & 7;
    temp_cb_idx4 = temp_cb_idx4 + (u32) temp_callback;
    func_80047784(arg2, M2C_FIELD((void *) temp_cb_idx4, u8 *, 0), 0);
    temp_arg3_13 = arg3;
    M2C_FIELD(temp_arg3_13, s8 *, 0x6D) = 0;
    M2C_FIELD(temp_arg3_13, u16 *, 0x46) = (u16) (M2C_FIELD(temp_arg3_13, u16 *, 0x46) & 0x7FFF);
block_state_inc:
    next_state = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
block_store_state:
    M2C_FIELD(arg0, u8 *, 0x9B) = next_state;
block_59:
    return;
}
