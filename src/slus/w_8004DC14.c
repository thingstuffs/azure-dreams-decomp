#include "common.h"

/* Already-matched callees (reuse their real signature where it doesn't
   conflict with how THIS call site uses the return value / passes args). */
extern void *func_8004B404(s32 a0, s32 a1, s32 a2, s32 a3); /* code7.c's own
    decl is `void func_8004B404(...)`, but its body ends in a tail call to the
    still-unmatched func_8004B364, whose return value passes through in $v0;
    this caller relies on that passthrough, so it's declared returning a
    pointer here. Argument shape (4 ints) is identical. */
extern s32 func_8004B4DC(void *a0);
extern void func_8004B1A4(void *a0);

/* Not yet matched elsewhere -- inventing a prototype that matches this call
   site's register setup only (a0=obj, a1=format string, a2=arg value). */
extern s32 func_8004DA74(void *a0, char *a1, s32 a2);

extern int puts(const char *s);

/* Allocates a fixed-size (0x100) object via func_8004B404 (forwarding this
 * function's own a1-a3 straight through, unused itself), then formats a0
 * (as a printf-style format string, with a1 as the value/arg-list) into the
 * new object via func_8004DA74. On formatting failure the object is freed
 * (func_8004B1A4) and NULL is returned. On success, if the formatted-length
 * indicator from func_8004B4DC comes back under 0x16 the object is returned
 * as-is; otherwise a0 is also echoed via puts() before returning the object. */
void *allocObject100(char *a0, s32 a1, s32 a2, s32 a3)
{
    void *obj;

    obj = func_8004B404(0x100, a1, a2, a3);
    if (obj != 0) {
        if (func_8004DA74(obj, a0, a1) != 0) {
            if (func_8004B4DC(obj) < 0x16) {
                return obj;
            }
            puts(a0);
            return obj;
        }
        func_8004B1A4(obj);
        obj = 0;
    }

    return obj;
}
