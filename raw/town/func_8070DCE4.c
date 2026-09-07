#include "common.h"

extern s32 func_8001A64C(s32);
extern char D_8001B9E8[];

char *func_80016CE4(void) {
    register char *result ASM_REG("$2");

    if (func_8001A64C(0x930) == 0) {
        result = 0;
    } else {
        result = D_8001B9E8;
    }
    ASM_KEEP(result);
    return result;
}
