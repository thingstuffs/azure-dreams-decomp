/* cfail-repair: tf7-phase1-cache-v3 */
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

void func_800353F4(void *);                   /* extern */
void func_80047738(void *, u8, s8);              /* extern */
void func_800478B8(void *);                      /* extern */
void func_800A020C(s32, void *);                 /* extern */
void func_800A1D4C(void *, s32);             /* extern */
s32 func_800A9E70(void *, void *, void *, void *);  /* extern */
void func_800AA36C(void *, void *, void *, void *); /* extern */
s16 func_800BCB04(u16, u16, s16);                   /* extern */
void func_8016A908(void *);                         /* extern */
void func_8016B518(void) __attribute__((noreturn)); /* extern */
void func_8016B564(void) __attribute__((noreturn)); /* extern */
void func_8016B588(void) __attribute__((noreturn)); /* extern */
void func_8016B5F4(void) __attribute__((noreturn)); /* extern */
void func_8016B68C(void) __attribute__((noreturn)); /* extern */
void func_8016B6A4(void) __attribute__((noreturn)); /* extern */
void func_8016B724(void) __attribute__((noreturn)); /* extern */
void func_8016B748() __attribute__((noreturn)); /* extern */
extern u8 D_80013610[0x3612];
extern s16 D_80013714[5];
extern u8 D_8006CCF8[256];
extern s32 D_800814A0[3];
extern s16 D_80083228[5];
extern u8 D_80083460[0x100];
extern u16 D_80083462[5];
extern u32 D_800835E4[64];
extern u8 *D_800E3D7C[3];
extern u8 D_800F927E[16];
extern void D_8016B778(void);
extern void (*D_80174728[256])(void *, void *, void *, void *);

