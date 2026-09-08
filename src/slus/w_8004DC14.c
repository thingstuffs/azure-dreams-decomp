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

/* Allocates and formats a 0x100-byte object, freeing it on failure and echoing the format if the length reaches 0x16. */
void *allocObject100(char *format, s32 format_arg, s32 alloc_arg2, s32 alloc_arg3)
{
    void *obj;

    obj = func_8004B404(0x100, format_arg, alloc_arg2, alloc_arg3);
    if (obj != 0) {
        if (func_8004DA74(obj, format, format_arg) != 0) {
            if (func_8004B4DC(obj) < 0x16) {
                return obj;
            }
            puts(format);
            return obj;
        }
        func_8004B1A4(obj);
        obj = 0;
    }

    return obj;
}
