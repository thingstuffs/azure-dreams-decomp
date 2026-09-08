#include "common.h"

/* Allocator wrapper: the retail definition of func_8004B404 (code7.c, gcc 2.8.1)
 * declares "void func_8004B404(int,int,int,int)" but is a tail-call forwarder to
 * func_8004B364, whose return value passes through in $v0 untouched. This call
 * site only ever sets $a0 (the size), so we prototype/call it with just that one
 * argument and treat it as value-returning, matching the "value-returning wrapper"
 * idiom (v0 flows through from the tail jal, never re-touched before jr). */
extern void *func_8004B404(s32 a0);

/* func_8004951C: init routine for the freshly-allocated 0x104-byte object,
 * takes the object pointer and this function's original argument. Returns
 * nonzero on success. */
extern s32 func_8004951C(void *a0, void *a1);

/* func_8004B1A4 (code5.c, gcc 2.7.2): sets a "used" flag bit on a 16-bit
 * flags field 2 bytes before the object pointer, plus a global flags word. */
extern void func_8004B1A4(u16 *a0);

/* Allocates and initializes a 0x104-byte object, returning NULL on failure. */
void *func_80049790(void *init_data)
{
    void *object;

    object = func_8004B404(0x104);
    if (object != 0) {
        if (func_8004951C(object, init_data) == 0) {
            func_8004B1A4(object);
            object = 0;
        }
    }
    return object;
}
