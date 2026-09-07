#include "common.h"
#ifdef NON_MATCHING
#include <stdint.h>
typedef uintptr_t uptr;
#else
typedef u32 uptr;
#endif
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

s32 func_8009A180(void *, void *);
void func_8009A21C(s32, s32, s32);
void func_8009A3D0(s32, s32, s32);
s32 func_8009A66C(s32, void *, void *, s32);
s32 func_8009FD7C(s32, s32, s32, s32);
void *func_800A02AC(void *, s32, s32);
s32 func_800A04F0(void *, s32, s32, s32);
s16 func_800A0818(s32, s32, s32, s32, void *);
void func_800A0E6C(void *, s32, void *, void *);
void func_800A19E4(void *, void *, s32, s32, void *);
s32 func_800A6D30(void);
void func_800A9A0C(void *);
extern void call_800A9A0C_top(void *) __asm__("func_800A9A0C");
s16 func_800BCB04(s32, s32, s32);
void func_8016FF80(void) __attribute__((noreturn));
void func_8016FF84(void) __attribute__((noreturn));
void func_8016FFC0(void) __attribute__((noreturn));
void func_80170110(void) __attribute__((noreturn));
void func_8017018C(void) __attribute__((noreturn));
void func_801701E4(void) __attribute__((noreturn));
extern void call_8016FF80(void) __asm__("func_8016FF80") __attribute__((noreturn));
extern void call_8016FF84(void) __asm__("func_8016FF84") __attribute__((noreturn));
extern void call_8016FFC0(void) __asm__("func_8016FFC0") __attribute__((noreturn));
extern void call_80170110(void) __asm__("func_80170110") __attribute__((noreturn));
extern void call_8017018C(void) __asm__("func_8017018C") __attribute__((noreturn));
extern void call_801701E4(void) __asm__("func_801701E4") __attribute__((noreturn));
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s16 D_8006CD00[];
extern u8 *D_800814A8;
extern u8 D_80082E80[];
extern u8 D_80082E80_b[] __asm__("D_80082E80");
extern u8 D_80082E80_c[] __asm__("D_80082E80");
extern u16 D_80082EA4;
extern u16 D_80083462;
extern u8 D_80083460[];

void func_8016FCE4(void *arg0, void *arg1, void *in2, void *in3) {
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    register void *arg2 ASM_REG("$19");
    register void *arg3 ASM_REG("$18");
    register s16 *var_s1;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s0_2;
    s16 temp_v0_4;
    register s32 temp_a0 ASM_REG("$4");
    register s32 temp_call_a1 ASM_REG("$5");
    register s32 temp_s0 ASM_REG("$16");
    register s32 temp_v0_3 ASM_REG("$2");
    s32 temp_v1;
    register s32 temp_v1_2 ASM_REG("$3");
    register u8 *counter_base ASM_REG("$3");
    register s32 var_s4 ASM_REG("$20");
    register s32 var_s6 ASM_REG("$22");
    u8 *var_s7;
    void *temp_v0;
    void *temp_v0_2;

    arg2 = in2;
    arg3 = in3;
    var_s6 = 0;
    if ((D_80083462 & 0x4000) || (M2C_FIELD(arg3, s8 *, 0x71) >= 0)) {
        call_800A9A0C_top(arg3);
        call_801701E4();
        return;
    }
    if (D_80083462 & 0x2000) {
        func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
        ASM_KEEP_NV(arg2);
        ASM_KEEP_NV(arg3);
        temp_v1 = M2C_FIELD(arg3, s32 *, 0x1C);
        if (temp_v1 & 0x410) {
            if (temp_v1 & 0x400) {
                temp_v0 = func_800A02AC(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
                if (temp_v0 != NULL) {
                    temp_v0_2 = M2C_FIELD(temp_v0, void **, -0x14);
                    M2C_FIELD(arg3, u16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(temp_v0_2, u8 *, 0x24), M2C_FIELD(temp_v0_2, u8 *, 0x25), arg0 + 0x98);
                    M2C_FIELD(arg3, u8 *, 0x71) = M2C_FIELD(arg3, u8 *, 0x71) & 0x7F;
                    call_801701E4();
                    return;
                }
                temp_v0_3 = M2C_FIELD(arg3, s32 *, 0x14);
                if (temp_v0_3 >= 0) {
                    M2C_FIELD(arg3, s32 *, 0x14) = (s32) (temp_v0_3 | 0x80000000);
                    M2C_FIELD(arg3, u16 *, 0x2A) += (func_800A6D30() & 7) << 9;
                    call_8016FF80();
                    return;
                }
                goto block_26;
            }
            ASM_SCHED_BARRIER();
            temp_v0_3 = func_800A04F0(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) M2C_FIELD(arg3, u16 *, 0x2A));
            ASM_SCHED_BARRIER();
            var_s4 = 0;
            if (temp_v0_3 != 0) {
                call_8017018C();
                return;
            }
            goto block_27;
        }
        var_s4 = 0;
        if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
            if (temp_v1 & 0x20000) {
                register u8 **heading_ref ASM_REG("$2") = &D_800814A8;
                register u8 *position_base = D_80082E80;
                u8 *heading_base;
                register u8 *x_table_base ASM_REG("$4");
                register s32 dir_index ASM_REG("$3");

                ASM_USE(position_base);
                x_table_base = D_8006CCD8;
                heading_base = *heading_ref;
                dir_index = ((M2C_FIELD(arg3, u8 *, 0x45) + ((s32) (M2C_FIELD(heading_base, u16 *, 0x2A) << 0x10) >> 0x19)) & 7) * 2;
                temp_a2 = position_base[0x24] + *(u16 *)(x_table_base + dir_index);
                temp_a1 = D_80082E80[0x25] + *(u16 *)(D_8006CCE8 + dir_index);
                if ((M2C_FIELD(arg2, u8 *, 0x24) != (temp_a2 & 0xFFFF)) || (M2C_FIELD(arg2, u8 *, 0x25) != (temp_a1 & 0xFFFF))) {
                    ASM_MEM_BARRIER();
                    temp_s0 = arg0 + 0x98;
                    temp_v0_4 = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) temp_a2, (s16) temp_a1, temp_s0);
                    M2C_FIELD(arg3, u16 *, 0x2A) = (u16) temp_v0_4;
                    if ((func_8009A66C(temp_v0_4, arg2, arg3, 0x20) << 0x10) <= 0) {
                        M2C_FIELD(arg3, u16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), D_80082E80_b[0x24], D_80082E80_b[0x25], temp_s0);
                    }
                    temp_v0_3 = func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), D_80082E80_b[0x24], D_80082E80_b[0x25]);
                    ASM_SCHED_BARRIER();
                    var_s4 = 0;
                    if ((temp_v0_3 << 0x10) != 0) {
                        ASM_USE(var_s4);
                        var_s6 = 1;
                        ASM_TAILSLOT_PIN(var_s6);
                        call_8016FF84();
                        return;
                    }
                    goto block_27;
                }
                goto block_cleanup;
            }
            func_800A0E6C(arg2, M2C_FIELD(arg0, s8 *, 0x9C), arg3, arg0 + 0x98);
