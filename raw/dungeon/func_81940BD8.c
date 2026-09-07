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
typedef struct Copy12 {
    M2C_UNK word[3];
} __attribute__((packed)) Copy12;
typedef struct {
    u8 pad0[6];
    s16 field6;
    void *ptr8;
    u8 byteC;
    u8 byteD;
    u8 byteE;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 flags14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} Part;

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
void *func_8003FC64(s32);                       /* extern */
void func_8004491C(void *, void *);                /* extern */
extern M2C_UNK D_80024104;
extern u8 D_800256E0[12];

void func_800243D8(void *arg0) {
    void *temp_a0;
    Part *temp_a3;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1, s16 *, 0x2A) = 0xB;
        M2C_FIELD(temp_v1, void **, 0x60) = arg0;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024104;
        func_8004491C(temp_v0, D_80045340);
        temp_a3 = M2C_FIELD(temp_v0, Part **, 0xC);
        temp_a3->field10 = 0x20;
        temp_a3->field6 = 0;
        temp_a3->flags14 = (u16) (temp_a3->flags14 | 0xC);
        temp_v1_2 = M2C_FIELD(arg0, void **, -0x18);
        temp_a0 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a0, s32 *, 0) = (s32) M2C_FIELD(temp_v1_2, s32 *, 0);
        M2C_FIELD(temp_a0, s32 *, 4) = (s32) M2C_FIELD(temp_v1_2, s32 *, 4);
        M2C_FIELD(temp_a0, s32 *, 8) = (s32) M2C_FIELD(temp_v1_2, s32 *, 8);
        temp_a3 = M2C_FIELD(temp_v0, Part **, 0xC);
        temp_a3->field1E = 0;
        temp_a3->field1C = 0;
        temp_a3->byteE = 0;
        temp_a3->byteD = 0;
        temp_a3->byteC = 0;
        M2C_FIELD(temp_v0, Copy12 *, 0x92) = *(Copy12 *)D_800256E0;
        temp_a3->ptr8 = (void *) (temp_v0 + 0x92);
    }
}
