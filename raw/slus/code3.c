#include "common.h"

/* --- gcc 2.95.2 -O2 -fno-delayed-branch translation unit --- */

/* Looks up a pointer in table D_8006CDC8 indexed by a0 (16-bit) and dispatches it
 * to func_80041284. */
extern void *D_8006CDC8[];
extern int func_80041284(void *arg);

int func_8003E1C4(short a0)
{
    return func_80041284(D_8006CDC8[a0]);
}
