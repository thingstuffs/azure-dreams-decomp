#include "common.h"
#include "m2c_compat.h"

extern u8 D_80700000[];

void func_8087514C(void) {
    register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 var_a2;
    s32 var_t1;
    s16 *var_t0;

    var_a2 = zero | 1;
    ASM_UNDEF(zero);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    var_t1 = zero | 1;
    var_t0 = (s16 *)(D_80700000 + 0xBAE);
    do {
        register s32 temp_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 var_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        register s32 var_a3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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
        ASM_KEEP(temp_word_2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        var_v0 = ~var_v0;
        var_v0 = var_v0 & temp_word_2;
        *temp_a0 = var_v0;
        var_t0 += 1;
    } while (var_a2 < 4);
}
