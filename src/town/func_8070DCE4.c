#include "common.h"

extern s32 func_8001A64C(s32);
extern char D_8001B9E8[];

/* Return D_8001B9E8 when query 0x930 succeeds, otherwise null. */
char *func_80016CE4(void) {
    char *result;

    if (func_8001A64C(0x930) == 0) {
        result = 0;
    } else {
        result = D_8001B9E8;
    }
    return result;
}
