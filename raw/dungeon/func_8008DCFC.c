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
extern void *D_80088A58[];
s32 func_8003E4FC(); /* extern */
void func_800424E0();          /* extern */
void func_80042560();                      /* extern */
M2C_UNK func_80042640();                  /* extern */
void func_80043914();                      /* extern */
M2C_UNK func_80047FF4();                     /* extern */
s32 func_80048118();                   /* extern */
void func_80048A44(); /* extern */
M2C_UNK func_80093C70();      /* extern */
M2C_UNK func_80093D8C();      /* extern */
M2C_UNK func_80093E74(); /* extern */
s32 func_800990FC();                         /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_8009929C();                    /* extern */
s32 func_80099734();                     /* extern */
M2C_UNK func_80099F04();                         /* extern */
M2C_UNK func_80099F70();                         /* extern */
M2C_UNK func_8009A028();                      /* extern */
void *(*func_800A0B94())(M2C_UNK, s8, s8, s16); /* extern */
M2C_UNK func_800A152C();                 /* extern */
s32 func_800A1618();                     /* extern */
M2C_UNK func_800A18E8();                 /* extern */
s32 func_800A2BDC();                         /* extern */
M2C_UNK func_800A31D0();                      /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800A5720();                         /* extern */
extern M2C_UNK D_8003E140;
extern s32 D_80081488;
extern M2C_UNK D_8008149C;
extern M2C_UNK D_800814A0;
extern void *D_80082EB0[];
extern s16 D_80083228;
extern u16 D_80083460[];
extern M2C_UNK D_8008ACDC;
extern u8 D_800DD138[];
extern u8 D_800DD140[];
extern u8 D_800DD260;
extern M2C_UNK D_800DD262;
extern M2C_UNK D_800E05E1;
extern M2C_UNK D_800E05F0;
extern M2C_UNK D_800E06FA;
extern M2C_UNK D_800E0714;
extern s32 D_800E3D74[];
extern void *D_800E3DF0[];
extern s8 D_800E3E40;

typedef union ScratchS1 {
    s32 value;
    void **base;
} ScratchS1;

void func_8009345C(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *actor = arg0;
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8 };
    M2C_UNK *var_a0;
    M2C_UNK *var_a0_2;
    s32 temp_a1;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_object_flags;
    s32 cleanup_slot;
    s32 var_a1;
    u16 temp_v0;
    u16 temp_v0_7;
    u16 temp_flags;
    u16 temp_raw;
    s16 temp_idx;
    s32 temp_slot;
    u8 temp_v1;
    u8 var_v0;
    void *temp_v0_5;
    void *temp_case0_ptr;
    void *temp_case2_ptr;
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;
    ScratchS1 scratch_s1;

    temp_v1 = M2C_FIELD(actor, u8 *, 0x9B);
    if (temp_v1 >= 0xAU) {
        goto block_36;
    }
    (void)jt_keep; goto *D_80088A58[(u32)(temp_v1)];
