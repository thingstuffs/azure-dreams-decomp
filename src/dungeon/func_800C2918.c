#include "common.h"
#include "m2c_compat.h"

extern s32 D_800E3D7C[4];
s32 func_800C80E8(s32);                      /* extern */

typedef struct S_800C8078_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x3C];
    s32 unk_54;
} S_800C8078_0;   /* arg0 in func_800C8078 */

typedef struct S_800C8078_1 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800C8078_1;   /* var_v1 in func_800C8078 */

typedef struct S_800C8078_2 {
    u8 pad_00[0x54];
    s32 unk_54;
} S_800C8078_2;   /* temp_v0 in func_800C8078 */

s32 func_800C8078(S_800C8078_0 *arg0) {
    s32 var_a0;
    s32 var_v0;
    S_800C8078_2 *temp_v0;
    void *var_v1;

    if (arg0->unk_14 & 0x4000) {
        var_a0 = 1;
        var_v1 = (void *)(D_800E3D7C[0] + 4);
loop_2:
        temp_v0 = ((S_800C8078_1 *)var_v1)->unk_AC;
        if ((temp_v0 == NULL) || (var_v0 = 1, ((temp_v0->unk_54 & 0x4000) == 0))) {
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
        register s32 flags ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

        flags = arg0->unk_54 & 0x4000;
        var_v0 = 1;
        if (!flags) {
            ASM_CLOBBER("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            var_v0 = 0;
        }
    }
    return var_v0;
}

/* MECHANISM: Discard the tail callee result and explicitly return zero to recover the frameless sibcall contract.
   A guarded $v1 flag pin plus edge-local ASM_KEEP/ASM_CLOBBER preserves the branch/li/move return CFG.
   2.7.2-cdk-G0 supplies retail's nop/delay-slot schedule; plain 2.7.2 plateaued at aligned 3. */
