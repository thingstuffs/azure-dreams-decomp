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
    u8 pad[0xC];
    u32 word0;
    u32 word1;
} CopySource __attribute__((packed));

typedef struct {
    u8 pad[0x24];
    u32 word0;
    u32 word1;
} CopyDestination __attribute__((packed));


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
extern s16 D_80083780[];
extern s32 D_800814A0[3];
extern s32 D_80082E80[];
extern u8 D_80083498[];
s32 func_8003DE58();       /* extern */
void *func_8003FD64();                 /* extern */
s32 func_800644B8(s32, s16 *); /* extern */
s16 func_80066460(); /* extern */
s32 rand();                                /* extern */
void func_800478B8(M2C_UNK);                         /* extern */
extern M2C_UNK D_80024E4C;

void func_800244BC(void *arg0, void *arg1, M2C_UNK arg2) {
    s16 result[3];
    s16 temp_v1_2;
    s32 var_s3;
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(arg0, u16 *, 0x48) = (u16) (M2C_FIELD(arg0, u16 *, 0x48) - 1);
    M2C_FIELD(temp_v1, u16 *, 0x52) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x52) | 0x8000);
    temp_v1_2 = M2C_FIELD(arg0, s16 *, 0x4C);
    if (temp_v1_2 == 1) {
        goto phase_e;
    }
    if (temp_v1_2 < 2) {
        if (temp_v1_2 == 0) {
            goto state_update;
        }
        return;
    }
    if (temp_v1_2 == 2) {
        goto phase_f;
    }
    return;

state_update:
    M2C_FIELD(arg0, u16 *, 0x48) = 0xAU;
    M2C_FIELD(arg0, s16 *, 0x4C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x4C) + 1);

phase_e:
    if (func_8003DE58(D_80082E80[2], D_80082E80, result, 0) != 0) {
        func_800478B8(arg2);
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + (((result[0] + D_80083780[1]) - M2C_FIELD(arg1, s16 *, 2)) << 0xE));
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + (((result[1] + D_80083780[3]) - M2C_FIELD(arg1, s16 *, 6)) << 0xE));
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + (((result[2] + D_80083780[5]) - M2C_FIELD(arg1, s16 *, 0xA)) << 0xE));
        var_s3 = 0;
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) - (func_800644B8(((s16) M2C_FIELD(arg0, u16 *, 0x48) << 0xB) / 10, D_80083780) << 9));
        do {
            temp_v0 = func_8003FD64(0x302, D_80083498);
            temp_s0 = temp_v0 + 0x20;
            if (temp_v0 != NULL) {
                M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024E4C;
                M2C_FIELD(temp_s0, s16 *, 0x3C) = 0;
                M2C_FIELD(temp_s0, s16 *, 0x3E) = (s16) ((rand() & 3) + 2);
                M2C_FIELD(temp_s0, s16 *, 0x32) = 0x1F;
                M2C_FIELD(temp_s0, s16 *, 0x30) = 0x1F;
                M2C_FIELD(temp_s0, s16 *, 0x40) = func_80066460(0, 1, 0x2C0, 0x100);
                M2C_FIELD(temp_s0, s32 *, 0x38) = 0x404040;
                memcpy((u8 *) temp_v0 + 0x24, (u8 *) arg0 + 0xC, 8);
                M2C_FIELD(temp_s0, u16 *, 0x24) = (u16) M2C_FIELD(arg1, s16 *, 2);
                M2C_FIELD(temp_s0, u16 *, 0x26) = (u16) M2C_FIELD(arg1, s16 *, 6);
                M2C_FIELD(temp_s0, u16 *, 0x28) = (u16) M2C_FIELD(arg1, s16 *, 0xA);
                M2C_FIELD(temp_v0, void **, 0x20) = (void *) M2C_FIELD(arg0, void **, 0);
            }
            var_s3 -= 1;
        } while (var_s3 >= 0);
    }
    if ((s16) M2C_FIELD(arg0, u16 *, 0x48) <= 0) {
        M2C_FIELD(arg0, u16 *, 0x48) = 8U;
        M2C_FIELD(arg0, s16 *, 0x4C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x4C) + 1);
        return;
    }

    return;

phase_f:
    if (func_8003DE58(D_80082E80[2], D_80082E80, result, 0) != 0) {
        func_800478B8(arg2);
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + (((result[0] + D_80083780[1]) - M2C_FIELD(arg1, s16 *, 2)) << 0xF));
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + (((result[1] + D_80083780[3]) - M2C_FIELD(arg1, s16 *, 6)) << 0xF));
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + (((result[2] + D_80083780[5]) - M2C_FIELD(arg1, s16 *, 0xA)) << 0xF));
    }
    if ((s16) M2C_FIELD(arg0, u16 *, 0x48) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