jt_c0:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x6000)) {
        goto block_36;
    }
    M2C_FIELD(arg2, void **, 0x2C) = D_800DD138;
    func_80048A44(arg2, D_800DD138[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    func_80093C70(actor, arg1, arg2);
    func_80093D8C(actor, arg1, arg2);
    temp_flags = M2C_FIELD(arg2, u16 *, 0x14);
    D_800DD260 = 0;
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (temp_flags | 0x200);
    M2C_FIELD(actor, u16 *, 0x96) = 0x10U;
    temp_idx = M2C_FIELD(arg3, s16 *, 0x8A);
    temp_raw = M2C_FIELD(arg3, u16 *, 0x8A);
    temp_case0_ptr = (void *) M2C_FIELD(((temp_idx * 4) + actor), void **, 0xAC);
    M2C_FIELD(&D_800DD262, u16 *, 0) = temp_raw;
    M2C_FIELD(arg3, void **, 0x60) = temp_case0_ptr;
    goto block_33;
jt_c1:
    temp_v0 = M2C_FIELD(actor, u16 *, 0x96) - 1;
    M2C_FIELD(actor, u16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_36;
    }
    if (M2C_FIELD(arg3, void **, 0x60) == NULL) {
        goto block_7;
    }
    func_80093E74(actor, arg1, arg2, arg3);
    goto block_33;
block_7:
    var_v0 = M2C_FIELD(actor, u8 *, 0x9B) + 2;
    goto block_35;
jt_c2:
    if (!(M2C_FIELD(M2C_FIELD(arg3, void **, 0x60), s32 *, 0x1C) & 0x800000)) {
        goto block_36;
    }
    scratch_s1.value = func_800990FC();
    temp_a1 = func_8009929C(8, scratch_s1.value);
    if (M2C_FIELD(&D_800DD262, s16 *, 0) == 0) {
        goto block_11;
    }
    var_a0 = &D_800E05F0;
    goto block_12;
block_11:
    var_a0 = &D_800E05E1;
block_12:
    func_80099290(func_80099194(&D_800E06FA, func_80099734(M2C_FIELD(arg3, void **, 0x60), func_80099194(var_a0, temp_a1))));
    func_800A5720(scratch_s1.value);
    temp_case2_ptr = M2C_FIELD(arg3, void **, 0x60);
    D_800DD260 = 1;
    func_800A31D0(temp_case2_ptr);
    M2C_FIELD(((M2C_FIELD(&D_800DD262, s16 *, 0) * 4) + actor), s32 *, 0xAC) = 0;
    func_800A18E8(M2C_FIELD(M2C_FIELD(arg3, void **, 0x60), u8 *, 0x13), 3);
    func_8009A028(M2C_FIELD(arg3, void **, 0x60));
    temp_v1_2 = M2C_FIELD(arg3, void **, 0x60);
    M2C_FIELD(temp_v1_2, u16 *, -2) = (u16) (M2C_FIELD(temp_v1_2, u16 *, -2) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (M2C_FIELD(&D_800814A0, s32 *, 0) | 0x8000);
    if (D_80082EB0[0] != NULL) {
        goto block_33;
    }
    M2C_FIELD(actor, u16 *, 0x96) = 0U;
    var_v0 = M2C_FIELD(actor, u8 *, 0x9B) + 4;
    goto block_35;
jt_c3:
    scratch_s1.base = D_80082EB0;
    if ((func_800A2BDC(0) << 0x10) != 0) {
        goto block_36;
    }
    temp_v0_3 = func_800A1618(M2C_FIELD(*scratch_s1.base, u8 *, 0), 3);
    if (temp_v0_3 == 0) {
        goto block_33;
    }
    D_80081488 = func_80048118(M2C_FIELD(*scratch_s1.base, u8 *, 0), &D_8008149C);
    func_800A0B94(M2C_FIELD(*scratch_s1.base, u8 *, 0), temp_v0_3, 0);
    (*(s8 *)&D_800E3E40) = 0;
    func_8003E4FC(0xFF, &D_8003E140, &D_800E3E40);
    goto block_33;
jt_c4:
    if (M2C_FIELD(&D_800E3E40, u8 *, 0) == 0) {
        goto block_36;
    }
    if (D_80081488 == 0) {
        goto block_33;
    }
    func_80047FF4(M2C_FIELD(D_80082EB0[0], u8 *, 0), D_80081488);
    goto block_33;
jt_c5:
    scratch_s1.base = D_80082EB0;
    temp_v0_4 = func_800A1618(M2C_FIELD(*scratch_s1.base, u8 *, 0), 3);
    if (temp_v0_4 == 0) {
        goto block_28;
    }
    func_80043914(*scratch_s1.base);
    temp_v0_5 = func_800A0B94(M2C_FIELD(*scratch_s1.base, u8 *, 0), temp_v0_4, 1)(1, M2C_FIELD(arg3, s8 *, 0x72), M2C_FIELD(arg3, s8 *, 0x73), (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
    if (temp_v0_5 == NULL) {
        goto block_28;
    }
    M2C_FIELD(((M2C_FIELD(&D_800DD262, s16 *, 0) * 4) + actor), void **, 0xAC) = temp_v0_5;
    D_800E3DF0[M2C_FIELD(*scratch_s1.base, u8 *, 3) & 0x1F] = temp_v0_5;
    temp_v1_3 = M2C_FIELD(temp_v0_5, void **, -0x14);
    M2C_FIELD(temp_v1_3, s16 *, 0x1E) = 0x800;
    M2C_FIELD(temp_v1_3, s16 *, 0x1C) = 0x800;
    temp_v1_4 = M2C_FIELD(temp_v0_5, void **, -0x18);
    M2C_FIELD(temp_v1_4, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(temp_v1_4, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
    M2C_FIELD(temp_v1_4, s16 *, 0xA) = (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x10);
    func_80042640(temp_v0_5, M2C_FIELD(temp_v0_5, u8 *, 0x13));
    func_800424E0(temp_v0_5, M2C_FIELD(temp_v0_5, u8 *, 0x13), *scratch_s1.base);
    temp_object_flags = M2C_FIELD(temp_v0_5, s32 *, 0x1C);
    temp_slot = M2C_FIELD(&D_800DD262, s16 *, 0);
    M2C_FIELD(temp_v0_5, s32 *, 0x1C) = temp_object_flags | 0x02000000;
    M2C_FIELD(((temp_slot * 4) + actor), void **, 0xD0) = D_80082EB0[0];
    M2C_FIELD(D_80082EB0[0], u8 *, 3) = (u8) (M2C_FIELD(D_80082EB0[0], u8 *, 3) | 0x20);
    scratch_s1.value = func_800990FC(0x02000000);
    var_a1 = scratch_s1.value;
    if (D_800DD260 != 0) {
        goto block_24;
    }
    var_a1 = func_8009929C(8, var_a1);
block_24:
    if (M2C_FIELD(&D_800DD262, s16 *, 0) == 0) {
        goto block_26;
    }
    var_a0_2 = &D_800E05F0;
    goto block_27;
block_26:
    var_a0_2 = &D_800E05E1;
block_27:
    func_80099290(func_80099194(&D_800E0714, func_80099734(temp_v0_5, func_80099194(var_a0_2, var_a1))));
    func_800A5720(scratch_s1.value);
    cleanup_slot = M2C_FIELD(&D_800DD262, s16 *, 0);
    D_800E3D74[cleanup_slot] = 0;
    func_800A152C(M2C_FIELD(D_80082EB0[0], u8 *, 0), 3);
    func_80042560(temp_v0_5);
    func_800A56E0(0x704);
block_28:
    M2C_FIELD(actor, u16 *, 0x96) = 0x10U;
    goto block_34;
jt_c7:
    temp_v0_7 = M2C_FIELD(actor, u16 *, 0x96) - 1;
    M2C_FIELD(actor, u16 *, 0x96) = temp_v0_7;
    if ((temp_v0_7 << 0x10) > 0) {
        goto block_36;
    }
    M2C_FIELD(arg2, void **, 0x2C) = D_800DD140;
    func_80048A44(arg2, D_800DD140[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    goto block_33;
jt_c8:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x6000)) {
        goto block_36;
    }
    M2C_FIELD(actor, M2C_UNK **, 0x8C) = &D_8008ACDC;
    func_80099F70(M2C_FIELD(arg3, s32 *, 0x5C));
    func_80099F04(M2C_FIELD(arg3, s32 *, 0x5C));
    D_80083460[1] = (u16) (D_80083460[1] | 0x812);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFDFF);
jt_c6:
block_33:
block_34:
    var_v0 = M2C_FIELD(actor, u8 *, 0x9B) + 1;
block_35:
    M2C_FIELD(actor, u8 *, 0x9B) = var_v0;
block_36:
    return;
}