void func_8016B0E8(void *arg0, void *arg1, void *arg2) {
    register M2C_UNK (*temp_v0_4)(void *, void *, void *, void *);
    register M2C_UNK (*temp_v1_5)(void *, void *, void *, void *);
    register s16 temp_a2;
    register s32 temp_s0_2;
    register s32 direction_index ASM_REG("$3");
    register s32 prior_direction;
    register s16 temp_v0_6 ASM_REG("$5");
    register s16 height_delta ASM_REG("$2");
    register s32 temp_a0_2;
    register s32 temp_a0_3;
    register s32 temp_a1;
    register s32 motion_position ASM_REG("$2");
    register s32 motion_delta ASM_REG("$4");
    register u16 motion_flags ASM_REG("$3");
    register s32 temp_s1 ASM_REG("$17");
    register s32 temp_v0;
    register u8 * temp_v0_5;
    register s32 temp_v1_7;
    register s32 var_s0 ASM_REG("$16");
    register s32 var_s0_2 ASM_REG("$16");
    register u32 var_v0;
    register u16 tail_flag ASM_REG("$2");
    register s16 temp_s0;
    register u16 *var_v0_2 ASM_REG("$2");
    register u16 temp_a0_4;
    register u16 temp_v1_6 ASM_REG("$3");
    register u16 var_v0_3 ASM_REG("$2");
    register u32 tail_predicate ASM_REG("$2");
    register u32 temp_v1;
    register u32 var_v1;
    register u8 temp_v0_3;
    register u32 *base_835e4;
    register u32 *limit_base;
    register u32 *loop_base;
    register u8 *state_83460;
    register u8 *late_state_83460;
    register u8 *message ASM_REG("$4");
    register void *entry_base ASM_REG("$2");
    register void *temp_v0_2;
    register void *temp_v1_2;
    register void *temp_v1_3;
    register void *temp_v1_4;
    register void *var_a0;
    register void *page_8001 ASM_REG("$2");
    register void *reg_arg0 ASM_REG("$19") = arg0;
    register void *reg_arg1 ASM_REG("$22") = arg1;
    register void *reg_arg2 ASM_REG("$21") = arg2;
    register void *obj ASM_REG("$18");
    register u8 *page_e ASM_REG("$20");
    register s32 high_bit ASM_REG("$23");
#define arg0 reg_arg0
#define arg1 reg_arg1
#define arg2 reg_arg2

    obj = arg0;
    if (M2C_FIELD(arg0, u32 *, 0x18) == 0) {
        page_8001 = (void *)0x80010000;
        ASM_KEEP(page_8001);
        temp_v0 = M2C_FIELD(page_8001, u8 *, 0x3611) | (M2C_FIELD(page_8001, u8 *, 0x3610) << 8);
        var_v1 = (u32) temp_v0 >> 2;
        if (temp_v0 < 0) {
            var_v1 = (u32) (temp_v0 + 3) >> 2;
        }
        if (var_v1 < 0x1AU) {
            var_v0 = var_v1 & 0xFFFF;
        } else {
            var_v1 = 0x19;
            ASM_KEEP_NV(var_v1);
            var_v0 = var_v1 & 0xFFFF;
        }
        base_835e4 = D_800835E4;
        limit_base = base_835e4 + 1;
        temp_v1 = base_835e4[var_v0] + 1;
        M2C_FIELD(arg0, u32 *, 0x18) = temp_v1;
        if (temp_v1 >= (u32) limit_base[M2C_FIELD(arg0, u8 *, 0x11)]) {
            loop_base = limit_base;
            do {
                func_800A1D4C(obj, 0);
            } while (!((u32) loop_base[M2C_FIELD(obj, u8 *, 0x11)] > (u32) M2C_FIELD(obj, u32 *, 0x18)));
        }
    }
    if (M2C_FIELD(arg0, u8 *, 0xB4) != 0) {
        state_83460 = D_80083460;
        if ((M2C_FIELD(state_83460, s32 *, 0xC) != 0) || (M2C_FIELD(state_83460, s16 *, 0xA) != 1)) {
            goto block_return;
        }
        if (M2C_FIELD(arg0, u8 *, 0xB4) == M2C_FIELD(state_83460, s16 *, 0xA)) {
            message = D_800F927E;
            ASM_KEEP(message);
            var_s0 = 0;
            page_e = (u8 *)0x800E0000;
            (*(s16 *)D_80013714) = (s16) ((*(u16 *)D_80013714) | 8);
            high_bit = 0x80000000;
            func_800353F4(message);
            M2C_FIELD(obj, u8 *, 0x6D) = 0U;
            M2C_FIELD(arg0, s8 *, 0x9B) = 0;
            M2C_FIELD(arg0, u8 *, 0xB4) = 0U;
            do {
                temp_s1 = var_s0 * 4;
                temp_a0_2 = M2C_FIELD((temp_s1 + M2C_FIELD(page_e, s32 *, 0x3D7C)), s32 *, 0xAC);
                if (temp_a0_2 != 0) {
                    func_8016A908(temp_a0_2);
                    entry_base = (void *)(temp_s1 + M2C_FIELD(page_e, s32 *, 0x3D7C));
                    temp_v1_2 = M2C_FIELD(entry_base, s32 *, 0xAC) - 0x20;
                    M2C_FIELD(temp_v1_2, s32 *, 0x10) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 0x10) | high_bit);
                }
                var_s0 += 1;
            } while (var_s0 < 2);
        }
    }
