#include "common.h"

extern void *D_80016000;

/* Set the linked record's second and third values to 1696 and 800. */
void func_8001702C(void) {
    (*(s32 **)((s8 *)D_80016000 + 0x1C))[1] = 1696;
    (*(s32 **)((s8 *)D_80016000 + 0x1C))[2] = 800;
}
