#include "common.h"

typedef struct S_8001DC34_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8001DC34_0;   /* argp in func_8001DC34 */

typedef struct S_8001DC34_1_pre {
    s16 unk_00;
} S_8001DC34_1_pre;   /* the 0x2 bytes before var_a0 in func_8001DC34, addressed as var_a0[-1] */

typedef struct S_8001DC34_1 {
    s16 unk_00;
} S_8001DC34_1;   /* var_a0 in func_8001DC34 */



extern u8 D_8008333C[32];
extern u8 D_800E9FFA[];

void func_8001DC34(void *arg0)
{
    S_8001DC34_0 *argp;
    s16 var_a2;
    s16 var_a1;
    s16 *var_v1;
    u8 *var_a0;
    s32 var_v0;
    s16 *var_t2;
    u32 var_t1;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1;
    s16 temp_v0_4;
    s32 temp_v0_3;

    argp = arg0;
    var_t2 = (s16 *)D_8008333C;
    argp->unk_0A = 0;
    temp_v0 = argp->unk_02 - 1;
    var_a2 = temp_v0;
    ASM_KEEP_NV(var_a2);   /* MATCH pin: retail register colouring depends on it */
    temp_v1 = temp_v0 + argp->unk_06 + 2;
    if ((temp_v0 << 16) < (temp_v1 << 16)) {
        var_t1 = (u32)D_800E9FFA;
        do {
            var_v0 = var_a2 << 16;
            var_v1 = (s16 *)(((((var_v0 >> 16) << var_t2[10]) +
                  argp->unk_00) * 6) + var_t1);
            temp_v0_3 = argp->unk_04 + 2;
            var_a1 = temp_v0_3;
            if ((temp_v0_3 << 16) > 0) {
                var_a0 = (u8 *)var_v1 + 4;
                do {
                    temp_v0_4 = var_a1 - 1;
                    var_a1 = temp_v0_4;
                    *var_v1 = 0;
                    ((S_8001DC34_1_pre *)var_a0)[-1].unk_00 = 0;
                    ((S_8001DC34_1 *)var_a0)->unk_00 = 0;
                    var_a0 += 6;
                    var_v1 = (s16 *)((u8 *)var_v1 + 6);
                } while ((temp_v0_4 << 16) > 0);
                
                
            }
            
            temp_v0_2 = var_a2 + 1;
            var_a2 = temp_v0_2;
        } while (temp_v0_2 < temp_v1);
    }
    
    
}

/* MECHANISM: Frameless true-name leaf; runtime pins preserve a3/a2/a1 and v1/a0 roles.
   Narrow inner counters plus top-of-loop sign rematerialization recover both loop shapes.
   Integer-address D_800E9FFA with scaled-index-first addition closes the final addu. */
