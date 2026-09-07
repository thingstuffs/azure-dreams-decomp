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

typedef struct DdcbcEntry {
    u8 pad[7];
    u8 flags;
} DdcbcEntry;

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
extern void *D_800888B0[];
M2C_UNK func_8002534C(); /* extern */
void func_8003DB94();        /* extern */
s32 func_80042900();                 /* extern */
void func_80048A44(); /* extern */
void func_8004B568();                            /* extern */
s32 func_8008D024(); /* extern */
M2C_UNK func_8008D330(); /* extern */
s32 func_8008D388(); /* extern */
void func_8008D9F0(); /* extern */
M2C_UNK func_80091920(); /* extern */
s32 func_80094270(); /* extern */
M2C_UNK func_800956B8(); /* extern */
s32 func_80095854(); /* extern */
M2C_UNK func_80096088();              /* extern */
M2C_UNK func_80097F84(); /* extern */
M2C_UNK func_800982A8();              /* extern */
void func_80098614();              /* extern */
s32 func_80098920(); /* extern */
s16 func_80098C80();                          /* extern */
M2C_UNK func_80098CF8(); /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_80099734();                        /* extern */
M2C_UNK func_800997FC();                   /* extern */
s32 func_8009B88C(); /* extern */
M2C_UNK func_8009F644();   /* extern */
M2C_UNK func_800A5720();                         /* extern */
s32 func_800BA33C();                             /* extern */
M2C_UNK func_800BA810();            /* extern */
extern M2C_UNK D_8001EF2C;
extern M2C_UNK D_8004F5F4;
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern M2C_UNK D_80082EB0;
extern s32 D_80082EB8;
extern s16 D_80083228;
extern s8 D_800DCF4D;
extern u8 D_800DCFB0[];
extern u8 D_800DD0B8[];
extern u8 D_800DD274[];
extern DdcbcEntry D_800DDCBC[];
extern M2C_UNK D_800E0462;
extern M2C_UNK D_800E0472;
extern M2C_UNK D_800E0542;
extern M2C_UNK D_800E0571;
extern M2C_UNK D_800E069D;
extern M2C_UNK D_800E06BD;
extern M2C_UNK D_800E06C0;
extern M2C_UNK D_800E06E0;
extern M2C_UNK D_800E296C;
extern s32 D_800E3DF0[];
extern M2C_UNK D_800E4938;

void func_80090C10(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19, &&jt_c20, &&jt_c21 };
    s16 sp18;
    s16 sp1A;
    u8 *var_a1;
    s32 temp_s0;
    s16 temp_v0_4;
    s32 temp_flags;
    s32 temp_v0_3;
    s32 temp_v1_2;
    s32 var_s0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 temp_v1;
    u8 temp_v1_4;
    s32 temp_a0;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1_3;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 == 1) {
        goto block_14;
    }
    if ((s32) temp_v1 >= 2) {
        goto block_4;
    }
    if (temp_v1 == 0) {
        goto block_6;
    }
    return;
block_4:
    if (temp_v1 == 2) {
        goto block_16;
    }
    return;
block_6:
    D_800DCF4D = -1;
    func_8004B568();
    if (M2C_FIELD(&D_800E4938, s32 *, 0) == &D_8004F5F4) {
        goto block_13;
    }
    if ((func_80042900(arg3, 0xA) << 0x10) == 0) {
        goto block_9;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_800DD274;
    func_8003DB94(arg2, *(s32 *)(D_800DD274 + (((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 7) & 0x1C)), 0);
    goto block_13;
block_9:
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x100000)) {
        goto block_11;
    }
    var_a1 = D_800DD0B8;
    goto block_12;
block_11:
    var_a1 = D_800DCFB0;
block_12:
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
    func_80048A44(arg2, *(var_a1 + (((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7)), 0, 1);
block_13:
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
block_14:
    temp_v0 = M2C_FIELD(&D_800E4938, void *(**)(s32, s32), 0)(M2C_FIELD(&D_800E4938, s32 *, 4), M2C_FIELD(&D_800E4938, s32 *, 8));
    M2C_FIELD(arg0, void **, 0xC8) = temp_v0;
    if (temp_v0 == NULL) {
        goto block_68;
    }
    M2C_FIELD(arg0, s16 *, 0x96) = 0;
    M2C_FIELD(&D_80082EB0, void **, 0) = NULL;
    temp_v0_2 = &D_80082EB0;
    M2C_FIELD(temp_v0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_v0_2, s32 *, 8) = 0;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
block_16:
    if (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC8), u16 *, 0x1E) & 0x8000)) {
        goto block_18;
    }
    func_800BA810(0, 0);
    temp_flags = M2C_FIELD(&D_800E296C, s32 *, 0);
    M2C_FIELD(arg0, void **, 0xC8) = NULL;
    (*(s32 *)&D_800E296C) = temp_flags & ~0x2000;
