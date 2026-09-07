#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_8008938C[];
extern u8 D_80010000[];
s32 func_80042900();
s32 func_8004491C();
void func_80044A50();
M2C_UNK func_80099844();
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
void *func_800A32A4();
M2C_UNK func_800A56E0();
s32 func_800A6620();
M2C_UNK func_800B8FC8();
s32 func_800BBA40(u8, u8, s16, void *, s32, s32, void *);
void func_800BC318();
extern M2C_UNK D_800814A0;
extern u8 D_80082E80[];
extern M2C_UNK D_800C0180;
extern M2C_UNK D_800C27F0;
extern M2C_UNK D_800CEF54;
extern M2C_UNK D_800DF45C;
extern M2C_UNK D_800DF4A4;
extern void *D_800DF55C;
extern void *D_800DF560;
extern M2C_UNK D_800E1640;
extern void *D_800E3D7C;
extern void func_800C2B8C() __attribute__((noreturn));
extern void func_800C2C48() __attribute__((noreturn));

typedef struct {
    s32 sp20;
    s32 sp24;
    s16 sp28;
    s16 sp2A;
} StackArgs;

void func_800C2824(void *arg0, void *arg1, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c16, &&jt_c17 };
    StackArgs sp;
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    s16 temp_v0_4;
    s16 temp_v0_8;
    s32 temp_v1;
    s16 var_v0;
    void *temp_v0_5;
    s32 var_v1;
    s32 temp_v1_9;
    s32 temp_v0_9;
    register s32 bba_flags ASM_REG("$3");
    s32 temp_v1_4;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u8 temp_v1_3;
    void *temp_a1;
    void *temp_a1_2;
    void *temp_a1_3;
    void *temp_s0;
    register void *temp_v0_7 ASM_REG("$2");
    void *temp_v1_2;
    void *temp_v1_5;
    void *temp_v1_6;
    void *temp_v1_7;
    void *temp_v1_8;
    register u8 *temp_a1_4 ASM_REG("$5");
    register void *c2_object ASM_REG("$3");
    register u32 c2_coord ASM_REG("$5");
    s32 c2_status;
    s32 c2_x;
    register void *c17_object ASM_REG("$3");
    register u32 c17_coord ASM_REG("$5");
    s32 c17_status;
    s32 c17_x;
    register void *c17_final_ptr ASM_REG("$5");
    register s32 c17_flags ASM_REG("$3");
    u16 c17_field;
    void *temp_t0;
    u8 *page_base;

    temp_v1 = M2C_FIELD(arg0, s16 *, 4);
    if ((u32) temp_v1 >= 0x12U) {
        goto block_27;
    }
    (void)jt_keep; goto *D_8008938C[(u32)(temp_v1)];
jt_c0:
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x14) & 0x4000) {
        goto block_4;
    }
    M2C_FIELD(arg0, s16 *, 4) = 0x10;
    return;
block_4:
    sp.sp20 = 0x01800340;
    sp.sp24 = 0x400040;
    sp.sp28 = 0x360;
    sp.sp2A = 0x1B8;
    func_800B8FC8(M2C_FIELD(arg0, void **, 0), &sp.sp20, &sp.sp28, 1, 2);
    temp_s0 = M2C_FIELD(arg0, void **, 0) - 0x20;
    func_80044A50(temp_s0);
    func_800BC318(temp_s0);
    temp_v1_2 = M2C_FIELD(temp_s0, void **, 8);
    temp_v0 = M2C_FIELD(temp_v1_2, u16 *, 2);
    M2C_FIELD(arg1, u16 *, 2) = temp_v0;
    M2C_FIELD(arg1, u16 *, 0xE) = temp_v0;
    temp_v0_2 = M2C_FIELD(temp_v1_2, u16 *, 6);
    M2C_FIELD(arg1, u16 *, 6) = temp_v0_2;
    M2C_FIELD(arg1, u16 *, 0x12) = temp_v0_2;
    temp_v0_3 = M2C_FIELD(temp_v1_2, u16 *, 0xA);
    M2C_FIELD(arg1, u16 *, 0xA) = temp_v0_3;
    M2C_FIELD(arg1, u16 *, 0x16) = temp_v0_3;
    func_8004491C(arg0 - 0x20, &D_800CEF54);
    M2C_FIELD(arg2, s16 *, 0x10) = 0x20;
    M2C_FIELD(arg2, M2C_UNK **, 8) = &D_800DF4A4;
    M2C_FIELD(arg2, s32 *, 0xC) = 0x808080;
    M2C_FIELD(arg2, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(arg2, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0xC);
    M2C_FIELD(arg0, s16 *, 6) = 0x10;
    func_800A56E0(1);
    M2C_FIELD(arg0, s16 *, 4) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 4) + 1);
