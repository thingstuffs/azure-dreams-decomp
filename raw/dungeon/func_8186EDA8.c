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

/* cfail-repair: tf7-phase1-cache-v3 */
extern u16 D_80025308[];
extern s32 D_800814A0[];
extern void func_80024710() __attribute__((noreturn));
void func_80024770() __attribute__((noreturn));      /* extern */
void func_80024874(void) __attribute__((noreturn));  /* extern */
s32 func_800644B8(s16);                          /* extern */
s32 func_80064584(s16);                          /* extern */
void func_800478B8(void *);                       /* extern */

typedef struct {
    s16 state;
    u16 timer;
    u8 pad4[6];
    s16 count;
    s16 angle;
    u16 angle2;
    u8 pad10[0x3C];
    s32 base0;
    s32 base1;
} DungeonState;

typedef struct {
    u8 pad0[0xC];
    u8 c;
    u8 d;
    u8 e;
    u8 padF[5];
    u16 flags14;
    u8 pad16[6];
    u16 x1C;
    u16 y1E;
} DungeonEffect;

void func_8186EDA8(DungeonState *arg0, void *arg1, DungeonEffect *arg2) {
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_4;
    s16 temp_v1_5;
    s32 var_a0;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 effect_x;
    u16 effect_y;
    u8 effect_c;
    u8 effect_d;
    u8 effect_e;
    u8 temp_v1_3;
    DungeonEffect *effect = arg2;
    u16 *flag_page = (u16 *)0x80020000;
    s32 first_angle = arg0->angle;


    ASM_USE_NV(flag_page);
    
    M2C_FIELD(arg1, s32 *, 0) = (s32) (arg0->base0 + (arg0->count * func_800644B8((flag_page[0x2984] = 1, first_angle)) * 0x10));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (arg0->base1 + (arg0->count * func_80064584(arg0->angle) * 0x10));
    func_800478B8(effect);
    temp_v1 = arg0->state;
    if (temp_v1 == 1) {
        goto case_1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto case_0;
        }
        ASM_SCHED_BARRIER();
        func_80024874();
        return;
    }
    if (temp_v1 == 2) {
        goto case_2;
    }
    if (temp_v1 == 3) {
        goto case_3;
    }
    func_80024874();
    return;

case_0:
            temp_v0 = M2C_FIELD(arg0, u16 *, 2) - 1;
            M2C_FIELD(arg0, u16 *, 2) = temp_v0;
            if ((temp_v0 << 0x10) <= 0) {
                u16 state_plus_one = M2C_FIELD(arg0, u16 *, 0) + 1;
                ASM_TAILSLOT_PIN(state_plus_one);
                func_80024770();
                return;
            }
            goto block_41;

case_1:
            temp_v1_4 = (u16) M2C_FIELD(arg0, s16 *, 0xC) - M2C_FIELD(arg0, u16 *, 0xE);
            M2C_FIELD(arg0, s16 *, 0xC) = temp_v1_4;
            if (temp_v1_4 < 0) {
                M2C_FIELD(arg0, s16 *, 0xC) = (s16) (temp_v1_4 + 0x1000);
            }
            if ((s16) M2C_FIELD(arg0, u16 *, 0xE) < 0x7F8) {
                M2C_FIELD(arg0, u16 *, 0xE) = (u16) (M2C_FIELD(arg0, u16 *, 0xE) + 8);
            }
            temp_v1_5 = M2C_FIELD(arg0, s16 *, 0xA);
            if (temp_v1_5 >= 0x41) {
                if (temp_v1_5 >= 0x65) {
                    s32 tail_arg = 3;
                    ASM_TAILSLOT_PIN(tail_arg);
                    func_80024710(tail_arg);
                    return;
                }
                var_a0 = 2;
                if (temp_v1_5 < 0x47) {
                    var_a0 = 1;
                    if (temp_v1_5 >= 0x33) {
                        var_a0 = 2;
                    }
                }
                M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) - var_a0);
                effect_x = ((volatile DungeonEffect *)effect)->x1C;
                effect_c = ((volatile DungeonEffect *)effect)->c;
                effect_x -= 0x46;
                ((volatile DungeonEffect *)effect)->x1C = effect_x;
                effect_y = ((volatile DungeonEffect *)effect)->y1E;
                effect_c += 4;
                ((volatile DungeonEffect *)effect)->c = effect_c;
                effect_e = ((volatile DungeonEffect *)effect)->e;
                effect_y -= 0x46;
                ((volatile DungeonEffect *)effect)->y1E = effect_y;
                effect_d = ((volatile DungeonEffect *)effect)->d;
                effect_e += 4;
                ((volatile DungeonEffect *)effect)->e = effect_e;
                effect->d = effect_d + 4;
                func_80024874();
                return;
            }
            M2C_FIELD(arg0, u16 *, 2) = 0x28U;
            M2C_FIELD(arg0, s16 *, 0) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0) + 1);
            func_80024874();
            return;

case_2:
            temp_v1_2 = (u16) M2C_FIELD(arg0, s16 *, 0xC) - M2C_FIELD(arg0, u16 *, 0xE);
            M2C_FIELD(arg0, s16 *, 0xC) = temp_v1_2;
            if (temp_v1_2 < 0) {
                M2C_FIELD(arg0, s16 *, 0xC) = (s16) (temp_v1_2 + 0x1000);
            }
            if ((s16) M2C_FIELD(arg0, u16 *, 0xE) < 0x100) {
                M2C_FIELD(arg0, u16 *, 0xE) = (u16) (M2C_FIELD(arg0, u16 *, 0xE) + 8);
            }
            temp_v1_5 = M2C_FIELD(arg0, s16 *, 0xA);
            if (temp_v1_5 >= 0x1B) {
                M2C_FIELD(arg0, s16 *, 0xA) = (s16) (temp_v1_5 - 1);
            }
            temp_v1_3 = effect->c;
            if (temp_v1_3 >= 2U) {
                effect->c = (u8) (temp_v1_3 - 2);
                effect->d -= 2;
                effect->e -= 2;
            }
            if (effect->c == 0) {
                M2C_FIELD(arg0, u16 *, 2) = 0U;
                M2C_FIELD(arg0, s16 *, 0) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0) + 1);
            }
            effect->x1C -= 0x14;
            effect->y1E += 0xC8;
            func_80024874();
            return;

case_3:
            temp_v0_2 = M2C_FIELD(arg0, u16 *, 2) - 1;
            M2C_FIELD(arg0, u16 *, 2) = temp_v0_2;
            if ((temp_v0_2 << 0x10) <= 0) {
                M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
                D_800814A0[0] |= 0x8000;
            }
block_41:
            if (effect->flags14 & 0x8000) {
                M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
                D_800814A0[0] |= 0x8000;
            }
            return;

}
