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

s32 func_8009A180();                     /* extern */
M2C_UNK func_8009A21C();             /* extern */
M2C_UNK func_8009A3D0();             /* extern */
s32 func_8009A540();                /* extern */
s32 func_8009A66C();    /* extern */
s32 func_8009FD7C();                  /* extern */
s16 func_800A0134();                  /* extern */
void *func_800A02AC();                /* extern */
void *func_800A04F0();           /* extern */
u16 func_800A0818();          /* extern */
M2C_UNK func_800A0E6C();  /* extern */
M2C_UNK func_800A19E4(); /* extern */
M2C_UNK func_800A6D30();                            /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
s16 func_800BCB04();                   /* extern */
s32 func_8016C720();          /* extern */
typedef struct {
    u8 pad[0xC];
    u16 flags;
    u8 tail[6];
} D_800E2970Entry;
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern s16 D_8006CD00;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern u16 D_80082EA4;
extern M2C_UNK D_80083460;
extern D_800E2970Entry D_800E2970[];

void func_8016BF74(void *raw_arg0, void *arg1, void *raw_arg2, void *raw_arg3) {
    register void *arg0 ASM_REG("$21");
    register void *arg2 ASM_REG("$20");
    register void *arg3 ASM_REG("$18");
    register s32 var_s3 ASM_REG("$19");
    register s32 var_s6 ASM_REG("$22");
    register u8 *var_s7 ASM_REG("$23");
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    register s8 *var_s1 ASM_REG("$17");
    register s8 *loop_page ASM_REG("$2");
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_w1;
    s32 temp_w2;
    s16 temp_v0_4;
    s16 temp_v0_6;
    register s32 temp_a0_2 ASM_REG("$4");
    u8 *temp_v1_ptr;
    register s32 temp_v0_3 ASM_REG("$2");
    register s32 temp_high_bit ASM_REG("$3");
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_v0;
    s8 temp_a0;
    s8 *state;
    s32 state_flags;
    register void *temp_v0 ASM_REG("$3");
    void *temp_v0_2;
    void *temp_v0_7;
    register void *temp_v0_5 ASM_REG("$3");
    register s32 temp_c008 ASM_REG("$2");
    register s32 temp_call_a1 ASM_REG("$5");
    register s32 loop_angle ASM_REG("$3");
    register s16 loop_sum ASM_REG("$16");
    register void *first_position ASM_REG("$2");
    s32 first_a0;
    s32 first_a1;
    s32 first_a2;
    s32 first_a3;
    register s32 loop_flags ASM_REG("$3");
    register s32 loop_flags2 ASM_REG("$2");
    register s32 loop_table_y ASM_REG("$3");
    register s32 loop_call_a0 ASM_REG("$4");
    register s32 first_compare_x ASM_REG("$3");
    register s32 loop_next ASM_REG("$2");
    register s32 loop_y ASM_REG("$2");
    register u8 *loop_table_base ASM_REG("$2");
    register u8 *loop_table_ptr ASM_REG("$4");
    register u8 *world_call ASM_REG("$2");

    arg0 = raw_arg0;
    arg2 = raw_arg2;
    arg3 = raw_arg3;
    state = (s8 *)&D_80083460;
    ASM_KEEP(arg0);
    ASM_KEEP(arg2);
    ASM_KEEP(arg3);
    state_flags = M2C_FIELD(state, u16 *, 2);
    var_s6 = 0;
    if ((state_flags & 0x4000) || (M2C_FIELD(arg3, s8 *, 0x71) >= 0)) {
        if (((u8) M2C_FIELD(arg3, u8 *, 0x12) >= 2U) || ((func_8016C720(arg0, arg1, arg2, arg3) << 0x10) == 0)) {
            func_800A9A0C(arg3);
            ASM_KEEP(arg3);
            return;
        }
        temp_c008 = M2C_FIELD(state, s32 *, 0xC);
        if ((void *)temp_c008 == arg3) {
            temp_c008 = 0xC008;
            M2C_FIELD(arg3, u16 *, 0x46) = (u16) temp_c008;
            return;
        }
        return;
    }
    if (state_flags & 0x2000) {
        func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
        temp_v1 = M2C_FIELD(arg3, s32 *, 0x1C);
        if (temp_v1 & 0x410) {
            if (temp_v1 & 0x400) {
                temp_v0 = func_800A02AC(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
                if (temp_v0 != NULL) {
                    first_a0 = M2C_FIELD(arg2, u8 *, 0x24);
                    temp_v0_2 = M2C_FIELD(temp_v0, void **, -0x14);
                    first_a1 = M2C_FIELD(arg2, u8 *, 0x25);
                    first_a2 = M2C_FIELD(temp_v0_2, u8 *, 0x24);
                    first_a3 = M2C_FIELD(temp_v0_2, u8 *, 0x25);
                    ASM_KEEP4(first_a0, first_a1, first_a2, first_a3);
                    ASM_CLOBBER("$2");
                    first_position = arg0 + 0x98;
                    ASM_KEEP(first_position);
                    M2C_FIELD(arg3, u16 *, 0x2A) = func_800A0818(first_a0, first_a1, first_a2, first_a3, first_position);
                    M2C_FIELD(arg3, u8 *, 0x71) &= 0x7F;
                    return;
                }
                temp_v0_3 = M2C_FIELD(arg3, s32 *, 0x14);
                if (temp_v0_3 >= 0) {
                    temp_high_bit = 0x80000000;
                    temp_v0_3 |= temp_high_bit;
                    M2C_FIELD(arg3, s32 *, 0x14) = temp_v0_3;
                    var_v0 = func_800A6D30();
                    M2C_FIELD(arg3, u16 *, 0x2A) += (var_v0 & 7) << 9;
                    goto block_46;
                }
                goto block_46;
            }
            temp_v0_7 = func_800A04F0(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) M2C_FIELD(arg3, u16 *, 0x2A));
            var_s3 = 0;
            if (temp_v0_7 == NULL) {
                goto block_47;
            }
            goto block_clear_71;
        }
        if (M2C_FIELD(arg0, u8 *, 0xB2) != 0) {
                var_s3 = 0;
                if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
                    if (temp_v1 & 0x20000) {
                    temp_v1_2 = ((M2C_FIELD(arg3, u8 *, 0x45) + ((s32) (M2C_FIELD(D_800814A8, u16 *, 0x2A) << 0x10) >> 0x19)) & 7) * 2;
                    temp_w2 = D_80082E80[0x24];
                    temp_w1 = D_80082E80[0x25];
                    temp_t2 = M2C_FIELD(&D_8006CCD8, u16 *, temp_v1_2);
                    temp_t1 = M2C_FIELD(&D_8006CCE8, u16 *, temp_v1_2);
                    ASM_MEM_BARRIER();
                    first_compare_x = M2C_FIELD(arg2, u8 *, 0x24);
                    temp_a2 = temp_w2 + temp_t2;
                    temp_a1 = temp_w1 + temp_t1;
                    ASM_KEEP(first_compare_x);
                    ASM_USE_NV(temp_t2);
                    if ((first_compare_x != (temp_a2 & 0xFFFF)) || (M2C_FIELD(arg2, u8 *, 0x25) != (temp_a1 & 0xFFFF))) {
                        ASM_MEM_BARRIER();
                        temp_v0_4 = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) temp_a2, (s16) temp_a1, arg0 + 0x98);
                        M2C_FIELD(arg3, u16 *, 0x2A) = (u16) temp_v0_4;
                        if ((func_8009A66C(temp_v0_4, arg2, arg3, 0x20) << 0x10) <= 0) {
                            u8 *wcf;

                            wcf = (u8 *)&D_80082EA4 - 0x24;
                            M2C_FIELD(arg3, u16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), wcf[0x24], wcf[0x25], arg0 + 0x98);
                        }
                        world_call = (u8 *)&D_80082EA4 - 0x24;
                        var_v0 = func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), world_call[0x24], world_call[0x25]);
                        ASM_CLOBBER("$19");
                        var_s3 = 0;
                        if ((var_v0 << 0x10) == 0) {
                            goto block_47;
                        }
                        var_s6 = 1;
                        goto block_47;
                    }
                    goto block_clear_71;
                }
                goto block_44;
            }
            goto block_47;
        }
        temp_a0 = M2C_FIELD(arg2, s8 *, 0x26);
        if ((temp_a0 < 0) || !(D_800E2970[temp_a0].flags & 2)) {
            var_s3 = 0;
            if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
                temp_v0_5 = func_800A04F0(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) M2C_FIELD(arg3, u16 *, 0x2A));
                if ((temp_v0_5 == NULL) || !(M2C_FIELD(temp_v0_5, s32 *, 0x1C) & 0x2000) || (func_800A0134(temp_v0_5, arg3) >= 0x81) || ((func_8009A540(((s32) (M2C_FIELD(arg3, u16 *, 0x2A) << 0x10) >> 0x19) & 0xFFFF, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20)) << 0x10) == 0)) {
                    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x20000) {
                        u8 *world2;

                        world2 = (u8 *)&D_80082E80;
                        M2C_FIELD(arg3, u16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), world2[0x24], world2[0x25], arg0 + 0x98);
                        if ((func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), world2[0x24], world2[0x25]) << 0x10) != 0) {
                            temp_v0_6 = func_800A0134(D_800814A8, arg3);
                            ASM_CLOBBER("$19");
                            var_s3 = 0;
                            if (temp_v0_6 < 0x81) {
                                var_v0 = func_8009A540(((s32) (M2C_FIELD(arg3, u16 *, 0x2A) << 0x10) >> 0x19) & 0xFFFF, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
                                ASM_CLOBBER("$19");
                                var_s3 = 0;
                                if ((var_v0 << 0x10) == 0) {
                                    goto block_47;
                                }
                                goto block_clear_71;
                            }
                            goto block_47;
                        }
                        goto block_46;
                    }
