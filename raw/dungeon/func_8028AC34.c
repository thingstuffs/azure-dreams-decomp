#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern u8 D_8008333C[32];
extern u8 D_800E9FFA[];

void func_8001DC34(void *arg0)
{
    void *argp;
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
    FIELD(argp, s16, 0xA) = 0;
    temp_v0 = FIELD(argp, u16, 2) - 1;
    var_a2 = temp_v0;
    ASM_KEEP_NV(var_a2);
    temp_v1 = temp_v0 + FIELD(argp, u16, 6) + 2;
    if ((temp_v0 << 16) < (temp_v1 << 16)) {
        var_t1 = (u32)D_800E9FFA;
        do {
            var_v0 = var_a2 << 16;
            var_v1 = (s16 *)(((((var_v0 >> 16) << var_t2[10]) +
                  FIELD(argp, u16, 0)) * 6) + var_t1);
            temp_v0_3 = FIELD(argp, u16, 4) + 2;
            var_a1 = temp_v0_3;
            if ((temp_v0_3 << 16) > 0) {
                var_a0 = (u8 *)var_v1 + 4;
                do {
                    temp_v0_4 = var_a1 - 1;
                    var_a1 = temp_v0_4;
                    *var_v1 = 0;
                    FIELD(var_a0, s16, -2) = 0;
                    FIELD(var_a0, s16, 0) = 0;
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
