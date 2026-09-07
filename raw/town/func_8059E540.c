/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef u32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
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
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

M2C_UNK func_800168E0();
s32 func_80018964();
extern u8 D_80010000[];
extern M2C_UNK D_80018EE4;
extern M2C_UNK D_80019148[3];
extern M2C_UNK D_8001D07C;

void func_8059E540(void) {
    M2C_UNK *temp_v1;
    M2C_UNK *new_value;
    void *state;

    if (func_80018964(0x11FC) == 0) {
        u8 *page = (u8 *)0x80010000;
        ASM_KEEP(page);
        M2C_FIELD(M2C_FIELD(M2C_FIELD(page, void **, 0x6000), void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x27C)(0);
        M2C_FIELD(M2C_FIELD(M2C_FIELD(page, void **, 0x6000), void **, 0x20), M2C_UNK (**)(M2C_UNK, M2C_UNK), 0x2F4)(-1, -5);
    }
    func_800168E0();
    ASM_CLOBBER("$2");
    {
        u8 *page = (u8 *)0x80010000;
        ASM_KEEP(page);
        state = M2C_FIELD(page, void **, 0x6000);
    }
    new_value = (M2C_UNK *)&D_80010000[0xD07C];
    M2C_FIELD(M2C_FIELD(state, void **, 0x1C), M2C_UNK **, 0x40) = new_value;
    temp_v1 = *(M2C_UNK **)((s8 *)M2C_FIELD(state, s8 **, 0x40) + (M2C_FIELD(state, s32 *, 8) * 8));
    if (temp_v1 != NULL) {
        M2C_FIELD(M2C_FIELD(state, void **, 0x1C), M2C_UNK **, 0x40) = temp_v1;
        *(M2C_UNK **)((s8 *)M2C_FIELD(state, s8 **, 0x40) + (M2C_FIELD(state, s32 *, 8) * 8)) = 0;
    }
    *(M2C_UNK **)&D_80019148[0] = &D_80018EE4;
}