block_18:
    if (M2C_FIELD(arg0, void **, 0xC8) != NULL) {
        goto block_68;
    }
    if ((u32) (D_80082EB8 - 1) >= 0x15U) {
        goto block_64;
    }
    (void)jt_keep; goto *D_800888B0[(u32)((D_80082EB8) - 1)];
jt_c1:
    func_8009F644(arg3, 0x48, func_80098C80(M2C_FIELD(&D_80082EB0, void **, 0)), 0);
    if (M2C_FIELD((*(void **)&D_80082EB0), u8 *, 1) != 0x11) {
        goto block_23;
    }
    func_80098614(arg3, (*(void **)&D_80082EB0));
    goto block_64;
block_23:
    func_800982A8(arg3, (*(void **)&D_80082EB0));
    goto block_64;
jt_c2:
    if (M2C_FIELD(M2C_FIELD(&D_80082EB0, void **, 0), u8 *, 1) != 0x11) {
        goto block_26;
    }
    func_8009F644(arg3, 0x48, func_80098C80(M2C_FIELD(arg3, void **, 0x50)), 0);
    func_80098614(arg3, NULL);
    goto block_64;
block_26:
    func_8009F644(arg3, 0x48, func_80098C80(M2C_FIELD(arg3, void **, 0x4C)), 0);
    func_800982A8(arg3, NULL);
    goto block_64;
jt_c21:
    if (!(M2C_FIELD(M2C_FIELD(&D_80082EB0, void **, 0), u8 *, 3) & 0x20)) {
        goto block_29;
    }
    func_800997FC(&D_800E0542);
    goto block_64;
block_29:
    if (func_800BA33C(M2C_FIELD(arg0, s32 *, 0xAC)) != 0) {
        goto block_31;
    }
    if (func_800BA33C(M2C_FIELD(arg0, s32 *, 0xB0)) == 0) {
        goto block_32;
    }
block_31:
    func_80091920(arg0, arg1, arg2, arg3);
    return;
block_32:
    func_800997FC(&D_800E0571);
    goto block_64;
jt_c3:
jt_c4:
jt_c20:
    temp_v0_3 = func_80098920(arg3, M2C_FIELD(&D_80082EB0, void **, 0), 3, 0);
    if (temp_v0_3 < 0) {
        goto block_36;
    }
    temp_s0 = (s16) func_80098C80((*(void **)&D_80082EB0));
    func_8009F644(arg3, 0x48, temp_s0, func_80098C80(M2C_FIELD(&D_80082EB0, void **, 4)));
    if (temp_v0_3 > 0) {
        goto block_64;
    }
    if (temp_v0_3 >= 0) {
        goto block_68;
    }
block_36:
    if (M2C_FIELD((*(void **)&D_80082EB0), u8 *, 1) != 0x15) {
        goto block_68;
    }
    M2C_FIELD(arg0, u8 *, 0x9B) = 3U;
    return;
jt_c5:
    func_8009F644(arg3, 0x58, 0, func_80098C80(M2C_FIELD(&D_80082EB0, void **, 0)));
    func_80098CF8(arg0, arg1, arg2, (*(void **)&D_80082EB0));
    goto block_64;
jt_c8:
jt_c9:
    func_8009F644(arg3, 0x98, 0, func_80098C80(M2C_FIELD(&D_80082EB0, void **, 0)));
    if (!(M2C_FIELD((*(void **)&D_80082EB0), u8 *, 3) & 0x20)) {
        goto block_41;
    }
    func_800956B8(arg0, arg1, arg2, (*(void **)&D_80082EB0));
    goto block_64;
