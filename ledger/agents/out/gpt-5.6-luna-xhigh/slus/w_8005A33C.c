#include "common.h"

/* Globals accessed directly via %hi/%lo (not $gp small-data). Declared with a
 * size > -G (8) so gcc/as emit %hi/%lo rather than $gp-relative access; the
 * element type reflects the access width, the array length is provisional. */
extern int D_80086D4C[3];
extern int D_80073824[4];

extern void func_800585A0(void);

/* Runs the guarded callback and sets the counter to 1. */
void func_8005A33C(void)
{
    if (D_80086D4C[0] > 0)
    {
        if (D_80086D4C[0] < 4)
        {
            func_800585A0();
        }
    }
    D_80073824[0] = 1;
}
