#include "common.h"

/* Table-lookup dispatcher: finds arg0's record for id=arg3 via func_8004CAE8;
 * if found, derives an orientation Vec via func_8003DBD0 and copies it into
 * *arg2. If not found and arg1's status flags (0x14) have bit 0x2000 or
 * 0x4000 set, resets *arg2 to (0,0,-0x40) and returns arg0 unchanged. */
#include "common.h"

#ifndef NULL
#define NULL 0
#endif

/* Opaque record type; matches the already-matched func_8004CAE8's own type
 * (src/w_8004CAE8.c defines its full layout: flags/id table entry). This
 * function never dereferences it directly, only forwards the pointer. */
typedef struct S_8004CAE8 S_8004CAE8;
extern S_8004CAE8 *func_8004CAE8(S_8004CAE8 *a0, u32 a1);

/* arg1: entity/actor-like struct; only the status/flag halfword at 0x14 is
 * touched directly here (bits 0x6000), the rest is opaque and forwarded on
 * to func_8003DBD0. */
typedef struct S_8003DE58_Ent {
    u8 pad[0x14];
    u16 unk14;
} S_8003DE58_Ent;

/* Output vector (3 signed halfwords, e.g. rotation/orientation); also used
 * as the local stack temp filled in by func_8003DBD0's third parameter. */
typedef struct S_8003DE58_Vec {
    s16 x;
    s16 y;
    s16 z;
} S_8003DE58_Vec;

extern void func_8003DBD0(S_8003DE58_Ent *a0, void *a1, S_8003DE58_Vec *a2);

/* If arg0's table lookup (keyed by arg3) succeeds, compute arg2 via
 * func_8003DBD0 into a stack temp and copy it out. Otherwise, if arg1's
 * status flags have either of bits 0x2000/0x4000 set, fall back to a fixed
 * "reset" orientation (0,0,-0x40) and return arg0 itself. */
S_8004CAE8 *func_8003DE58(S_8004CAE8 *arg0, S_8003DE58_Ent *arg1, S_8003DE58_Vec *arg2, s16 arg3) {
    S_8003DE58_Vec tmp;
    register S_8004CAE8 *var_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */

    var_s0 = func_8004CAE8(arg0, arg3);
    if (var_s0 != NULL) {
        func_8003DBD0(arg1, (void *)var_s0, &tmp);
        arg2->x = tmp.x;
        arg2->y = tmp.y;
        arg2->z = tmp.z;
    } else if (arg1->unk14 & 0x6000) {
        var_s0 = arg0;
        arg2->y = 0;
        arg2->x = 0;
        arg2->z = (s16)-0x40;
    }
    return var_s0;
}
