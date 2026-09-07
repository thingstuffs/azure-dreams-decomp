#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009D808(); /* extern */
M2C_UNK func_8009D940(); /* extern */
M2C_UNK func_8009DA50();    /* extern */
extern u16 D_80082D08[];
extern s32 D_801007F8[];
extern s32 D_80100900[];

typedef struct S_8009CEE8_0 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x8];
    s32 * unk_0C;
} S_8009CEE8_0;   /* temp_v1 in func_8009CEE8 */

void func_8009CEE8(void) {
    register u16 *call_base ASM_REG("$5");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 call_a2 ASM_REG("$6");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 call_a3 ASM_REG("$7");   /* MATCH pin: retail schedule: same instructions, different order without it */
    M2C_UNK sp10[2];
    M2C_UNK sp18[2];
    s32 *var_s0;
    s32 temp_a2;
    s32 temp_a3;
    void **var_s1;
    S_8009CEE8_0 *temp_v1;
    u16 *base;

    base = D_80082D08;
    func_8009D808(base, sp10, sp18);
    func_8009D940(sp10, sp18, D_80100900, D_801007F8);
    var_s1 = (void **)D_801007F8;
    if (D_801007F8[0] != 0) {
        do {
            temp_v1 = *var_s1;
            var_s0 = temp_v1->unk_0C;
            if (var_s0 != NULL) {
                temp_a2 = temp_v1->unk_00;
                temp_a3 = temp_v1->unk_02;
                while (*var_s0 != 0) {
                    call_base = base;
                    call_a2 = (s16)temp_a2;
                    call_a3 = (s16)temp_a3;
                    func_8009DA50(*var_s0++, call_base, call_a2, call_a3);
                }
            }
            var_s1 = (void **)((s8 *)((void **)((s8 *)var_s1 + 4)));
        } while (*var_s1 != NULL);
    }
}

/* MECHANISM: Two sibling 8-byte stack arrays force the retail 0x38 frame and save contract.
   Held D_80082D08 plus the split D_801007F8 call/traversal live ranges recover s4/s0/s1.
   Nested guards keep raw u16 coordinates until the sentinel branch, avoiding two load nops.
   Guarded a1/a2/a3 call-register lives pipeline the exact inner-loop argument/delay order. */
