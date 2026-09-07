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
extern s32 D_800E296C[3];
extern void *D_8008ACDC[];
extern void *D_8008EAC8[];
struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern volatile s32 D_80082EB0[];
extern s16 D_800DCE66[5];
extern s32 D_800E4940[];
extern u8 D_8004F5F4[];
M2C_UNK func_8004DD2C();                     /* extern */
s32 func_8009074C();                /* extern */
M2C_UNK func_80091500();                   /* extern */
M2C_UNK func_80091628();                            /* extern */
M2C_UNK func_80091708(); /* extern */
M2C_UNK func_80091714(); /* extern */
M2C_UNK func_80091778();                            /* extern */
M2C_UNK func_80091860();                            /* extern */
M2C_UNK func_800918A0();                       /* extern */
M2C_UNK func_800918F8();                       /* extern */
M2C_UNK func_800918FC();                       /* extern */
s32 func_8009402C(); /* extern */
s32 func_80094208();                         /* extern */
M2C_UNK func_800997FC();                   /* extern */
M2C_UNK func_8009F644();   /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800B0F50();                      /* extern */
s32 func_800B9964();                          /* extern */
M2C_UNK func_800BA810();                 /* extern */
M2C_UNK func_800C77D0();   /* extern */
extern u8 D_80012D6D;
extern M2C_UNK D_8001EF2C;
extern M2C_UNK D_80023C58;
extern M2C_UNK D_80088904;
extern M2C_UNK D_80088934;
extern M2C_UNK D_80088970;
extern M2C_UNK D_800E0040;
extern M2C_UNK D_800E2004;

void func_80091430(void *arg0, M2C_UNK arg1, M2C_UNK arg2, void *arg3) {
    void *actor = arg3;
    S_8003E2D8 *dungeon_state = &D_80083160;
    s16 sp18;
    s16 sp1A;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v1_3;
    s32 temp_v1;
    void **var_a0;
    void *temp_a0;
    void *temp_a0_2;
    register void *temp_t0 ASM_REG("$8");
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 == 1) {
        goto block_16;
    }
    if (temp_v1 < 2) {
        if (temp_v1 != 0) {
            func_800918FC();
            return;
        }
    } else {
        register s32 dispatch_v0 ASM_REG("$2");

        ASM_USE(arg0);
        dispatch_v0 = 2;
        ASM_KEEP(dispatch_v0);
        if (temp_v1 == dispatch_v0) {
            goto block_case_2;
        }
        func_800918FC();
        return;
    }
    {
        temp_v0 = func_800B9964(arg0 + 0x104);
        M2C_FIELD(arg0, s32 *, 0xC8) = temp_v0;
        if (temp_v0 != 0) {
            func_8004DCE0(2);
            func_8004DCEC();
            if (M2C_FIELD(arg0, s16 *, 0x120) == 0) {
                if (D_80012D6D == 0) {
                    ASM_USE(arg0);
                    func_80091500(&D_80088904);
                    return;
                }
                ASM_USE(arg0);
                func_80091500(&D_80088934);
                return;
            }
            {
                register void *call_a0 ASM_REG("$4");

                call_a0 = &D_80088970;
                ASM_KEEP(call_a0);
                func_8004DD2C();
            }
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            goto block_16;
        }
    }
    return;

