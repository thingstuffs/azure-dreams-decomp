#include "common.h"

extern u8 D_800E045D[];

void *func_80099978(void *arg0) {
    register u8 *dst ASM_REG("$4") = (u8 *)arg0;

    *dst = D_800E045D[0];
    ASM_KEEP(dst);
    dst++;
    *dst = D_800E045D[1];
    ASM_KEEP(dst);
    dst++;
    *dst = 7;
    ASM_KEEP(dst);
    dst++;
    *dst = 7;
    dst++;

    return dst;
}
