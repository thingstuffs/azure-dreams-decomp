#include "common.h"

extern s32 *D_807030A4[];

/* Tests an indexed flag, treating indices zero and one as constant results. */
s32 func_80702714(s32 flag_index)
{
    s32 unit_bit;
    register s32 value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 *flag_word;
    s32 adjusted_index;
    unsigned long word_address;

    unit_bit = 1;
    if (flag_index != 0) {
        if (flag_index != unit_bit) {
            adjusted_index = flag_index;
            if (flag_index < 0) {
                adjusted_index = flag_index + 31;
            }
            value = adjusted_index >> 5;
            word_address = value << 2;
            value <<= 5;
            word_address += (unsigned long)D_807030A4[0];
            value = flag_index - value;
            value = unit_bit << value;
            flag_word = (s32 *)word_address;
            value &= *flag_word;
        } else {
            register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
            zero = 0;
#endif
            value = zero + 1;
        }
    } else {
        register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        zero = 0;
#endif
        value = zero;
    }
    return value;
}

/* MECHANISM: Nested nonzero/default fallthrough gives the frameless retail CFG; loading
   the table base before remainder formation fills its delay slot with the subu.
   Tied v0 tail pins form both jumps, while block-local $zero carriers force literal
   addiu/move materialization without fencing a2 out of the first branch delay. */