jt_c1:
    temp_v1_3 = (u8) M2C_FIELD(arg2, s32 *, 0xC);
    temp_v1_4 = temp_v1_3 - ((s32) temp_v1_3 / (s16) M2C_FIELD(arg0, s16 *, 6));
    M2C_FIELD(arg2, s8 *, 0xC) = temp_v1_4;
    M2C_FIELD(arg2, s8 *, 0xE) = temp_v1_4;
    M2C_FIELD(arg2, s8 *, 0xD) = temp_v1_4;
    temp_v0_4 = (u16) M2C_FIELD(arg0, s16 *, 6) - 1;
    M2C_FIELD(arg0, s16 *, 6) = temp_v0_4;
    if ((temp_v0_4 << 0x10) > 0) {
        return;
    }
    var_v0 = (u16) M2C_FIELD(arg0, s16 *, 4) + 1;
    ASM_TAILSLOT_PIN(var_v0);
    return func_800C2B8C();
jt_c2:
    temp_v0_5 = func_800A32A4(M2C_FIELD(arg0, void **, 0));
    if (temp_v0_5 == 0) {
        goto block_10;
    }
    var_a2 = func_800A6620(temp_v0_5, 0);
    if (var_a2 >= 0x40) {
        goto block_10;
    }
    page_base = (u8 *)0x80010000;
    M2C_FIELD(page_base + (var_a2 * 0x54), s8 *, 0xA93) = 0;
    ((s32 *)0x80010980)[var_a2] = 0;
block_10:
    if ((func_80042900(M2C_FIELD(arg0, void **, 0), 0x1B) << 0x10) != 0) {
        goto block_14;
    }
    c2_object = M2C_FIELD(arg0, void **, 0);
    c2_status = M2C_FIELD(c2_object, s32 *, 0x1C);
    ASM_KEEP_NV(c2_status);
    c2_coord = (u32)M2C_FIELD(c2_object, void **, -0x14);
    c2_status &= 0x2000;
    c2_x = M2C_FIELD((void *)c2_coord, u8 *, 0x24);
    c2_coord = M2C_FIELD((void *)c2_coord, u8 *, 0x25);
    ASM_KEEP(c2_x);
    ASM_KEEP(c2_coord);
    var_a2 = 0x3000;
    if (!c2_status) {
        goto block_13;
    }
    var_a2 = 0x300;
block_13:
    func_8009A3D0(c2_x, c2_coord, var_a2);
block_14:
    func_8009A028(M2C_FIELD(arg0, void **, 0));
    func_80099844(M2C_FIELD(arg0, void **, 0), &D_800E1640);
    var_v0 = (u16) M2C_FIELD(arg0, s16 *, 4) + 1;
    ASM_TAILSLOT_PIN(var_v0);
    return func_800C2B8C();