block_26:
            ASM_SCHED_BARRIER();
            var_s4 = 0;
            goto block_27;
        }
block_27:
        var_s7 = D_8006CCD8;
        var_s1 = D_8006CD00;
loop_28:
        temp_v1_2 = M2C_FIELD(arg3, s16 *, 0x2A);
        if (M2C_FIELD(arg0, u16 *, 0x98) & 2) {
            temp_v0_3 = *var_s1;
            temp_s0_2 = temp_v1_2 - temp_v0_3;
            ASM_TAILSLOT_PIN(temp_s0_2);
            call_8016FFC0();
            return;
        }
        ASM_SCHED_BARRIER();
        temp_v0_3 = *var_s1;
        ASM_KEEP(temp_v0_3);
        temp_s0_2 = temp_v1_2 + temp_v0_3;
        if ((func_8009A66C((s16) temp_s0_2, arg2, arg3, 0x20) << 0x10) > 0) {
            if (var_s4 < 3) {
                goto block_step;
            }
            temp_v0_3 = var_s6;
            ASM_KEEP_NV(temp_v0_3);
            if (temp_v0_3 != 0) {
                goto block_cleanup;
            }
block_step:
            {
                M2C_FIELD(arg3, u16 *, 0x2A) = (u16) temp_s0_2;
                M2C_FIELD((arg3 + ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F)), u8 *, 0x74) = (u8) M2C_FIELD(arg2, u8 *, 0x24);
                M2C_FIELD((arg3 + ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F)), u8 *, 0x7C) = (u8) M2C_FIELD(arg2, u8 *, 0x25);
                M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) + 1);
                func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25),
                              (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) ? 0x300 : 0x3000);
                temp_a0 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
                M2C_FIELD(arg2, u8 *, 0x24) = (u8) (M2C_FIELD(arg2, u8 *, 0x24) + *(u8 *) ((uptr) temp_a0 + (uptr) var_s7));
                M2C_FIELD(arg2, u8 *, 0x25) = (u8) (M2C_FIELD(arg2, u8 *, 0x25) + D_8006CCE8[temp_a0]);
                temp_a0 = M2C_FIELD(arg2, u8 *, 0x24);
                temp_call_a1 = M2C_FIELD(arg2, u8 *, 0x25);
                if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                    var_a2_2 = 0x300;
                } else {
                    var_a2_2 = 0x3000;
                }
                func_8009A21C(temp_a0, temp_call_a1, var_a2_2);
                temp_v0_3 = var_s4 < 8;
                ASM_KEEP_NV(temp_v0_3);
                ASM_TAILSLOT_PIN(temp_v0_3);
                call_80170110();
            }
        }
        if ((var_s4 != 0) || (D_80082EA4 == M2C_FIELD(arg2, u16 *, 0x24)) || ((func_8009A180(arg3, M2C_FIELD(D_800814A8, s32 *, 0x58) + 0x20) << 0x10) == 0)) {
            var_s4 += 1;
            var_s1 += 1;
            if (var_s4 >= 8) {
block_48:
                ASM_KEEP_NV(var_s4);
                temp_v0_3 = var_s4 < 8;
                ASM_KEEP_NV(temp_v0_3);
                if (temp_v0_3 == 0) {
                    M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F);
                    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                    func_800A9A0C(arg3);
                    call_801701E4();
                    return;
                }
                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                M2C_FIELD(arg0, s8 *, 0x9C) = (s8) M2C_FIELD(arg2, u8 *, 0x26);
                M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
                counter_base = D_80083460;
                M2C_FIELD(counter_base, u16 *, 8) = (u16) (M2C_FIELD(counter_base, u16 *, 8) + 1);
                if (M2C_FIELD(arg3, s8 *, 0x6D) != 0) {
                    goto block_life_nonzero;
                }
block_cleanup:
                M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F);
                call_801701E4();
                return;
block_life_nonzero:
                var_s4 = (s16) func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
                if (var_s4 < 0x200) {
                    M2C_FIELD(arg3, u16 *, 0x88) = (u16) var_s4;
                }
            } else {
                goto loop_28;
            }
        }
    }
}
