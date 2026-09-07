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

typedef struct {
    u8 bytes[32];
} __attribute__((packed)) Packed32;

typedef struct {
    s64 out18;
    Packed32 copy;
} WorkMid;

typedef struct {
    s32 words[4];
} Copy16;

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

s32 func_8003DE58();     /* extern */
void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C(); /* extern */
M2C_UNK func_80047784();         /* extern */
s32 func_80065420(); /* extern */
s32 rand();                                /* extern */
M2C_UNK func_8009C12C(); /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A56E0();                     /* extern */
void func_800AD594(void *, s32);  /* extern */
void func_801731C8(void);  /* extern */
void func_80173618(void); /* extern */
extern M2C_UNK D_80045340;
extern s16 D_80083228;
extern s32 D_8008346C;
extern M2C_UNK D_80083498;
extern s8 D_800DCECC[];
extern Packed32 D_80170838;
extern M2C_UNK D_80170874;
extern M2C_UNK D_80171760;
extern u8 D_80174E90[];
extern u8 D_80174EB8[];
extern u8 D_80174EC0;

void func_80172FFC(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 sp10[3];
    u16 sp18[3];
    WorkMid mid;
    M2C_UNK sp48;
    M2C_UNK sp4C;
    void *sp50;
    u16 sp58;                                       /* compiler-managed */
    u8 *sp60;
    u16 *sp64;
    M2C_UNK *sp68;
    M2C_UNK temp_a0;
    M2C_UNK temp_a1;
    s16 temp_v0_2;
    s32 temp_v0_4;
    s32 random_value;
    register s32 base_value ASM_REG("$3");
    register s32 final_value ASM_REG("$6");
    u16 temp_v0;
    u16 temp_v0_5;
    u16 temp_v1_2;
    u8 table_byte;
    s32 temp_v1;
    void *temp_a1_2;
    void *temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_v0_3;
    Copy16 *var_a2;
    Copy16 *var_a3;
    Copy16 *copy_end;
    Packed32 *copy_source = &D_80170838;

    mid.copy = *copy_source;
    sp50 = arg0 - 0x20;
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 == 1) {
        goto state1;
    }
    if ((s32) temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto state0;
        }
        goto done;
    }
    if (temp_v1 == 2) {
        goto state2;
    }
    if (temp_v1 == 3) {
        goto state3;
    }
    goto done;

state0:
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        M2C_FIELD(arg0, u8 *, 0x9B) = 3U;
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
        func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
        goto done;
    }
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    goto advance;

