/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80016000[3];

void func_8001A51C(u16 *arg0, void *arg1) {
    s32 var_a2;
    s32 var_t0;
    register s32 var_a0 ASM_REG("$4");
    s32 var_v0;
    register s32 var_v1 ASM_REG("$3");
    volatile u16 *var_a3;
    u16 *var_t1;
    register u16 *var_store ASM_REG("$2");
    s8 *var_t2;
    void *temp_v0;

    var_a3 = arg0;
    ASM_KEEP(var_a3);
    temp_v0 = M2C_FIELD(M2C_FIELD(D_80016000[0], void **, 0x24), void **, 0x70);
    var_t2 = (s8 *)temp_v0 + 0x1DC;
    var_t1 = M2C_FIELD(temp_v0, u16 **, 0x1DC);
    var_t0 = 0;
    if (M2C_FIELD(arg1, s16 *, 6) > 0) {
        do {
            var_a2 = 0;
            if (M2C_FIELD(arg1, s16 *, 4) > 0) {
                do {
                    var_a0 = M2C_FIELD(arg1, s16 *, 0);
                    var_a0 += var_a2;
                    ASM_KEEP(var_a0);
                    var_v0 = M2C_FIELD(arg1, s16 *, 2);
                    var_v0 += var_t0;
                    ASM_KEEP(var_v0);
                    var_v1 = M2C_FIELD(var_t2, s16 *, 0x14);
                    ASM_KEEP(var_v1);
                    var_v0 <<= var_v1;
                    var_a0 += var_v0;
                    if (*var_a3 != 0) {
                        var_store = (u16 *)((var_a0 << 1) + (s32)var_t1);
                        ASM_KEEP(var_store);
                        *var_store = *var_a3;
                    }
                    var_a2 += 1;
                    var_a3 += 1;
                } while (var_a2 < M2C_FIELD(arg1, s16 *, 4));
            }
            do {
                var_t0 += 1;
            } while (0);
        } while (var_t0 < M2C_FIELD(arg1, s16 *, 6));
    }
}
