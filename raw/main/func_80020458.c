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

/* Callback function addresses outside this overlay's own window (0x8000D000-
   0x80022000); they belong to code loaded elsewhere and are only ever stored
   as raw pointers here, never called, so bind them as absolute symbols
   (established .set idiom) rather than declaring undefined func_ externs. */
__asm__(".set D_80409110, 0x80409110");
__asm__(".set D_80409128, 0x80409128");
extern M2C_UNK D_80409110;
extern M2C_UNK D_80409128;

void func_80020458(void *arg0) {
    register void *temp_a2 ASM_REG("$6");
    register void *temp_a2_2 ASM_REG("$6");

    temp_a2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), void **, 0);
    M2C_FIELD(M2C_FIELD(temp_a2, void **, 4), s16 *, 8) = 0x40;
    M2C_FIELD(M2C_FIELD(temp_a2, void **, 4), s16 *, 0xA) = 0x20;
    M2C_FIELD(temp_a2, M2C_UNK **, 0) = &D_80409110;
    temp_a2_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), void **, 4);
    M2C_FIELD(M2C_FIELD(temp_a2_2, void **, 4), s16 *, 8) = 0xC0;
    M2C_FIELD(M2C_FIELD(temp_a2_2, void **, 4), s16 *, 0xA) = 0x20;
    M2C_FIELD(temp_a2_2, M2C_UNK **, 0) = &D_80409128;
}
