#include "common.h"

/* --- gcc 2.95.2 -O2 -fstrict-aliasing TU --- */

/* Sets the "used"/flag bit (0x8000) on a 16-bit field at offset 0x1E within
 * *a0, and on the global flags word D_800814A0, but only if a0 is non-NULL. */
typedef struct {
    int val;
    int pad[2];
} S_800814A0;
extern S_800814A0 D_800814A0;

void func_8004EE90(unsigned short *a0)
{
    if (a0 != 0) {
        a0[0xF] |= 0x8000;
        D_800814A0.val |= 0x8000;
    }
}
