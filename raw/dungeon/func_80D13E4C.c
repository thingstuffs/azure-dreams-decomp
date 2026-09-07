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
extern void *D_80170858[];
s32 func_8003F270(void);                 /* extern */
void func_80047784();         /* extern */
s32 func_80069EF8();                                /* extern */
void *func_800A05A4();      /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A56E0();                     /* extern */
s32 func_800A94A0();       /* extern */
void func_80171020(); /* extern */
extern M2C_UNK D_8006DE24;
extern void *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[16];
extern s32 D_8008346C;
extern M2C_UNK D_80171760;
extern u8 D_80174E88[9];

void func_8017364C(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    s16 temp_v0_3;
    s16 var_s0;
    s32 temp_v0;
    s32 temp_v1_2;
    register s32 var_s4 ASM_REG("$20");
    s8 var_v0_2;
    s8 var_v1;
    u16 temp_v0_2;
    u16 temp_v0_4;
    u8 *global_state;
    u8 *var_s1;
    s32 temp_v1;
    void *temp_v1_3;
    void *var_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    var_s4 = 0;
    if (temp_v1 == 1) {
        goto block_37;
    }
    if ((s32) temp_v1 >= 2) {
        goto block_4;
    }
    if (temp_v1 == 0) {
        goto block_7;
    }
    return;
block_4:
    if (temp_v1 == 2) {
        goto block_40;
    }
    if (temp_v1 == 3) {
        goto block_46;
    }
    return;
block_7:
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000)) {
        goto block_13;
    }
    temp_v0 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
    if ((u32) (temp_v0 - 1) >= 7U) {
        goto block_21;
    }
    (void)jt_keep; goto *D_80170858[(u32)((temp_v0) - 1)];
jt_c7:
    var_s4 = 1;
    goto block_18;
jt_c6:
    var_s4 = 1;
    goto block_19;
jt_c5:
    var_s4 = 1;
    goto block_20;
block_13:
    temp_v1_2 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
    if (temp_v1_2 == 2) {
        goto block_19;
    }
    if (temp_v1_2 >= 3) {
        goto block_17;
    }
    var_s1 = NULL;
    if (temp_v1_2 == 1) {
        goto block_20;
    }
    goto block_22;
block_17:
    var_s1 = NULL;
    if (temp_v1_2 != 3) {
        goto block_22;
    }
jt_c3:
block_18:
    var_s1 = arg3 + 0xE;
    goto block_22;
jt_c2:
block_19:
    var_s1 = arg3 + 0xB;
    goto block_22;
jt_c1:
block_20:
    var_s1 = arg3 + 8;
    goto block_22;
jt_c4:
block_21:
    var_s1 = NULL;
block_22:
    if (*var_s1 == 0) {
        goto block_36;
    }
    *(volatile u16 *)((u8 *)arg0 + 0x98) =
        M2C_FIELD(arg0, u16 *, 0x98) & 0xFF7F;
    ASM_MEM_BARRIER();
    {
        register s32 use_mode ASM_REG("$2") = var_s4;
        ASM_KEEP(use_mode);
        if (use_mode) {
            var_v0 = D_800814A8;
            M2C_FIELD(arg3, void **, 0x60) = var_v0;
            goto block_27;
        }
    }
block_25:
    {
        u8 *base;
        u8 kind;
        register u32 entry ASM_REG("$2");

        base = (u8 *)0x80070000;
        ASM_KEEP(base);
        kind = *var_s1;
        base -= 0x21DC;
        entry = kind * 20;
        entry += (u32)base;
        ASM_KEEP(entry);
        if (((u8 *)entry)[0x12] != 2) {
            goto block_28;
        }
    }
    var_v0 = M2C_FIELD(arg3, void **, 0x60);
    if (var_v0 == NULL) {
        goto block_34;
    }
block_27:
    {
        register u8 *other ASM_REG("$3") =
            M2C_FIELD((u8 *)var_v0 - 0x14, u8 **, 0);
        M2C_FIELD(arg3, u8 *, 0x72) = other[0x24];
        M2C_FIELD(arg3, u8 *, 0x73) = other[0x25];
    }
    goto block_33;
block_28:
    *(void * volatile *)((u8 *)arg3 + 0x60) =
        func_800A05A4(arg3, M2C_FIELD(arg2, u8 *, 0x24),
                      M2C_FIELD(arg2, u8 *, 0x25),
                      M2C_FIELD(arg3, s16 *, 0x2A), 0x10);
    ASM_KEEP(var_s4);
    {
        s32 x = M2C_FIELD(arg3, s8 *, 0x72);
        s32 y = M2C_FIELD(arg3, s8 *, 0x73);

        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        M2C_FIELD(arg3, u8 *, 0x72) = x;
        M2C_FIELD(arg3, u8 *, 0x73) = y;
    }
block_33:
block_34:
    if (func_800A94A0(arg3, var_s1, var_s4, arg0 + 0x98) == 0) {
        goto block_55;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0x13U;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    return;
block_36:
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    D_8008346C = 0;
    M2C_FIELD(D_800814A8, u16 *, 0xA6) = (u16) (M2C_FIELD(D_800814A8, u16 *, 0xA6) - 1);
    func_800A4ACC(arg3);
    M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80171760;
    M2C_FIELD(arg3, s8 *, 0x73) = 0;
    M2C_FIELD(arg3, s8 *, 0x72) = 0;
    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
    return;
block_37:
    if (func_8003F270() == 0) {
        goto block_39;
    }
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
    return;
block_39:
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    func_800A56E0(0x703);
block_40:
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        goto block_42;
    }
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_43;
    }
block_42:
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x80);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
    M2C_FIELD(arg0, u16 *, 0x96) = 0xFU;
block_43:
    if ((u32) (M2C_FIELD(arg0, u16 *, 0x96) - 9) >= 6U) {
        goto block_55;
    }
    var_s0 = 0;
loop_44:
    func_80171020(arg0 - 0x20, 0, 0xC0C0, (func_80069EF8() & 0xFF) | 0x80, 0, 0, 0);
    temp_v0_3 = var_s0 + 1;
    var_s0 = temp_v0_3;
    if (temp_v0_3 >= 0xA) {
        return;
    }
    goto loop_44;
block_46:
    global_state = D_80083460;
    if (M2C_FIELD(global_state, s32 *, 0xC) != 0) {
        goto block_48;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
block_48:
    temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_4;
    if ((temp_v0_4 << 0x10) > 0) {
        goto block_50;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
block_50:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_55;
    }
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == D_80174E88) {
        goto block_53;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = D_80174E88;
    func_80047784(arg2, D_80174E88[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
block_53:
    if (M2C_FIELD(global_state, s32 *, 0xC) != 0) {
        goto block_55;
    }
    M2C_FIELD(global_state, u16 *, 0xA) = (u16) (M2C_FIELD(global_state, u16 *, 0xA) - 1);
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80171760;
    func_800A4ACC(arg3);
    M2C_FIELD(arg3, s8 *, 0x73) = 0;
    M2C_FIELD(arg3, s8 *, 0x72) = 0;
    M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
    func_800A56E0(0xB4);
block_55:
    return;
}
