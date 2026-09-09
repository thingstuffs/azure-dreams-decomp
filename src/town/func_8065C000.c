#include "common.h"

extern s32 func_80016788();
extern s32 func_80016CB4(s32, s32, s32, s32);

/* Check whether the initial query is zero or the secondary value is at least three. */
s32 func_8065C000(s32 query_input_a, s32 query_input_b, s32 query_input_c, s32 query_input_d) {
    s32 less_than_three;

    if (func_80016CB4(query_input_a, query_input_b, query_input_c, query_input_d) == 0) {
        goto return_one;
    }
    less_than_three = func_80016788() < 3;
    if (less_than_three != 0) {
        return 0;
    }
return_one:
    return 1;
}