block_44:
                    goto block_45;
                }
                goto block_clear_71;
            }
            goto block_47;
        }
block_45:
        func_800A0E6C(arg2, M2C_FIELD(arg0, s8 *, 0x9C), arg3, arg0 + 0x98);
block_46:
        ASM_SCHED_BARRIER();
        var_s3 = 0;
block_47:
#ifdef __mips__
        loop_page = (s8 *)0x80070000;
#else
        loop_page = (s8 *)&D_8006CCD8 + 0x3328;
#endif
        ASM_KEEP(loop_page);
        var_s7 = (u8 *)(loop_page - 0x3328);
#ifdef __mips__
        loop_page = (s8 *)0x80070000;
#else
        loop_page = (s8 *)&D_8006CD00 + 0x3300;
#endif
        ASM_KEEP(loop_page);
        var_s1 = loop_page - 0x3300;
loop_48:
        loop_angle = M2C_FIELD(arg3, s16 *, 0x2A);
        if (M2C_FIELD(arg0, u16 *, 0x98) & 2) {
            temp_v0_3 = *(s16 *)var_s1;
            loop_sum = loop_angle - temp_v0_3;
            goto block_444;
        }
        ASM_SCHED_BARRIER();
        temp_v0_3 = *(s16 *)var_s1;
        ASM_KEEP(temp_v0_3);
        loop_sum = loop_angle + temp_v0_3;
