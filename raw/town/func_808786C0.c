#include "common.h"

extern s32 *D_807030A4[];

void func_807026C0(s32 arg0) {
    register s32 input ASM_REG("$5");
    s32 *ptr;
    s32 word;
    s32 value;
    unsigned long offset;

    input = arg0;
    if (input != 1) {
        word = input;
        if (input < 0) {
            word = input + 31;
        }
        value = word >> 5;
        offset = value << 2;
        value <<= 5;
        value = input - value;
        ASM_KEEP(input);
        value = 1 << value;
        offset += (unsigned long)D_807030A4[0];
        ptr = (s32 *)offset;
        value = ~value;
        value &= *ptr;
        *ptr = value;
    }
}
