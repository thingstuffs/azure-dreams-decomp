#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
/*
 * This header contains macros emitted by m2c in "valid syntax" mode,
 * which can be enabled by passing `--valid-syntax` on the command line.
 *
 * In this mode, unhandled types and expressions are emitted as macros so
 * that the output is compilable without human intervention.
 */


/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)

#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

M2C_UNK func_8002589C();        /* extern */
void func_8002600C(void) __attribute__((noreturn)); /* extern */
void func_80026270(void) __attribute__((noreturn)); /* extern */
void func_8002633C() __attribute__((noreturn));        /* extern */
void func_80026368(void) __attribute__((noreturn)); /* extern */
M2C_UNK func_80026548();                 /* extern */
M2C_UNK func_8002660C();    /* extern */
M2C_UNK func_800266D0();                  /* extern */
s32 func_8003DE58(); /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_8009B4B0();                /* extern */
M2C_UNK func_8009CE1C(); /* extern */
s32 func_800A44E0();              /* extern */
extern u16 D_800281F8;
extern s16 D_8002966C[6];
extern u8 D_8002966E;
extern s32 D_80029670;
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_800814A0;
extern M2C_UNK D_80082E80;
extern u16 D_80082E94;
extern u16 D_80083780[];
extern M2C_UNK D_800C9034;
extern void *D_800E3D7C;

void func_80025C80(void *arg0_in, void *arg1_in, void *arg2_in) {
    register void *arg0 ASM_REG("$17");
    register void *arg1 ASM_REG("$16");
    register void *arg2 ASM_REG("$18");
    register s32 x_step ASM_REG("$3");
    register s32 y_step ASM_REG("$4");
    register s32 eight ASM_REG("$5");
    register void *case0_base ASM_REG("$2");
    register void *temp_v1_6 ASM_REG("$3");
    register s16 *update_base ASM_REG("$2");
    register s16 *update_ptr ASM_REG("$3");
    register s16 *update_y_page ASM_REG("$3");
    register s16 *update_y_base ASM_REG("$3");
    register s16 *update_y_ptr ASM_REG("$2");
    register s32 update_y_offset ASM_REG("$2");
    register s32 motion_x ASM_REG("$2");
    register s32 motion_dx ASM_REG("$4");
    register s32 motion_y ASM_REG("$3");
    register s32 motion_dy ASM_REG("$5");
    register s32 motion_z ASM_REG("$3");
    register s32 motion_dz ASM_REG("$4");
    register s32 motion_damp_x ASM_REG("$2");
    register s32 motion_damp_y ASM_REG("$3");
    register u16 linked_flags ASM_REG("$2");
    register s32 *linked_global ASM_REG("$3");
    register u8 *resident_hi ASM_REG("$2");
    s16 temp_v0;
    s16 temp_v0_4;
    s16 temp_v0_7;
    s16 temp_v0_8;
    s16 temp_v1;
    s16 temp_v1_4;
    s16 temp_v1_5;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 delta_x;
    s32 delta_y;
    s32 target_x;
    s32 target_y;
    s32 temp_v0_10;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_9;
    u16 *var_v0;
    u16 temp_v0_6;
    register u16 update_x ASM_REG("$2");
    register u16 update_y ASM_REG("$3");
    u8 temp_v0_5;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 case0_byte;
    void *temp_a0;
    void *temp_s0;
    void *var_a0;

    arg0 = arg0_in;
    arg1 = arg1_in;
    arg2 = arg2_in;
    temp_a0 = M2C_FIELD(arg0, void **, 0x20);
    D_800281F8 = D_800281F8 + 1;
    if (temp_a0 != NULL) {
        goto linked_monster;
    }
    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    func_8002660C(arg2, arg0 + 0x32, M2C_FIELD(arg0, s16 *, 0x38), M2C_FIELD(arg0, s16 *, 0x36));
    func_80026548(arg0, M2C_FIELD(arg2, s32 *, 0));
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x2C);
    if (temp_v1 == 1) {
        goto case_1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto case_0;
        }
        func_8002633C();
        return;
    }
    if (temp_v1 == 2) {
        goto case_2;
    }
    if (temp_v1 == 0x10) {
        goto case_16;
    }
    func_8002633C();
    return;