block_444:
        if ((func_8009A66C(loop_sum, arg2, arg3, 0x20) << 0x10) > 0) {
            if (var_s3 < 3) {
                goto block_step_loop;
            }
            temp_v0_3 = var_s6;
            ASM_KEEP_NV(temp_v0_3);
            if (temp_v0_3 != 0) {
                goto block_cleanup_loop;
            }
block_step_loop:
                M2C_FIELD(arg3, u16 *, 0x2A) = (u16) loop_sum;
                M2C_FIELD((arg3 + ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F)), u8 *, 0x74) = (u8) M2C_FIELD(arg2, u8 *, 0x24);
                M2C_FIELD((arg3 + ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F)), u8 *, 0x7C) = (u8) M2C_FIELD(arg2, u8 *, 0x25);
                loop_next = (u8) M2C_FIELD(arg3, s8 *, 0x71) + 1;
                loop_flags = M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000;
                M2C_FIELD(arg3, s8 *, 0x71) = (s8) loop_next;
                temp_a0_2 = M2C_FIELD(arg2, u8 *, 0x24);
                temp_call_a1 = M2C_FIELD(arg2, u8 *, 0x25);
                var_a2 = 0x3000;
                if (loop_flags) {
                    var_a2 = 0x300;
                }
                func_8009A3D0(temp_a0_2, temp_call_a1, var_a2);
                temp_a0_2 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
                temp_v1_ptr = (u8 *)((u32) temp_a0_2 + (u32) var_s7);
                M2C_FIELD(arg2, u8 *, 0x24) = (u8) (M2C_FIELD(arg2, u8 *, 0x24) + *temp_v1_ptr);
                ASM_KEEP(var_s7);
                loop_table_base = (u8 *)&D_8006CCE8;
                ASM_KEEP_NV(loop_table_base);
                loop_table_ptr = (u8 *)((u32) temp_a0_2 + (u32) loop_table_base);
                loop_y = M2C_FIELD(arg2, u8 *, 0x25);
                loop_table_y = *loop_table_ptr;
                loop_call_a0 = M2C_FIELD(arg2, u8 *, 0x24);
                M2C_FIELD(arg2, u8 *, 0x25) = (u8) (loop_y + loop_table_y);
                var_a2_2 = 0x3000;
                loop_flags2 = M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000;
                temp_call_a1 = M2C_FIELD(arg2, u8 *, 0x25);
                if (loop_flags2) {
                    var_a2_2 = 0x300;
                }
                func_8009A21C(loop_call_a0, temp_call_a1, var_a2_2);
                var_v0 = var_s3 < 8;
                goto block_594;
