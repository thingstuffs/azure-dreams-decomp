#include "modules/ovmovie_libpress.h"


/* Writes the command word and starts a transfer of the remaining input data. */
static void func_80177A9C(s32 *input_data, u32 word_count) {
    func_80177BC0();
    *D_80178384 |= 0x88;
    *D_8017834C = input_data + 1;
    *D_80178350 = ((word_count >> 5) << 0x10) | 0x20;
    *D_8017837C = *input_data;
    *D_80178354 = 0x01000201;
}