case_0:
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + 0xFFFF0000);
    temp_v1_2 = M2C_FIELD(arg2, u8 *, 0xC);
    temp_v1_3 = temp_v1_2 + ((s32) (0x80 - temp_v1_2) / (s16) M2C_FIELD(arg0, s16 *, 0x30));
    M2C_FIELD(arg2, u8 *, 0xC) = temp_v1_3;
    M2C_FIELD(arg2, u8 *, 0xE) = temp_v1_3;
    M2C_FIELD(arg2, u8 *, 0xD) = temp_v1_3;
    temp_v0 = ((u16) M2C_FIELD(arg0, s16 *, 0x30) ^ 1) & 1;
    temp_v1_4 = M2C_FIELD(arg0, volatile u16 *, 0x30) - 1;
    ASM_KEEP(temp_v0);
    M2C_FIELD(arg0, s16 *, 0x30) = temp_v1_4;
    M2C_FIELD(arg0, s16 *, 0x32) = temp_v0;
    if (((temp_v1_4 << 0x10) <= 0) && (M2C_FIELD(arg2, u16 *, 0x14) & 0x4000)) {
        eight = 8;
        ASM_KEEP(eight);
        temp_v1_6 = D_800E3D7C;
        M2C_FIELD(arg0, s16 *, 0x38) = eight;
        M2C_FIELD(arg0, s16 *, 0x36) = 0xF;
        M2C_FIELD(arg0, s16 *, 0x32) = 1;
        M2C_FIELD(arg0, u16 *, 0x3A) = (u16) M2C_FIELD(temp_v1_6, u16 *, 0x88);
        M2C_FIELD(arg0, u16 *, 0x40) = (u16) (((u16) M2C_FIELD(temp_v1_6, u16 *, 0x2A) >> 9) & 7);
        ASM_SCHED_BARRIER();
        case0_base = &D_80082E80;
        M2C_FIELD(arg0, s16 *, 0x3C) = M2C_FIELD(case0_base, u8 *, 0x24);
        ASM_SCHED_BARRIER();
        case0_byte = M2C_FIELD(case0_base, u8 *, 0x25);
        M2C_FIELD(arg0, u16 *, 0x42) = eight;
        M2C_FIELD(arg0, s16 *, 0x30) = 3;
        M2C_FIELD(arg0, s16 *, 0x2C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2C) + 1);
        M2C_FIELD(arg0, s16 *, 0x3E) = case0_byte;
        func_8002633C();
        return;
    }
    goto block_54;

case_1:
    resident_hi = (u8 *) 0x80080000;
    ASM_KEEP_NV(resident_hi);
    arg2 = resident_hi + 0x2E80;
    temp_v0_10 = func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, arg0 + 0x24, 0);
    temp_v1_5 = (u16) M2C_FIELD(arg0, s16 *, 0x30) - 1;
    M2C_FIELD(arg0, s16 *, 0x30) = temp_v1_5;
    if ((temp_v1_5 << 0x10) <= 0) {
        goto case1_check_flag;
    }
    if (temp_v0_10 == 0) {
        goto case1_check_flag;
    }
    if ((M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) == 0) {
        goto case1_add_base;
    }
case1_check_flag:
    if (D_80082E94 & 0x8000) {
        M2C_FIELD(arg1, s16 *, 2) = D_80083780[1];
        M2C_FIELD(arg1, s16 *, 6) = D_80083780[3];
        M2C_FIELD(arg1, s16 *, 0xA) = D_80083780[5] - 0x10;
    }
    M2C_FIELD(arg0, s16 *, 0x30) = 0;
    M2C_FIELD(arg0, s16 *, 0x2C) = (u16) M2C_FIELD(arg0, s16 *, 0x2C) + 1;
    func_8002633C();
    return;

case1_add_base:
    var_a0 = &D_80083780;
    M2C_FIELD(arg1, s16 *, 2) = (s16) (M2C_FIELD(var_a0, u16 *, 2) + M2C_FIELD(arg0, u16 *, 0x24));
    M2C_FIELD(arg1, s16 *, 6) = (s16) (M2C_FIELD(var_a0, u16 *, 6) + M2C_FIELD(arg0, u16 *, 0x26));
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(var_a0, u16 *, 0xA) + M2C_FIELD(arg0, u16 *, 0x28));
    func_8002633C();
    return;

case_2:
    if (M2C_FIELD(arg0, s16 *, 0x30) != 0) {
        goto block_31;
    }
    if ((func_800A44E0(((M2C_FIELD(arg0, s16 *, 0x3C) << 6) + 0x20) & 0xFFE0, ((M2C_FIELD(arg0, s16 *, 0x3E) << 6) + 0x20) & 0xFFE0, (s16) (M2C_FIELD(arg0, u16 *, 0x3A) - 0x20), (s16) (M2C_FIELD(arg0, u16 *, 0x40) << 9)) << 0x10) != 0) {
        goto case2_complete;
    }
    temp_v0_6 = M2C_FIELD(arg0, u16 *, 0x42) - 1;
    M2C_FIELD(arg0, u16 *, 0x42) = temp_v0_6;
    if ((temp_v0_6 << 0x10) > 0) {
        goto case2_update;
    }