block_cleanup_loop:
            goto block_clear_71;
        }
        if ((var_s3 != 0) || (D_80082EA4 == M2C_FIELD(arg2, u16 *, 0x24)) || (var_v0 = func_8009A180(arg3, M2C_FIELD(D_800814A8, s32 *, 0x58) + 0x20) << 0x10, (var_v0 == 0))) {
            var_s3 += 1;
            var_s1 += 2;
            if (var_s3 >= 8) {
                s8 *state2;

                ASM_KEEP(var_s3);
                var_v0 = var_s3 < 8;
block_594:
                if (var_v0 == 0) {
                    M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F);
                    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                    func_800A9A0C(arg3);
                    return;
                }
                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                M2C_FIELD(arg0, s8 *, 0x9C) = (s8) (u8) M2C_FIELD(arg2, s8 *, 0x26);
                M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
                state2 = (s8 *)&D_80083460;
                M2C_FIELD(state2, u16 *, 8) = (u16) (M2C_FIELD(state2, u16 *, 8) + 1);
                if (M2C_FIELD(arg3, s8 *, 0x6D) == 0) {
block_clear_71:
                    M2C_FIELD(arg3, u8 *, 0x71) &= 0x7F;
                    return;
                }
                var_s3 = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
                var_v0 = var_s3 < 0x200;
                if (var_v0 != 0) {
                    M2C_FIELD(arg3, u16 *, 0x88) = (u16) var_s3;
                }
                /* Duplicate return node #72. Try simplifying control flow for better match */
                return;
            }
            goto loop_48;
        }
        /* Duplicate return node #72. Try simplifying control flow for better match */
        return;
    }
    return;
}
