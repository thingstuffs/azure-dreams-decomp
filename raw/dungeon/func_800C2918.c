#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 D_800E3D7C[4];
s32 func_800C80E8(s32);                      /* extern */

s32 func_800C8078(void *arg0) {
    s32 var_a0;
    s32 var_v0;
    void *temp_v0;
    void *var_v1;

    if (M2C_FIELD(arg0, s32 *, 0x14) & 0x4000) {
        var_a0 = 1;
        var_v1 = (void *)(D_800E3D7C[0] + 4);
loop_2:
        temp_v0 = M2C_FIELD(var_v1, void **, 0xAC);
        if ((temp_v0 == NULL) || (var_v0 = 1, ((M2C_FIELD(temp_v0, s32 *, 0x54) & 0x4000) == 0))) {
            var_a0 -= 1;
            var_v1 -= 4;
            if (var_a0 < 0) {
                func_800C80E8(var_a0);
                return 0;
            }
            goto loop_2;
        }
        return var_v0;
    }
    {
        register s32 flags ASM_REG("$3");

        flags = M2C_FIELD(arg0, s32 *, 0x54) & 0x4000;
        ASM_KEEP(flags);
        var_v0 = 1;
        if (!flags) {
            ASM_CLOBBER("$3");
            var_v0 = 0;
            ASM_KEEP(var_v0);
        }
    }
    return var_v0;
}

/* MECHANISM: Discard the tail callee result and explicitly return zero to recover the frameless sibcall contract.
   A guarded $v1 flag pin plus edge-local ASM_KEEP/ASM_CLOBBER preserves the branch/li/move return CFG.
   2.7.2-cdk-G0 supplies retail's nop/delay-slot schedule; plain 2.7.2 plateaued at aligned 3. */
