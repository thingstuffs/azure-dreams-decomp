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

typedef struct S_801264AC_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_801264AC_0;   /* var_a0 in func_801264AC */

typedef struct S_801264AC_1 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    M2C_UNK * unk_0C;
} S_801264AC_1;   /* *var_v1 in func_801264AC */

typedef struct S_801264AC_2 {
    u8 pad_00[0x54];
    s32 unk_54;
    M2C_UNK ** unk_58;
} S_801264AC_2;   /* arg0 in func_801264AC */

typedef struct S_801264AC_3 {
    u8 pad_00[0x184];
    s32 unk_184;
} S_801264AC_3;   /* &D_80129728 in func_801264AC */

s32 func_801264AC(S_801264AC_2 *arg0) {
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
        ((S_801264AC_0 *)var_a0)->unk_04 = var_a1;
        var_a1 += 4;
        var_a0 += 4;
        var_a3 += 1;
        ((S_801264AC_1 *)(*var_v1))->unk_08 = var_a2;
        var_a2 += 3;
        ((S_801264AC_1 *)(*var_v1))->unk_0C = var_t0;
        var_t0 = *var_v1;
        var_v1 += 1;
    } while (var_a3 < 0x62);
    func_8004CC38(&D_80129728, 0x62, var_a2, var_a3);
    func_8004CCBC(&D_80129728, 0x62);
    arg0->unk_58 = &D_80129728;
    arg0->unk_54 = (s32)((S_801264AC_3 *)(&D_80129728))->unk_184;
    ret = 1;
    ASM_KEEP(ret);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    return ret;
}

/* MECHANISM: The natural loop shape yields the exact 32-byte frame and s1/s0/ra saves.
   A post-store ASM_SCHED_BARRIER makes the tail load/store reuse v0 instead of v1.
   An unpinned named return kept at last use places li v0,1 before the epilogue reloads. */
