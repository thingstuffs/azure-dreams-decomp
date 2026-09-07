#include "common.h"

/* --- gcc 2.8.1 -O2 -G0 TU --- */

/* Sets a "used"/flag bit (0x8000) both on a 16-bit flags field at offset
 * 0x1E of the object, and on a global 32-bit flags word, when the object
 * pointer is non-NULL. */
/* Same 32-bit "global flags" word touched by the sibling func_8004B530
 * (`a0[-1] |= 0x8000; D_800814A0 |= 0x8000;`, matched in code5.c under
 * gcc 2.7.2 -G0 -fno-schedule-insns). This function needs -G0 too (a plain
 * 4-byte int addressed via lui/%hi + lw|sw/%lo, not $gp-relative), but WITH
 * instruction scheduling left ON (no -fno-schedule-insns): the target
 * groups the two loads together, the two ORs together, and the two stores
 * together, and reuses ONE lui-computed base register across both the load
 * and the store of D_800814A0 (freeing $a0, once copied to $a1 for the
 * object pointer, to hold the global's loaded value). That reuse-without-a
 * -second-lui behavior only reproduces on gcc>=2.8 (2.8.0/2.8.1/2.95.2) or
 * the 2.7.2-cdk patch level -- plain 2.7.2 always recomputes a fresh lui
 * for the store. */
extern int D_800814A0;

typedef struct {
    u8 pad[0x1E];
    u16 flags;
} UnkStruct1E;

void func_8004F52C(UnkStruct1E *a0)
{
    if (a0 != 0) {
        a0->flags |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
