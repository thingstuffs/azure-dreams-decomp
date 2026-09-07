#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

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
extern u8 D_80045340[];
extern s32 D_800814A0[3];
extern s32 D_80083460[3];
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();                /* extern */
M2C_UNK func_80099FDC();                      /* extern */
s32 func_800A94A0(); /* extern */
extern M2C_UNK D_800CB600;
extern M2C_UNK D_800E03BC;
extern u8 D_800E3CC8;

void *func_800CB82C(void *arg0, void *arg1, void *arg2) {
    u16 temp_a0;
    s32 temp_global;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_a1;
    void *temp_v0;
    void *temp_v1;
    u16 *counter;
    u16 counter_value;

    temp_v0 = func_8003FC64(0x102);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800CB600;
        func_8004491C(temp_v0, D_80045340);
        temp_a1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a1, u16 *, 2) = (u16) M2C_FIELD(arg0, u16 *, 2);
        M2C_FIELD(temp_a1, u16 *, 6) = (u16) M2C_FIELD(arg0, u16 *, 6);
        M2C_FIELD(temp_a1, u16 *, 0xA) = (u16) M2C_FIELD(arg0, u16 *, 0xA);
        temp_a0_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0_2, M2C_UNK **, 8) = &D_800E03BC;
        M2C_FIELD(temp_a0_2, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0_2, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_a0_2, s8 *, 0x24) = (s8) ((u16) M2C_FIELD(temp_a1, u16 *, 2) >> 6);
        M2C_FIELD(temp_a0_2, s8 *, 0x25) = (s8) ((u16) M2C_FIELD(temp_a1, u16 *, 6) >> 6);
        temp_a0_3 = temp_v0 + 0x20;
        M2C_FIELD(temp_a0_3, s16 *, 0x96) = 0x10;
        M2C_FIELD(temp_a0_3, u8 *, 8) = (u8) D_800E3CC8;
        M2C_FIELD(temp_a0_3, u8 *, 9) = (u8) M2C_FIELD(&D_800E3CC8, u8 *, 1);
        M2C_FIELD(temp_a0_3, void **, 0x60) = arg2;
        temp_v1 = M2C_FIELD(arg2, void **, -0x14);
        M2C_FIELD(temp_a0_3, u8 *, 0x72) = (u8) M2C_FIELD(temp_v1, u8 *, 0x24);
        M2C_FIELD(temp_a0_3, u8 *, 0x73) = (u8) M2C_FIELD(temp_v1, u8 *, 0x25);
        M2C_FIELD(temp_a0_3, u16 *, 0x88) = (u16) M2C_FIELD(arg1, u16 *, 0x88);
        M2C_FIELD(temp_a0_3, u8 *, 0x13) = 0xFF;
        M2C_FIELD(temp_a0_3, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(temp_a0_3, s32 *, 0x1C) = (s32) M2C_FIELD(arg1, s32 *, 0x1C);
        M2C_FIELD(temp_a0_3, s16 *, 0x2A) = (s16) (M2C_FIELD(arg2, u16 *, 0x2A) - 0x800);
        M2C_FIELD(temp_a0_3, s32 *, 0x90) = (s32) M2C_FIELD(arg0, s32 *, 8);
        if (func_800A94A0(temp_a0_3, temp_v0 + 0x28, 0, temp_v0 + 0xB8) == 0) {
            temp_a0 = M2C_FIELD(temp_v0, u16 *, 0x1E) | 0x8000;
            temp_global = D_800814A0[0] | 0x8000;
            M2C_FIELD(temp_v0, u16 *, 0x1E) = temp_a0;
            D_800814A0[0] = temp_global;
            return NULL;
        }
        func_80099FDC(temp_v0);
        counter = (u16 *)D_80083460;
        counter_value = counter[5];
        counter_value = (u16) (counter_value + 1);
        counter[5] = counter_value;
    }
    return temp_v0;
}
