#include "common.h"

extern u8 D_800E045F[];

void *func_800998C0(void *arg0, void *arg1) {
    u8 temp_a1;
    u8 *var_a0 = arg0;
    u8 *src = D_800E045F;

    if ((*(u8 *)arg1 == 0x82) &&
        ((temp_a1 = *((u8 *)arg1 + 1), (temp_a1 == 0x81)) ||
         (temp_a1 == 0x89) || (temp_a1 == 0x95) ||
         (temp_a1 == 0x85) || (temp_a1 == 0x8F) ||
         (temp_a1 == 0x60) || (temp_a1 == 0x68) ||
         (temp_a1 == 0x74) || (temp_a1 == 0x64) ||
         (temp_a1 == 0x6E))) {
        *var_a0++ = src[0];
        *var_a0++ = src[1];
    }
    return var_a0;
}