block_16:
        ASM_SCHED_BARRIER();
        if ((*(u16 *)D_80013714) & 8) {
            var_s0_2 = 1;
            var_a0 = M2C_FIELD(&D_800E3D7C, s32 *, 0) + 4;
            do {
                temp_v0_2 = M2C_FIELD(var_a0, void **, 0xAC);
                if (temp_v0_2 != NULL) {
                    temp_v1_3 = M2C_FIELD(temp_v0_2, void **, -0x14);
                    M2C_FIELD(temp_v1_3, u16 *, 0x14) = (u16) (M2C_FIELD(temp_v1_3, u16 *, 0x14) & 0xFFBF);
                }
                var_s0_2 -= 1;
                var_a0 -= 4;
            } while (var_s0_2 >= 0);
        }
        if (M2C_FIELD(arg0, u8 *, 0xB0) != 0) {
            temp_v0_3 = M2C_FIELD(arg0, u8 *, 0xB1) - 1;
            M2C_FIELD(arg0, u8 *, 0xB1) = temp_v0_3;
            if (!(temp_v0_3 & 0xFF)) {
                M2C_FIELD(obj, volatile s32 *, 0x14) = (s32) (M2C_FIELD(obj, volatile s32 *, 0x14) & 0xFFEFFFFF);
                M2C_FIELD(arg0, volatile u8 *, 0xB0) = 0U;
                late_state_83460 = D_80083460;
                M2C_FIELD(late_state_83460, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(late_state_83460, s16 *, 0xA) - 1);
                temp_v1_4 = M2C_FIELD(arg0, void **, 0xA4);
                M2C_FIELD(temp_v1_4, u16 *, 0x1E) = (u16) (M2C_FIELD(temp_v1_4, u16 *, 0x1E) | 0x8000);
                D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
            }
        }
        var_v0_2 = (u16 *)0x80080000;
        ASM_KEEP_NV(var_v0_2);
        if (M2C_FIELD(var_v0_2, u16 *, 0x3462) & 0x2000) {
            temp_v1_5 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
            if (temp_v1_5 == &D_8016B778) {
                temp_v1_5(arg0, arg1, arg2, obj);
                func_8016B748();
                return;
            }
            M2C_FIELD(obj, u8 *, 0x71) = (u8) (M2C_FIELD(obj, u8 *, 0x71) & 0x7F);
            func_8016B748(arg0);
            return;
        }
        temp_s0 = (s8) M2C_FIELD(obj, u8 *, 0x6D);
        if (func_800A9E70(arg0, arg1, arg2, obj) == 0) {
            temp_v0_4 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
            if (temp_v0_4 != NULL) {
                temp_v0_4(arg0, arg1, arg2, obj);
            }
            D_80174728[M2C_FIELD(arg0, u8 *, 0x9A)](arg0, arg1, arg2, obj);
            if ((s16) temp_s0 != (s8) M2C_FIELD(obj, u8 *, 0x6D)) {
                func_800AA36C(arg0, arg1, arg2, obj);
            }
            temp_v1_6 = M2C_FIELD(arg2, u16 *, 0x14);
            tail_predicate = temp_v1_6 & 0x8000;
            if (!tail_predicate) {
                temp_s0_2 = ((s32) (D_80083228[0] + M2C_FIELD(obj, s16 *, 0x2A) + 0x100) >> 9) & 7;
                prior_direction = M2C_FIELD(arg0, s16 *, 0x94);
                ASM_USE_NV(prior_direction);
                direction_index = temp_s0_2;
                ASM_KEEP_NV(direction_index);
                temp_s1 = temp_s0_2;
                if (prior_direction != direction_index) {
                    temp_v0_5 = M2C_FIELD(arg2, s32 *, 0x2C);
                    if (temp_v0_5 != 0) {
                        temp_a1 = *(temp_v0_5 + direction_index);
                        ASM_USE_NV(direction_index);
                        func_80047738(arg2, temp_a1, M2C_FIELD(arg2, s8 *, 4));
                    }
                    M2C_FIELD(arg0, s16 *, 0x94) = temp_s0_2;
                }
                temp_v0_3 = D_8006CCF8[temp_s1];
                ASM_USE_NV(temp_s1);
                if (temp_v0_3 != 0) {
                    tail_flag = M2C_FIELD(arg2, u16 *, 0x14) | 1;
                    ASM_TAILSLOT_PIN(tail_flag);
                    func_8016B518();
                    return;
                }
                M2C_FIELD(arg2, volatile u16 *, 0x14) = (u16) (M2C_FIELD(arg2, volatile u16 *, 0x14) & 0xFFFE);
                if (!(M2C_FIELD(obj, s32 *, 0x1C) & 0x20)) {
                    if (M2C_FIELD(arg2, volatile u16 *, 0x14) & 0x40) {
                        goto block_after_7000;
                    }
                    {
                        func_800478B8(arg2);
                        func_8016B564();
                        return;
                    }
                }
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x7000);
block_after_7000:
                func_800A020C(M2C_FIELD(obj, s32 *, 0x1C), arg2 + 0xC);
                func_8016B588();
                return;
            }
            tail_predicate = temp_v1_6 & 0x800;
            if (tail_predicate) {
                var_v0_3 = temp_v1_6 & 0x8FFF;
            } else {
                var_v0_3 = temp_v1_6 | 0x7000;
            }
            M2C_FIELD(arg2, u16 *, 0x14) = var_v0_3;
            M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
            M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
            if (!(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
                goto block_after_b5f4;
            }
block_tail_b5f4:
            M2C_FIELD(arg0, s8 *, 0x9D) = 0;
            {
                func_8016B5F4();
                return;
            }
block_after_b5f4:
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + (M2C_FIELD(arg0, s8 *, 0x9D) * 0x14000));
            temp_v0_3 = (u8) M2C_FIELD(arg0, s8 *, 0x9D) + 1;
            ASM_SCHED_BARRIER();
            M2C_FIELD(arg0, s8 *, 0x9D) = (s8) temp_v0_3;
            ASM_SCHED_BARRIER();
            motion_position = M2C_FIELD(arg0, s32 *, 0x90);
            ASM_SCHED_BARRIER();
            motion_delta = M2C_FIELD(arg1, s32 *, 0x14);
            ASM_SCHED_BARRIER();
            motion_flags = M2C_FIELD(arg0, u16 *, 0x98);
            motion_position += motion_delta;
            M2C_FIELD(arg0, s32 *, 0x90) = motion_position;
            if (!(motion_flags & 4)) {
                temp_v0_6 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(obj, u16 *, 0x88) - 0x20));
                ASM_KEEP(temp_v0_6);
                if (temp_v0_6 < 0x200) {
                    temp_a2 = (s16) M2C_FIELD(obj, u16 *, 0x88);
                    temp_a0_4 = M2C_FIELD(obj, u16 *, 0x88);
                    if (!((M2C_FIELD(arg0, s16 *, 0x92) + temp_a2) < temp_v0_6)) {
                        goto block_check_b68c;
                    }
block_tail_b6a4:
                    M2C_FIELD(obj, s32 *, 0x1C) = (s32) (M2C_FIELD(obj, s32 *, 0x1C) & 0xF7FFFFFF);
                    {
                        func_8016B6A4();
                        return;
                    }
block_check_b68c:
                    if (temp_v0_6 < temp_a2) {
                        goto block_normal_motion;
                    }
block_tail_b68c:
                    M2C_FIELD(arg0, s32 *, 0x90) = 0;
                    {
                        func_8016B68C();
                        return;
                    }
block_normal_motion:
                    height_delta = temp_v0_6 - temp_a0_4;
                    M2C_FIELD(arg0, s16 *, 0x92) = height_delta;
                    M2C_FIELD(arg1, s32 *, 0x14) = 0;
                    M2C_FIELD(obj, s32 *, 0x1C) = (s32) (M2C_FIELD(obj, s32 *, 0x1C) | 0x08000000);
                    M2C_FIELD(arg0, s8 *, 0x9D) = 0;
                    temp_v1_7 = M2C_FIELD(obj, s32 *, 0x1C);
                    if (temp_v1_7 & 0x40000000) {
                        M2C_FIELD(obj, s32 *, 0x1C) = (s32) (temp_v1_7 & 0xBFFFFFFF);
                        temp_v0_6 = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(obj, u16 *, 0x88) - 0x20));
                        ASM_KEEP(temp_v0_6);
                        M2C_FIELD(arg0, s16 *, 0x92) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x92) + (M2C_FIELD(obj, u16 *, 0x88) - temp_v0_6));
                        M2C_FIELD(obj, s16 *, 0x88) = temp_v0_6;
                        func_8016B724();
                        return;
                    }
                    goto block_67;
                }
            }
            M2C_FIELD(obj, s32 *, 0x1C) = (s32) (M2C_FIELD(obj, s32 *, 0x1C) & 0xF7FFFFFF);
block_67:
            M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(obj, u16 *, 0x88) + (u16) M2C_FIELD(arg0, s16 *, 0x92));
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x40);
        }
block_return:
    return;
}
