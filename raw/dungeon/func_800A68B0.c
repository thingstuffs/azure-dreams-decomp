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
extern s32 D_80083460[3];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
s32 func_8009B164();             /* extern */
s32 func_8009B88C();      /* extern */
void *func_8009C93C(); /* extern */
M2C_UNK func_8009CE1C(); /* extern */
u8 func_8009FB34();                           /* extern */
M2C_UNK func_800A19E4(); /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800AA5E4(); /* extern */
s16 func_800BCB04();                   /* extern */

s32 func_800AC010(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 sp20;
    u16 sp22;
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    M2C_UNK move_flags1;
    M2C_UNK move_flags2;
    u8 move_x1;
    u8 move_y1;
    u8 move_x2;
    u8 move_y2;
    s32 *counter1;
    s32 *counter2;
    s16 temp_a0;
    s32 temp_v0_5;
    s32 temp_v1;
    s16 temp_v0;
    s16 temp_v0_4;
    u16 temp_v0_3;
    void *temp_v0_2;

    temp_a0 = M2C_FIELD(arg0, s16 *, 0x96);
    if (temp_a0 != 0) {
        temp_v0_5 = M2C_FIELD(arg2, u8 *, 0x24);
        temp_v1 = M2C_FIELD(arg1, s16 *, 2);
        temp_v0_5 <<= 6;
        temp_v1 -= 0x20;
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) ((temp_v0_5 - temp_v1) << 0x10) / temp_a0);
        temp_v1 = M2C_FIELD(arg1, s16 *, 6) - 0x20;
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - temp_v1) << 0x10) / (s16) M2C_FIELD(arg0, s16 *, 0x96));
    }
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        temp_v0_2 = func_8009C93C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x6A), 0, 0);
        if (temp_v0_2 != NULL) {
            func_8009CE1C(arg3, 4, 1, 8, (s32) (s16) ((u16) M2C_FIELD(arg3, s16 *, 0x6A) + 0x800), 0, 1);
            func_8009CE1C(temp_v0_2, 8, 1, 8, (s32) M2C_FIELD(arg3, s16 *, 0x6A), 0, 1);
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000000);
            M2C_FIELD(arg0, u8 *, 0x9C) = (u8) M2C_FIELD(arg2, u8 *, 0x26);
            M2C_FIELD(arg2, u8 *, 0x26) = func_8009FB34(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
            if ((func_8009B88C(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), &sp20, &sp22) << 0x10) != 0) {
                goto object_move_ok;
            }
common_fail:
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            func_800AA5E4(arg0, arg1, arg2, arg3);
            return 0;
object_move_ok:
            M2C_FIELD(arg2, u8 *, 0x24) = sp20;
            M2C_FIELD(arg2, u8 *, 0x25) = sp22;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            move_flags1 = M2C_FIELD(arg3, s32 *, 0x1C);
            move_x1 = M2C_FIELD(arg2, u8 *, 0x24);
            move_y1 = M2C_FIELD(arg2, u8 *, 0x25);
            var_a2 = 0x3000;
            if (move_flags1 & 0x2000) {
                var_a2 = 0x300;
            }
            func_8009A21C(move_x1, move_y1, var_a2);
            counter1 = D_80083460;
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xFFDFFFFF);
            M2C_FIELD(counter1, u16 *, 0xA) = (u16) (M2C_FIELD(counter1, u16 *, 0xA) - 1);
            M2C_FIELD(arg0, s16 *, 0x96) = 0;
            M2C_FIELD(arg3, s8 *, 0x71) = 0;
            return 1;
        }
        if ((func_8009B164(M2C_FIELD(arg3, s16 *, 0x6A), arg1, arg2) << 0x10) != 0) {
            temp_v0_3 = M2C_FIELD(arg3, u16 *, 0x8A) - 1;
            M2C_FIELD(arg3, u16 *, 0x8A) = temp_v0_3;
            if ((temp_v0_3 << 0x10) > 0) {
                M2C_FIELD(arg2, u8 *, 0x24) = (u8) (M2C_FIELD(arg2, u8 *, 0x24) + *(((u16) M2C_FIELD(arg3, s16 *, 0x6A) >> 9 & 7) + D_8006CCD8));
                M2C_FIELD(arg2, u8 *, 0x25) = (u8) (M2C_FIELD(arg2, u8 *, 0x25) + *(((u16) M2C_FIELD(arg3, s16 *, 0x6A) >> 9 & 7) + D_8006CCE8));
                M2C_FIELD(arg0, s16 *, 0x96) = 2;
                goto movement_return;
            }
        }
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
        M2C_FIELD(arg0, u8 *, 0x9C) = (u8) M2C_FIELD(arg2, u8 *, 0x26);
        M2C_FIELD(arg2, u8 *, 0x26) = func_8009FB34(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
        temp_v0_4 = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x20));
        if (temp_v0_4 < 0x200) {
            M2C_FIELD(arg0, s16 *, 0x92) = 0;
            M2C_FIELD(arg3, s16 *, 0x88) = temp_v0_4;
        }
        counter2 = D_80083460;
        M2C_FIELD(counter2, u16 *, 0xA) = (u16) (M2C_FIELD(counter2, u16 *, 0xA) - 1);
        M2C_FIELD(arg0, s16 *, 0x96) = 0;
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) ((M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000000) & 0xFFDFFFFF);
        if ((func_8009B88C(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), &sp20, &sp22) << 0x10) != 0) {
            M2C_FIELD(arg2, u8 *, 0x24) = sp20;
            M2C_FIELD(arg2, u8 *, 0x25) = sp22;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            move_flags2 = M2C_FIELD(arg3, s32 *, 0x1C);
            move_x2 = M2C_FIELD(arg2, u8 *, 0x24);
            move_y2 = M2C_FIELD(arg2, u8 *, 0x25);
            var_a2_2 = 0x3000;
            if (move_flags2 & 0x2000) {
                var_a2_2 = 0x300;
            }
            func_8009A21C(move_x2, move_y2, var_a2_2);
            M2C_FIELD(arg3, s8 *, 0x71) = 0;
            return 1;
        }
        goto common_fail;
    }
movement_return:
    return 0;
}