case2_complete:
    M2C_FIELD(arg0, s16 *, 0x2C) = 0x10;
    M2C_FIELD(arg1, s16 *, 0xE) = D_8006CCD8[M2C_FIELD(arg0, s16 *, 0x40)] * 8;
    M2C_FIELD(arg1, s16 *, 0x12) = D_8006CCE8[M2C_FIELD(arg0, s16 *, 0x40)] * 8;
    x_step = 8;
    M2C_FIELD(arg1, s16 *, 0x16) = x_step;
    M2C_FIELD(arg0, s16 *, 0x30) = x_step;
    func_8002600C();
    return;

case2_update:
    update_base = D_8006CCD8;
    update_ptr = &update_base[M2C_FIELD(arg0, s16 *, 0x40)];
    update_x = (u16) M2C_FIELD(arg0, s16 *, 0x3C);
    x_step = (u16) *update_ptr;
    update_x += x_step;
    update_y_page = (s16 *) 0x80070000;
    ASM_KEEP_NV(update_y_page);
    M2C_FIELD(arg0, s16 *, 0x3C) = update_x;
    ASM_SCHED_BARRIER();
    update_y_base = (s16 *) ((u8 *) update_y_page - 0x3318);
    update_y_offset = M2C_FIELD(arg0, s16 *, 0x40) << 1;
    update_y_ptr = (s16 *) ((unsigned long) update_y_offset + (unsigned long) update_y_base);
    update_y = (u16) M2C_FIELD(arg0, volatile s16 *, 0x3E);
    y_step = (u16) *(volatile u16 *) update_y_ptr;
    M2C_FIELD(arg0, s16 *, 0x30) = 3;
    ASM_KEEP_NV(y_step);
    update_y += y_step;
    M2C_FIELD(arg0, s16 *, 0x3E) = update_y;
block_31:
    target_x = M2C_FIELD(arg0, s16 *, 0x3C) << 6;
    delta_x = M2C_FIELD(arg1, s16 *, 2) - 0x20;
    x_step = (target_x - delta_x) / M2C_FIELD(arg0, s16 *, 0x30);
    M2C_FIELD(arg1, s16 *, 2) = (u16) M2C_FIELD(arg1, s16 *, 2) + x_step;
    target_y = M2C_FIELD(arg0, s16 *, 0x3E) << 6;
    delta_y = M2C_FIELD(arg1, s16 *, 6) - 0x20;
    y_step = (target_y - delta_y) / M2C_FIELD(arg0, s16 *, 0x30);
    temp_v0_7 = (u16) M2C_FIELD(arg1, s16 *, 0xA) + 5;
    M2C_FIELD(arg1, s16 *, 0xA) = temp_v0_7;
    M2C_FIELD(arg1, s16 *, 6) = (u16) M2C_FIELD(arg1, s16 *, 6) + y_step;
    if (((s16) M2C_FIELD(arg0, u16 *, 0x3A) - 0x10) < temp_v0_7) {
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(arg0, u16 *, 0x3A) - 0x10);
    }
    temp_v0_8 = (u16) M2C_FIELD(arg0, s16 *, 0x30) - 1;
    M2C_FIELD(arg0, s16 *, 0x30) = temp_v0_8;
    if (temp_v0_8 == 2) {
        temp_v0_9 = func_8009B4B0(D_800E3D7C, (u16) M2C_FIELD(arg0, s16 *, 0x3C), (u16) M2C_FIELD(arg0, s16 *, 0x3E));
        if (temp_v0_9 != 0) {
            func_8009CE1C(temp_v0_9, 0xC, D_8002966E, 9, (s32) (s16) (M2C_FIELD(arg0, u16 *, 0x40) << 9), D_80029670, 5);
        }
        goto block_47;
    }
    goto block_47;