state1:
    temp_v0_5 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_5;
    if (((s16) temp_v0_5 != 4) && !(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        goto done;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80174EB8;
    func_80047784(arg2, D_80174EB8[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);

advance:
    ASM_KEEP_NV(arg0);
    ASM_KEEP_NV(arg0);
    ASM_KEEP_NV(arg0);
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    goto done;

state2:
            temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
            M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
            if (((s16) temp_v0 == 0x11) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
                M2C_FIELD(arg0, u16 *, 0x96) = 0U;
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            }
            if (((s16) M2C_FIELD(arg0, u16 *, 0x96) == 0xB) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
                func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
            }
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80174E90;
                func_80047784(arg2, D_80174E90[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
            }
            temp_v1_2 = M2C_FIELD(arg0, u16 *, 0x96);
            if ((u32) (temp_v1_2 - 9) < 5U) {
                if ((s16) temp_v1_2 == 9) {
                    func_800A56E0(0x810);
                }
                sp60 = (u8 *)&mid.copy;
                sp64 = &sp18;
                sp58 = 0;
                sp68 = (M2C_UNK *)&mid.out18;
                do {
                    temp_v0_3 = func_8003FD64(0x112, &D_80083498);
                    temp_s2 = temp_v0_3 + 0x20;
                    if (temp_v0_3 != NULL) {
                        M2C_FIELD(temp_s2, s16 *, 0x96) = 0x19;
                        M2C_FIELD(temp_s2, s16 *, 0x9E) = 0x19;
                        M2C_FIELD(temp_v0_3, M2C_UNK **, 0x10) = &D_80170874;
                        M2C_FIELD(temp_s2, void **, 0xA8) = arg1;
                        var_a3 = (Copy16 *)arg2;
                        copy_end = (Copy16 *)arg2 + 3;
                        M2C_FIELD(temp_s2, u16 *, 0x94) = (u16) M2C_FIELD(arg3, s16 *, 0x2A);
                        temp_s1 = M2C_FIELD(temp_v0_3, void **, 0xC);
                        var_a2 = (Copy16 *)temp_s1;
                        do {
                            *var_a2 = *var_a3;
                            var_a3++;
                            var_a2++;
                        } while (var_a3 != copy_end);
                        M2C_FIELD(temp_s1, s16 *, 0x1E) = 0;
                        M2C_FIELD(temp_s1, s16 *, 0x1C) = 0;
                        M2C_FIELD(temp_s1, u8 *, 0xE) = 0x80;
                        M2C_FIELD(temp_s1, u8 *, 0xD) = 0x80;
                        M2C_FIELD(temp_s1, u8 *, 0xC) = 0x80;
                        func_8004491C(temp_v0_3, &D_80045340, var_a2, var_a3);
                        table_byte = D_80174EC0;
                        M2C_FIELD(temp_s1, u8 **, 0x2C) = &D_80174EC0;
                        func_80047784(temp_s1, table_byte, 0);
                        temp_s0 = M2C_FIELD(temp_v0_3, void **, 8);
                        M2C_FIELD(temp_s0, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
                        M2C_FIELD(temp_s0, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
                        M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
                        temp_a1_2 = M2C_FIELD(sp50, void **, 0xC);
                        if (func_8003DE58(M2C_FIELD(temp_a1_2, s32 *, 8), temp_a1_2, sp10, 0) != 0) {
                            M2C_FIELD(temp_s0, u16 *, 2) = (u16) (M2C_FIELD(temp_s0, u16 *, 2) + sp10[0]);
                            M2C_FIELD(temp_s0, u16 *, 6) = (u16) (M2C_FIELD(temp_s0, u16 *, 6) + sp10[1]);
                            M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) (M2C_FIELD(temp_s0, u16 *, 0xA) + sp10[2]);
                        }
                        M2C_FIELD(temp_s0, s32 *, 0x14) = (s32) (((0xD - (s16) M2C_FIELD(arg0, u16 *, 0x96)) << 0x11) + 0xFFE80000);
                        M2C_FIELD(temp_s2, s32 *, 0xB4) = 0xC000;
                        M2C_FIELD(temp_s0, s32 *, 0xC) = (s32) (M2C_FIELD(&sp60[((u16) M2C_FIELD(temp_s2, u16 *, 0x94) >> 7) & 0x1C], s16 *, 0) << 0x11);
                        M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) (M2C_FIELD(&sp60[((u16) M2C_FIELD(temp_s2, u16 *, 0x94) >> 7) & 0x1C], u16 *, 2) << 0x11);
                        random_value = rand();
                        base_value = M2C_FIELD(temp_s0, s32 *, 0xC) + 0xFFFE0000;
                        base_value += (random_value & 0x3FFF) << 4;
                        M2C_FIELD(temp_s0, s32 *, 0xC) = base_value;
                        random_value = rand();
                        base_value = M2C_FIELD(temp_s0, s32 *, 0x10) + 0xFFFE0000;
                        base_value += (random_value & 0x3FFF) << 4;
                        M2C_FIELD(temp_s0, s32 *, 0x10) = base_value;
                        random_value = rand();
                        base_value = 0xFFF80000;
                        final_value = M2C_FIELD(temp_s0, s32 *, 0x14);
                        final_value += base_value;
                        final_value += (random_value & 0x3FFF) << 6;
                        M2C_FIELD(temp_s0, s32 *, 0x14) = final_value;
                        sp18[0] = M2C_FIELD(temp_s0, u16 *, 2);
                        sp18[1] = M2C_FIELD(temp_s0, u16 *, 6);
                        sp18[2] = M2C_FIELD(temp_s0, u16 *, 0xA);
                        temp_v0_4 = func_80065420(sp64, sp68, &sp48, &sp4C);
                        sp18[0] = M2C_FIELD(arg1, u16 *, 2);
                        sp18[1] = M2C_FIELD(arg1, u16 *, 6);
                        sp18[2] = M2C_FIELD(arg1, u16 *, 0xA);
                        M2C_FIELD(temp_s1, s16 *, 6) = (s16) ((temp_v0_4 - func_80065420(sp64, sp68, &sp48, &sp4C)) - (D_800DCECC[((s32) (D_80083228 + (s16) M2C_FIELD(temp_s2, u16 *, 0x94) + 0x100) >> 9) & 7] * 2));
                    }
                    temp_v0_2 = sp58 + 1;
                    sp58 = temp_v0_2;
                } while (temp_v0_2 < 2);
            }
    goto done;

state3:
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
        func_800AD594(arg3, 0x100);
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80171760;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
    }

done:
    return;
}
