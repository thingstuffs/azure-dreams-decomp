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

M2C_UNK func_80048A44(); /* extern */
M2C_UNK func_80099F04();                         /* extern */
s32 func_8009C12C();    /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800B341C();        /* extern */
void func_800B357C() __attribute__((noreturn)); /* extern */
void func_800B3744() __attribute__((noreturn)); /* extern */
void func_800B3998() __attribute__((noreturn)); /* extern */
void func_800B3A40() __attribute__((noreturn)); /* extern */
M2C_UNK func_800B3D10();          /* extern */
M2C_UNK func_800B4194();             /* extern */
M2C_UNK func_800C77D0(); /* extern */
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008ACDC;
extern u8 D_800DD030[];
extern u8 D_800DD068[];
extern u8 D_800DD070[];
extern u8 D_800DD078[];
extern u8 D_800DD080[];
extern u8 D_800DD088[];
extern u8 D_800DD090[];
extern u8 D_800DD098[];
extern u8 D_800DD0A0[];
extern u8 D_800DD0A8[];
extern u8 D_800DD0B0[];
extern s32 D_800DF244[];
extern s16 D_800DF248[];
extern void *D_800891C0[];

void func_800B348C(void *arg0, void *arg1, void *arg2, void *arg3) {
    register void *held_arg1 ASM_REG("$18");
    register void *held_arg2 ASM_REG("$17");
    u8 *temp_a1;
    u8 *temp_a1_2;
    u8 *temp_a1_4;
    M2C_UNK var_a0;
    s32 temp_a1_3;
    s32 temp_v0_3;
    s32 temp_v1_2;
    s32 temp_v1_3;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_4;
    u8 jt_index;
    u8 state_9b;

    static void *const jt_keep[] = {
        &&jt_0, &&jt_1, &&jt_2, &&jt_3,
        &&jt_4, &&jt_5, &&jt_6, &&jt_7,
        &&jt_8, &&jt_9, &&jt_10, &&jt_default,
        &&jt_default, &&jt_default, &&jt_default, &&jt_15
    };

    held_arg1 = arg1;
    held_arg2 = arg2;
#define arg1 held_arg1
#define arg2 held_arg2
    jt_index = M2C_FIELD(arg0, u8 *, 0x9B);
    (void)jt_keep;
    if (jt_index >= 16) {
        goto jt_default;
    }
    goto *D_800891C0[jt_index];
    switch (M2C_FIELD(arg0, u8 *, 0x9B)) {
    case 0:
jt_0:
        M2C_FIELD(arg3, s32 *, 0x14) = (s32) (M2C_FIELD(arg3, s32 *, 0x14) & ~7);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        D_800DF248[0] = 0;
        return;
    case 1:
jt_1:
        if (M2C_FIELD(arg0, u16 *, 0xA6) != 0) {
            M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD030;
            func_80048A44(arg2, D_800DD030[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
            M2C_FIELD(arg0, u8 **, 0xCC) = NULL;
            if ((u16) M2C_FIELD(arg0, u16 *, 0xA6) < 2U) {
                func_800B357C();
                return;
            }
        } else {
            M2C_FIELD(arg0, s32 *, 0xF4) = 0;
            ASM_SCHED_BARRIER();
block_7:
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xDFFF);
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        case 2:
jt_2:
            if (M2C_FIELD(arg0, u16 *, 0xA6) == 0) {
                func_800C77D0(arg3 - 0x20, arg1, 8, 0x300);
                M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD068;
                func_80048A44(arg2, D_800DD068[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
                state_9b = M2C_FIELD(arg0, u8 *, 0x9B);
                M2C_FIELD(arg0, u8 **, 0xCC) = NULL;
                goto bump_state_9b;
            }
        }
        break;
    case 3:
jt_3:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            temp_v1_2 = ((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*(s16 *)((u8 *)&D_8006CCD8 + temp_v1_2) << 0x11);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*(s16 *)((u8 *)&D_8006CCE8 + temp_v1_2) << 0x11);
            M2C_FIELD(arg1, s32 *, 0x14) = 0xFFEBC000;
            M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD070;
            func_80048A44(arg2, D_800DD070[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
            {
                register u8 *next_v0 ASM_REG("$2");

                if (M2C_FIELD(arg3, s32 *, 0x4C) != 0) {
                    next_v0 = D_800DD078;
                } else {
                    next_v0 = D_800DD0A8;
                }
                M2C_FIELD(arg0, u8 **, 0xCC) = next_v0;
            }
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        break;
    case 4:
jt_4:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            temp_a1 = M2C_FIELD(arg0, u8 **, 0xCC);
            M2C_FIELD(arg2, u8 **, 0x2C) = temp_a1;
            func_80048A44(arg2, *(temp_a1 + (((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7)), 0, 1);
            if (M2C_FIELD(arg3, s32 *, 0x4C) != 0) {
                register u32 page_v0 ASM_REG("$2");
                register u8 *next_v1 ASM_REG("$3");

                page_v0 = 0x800E0000;
                ASM_KEEP(page_v0);
                next_v1 = (u8 *)page_v0 - 0x2F80;
                ASM_KEEP(next_v1);
                ASM_TAILSLOT_PIN(next_v1);
                func_800B3744();
                return;
            }
            {
                register u32 page_v0 ASM_REG("$2");
                register u8 *next_v1 ASM_REG("$3");

                ASM_CLOBBER("$2");
                page_v0 = 0x800E0000;
                ASM_KEEP(page_v0);
                next_v1 = (u8 *)page_v0 - 0x2F50;
                ASM_KEEP(next_v1);
                state_9b = M2C_FIELD(arg0, u8 *, 0x9B);
                M2C_FIELD(arg0, u8 **, 0xCC) = next_v1;
            }
            goto bump_state_9b;
        }
        break;
    case 5:
jt_5:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            if (M2C_FIELD(arg0, u8 *, 0xA8) != 0) {
                D_800DF248[0] = 1;
                goto load_state_9b;
            }
            M2C_FIELD(arg0, u16 *, 0x96) = 4U;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 0xA);
            return;
        }
        break;
    case 15:
jt_15:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
        if (((temp_v0 << 0x10) <= 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            var_a0 = 0x606;
            if (M2C_FIELD(arg3, s32 *, 0x4C) != 0) {
                var_a0 = 0x605;
            }
            func_800A56E0(var_a0);
            temp_a1_2 = M2C_FIELD(arg0, u8 **, 0xCC);
            M2C_FIELD(arg2, u8 **, 0x2C) = temp_a1_2;
            func_80048A44(arg2, *(temp_a1_2 + (((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7)), 0, 1);
            M2C_FIELD(arg0, u8 **, 0xCC) = D_800DD088;
            M2C_FIELD(arg0, u16 *, 0x96) = 2U;
            M2C_FIELD(arg0, u8 *, 0x9B) = 7U;
            return;
        }
        break;
    case 6:
jt_6:
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
        temp_a1_3 = M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
        D_800DF244[0] = temp_a1_3;
        if ((s16)temp_v0_2 < 0) {
            temp_v1_3 = ((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*(s16 *)((u8 *)&D_8006CCD8 + temp_v1_3) << 0x11);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*(s16 *)((u8 *)&D_8006CCE8 + temp_v1_3) << 0x11);
            M2C_FIELD(arg1, s32 *, 0x14) = temp_a1_3;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
            M2C_FIELD(arg0, u16 *, 0x96) = 4U;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            func_800B341C(arg0 - 0x20, M2C_FIELD(arg0, s32 *, 0xF4), 0x40);
            temp_a1_4 = M2C_FIELD(arg0, u8 **, 0xCC);
            M2C_FIELD(arg2, u8 **, 0x2C) = temp_a1_4;
            func_80048A44(arg2, *(temp_a1_4 + (((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7)), 0, 1);
            M2C_FIELD(arg0, u8 **, 0xCC) = D_800DD088;
            func_800B3D10(M2C_FIELD(arg0, u8 *, 0xA8), M2C_FIELD(arg3, void **, 0x60), arg3);
            return;
        }
        break;
    case 7:
jt_7:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            func_800B3998();
            return;
        } else {
            M2C_FIELD(arg0, u16 *, 0x96) = (u16) (M2C_FIELD(arg0, u16 *, 0x96) - 1);
        }
        ASM_MEM_BARRIER();
        if (M2C_FIELD(arg0, s16 *, 0x96) == 0) {
            if (M2C_FIELD(arg0, u8 *, 0x102) == 0) {
                register s32 temp_a2 ASM_REG("$6");

                temp_a2 = func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
                if (temp_a2 != 0) {
                    func_800B4194(M2C_FIELD(arg0, u8 *, 0xA8), temp_a2, arg3);
                    M2C_FIELD(arg0, u8 *, 0xA8) = 0U;
                    func_800B3A40();
                    return;
                } else {
                    register void *temp_a2 ASM_REG("$6");

                    temp_a2 = M2C_FIELD(arg3, void **, 0x60);
                    if (temp_a2 != NULL) {
                        M2C_FIELD(arg3, void **, 0x60) = NULL;
                        M2C_FIELD(temp_a2, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x1C) & 0xEFFFFFFF);
                        M2C_FIELD(M2C_FIELD(temp_a2, void **, -0x14), s32 *, 0xC) = 0x808080;
                        func_800B3A40();
                        return;
                    }
                }
            } else {
                void *temp_a0;

                temp_a0 = M2C_FIELD(arg3, void **, 0x60);
                if (temp_a0 != NULL) {
                    M2C_FIELD(temp_a0, s32 *, 0x14) = (s32) (M2C_FIELD(temp_a0, s32 *, 0x14) | 0x01000000);
                }
            }
        }
        if (((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) && (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
            M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD088;
            func_80048A44(arg2, D_800DD088[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
            M2C_FIELD(arg0, u8 **, 0xCC) = D_800DD090;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        }
        /* fallthrough */
    case 8:
jt_8:
        if (M2C_FIELD(arg0, u16 *, 0xA2) & 0x10) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            if (M2C_FIELD(arg0, u8 *, 0xA8) != 0) {
                M2C_FIELD(arg0, u8 *, 0xA8) = 0U;
            }
            if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
                M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD090;
                func_80048A44(arg2, D_800DD090[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
                M2C_FIELD(arg0, u8 **, 0xCC) = D_800DD098;
                M2C_FIELD(arg0, u8 *, 0x9B) = 9U;
                return;
            }
        }
        break;
    case 9: {
        s32 delta_x;
        s32 delta_y;

jt_9:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD098;
            func_80048A44(arg2, D_800DD098[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
            M2C_FIELD(arg0, u16 *, 0x96) = 2U;
            delta_x = M2C_FIELD(arg2, u8 *, 0x24) << 6;
            delta_y = M2C_FIELD(arg1, s16 *, 2);
            delta_y -= 0x20;
            delta_x -= delta_y;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((delta_x << 0x10) / (s16) M2C_FIELD(arg0, u16 *, 0x96));
            delta_y = M2C_FIELD(arg1, s16 *, 6) - 0x20;
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - delta_y) << 0x10) / (s16) M2C_FIELD(arg0, u16 *, 0x96));
load_state_9b:
            state_9b = M2C_FIELD(arg0, u8 *, 0x9B);
bump_state_9b:
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (state_9b + 1);
            return;
        }
        break;
    }
    case 10: {
        register u32 end_page ASM_REG("$2");
        register s32 *end_base ASM_REG("$5");
        register s32 end_mask ASM_REG("$4");
        register s32 end_timer_state ASM_REG("$3");
        s32 end_flags;

jt_10:
        temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_4;
        if (((temp_v0_4 << 0x10) <= 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            {
                register void *case10_arg2 ASM_REG("$4");
                case10_arg2 = arg2;
                M2C_FIELD(case10_arg2, u8 **, 0x2C) = D_800DD0A0;
                func_80048A44(case10_arg2, D_800DD0A0[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
            }
            func_80099F04(M2C_FIELD(arg3, s32 *, 0x5C));
            end_page = 0x80080000;
            ASM_KEEP(end_page);
            end_base = (s32 *)(end_page + 0x3460);
            ASM_KEEP(end_base);
            end_mask = -8;
            ASM_KEEP(end_mask);
            M2C_FIELD(end_base, u16 *, 2) = (u16) (M2C_FIELD(end_base, u16 *, 2) | 0x412);
            end_timer_state = 0x800E0000;
            ASM_KEEP(end_timer_state);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8008ACDC;
            end_flags = M2C_FIELD(arg3, s32 *, 0x14);
            end_timer_state = *(s16 *)((u8 *)end_timer_state - 0xDB8);
            end_flags &= end_mask;
            M2C_FIELD(arg3, s32 *, 0x14) = end_flags;
            if (end_timer_state == 0) {
                ASM_CLOBBER("$3");
                M2C_FIELD(end_base, s32 *, 0xC) = 0;
            }
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
        }
        break;
    }
    default:
jt_default:
        break;
    }
    ASM_KEEP(held_arg1);
    ASM_KEEP(held_arg2);
}
#undef arg1
#undef arg2