block_16:
        temp_a2 = func_8009074C(M2C_FIELD(arg0, s16 *, 0x9E), arg0 + 0xA2, M2C_FIELD(arg0, void **, 0x104) + 0x2A);
        temp_v0_2 = (s16) temp_a2;
        if (temp_v0_2 != 0xFFF) {
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x104), s16 *, 0x2A) = temp_a2;
            func_8009F644(actor, 0x70, (s32) M2C_FIELD(arg0, void **, 0x104) == M2C_FIELD(arg0, s32 *, 0xB0), (temp_a2 << 0x10 >> 0x19) & 7);
        }
        if (M2C_FIELD(arg0, s16 *, 0x120) == 0) {
            temp_t0 = M2C_FIELD(arg0, void **, 0x104);
            if (temp_t0 != NULL) {
                if (M2C_FIELD(dungeon_state, s32 *, 0x10) & 0x80) {
                    if ((func_80094208(0) == 0) && !(M2C_FIELD(actor, s32 *, 0x1C) & 0x100000)) {
                        M2C_FIELD(actor, s16 *, 0x8A) = (s16) ((s32) M2C_FIELD(arg0, void **, 0x104) != M2C_FIELD(arg0, s32 *, 0xAC));
                        D_80082EB0[0] = 0;
                        if ((func_8009402C(arg0, arg1, arg2, &sp18, &sp1A, D_80082EB0[0]) << 0x10) != 0) {
                            func_800997FC(&D_800E2004);
                            func_80091628(arg0);
                            return;
                        }
                        func_8004E130();
                        M2C_FIELD(arg0, s32 *, 0xC8) = 0;
                        func_8008DB0C(arg0, arg1, arg2, sp18, (s32) sp1A);
                        {
                            s32 tail_flags = D_800E296C[0];

                            M2C_FIELD(arg0, void **, 0x104) = NULL;
                            D_800E296C[0] = tail_flags & ~0x2000;
                        }
                        func_800918FC();
                    }
                } else {
                    if (M2C_FIELD(dungeon_state, s32 *, 0x10) & 0x10) {
                        register void *internal_a0 ASM_REG("$4");
                        register M2C_UNK internal_a1 ASM_REG("$5");
                        register M2C_UNK internal_a2 ASM_REG("$6");
                        register void *internal_a3 ASM_REG("$7");
                        register void *internal_v0 ASM_REG("$2");
                        register void *internal_v1 ASM_REG("$3");

                        func_800C77D0(temp_t0 - 0x20, M2C_FIELD(temp_t0, s32 *, -0x18), 8, *D_800DCE66);
                        internal_a0 = arg0;
                        internal_a1 = arg1;
                        internal_a2 = arg2;
                        internal_a3 = (void *) 0x80020000;
                        ASM_KEEP4(internal_a0, internal_a1, internal_a2, internal_a3);
                        internal_v0 = M2C_FIELD(arg0, void **, 0x104);
                        internal_v1 = M2C_FIELD(arg0, void **, 0xAC);
                        ASM_USE2(internal_v0, internal_v1);
                        internal_a3 = (u8 *) internal_a3 - 0x10D4;
                        ASM_TAILSLOT_PIN(internal_a3);
                        func_80091708();
                        return;
                    }
                    if (M2C_FIELD(dungeon_state, s32 *, 0x10) & 0x20) {
                        register void *internal_a0 ASM_REG("$4");
                        register M2C_UNK internal_a1 ASM_REG("$5");
                        register M2C_UNK internal_a2 ASM_REG("$6");
                        register void *internal_a3 ASM_REG("$7");
                        register s32 internal_v0 ASM_REG("$2");
                        register void *internal_v1 ASM_REG("$3");

                        internal_a0 = arg0;
                        internal_a1 = arg1;
                        internal_a2 = arg2;
                        internal_a3 = &D_80023C58;
                        ASM_KEEP4(internal_a0, internal_a1, internal_a2, internal_a3);
                        internal_v0 = (s32) temp_t0 != M2C_FIELD(arg0, s32 *, 0xAC);
                        internal_v1 = (void *) 0x800E0000;
                        ASM_USE(internal_v1);
                        ASM_TAILSLOT_PIN(internal_v0);
                        func_80091714();
                        return;
                    }
                    if (M2C_FIELD(dungeon_state, s32 *, 0x10) & 0x40) {
                        func_800C77D0(temp_t0 - 0x20, M2C_FIELD(temp_t0, s32 *, -0x18), 8, *D_800DCE66);
                        temp_v0_3 = (s32) M2C_FIELD(arg0, void **, 0x104) != M2C_FIELD(arg0, s32 *, 0xAC);
                        M2C_FIELD(actor, s16 *, 0x8A) = temp_v0_3;
                        *D_800E4940 = (s32) temp_v0_3;
                        func_8008CF6C(arg0, arg1, arg2, D_8004F5F4);
                        M2C_FIELD(D_80082EB0, s32 *, 0) = 0;
                        M2C_FIELD(arg0, s32 *, 0xC8) = 0;
                        M2C_FIELD(arg0, void **, 0x104) = NULL;
                        func_8004E130();
                        func_800918FC();
                        return;
                    }
                    goto block_37;
                }
            } else {
block_37:
                temp_v1_2 = M2C_FIELD(arg0, void **, 0x104);
                if (temp_v1_2 == M2C_FIELD(arg0, s32 *, 0xAC)) {
                    register s32 internal_v0 ASM_REG("$2");

                    internal_v0 = M2C_FIELD(dungeon_state, s32 *, 8) & 2;
                    ASM_TAILSLOT_PIN(internal_v0);
                    func_80091778();
                    return;
                }
                if ((temp_v1_2 != M2C_FIELD(arg0, s32 *, 0xB0)) || !(M2C_FIELD(dungeon_state, s32 *, 8) & 1)) {
                    if (M2C_FIELD(dungeon_state, s32 *, 8) & 3) {
                        var_a0 = arg0 + 0xAC;
                        if (!(M2C_FIELD(dungeon_state, s32 *, 8) & 2)) {
                            var_a0 = arg0 + 0xB0;
                        }
                        temp_a0 = *var_a0;
                        if ((temp_a0 != NULL) && (M2C_FIELD(arg0, void *volatile *, 0x104) != temp_a0)) {
                            temp_v1_3 = M2C_FIELD(temp_a0, s32 *, 0x1C);
                            if (temp_v1_3 & 0x20000) {
                                if (!(temp_v1_3 & 0x80000)) {
                                    M2C_FIELD(arg0, void **, 0x104) = temp_a0;
                                    func_800B0F50(temp_a0);
                                    func_800918FC();
                                }
                            }
                        }
                    } else {
                        M2C_FIELD(arg0, void **, 0x104) = NULL;
                        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
                        func_800918FC();
                    }
                }
            }
        } else {
            temp_a0_2 = M2C_FIELD(arg0, void **, 0x104);
            func_800BA810(temp_a0_2, M2C_FIELD(temp_a0_2, u16 *, 0x46));
            if (M2C_FIELD(dungeon_state, s32 *, 0x10) & 0x60) {
                if (M2C_FIELD(dungeon_state, s32 *, 0x10) & 0x20) {
                    func_800A56E0(0x515);
                    temp_v1_2 = M2C_FIELD(arg0, void **, 0x104);
                    M2C_FIELD(temp_v1_2, u16 *, 0x46) &= 0x7FFF;
                    func_80091860();
                    return;
                }
                func_800A56E0(0x503);
                M2C_FIELD(arg0, void **, 0x104) = NULL;
                func_8004E130();
                D_800E296C[0] &= ~0x2000;
                if (M2C_FIELD(actor, s32 *, 0x1C) & 0x100000) {
                    register void *callback ASM_REG("$2");

                    callback = D_8008EAC8;
                    ASM_TAILSLOT_PIN(callback);
                    func_800918A0();
                    return;
                } else {
                    M2C_FIELD(arg0, void **, 0x8C) = D_8008ACDC;
                }
                func_800BA810(NULL, 0U);
                func_800918FC();
            }
        }
    return;

block_case_2:
    M2C_FIELD(arg0, s32 *, 0xC8) = 0;
    func_8004E130();
    D_800E296C[0] &= ~0x2000;
    if (M2C_FIELD(actor, s32 *, 0x1C) & 0x100000) {
        register void *callback ASM_REG("$2");

        callback = D_8008EAC8;
        ASM_TAILSLOT_PIN(callback);
        func_800918F8();
        return;
    } else {
        M2C_FIELD(arg0, void **, 0x8C) = D_8008ACDC;
    }
}
/* Warning: struct S_8003E2D8 is not defined (only forward-declared) */
