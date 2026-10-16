#include "common.h"

extern s32 func_80016788();
extern s32 townGetFlagTestTableAddress(void);

/* Check whether the initial query is zero or the secondary value is at least two. */
s32 func_8065BFB4(s32 query_input_a, s32 query_input_b, s32 query_input_c, s32 query_input_d) {
    s32 below_two;

    if (townGetFlagTestTableAddress() != 0) {
        below_two = func_80016788() < 2;
        if (below_two != 0) {
            return 0;
        }
    }
    return 1;
}
