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

extern void func_80044D24(void *, void *, s32);
extern void func_800453E0(void *, void *, void *, s16);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80066640(void *, s32);
extern void func_800666E0(void *);
extern void func_800666F4(void *);
extern void func_80067E2C(void *, void *);
extern void func_80067EF4(void *, s32, s32);
extern s32 func_8008C180(s16, s16);
extern s32 func_800C1D44(s32);
extern u8 D_80082E80[];
extern u8 D_800834B8[];
extern u8 D_80083780[];
extern s32 D_800D0460[3];
extern u8 D_800D04D0[];
extern u8 D_800D04D8[];
extern u8 D_800D04E0[];
extern u8 D_800D0504[];
extern s16 D_800D45AA[];
extern u8 D_801C9E40[];

extern void *D_80083160[3];

#define CUR_CTX (*state)
#define CUR_PAGE (D_80083160[0])

s32 func_800970FC(void) {
    s32 carrier;
    s32 remainder_source;
    s32 remainder_adjusted;
    s16 temp_s0_6;
    s16 temp_s1;
    s32 var_s1;
    s32 var_s4;
    s32 temp_fp_calc;
    s16 temp_fp;
    s32 temp_s7;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 lhsv;
    s32 coord_x;
    s32 coord_y;
    s32 color;
    s32 mask;
    s32 two;
    u16 temp_s7_2;
    u32 temp_fp_2;
    u16 temp_s2;
    u16 temp_s3;
    void *temp_s0;
    u8 *entry;
    u8 *coord;
    u8 *xy;
    u8 *late_entry;
    u8 *late_ctx;
    void **state;
    u32 *scr_13c;
    u16 *scr_h0;
    u16 *scr_h2;
    u16 rf4;
    u32 rf6;
    u32 rf6b;

#define temp_s0_2 temp_s0
#define temp_s0_3 temp_s0
#define temp_s0_4 temp_s0
#define temp_s0_5 temp_s0
#define temp_s0_7 temp_s0
#define temp_s0_8 temp_s0
#define temp_s0_9 temp_s0
#define temp_s0_10 temp_s0
#define temp_s3_2 temp_s3
#define var_v0_2 var_v0
#define var_v0_3 var_v0
#define var_v0_4 var_v0
#define var_v0_5 var_v0
#define var_v0_6 var_v0
#define var_v0_7 var_v0
#define var_v0_8 var_v0

    state = &D_80083160[0];
    entry = D_80082E80;
    temp_fp_calc = CUR_PAGE != (void *)D_801C9E40;
    temp_s2 = M2C_FIELD(entry, u16 *, 6);
    temp_fp = (u16) temp_fp_calc;
    if (!(M2C_FIELD(entry, u16 *, 0x14) & 0x80)) {
        coord = D_80083780;
#define D_80083780 (*coord)
        D_800D0460[0] = 0;
        coord_x = M2C_FIELD(coord, s16 *, 2);
        coord_y = M2C_FIELD(coord, s16 *, 6);
        temp_v0 = func_800C1D44(func_8008C180(coord_x, coord_y) & 0xFFFF);
        if (temp_v0 != 0) {
            lhsv = M2C_FIELD(coord, s16 *, 0xA);
            temp_v0_2 = (s32) (lhsv - D_800D45AA[temp_v0]) / 2;
            temp_s7 = temp_v0_2;
            temp_s7 = temp_s7 + 6;
            if ((u32) ((temp_v0_2 + 5) & 0xFFFF) < 0x3FU) {
                D_800D0460[0] = 1;
                scr_13c = (u32 *)0x1F80013C;
                *scr_13c = 0;
                func_800453E0(NULL, coord, D_800D04E0, (s16) (temp_s2 + M2C_FIELD(&D_800D0504, u16 *, 0)));
                scr_13c = (void *)0;
                scr_13c = (u32 *)0x1F80013C;
                *scr_13c = 0;
                func_800453E0(D_800834B8, coord, entry, (s16) (temp_s2 + M2C_FIELD(&D_800D0504, u16 *, 0)));
                temp_s0 = M2C_FIELD(CUR_PAGE, void **, 0x8D0);
                M2C_FIELD(CUR_PAGE, void **, 0x8D0) = (void *) (temp_s0 + 0xC);
                func_80067E2C(temp_s0, CUR_PAGE);
                func_8006658C(CUR_PAGE + 0x830, temp_s0);
                temp_s0_2 = M2C_FIELD(CUR_PAGE, void **, 0x8D0);
                M2C_FIELD(CUR_PAGE, void **, 0x8D0) = (void *) (temp_s0_2 + 0x28);
                color = 0x808080;
                M2C_FIELD(temp_s0_2, s32 *, 4) = color;
                func_800666F4(temp_s0_2);
                two = 2;
                color = two;
                xy = D_800D04D0;
                mask = ~0xFF;
                M2C_FIELD(temp_s0_2, s16 *, 0x16) = func_80066460(two, color, (s16) (M2C_FIELD(D_800D04D0, u16 *, 0) & mask), (s16) (M2C_FIELD(xy, u16 *, 2) & mask));
                func_80066640(temp_s0_2, 1);
                M2C_FIELD(temp_s0_2, s8 *, 0xC) = (s8) (M2C_FIELD(D_800D04D0, s16 *, 0) % 0x100);
                M2C_FIELD(temp_s0_2, s8 *, 0xD) = (s8) (M2C_FIELD(xy, s16 *, 2) % 0x100);
                M2C_FIELD(temp_s0_2, s8 *, 0x14) = (s8) ((M2C_FIELD(D_800D04D0, s16 *, 0) % 0x100) + M2C_FIELD(xy, u8 *, 4));
                M2C_FIELD(temp_s0_2, s8 *, 0x15) = (s8) (M2C_FIELD(xy, s16 *, 2) % 0x100);
                M2C_FIELD(temp_s0_2, s8 *, 0x1C) = (s8) (M2C_FIELD(D_800D04D0, s16 *, 0) % 0x100);
                M2C_FIELD(temp_s0_2, s8 *, 0x1D) = (s8) ((M2C_FIELD(xy, s16 *, 2) % 0x100) + M2C_FIELD(xy, u8 *, 6));
                M2C_FIELD(temp_s0_2, s8 *, 0x24) = (s8) ((M2C_FIELD(D_800D04D0, s16 *, 0) % 0x100) + M2C_FIELD(xy, u8 *, 4));
                remainder_source = M2C_FIELD(xy, s16 *, 2);
                if (remainder_source < 0) {
                    remainder_adjusted = remainder_source + 0xFF;
                    carrier = temp_fp_calc;
                } else {
                    remainder_adjusted = remainder_source;
                    carrier = temp_fp;
                }
                M2C_FIELD(temp_s0_2, s8 *, 0x25) =
                    (s8)(remainder_source - ((remainder_adjusted >> 8) * 0x100) +
                         M2C_FIELD(xy, u8 *, 6));
                {
                u8 *rect;
                u32 rect_y;
                rect = D_800D04D8;
                temp_s3 = M2C_FIELD(D_800D04D8, u16 *, 0);
                    var_s1 = M2C_FIELD(rect, s16 *, 2);
                    carrier = temp_fp;
                    if (carrier != 0) {
                        var_s1 -= 0xE0;
                    }
                M2C_FIELD(temp_s0_2, u16 *, 8) = temp_s3;
                M2C_FIELD(temp_s0_2, s16 *, 0xA) = var_s1;
                rf4 = M2C_FIELD(rect, u16 *, 4);
                M2C_FIELD(temp_s0_2, s16 *, 0x10) = (s16) (temp_s3 + rf4);
                M2C_FIELD(temp_s0_2, s16 *, 0x12) = var_s1;
                M2C_FIELD(temp_s0_2, u16 *, 0x18) = temp_s3;
                rf6 = M2C_FIELD(rect, u16 *, 6);
                M2C_FIELD(temp_s0_2, s16 *, 0x1A) = (s16) (var_s1 + rf6);
                rf4 = 0;
                rf4 = M2C_FIELD(rect, u16 *, 4);
                M2C_FIELD(temp_s0_2, s16 *, 0x20) = (s16) (temp_s3 + rf4);
                rf6 = 0;
                rf6 = M2C_FIELD(rect, u16 *, 6);
                M2C_FIELD(temp_s0_2, s16 *, 0x22) = (s16) (var_s1 + rf6);
                func_8006658C(CUR_CTX + 0x830, temp_s0_2);
                temp_s0_3 = M2C_FIELD(CUR_CTX, void **, 0x8D0);
                M2C_FIELD(CUR_CTX, void **, 0x8D0) = (void *) (temp_s0_3 + 0x18);
                M2C_FIELD(temp_s0_3, u8 *, 4) = 0x40;
                M2C_FIELD(temp_s0_3, u8 *, 5) = 0x40;
                M2C_FIELD(temp_s0_3, u8 *, 6) = 0xC0;
                func_800666E0(temp_s0_3);
                func_80066640(temp_s0_3, 0);
                M2C_FIELD(temp_s0_3, u16 *, 8) = temp_s3;
                rf6b = M2C_FIELD(rect, u16 *, 6);
                M2C_FIELD(temp_s0_3, s16 *, 0xA) = (s16) ((var_s1 + rf6b) - temp_s7);
                rf4 = M2C_FIELD(rect, u16 *, 4);
                M2C_FIELD(temp_s0_3, s16 *, 0xC) = (s16) (temp_s3 + rf4);
                rf6b = 0;
                rect_y = M2C_FIELD(rect, u16 *, 6);
                M2C_FIELD(temp_s0_3, u16 *, 0x10) = temp_s3;
                M2C_FIELD(temp_s0_3, s16 *, 0xE) = (s16) ((var_s1 + rect_y) - temp_s7);
                rect_y = 0;
                rf6b = M2C_FIELD(rect, u16 *, 6);
                M2C_FIELD(temp_s0_3, s16 *, 0x12) = (s16) (var_s1 + rf6b);
                rf4 = 0;
                rf4 = M2C_FIELD(rect, u16 *, 4);
                M2C_FIELD(temp_s0_3, s16 *, 0x14) = (s16) (temp_s3 + rf4);
                rf6b = 0;
                rf6b = M2C_FIELD(rect, u16 *, 6);
                M2C_FIELD(temp_s0_3, s16 *, 0x16) = (s16) (var_s1 + rf6b);
                func_8006658C(CUR_CTX + 0x830, temp_s0_3);
                temp_s0_4 = M2C_FIELD(CUR_CTX, void **, 0x8D0);
                M2C_FIELD(CUR_CTX, void **, 0x8D0) = (void *) (temp_s0_4 + 0x18);
                M2C_FIELD(temp_s0_4, s8 *, 6) = 0;
                M2C_FIELD(temp_s0_4, s8 *, 5) = 0;
                M2C_FIELD(temp_s0_4, s8 *, 4) = 0;
                func_800666E0(temp_s0_4);
                func_80066640(temp_s0_4, 0);
                M2C_FIELD(temp_s0_4, u16 *, 8) = temp_s3;
                M2C_FIELD(temp_s0_4, s16 *, 0xA) = var_s1;
                rf4 = M2C_FIELD(rect, u16 *, 4);
                M2C_FIELD(temp_s0_4, s16 *, 0xC) = (s16) (temp_s3 + rf4);
                M2C_FIELD(temp_s0_4, s16 *, 0xE) = var_s1;
                M2C_FIELD(temp_s0_4, u16 *, 0x10) = temp_s3;
                rf6 = M2C_FIELD(rect, u16 *, 6);
                M2C_FIELD(temp_s0_4, s16 *, 0x12) = (s16) (var_s1 + rf6);
                rf4 = 0;
                rf4 = M2C_FIELD(rect, u16 *, 4);
                M2C_FIELD(temp_s0_4, s16 *, 0x14) = (s16) (temp_s3 + rf4);
                rf6 = 0;
                rf6 = M2C_FIELD(rect, u16 *, 6);
                M2C_FIELD(temp_s0_4, s16 *, 0x16) = (s16) (var_s1 + rf6);
                func_8006658C(CUR_CTX + 0x830, temp_s0_4);
                temp_s0_5 = M2C_FIELD(CUR_CTX, void **, 0x8D0);
                M2C_FIELD(CUR_CTX, void **, 0x8D0) = (void *) (temp_s0_5 + 0xC);
                func_80067E2C(temp_s0_5, rect);
                func_8006658C(CUR_CTX + 0x830, temp_s0_5);
                }
                late_entry = D_80082E80;
                temp_s3_2 = M2C_FIELD(xy, u16 *, 0);
                var_s4 = M2C_FIELD(xy, s16 *, 2);
                temp_fp_2 = M2C_FIELD(late_entry, u16 *, 0x14);
                temp_s7_2 = M2C_FIELD(late_entry, u16 *, 0x10);
                {
                    if (carrier != 0) {
                        var_s4 -= 0xE0;
                    }
                }
                temp_s1 = temp_s3_2 + 0x20;
                temp_s0_6 = var_s4 + 0x39;
                scr_h0 = (u16 *)0x1F800000;
                scr_h2 = (u16 *)0x1F800002;
                *scr_h0 = (u16) temp_s1;
                *scr_h2 = (u16) temp_s0_6;
                M2C_FIELD(late_entry, u16 *, 0x10) = 0x40U;
                M2C_FIELD(late_entry, u16 *, 0x14) = (u16) (M2C_FIELD(late_entry, u16 *, 0x14) | 0xC);
                func_80044D24(0, late_entry, 0x1F0);
                scr_h0 = (void *)0; scr_h2 = (void *)0;
                scr_h0 = (u16 *)0x1F800000;
                scr_h2 = (u16 *)0x1F800002;
                *scr_h0 = (u16) temp_s1;
                *scr_h2 = (u16) temp_s0_6;
                M2C_FIELD(late_entry, u16 *, 0x10) = 0x20U;
                M2C_FIELD(late_entry, u16 *, 0x14) = (u16) (M2C_FIELD(late_entry, u16 *, 0x14) & 0xFFF3);
                func_80044D24(0, late_entry, 0x1F0);
                late_ctx = CUR_CTX;
                M2C_FIELD(late_entry, u16 *, 0x14) = temp_fp_2;
                M2C_FIELD(late_entry, u16 *, 0x10) = temp_s7_2;
                temp_s0_7 = M2C_FIELD(late_ctx, void **, 0x8D0);
                M2C_FIELD(late_ctx, void **, 0x8D0) = (void *) (temp_s0_7 + 0xC);
                func_80067EF4(temp_s0_7, 0, 0);
                func_8006658C(CUR_CTX + 0x830, temp_s0_7);
                temp_s0_8 = M2C_FIELD(CUR_CTX, void **, 0x8D0);
                M2C_FIELD(CUR_CTX, void **, 0x8D0) = (void *) (temp_s0_8 + 0x18);
                M2C_FIELD(temp_s0_8, u8 *, 6) = 0xFF;
                M2C_FIELD(temp_s0_8, u8 *, 5) = 0xFF;
                M2C_FIELD(temp_s0_8, u8 *, 4) = 0xFF;
                func_800666E0(temp_s0_8);
                func_80066640(temp_s0_8, 0);
                M2C_FIELD(temp_s0_8, u16 *, 8) = temp_s3_2;
                M2C_FIELD(temp_s0_8, s16 *, 0xA) = var_s4;
                M2C_FIELD(temp_s0_8, s16 *, 0xC) = (s16) (temp_s3_2 + M2C_FIELD(xy, u16 *, 4));
                M2C_FIELD(temp_s0_8, s16 *, 0xE) = var_s4;
                M2C_FIELD(temp_s0_8, u16 *, 0x10) = temp_s3_2;
                M2C_FIELD(temp_s0_8, s16 *, 0x12) = (s16) (var_s4 + M2C_FIELD(xy, u16 *, 6));
                M2C_FIELD(temp_s0_8, s16 *, 0x14) = (s16) (temp_s3_2 + M2C_FIELD(xy, u16 *, 4));
                M2C_FIELD(temp_s0_8, s16 *, 0x16) = (s16) (var_s4 + M2C_FIELD(xy, u16 *, 6));
                func_8006658C(CUR_CTX + 0x830, temp_s0_8);
                temp_s0_9 = M2C_FIELD(CUR_CTX, void **, 0x8D0);
                M2C_FIELD(CUR_CTX, void **, 0x8D0) = (void *) (temp_s0_9 + 0xC);
                func_80067EF4(temp_s0_9, 0, 1);
                func_8006658C(CUR_CTX + 0x830, temp_s0_9);
                temp_s0_10 = M2C_FIELD(CUR_CTX, void **, 0x8D0);
                M2C_FIELD(CUR_CTX, void **, 0x8D0) = (void *) (temp_s0_10 + 0xC);
                func_80067E2C(temp_s0_10, xy);
                func_8006658C(CUR_CTX + 0x830, temp_s0_10);
                return 0;
            }
        }
        scr_13c = (void *)0;
        scr_13c = (u32 *)0x1F80013C;
        *scr_13c = 0;
        func_800453E0(D_800834B8, coord, entry, (s16) (temp_s2 + M2C_FIELD(&D_800D0504, u16 *, 0)));
        /* Duplicate return node #26. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}
