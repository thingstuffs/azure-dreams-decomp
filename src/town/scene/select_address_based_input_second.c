#include "script_symbols.h"
#include "common.h"

extern s32 func_8001A64C(s32);
extern char D_8001B9E8[];

/* Return D_8001B9E8 when query 0x930 succeeds, otherwise null. */
char *select_address_based_input(void) {
    char *result;

    if (func_8001A64C(F_sbs32_pad06) == 0) {
        result = 0;
    } else {
        result = D_8001B9E8;
    }
    return result;
}
