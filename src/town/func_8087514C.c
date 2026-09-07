#include "common.h"
#include "m2c_compat.h"

extern u8 D_80700000[];

void func_8087514C(void) {
    register s32 zero ASM_REG("$0");   /* MATCH pin: retail immediate-load split depends on it */
    s32 var_a2;
    s32 var_t1;
    s16 *var_t0;

    var_a2 = zero | 1;
    ASM_UNDEF(zero);   /* MATCH pin: load-bearing for the whole function shape */
    var_t1 = zero | 1;
    var_t0 = (s16 *)(D_80700000 + 0xBAE);
    do {
        register s32 temp_a1 ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
        register s32 var_v0 ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
        register s32 var_a3 ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
        s32 temp_a0_offset;
        s32 temp_word;
        s32 temp_word_2;
        s32 *temp_a0;

        temp_a1 = *var_t0;
        var_a3 = var_a2 << 1;
        var_v0 = temp_a1;
        if (temp_a1 < 0) {
            var_v0 = temp_a1 + 0x1F;
        }
        var_v0 >>= 5;
        temp_a0_offset = var_v0 << 2;
        var_v0 = temp_a1 - (var_v0 << 5);
        {
            s32 page;
            page = 0x80700000;
            page = *(s32 *)(page + 0x1968);
            var_v0 = var_t1 << var_v0;
            temp_a0_offset = temp_a0_offset + page;
            temp_a0 = (s32 *)temp_a0_offset;
        }
        temp_word = *temp_a0;
        var_v0 = ~var_v0;
        var_v0 = var_v0 & temp_word;
        *temp_a0 = var_v0;

        temp_a1 = *(s16 *)(D_80700000 + var_a3 + 0xBA4);
        var_v0 = temp_a1;
        if (temp_a1 < 0) {
            var_v0 = temp_a1 + 0x1F;
        }
        var_a2 += 1;
        var_v0 >>= 5;
        temp_a0_offset = var_v0 << 2;
        var_v0 = temp_a1 - (var_v0 << 5);
        {
            s32 page;
            page = 0x80700000;
            page = *(s32 *)(page + 0x1968);
            var_v0 = var_t1 << var_v0;
            temp_a0_offset = temp_a0_offset + page;
            temp_a0 = (s32 *)temp_a0_offset;
        }
        temp_word_2 = *temp_a0;
        ASM_KEEP(temp_word_2);   /* MATCH pin: load-bearing for the whole function shape */
        var_v0 = ~var_v0;
        var_v0 = var_v0 & temp_word_2;
        *temp_a0 = var_v0;
        var_t0 += 1;
    } while (var_a2 < 4);
}
