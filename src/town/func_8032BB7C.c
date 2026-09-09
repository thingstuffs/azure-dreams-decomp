#include "common.h"

extern s32 func_80019B54(void *, s32);
extern void func_8001ACE8(s32);
extern void func_8001AD60(s32);

/* Select the handler for 0xDB8 based on the query result and return its truth value. */
s32 func_8001637C(void *object, s32 query_value) {
    s32 result;

    if (func_80019B54(object, query_value) != 0) {
        goto nonzero;
    }
    func_8001ACE8(0xDB8);
    result = 0;
    goto done;

nonzero:
    func_8001AD60(0xDB8);
    result = 1;

done:
    return result;
}