block_41:
    temp_v1_2 = ((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 9) & 7;
    if ((func_8009B88C(0, (s16) (M2C_FIELD(arg2, u8 *, 0x24) + D_8006CCD8[temp_v1_2]), (s16) (M2C_FIELD(arg2, u8 *, 0x25) + D_8006CCE8[temp_v1_2]), &sp18, &sp1A) << 0x10) != 0) {
        goto block_43;
    }
    var_s0 = func_800990FC();
    var_v0_2 = func_80099734(D_800E3DF0[M2C_FIELD((*(void **)&D_80082EB0), u8 *, 3) & 0x1F], func_80099194(&D_800E069D, var_s0));
    func_80099290(func_80099194(&D_800E06BD, var_v0_2));
    func_800A5720(var_s0);
    goto block_64;
block_43:
    if (func_80095854(arg0, arg1, arg2, (*(void **)&D_80082EB0)) != 0) {
        goto block_68;
    }
    var_s0 = func_800990FC();
    var_v0_2 = func_80099734(D_800E3DF0[M2C_FIELD((*(void **)&D_80082EB0), u8 *, 3) & 0x1F], func_80099194(&D_800E06C0, var_s0));
    func_80099290(func_80099194(&D_800E06E0, var_v0_2));
    func_800A5720(var_s0);
    goto block_64;
jt_c10:
    func_8002534C(arg0, arg1, arg2, arg3);
    M2C_FIELD(arg0, void **, 0xC8) = NULL;
    return;
jt_c14:
    func_8008D330(arg0, arg1, arg2, arg3);
    M2C_FIELD(arg0, void **, 0xC8) = NULL;
    goto block_64;
jt_c12:
    temp_a0 = (s32) M2C_FIELD((((s32) M2C_FIELD(&D_80082EB0, void **, 0) * 4) + arg0), void **, 0xAC);
    if (M2C_FIELD((void *)temp_a0, s32 *, 0x1C) & 0x80000) {
        goto block_50;
    }
    M2C_FIELD((void *)temp_a0, s32 *, 0x60) = 0;
block_50:
    if (M2C_FIELD(&D_800E4938, s32 *, 0) == &D_8001EF2C) {
        goto block_64;
    }
    temp_v1_3 = M2C_FIELD((((s32) (*(void **)&D_80082EB0) * 4) + arg0), void **, 0xAC);
    temp_a0 = M2C_FIELD(temp_v1_3, u16 *, 0x46) & 0x3FFF;
    if ((u32) (temp_a0 - 5) < 3U) {
        goto block_64;
    }
    if ((u32) (temp_a0 - 9) >= 2U) {
        goto block_56;
    }
    temp_v1_4 = D_800DDCBC[M2C_FIELD(temp_v1_3, u8 *, 0x13)].flags;
    if (temp_a0 != 9) {
        var_v0_3 = temp_v1_4 & 2;
    } else {
        var_v0_3 = temp_v1_4 & 1;
    }
block_55:
    if (var_v0_3 != 0) {
        goto block_64;
    }
block_56:
    if (func_8008D024(arg0, arg1, arg2, (s16) M2C_FIELD(&D_80082EB0, void **, 0), 1) != 0) {
        goto block_68;
    }
    D_80082EB8 = 0;
    goto block_66;
jt_c16:
    M2C_FIELD(arg0, void **, 0xBC) = (void *) M2C_FIELD(&D_80082EB0, void **, 0);
    if (func_8008D388(arg0, arg1, arg2, arg3) != 0) {
        goto block_68;
    }
    D_80082EB8 = 0;
    goto block_66;
jt_c6:
jt_c7:
    {
        u8 *case_base = (u8 *)&D_80082EB0;
        temp_v0_4 = M2C_FIELD(case_base, u16 *, 8) - 6;
        M2C_FIELD(arg3, s16 *, 0x8A) = temp_v0_4;
        if (func_80094270(arg0, arg1, arg2, M2C_FIELD(case_base, void **, 0), (s32) temp_v0_4) == 0) {
            goto block_68;
        }
        D_80082EB8 = 0;
        goto block_66;
    }
jt_c17:
jt_c18:
    func_80097F84(M2C_FIELD(&D_80082EB0, void **, 0), &D_800E0462, &D_800E0472, 1);
    goto block_64;
jt_c19:
    func_8008D9F0(arg0, arg1, arg2, arg3);
    return;
jt_c11:
jt_c13:
jt_c15:
block_64:
    D_80082EB8 = 0;
block_66:
    if (M2C_FIELD(arg0, void **, 0xC8) != NULL) {
        goto block_68;
    }
    M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (M2C_FIELD(arg0, u16 *, 0xA2) | 0x40);
    func_80096088(arg0, arg3);
block_68:
    return;
}
