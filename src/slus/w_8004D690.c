#include "common.h"

/* func_8004D7E8: matched callee (gcc 2.8.1), src/w_8004D7E8.c */
extern void func_8004D7E8(void *a0);

/* func_8004D690: while a0's callback slot is NULL, poll a1's flag; if a1's
 * flag is zero, give up and return. Otherwise call func_8004D7E8(a2) and
 * re-check a0. Once a0's callback becomes non-NULL, invoke it once with
 * the address just past a0 (a0+4 bytes) and return. */
void func_8004D690(void (**a0)(void *), s32 *a1, void *a2)
{
    void (*temp_v0)(void *);

loop_1:
    temp_v0 = *a0;
    if (temp_v0 != (void *)0) {
        temp_v0((void *) (a0 + 1));
        return;
    }
    if (*a1 != 0) {
        func_8004D7E8(a2);
        goto loop_1;
    }
}