jt_c3: {
    register u8 *c3_page ASM_REG("$4");
    register u8 *c3_82_page ASM_REG("$2");
    register void *c3_object ASM_REG("$3");
    register s32 c3_flags ASM_REG("$3");

    c3_82_page = (u8 *)0x80080000;
    ASM_KEEP(c3_82_page);
    temp_a1_4 = c3_82_page + 0x2E80;
    temp_t0 = D_800E3D7C;
    D_800DF55C = temp_t0;
    bba_flags = 0x208020;
    if (func_800BBA40(temp_a1_4[0x24], temp_a1_4[0x25], M2C_FIELD(temp_t0, s16 *, 0x88), &D_800DF45C, 0x2800, bba_flags, &D_800C0180) == 0) {
        goto block_27;
    }
    c3_page = (u8 *)0x80080000;
    c3_object = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(c3_object, u16 *, -2) = (u16) (M2C_FIELD(c3_object, u16 *, -2) | 0x8000);
    c3_flags = M2C_FIELD(c3_page, s32 *, 0x14A0) | 0x8000;
    M2C_FIELD(c3_page, s32 *, 0x14A0) = c3_flags;
    return func_800C2C48();
}
jt_c16:
    temp_v0_7 = M2C_FIELD(arg0, void **, 0);
    temp_t0 = temp_v0_7;
    temp_a1_2 = M2C_FIELD(temp_t0, void **, -0x14);
    temp_v0_9 = M2C_FIELD(temp_t0, s16 *, 0x88);
    D_800DF55C = temp_t0;
    bba_flags = 0x208020;
    if (func_800BBA40(M2C_FIELD(temp_a1_2, u8 *, 0x24), M2C_FIELD(temp_a1_2, u8 *, 0x25), temp_v0_9, &D_800DF45C, 0x2800, bba_flags, &D_800C27F0) == 0) {
        goto block_27;
    }
    M2C_FIELD(arg0, s16 *, 6) = 0x3C;
    var_v0 = (u16) M2C_FIELD(arg0, s16 *, 4) + 1;
    M2C_FIELD(arg0, s16 *, 4) = var_v0;
    return;
jt_c17:
    temp_v0_8 = (u16) M2C_FIELD(arg0, s16 *, 6) - 1;
    M2C_FIELD(arg0, s16 *, 6) = temp_v0_8;
    if ((temp_v0_8 << 0x10) > 0) {
        goto block_27;
    }
    func_800A32A4(M2C_FIELD(arg0, void **, 0));
    if ((func_80042900(M2C_FIELD(arg0, void **, 0), 0x1B) << 0x10) != 0) {
        goto block_25;
    }
    c17_object = M2C_FIELD(arg0, void **, 0);
    c17_status = M2C_FIELD(c17_object, s32 *, 0x1C);
    ASM_KEEP_NV(c17_status);
    c17_coord = (u32)M2C_FIELD(c17_object, void **, -0x14);
    c17_status &= 0x2000;
    c17_x = M2C_FIELD((void *)c17_coord, u8 *, 0x24);
    c17_coord = M2C_FIELD((void *)c17_coord, u8 *, 0x25);
    ASM_KEEP(c17_x);
    ASM_KEEP(c17_coord);
    var_a2_2 = 0x3000;
    if (!c17_status) {
        goto block_24;
    }
    var_a2_2 = 0x300;
block_24:
    func_8009A3D0(c17_x, c17_coord, var_a2_2);
block_25:
    func_8009A028(M2C_FIELD(arg0, void **, 0));
    temp_v1_8 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v1_8, u16 *, -2) = (u16) (M2C_FIELD(temp_v1_8, u16 *, -2) | 0x8000);
    c17_final_ptr = D_800DF560;
    ASM_KEEP_NV(c17_final_ptr);
    c17_flags = D_800814A0;
    c17_field = M2C_FIELD(c17_final_ptr, u16 *, 0x1E);
    c17_flags |= 0x8000;
    D_800814A0 = c17_flags;
    ASM_KEEP(c17_flags);
    M2C_FIELD(c17_final_ptr, u16 *, 0x1E) = (u16)(c17_field | 0x8000);
block_26:
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    D_800814A0 = c17_flags;
block_27:
    return;
}
