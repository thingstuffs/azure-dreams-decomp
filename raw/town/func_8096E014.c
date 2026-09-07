#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#ifndef NULL
#define NULL 0
#endif

M2C_UNK func_8004CC38();
M2C_UNK func_8004CCBC();
extern M2C_UNK *D_80129728;
extern M2C_UNK D_801298B8;
extern M2C_UNK D_80129ED8;
extern M2C_UNK D_8012A4F8;

s32 func_801264AC(void *arg0) {
    M2C_UNK **var_v1;
    M2C_UNK *var_a0;
    M2C_UNK *var_a1;
    M2C_UNK *var_a2;
    M2C_UNK *var_t0;
    s32 var_a3;
    s32 ret;

    var_t0 = NULL;
    var_a3 = 0;
    var_v1 = &D_80129728;
    var_a2 = &D_8012A4F8;
    var_a1 = &D_80129ED8;
    var_a0 = &D_801298B8;
    do {
        *var_v1 = var_a0;
        M2C_FIELD(var_a0, M2C_UNK **, 4) = var_a1;
        var_a1 += 4;
        var_a0 += 4;
        var_a3 += 1;
        M2C_FIELD(*var_v1, M2C_UNK **, 8) = var_a2;
        var_a2 += 3;
        M2C_FIELD(*var_v1, M2C_UNK **, 0xC) = var_t0;
        var_t0 = *var_v1;
        var_v1 += 1;
    } while (var_a3 < 0x62);
    func_8004CC38(&D_80129728, 0x62, var_a2, var_a3);
    func_8004CCBC(&D_80129728, 0x62);
    M2C_FIELD(arg0, M2C_UNK ***, 0x58) = &D_80129728;
    M2C_FIELD(arg0, s32 *, 0x54) = (s32)M2C_FIELD(&D_80129728, s32 *, 0x184);
    ASM_SCHED_BARRIER();
    ret = 1;
    ASM_KEEP(ret);
    return ret;
}

/* MECHANISM: The natural loop shape yields the exact 32-byte frame and s1/s0/ra saves.
   A post-store ASM_SCHED_BARRIER makes the tail load/store reuse v0 instead of v1.
   An unpinned named return kept at last use places li v0,1 before the epilogue reloads. */