case_16:
    motion_x = M2C_FIELD(arg1, s32 *, 0);
    motion_dx = M2C_FIELD(arg1, s32 *, 0xC);
    motion_y = M2C_FIELD(arg1, s32 *, 4);
    motion_dy = M2C_FIELD(arg1, s32 *, 0x10);
    motion_x += motion_dx;
    motion_y += motion_dy;
    M2C_FIELD(arg1, s32 *, 4) = motion_y;
    motion_z = M2C_FIELD(arg1, s32 *, 8);
    motion_dz = M2C_FIELD(arg1, s32 *, 0x14);
    M2C_FIELD(arg1, s32 *, 0) = motion_x;
    motion_damp_x = M2C_FIELD(arg1, s32 *, 0xC);
    motion_z += motion_dz;
    M2C_FIELD(arg1, s32 *, 8) = motion_z;
    ASM_SCHED_BARRIER();
    motion_damp_x -= motion_damp_x >> 2;
    motion_damp_y = motion_dy;
    M2C_FIELD(arg1, s32 *, 0xC) = motion_damp_x;
    ASM_KEEP(motion_damp_y);
    motion_damp_y -= motion_damp_x >> 2;
    M2C_FIELD(arg1, s32 *, 0x10) = motion_damp_y;
    if (((s16) M2C_FIELD(arg0, u16 *, 0x3A) - 0x10) < M2C_FIELD(arg1, s16 *, 0xA)) {
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(arg0, u16 *, 0x3A) - 0x10);
    }
    M2C_FIELD(arg2, u8 *, 0xC) = M2C_FIELD(arg2, u8 *, 0xC) - ((s32) M2C_FIELD(arg2, u8 *, 0xC) / M2C_FIELD(arg0, s16 *, 0x30));
    M2C_FIELD(arg2, u8 *, 0xD) = M2C_FIELD(arg2, u8 *, 0xD) - ((s32) M2C_FIELD(arg2, u8 *, 0xD) / M2C_FIELD(arg0, s16 *, 0x30));
    M2C_FIELD(arg2, u8 *, 0xE) = M2C_FIELD(arg2, u8 *, 0xE) - ((s32) M2C_FIELD(arg2, u8 *, 0xE) / M2C_FIELD(arg0, s16 *, 0x30));
    temp_v0_4 = (u16) M2C_FIELD(arg0, s16 *, 0x30) - 1;
    M2C_FIELD(arg0, s16 *, 0x30) = temp_v0_4;
    if ((temp_v0_4 << 0x10) <= 0) {
        D_8002966C[0] = 0;
        func_80026270();
        return;
    }
    temp_v0_5 = M2C_FIELD(arg2, u8 *, 4);
    if ((s8) temp_v0_5 == M2C_FIELD(arg0, s16 *, 0x36)) {
        M2C_FIELD(arg0, s16 *, 0x32) = -1;
        goto block_47;
        return;
    }
    if ((s8) temp_v0_5 == M2C_FIELD(arg0, s16 *, 0x38)) {
        M2C_FIELD(arg0, s16 *, 0x32) = 1;
        goto block_47;
    }
block_47:
    func_8002589C(arg0 - 0x20, (s16) M2C_FIELD(arg0, u16 *, 0x40), 0xF0);
    func_8002633C();
    return;

linked_monster:
    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    if (M2C_FIELD(temp_a0, u16 *, 0x1E) & 0x8000) {
        linked_flags = M2C_FIELD(arg0, u16 *, -2);
        ASM_SCHED_BARRIER();
        linked_global = &D_800814A0;
        linked_flags |= 0x8000;
        M2C_FIELD(arg0, u16 *, -2) = linked_flags;
        ASM_MEM_BARRIER();
        *linked_global |= 0x8000;
        func_80026368();
        return;
    }
    temp_v1_6 = M2C_FIELD(temp_a0, void **, 8);
    M2C_FIELD(arg1, s16 *, 2) = (s16) M2C_FIELD(temp_v1_6, u16 *, 2);
    M2C_FIELD(arg1, s16 *, 6) = (s16) M2C_FIELD(temp_v1_6, u16 *, 6);
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) M2C_FIELD(temp_v1_6, u16 *, 0xA);
    temp_s0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), void **, 0xC);
    func_800266D0(arg2, M2C_FIELD(temp_s0, s8 *, 4));
    func_80026548(arg0, M2C_FIELD(arg2, s32 *, 0));
    M2C_FIELD(arg2, u16 *, 0x1C) = (u16) M2C_FIELD(temp_s0, u16 *, 0x1C);
    M2C_FIELD(arg2, u16 *, 0x1E) = (u16) M2C_FIELD(temp_s0, u16 *, 0x1E);
    M2C_FIELD(arg2, u16 *, 0x20) = (u16) M2C_FIELD(temp_s0, u16 *, 0x20);
    M2C_FIELD(arg2, s32 *, 0xC) = M2C_FIELD(temp_s0, s32 *, 0xC);
    M2C_FIELD(arg2, u16 *, 0x16) = (u16) M2C_FIELD(temp_s0, u16 *, 0x16);
    M2C_FIELD(arg2, u16 *, 0x18) = (u16) M2C_FIELD(temp_s0, u16 *, 0x18);
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) M2C_FIELD(temp_s0, u16 *, 0x1A);
block_54:
    if (M2C_FIELD(arg0, s16 *, 0x2E) == 0) {
        func_8004491C(arg0 - 0x20, &D_800C9034);
        M2C_FIELD(arg0, s16 *, 0x2E) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2E) + 1);
    }
}
