#include "common.h"

#include "common.h"

#ifndef NULL
#define NULL 0
#endif

/* Table entry scanned by func_8003DF0C (matched neighbor). */
typedef struct S_8003DF0C {
    /* 0x0 */ u8 flags;
    /* 0x1 */ u8 pad1[5];
    /* 0x6 */ u16 id;
    /* 0x8 */ u8 pad2[4];
} S_8003DF0C; /* size 0xC */

/* arg1: entity/actor-like struct; only the status/flag halfword at 0x14 is
 * touched directly here (bits 0x6000); rest is opaque and forwarded to
 * func_8003DBD0. */
typedef struct S_8003DF74_Ent {
    u8 pad[0x14];
    u16 unk14;
} S_8003DF74_Ent;

/* Output vector (3 signed halfwords); also the stack temp filled by
 * func_8003DBD0's third parameter. */
typedef struct S_8003DF74_Vec {
    s16 x;
    s16 y;
    s16 z;
} S_8003DF74_Vec;

extern S_8003DF0C *func_8003DF0C(S_8003DF0C *ent, s32 want, u16 *idxOut);
extern void func_8003DBD0(S_8003DF74_Ent *a0, void *a1, S_8003DF74_Vec *a2);

/* Twin of func_8003DE58: same control flow, but table lookup goes through
 * func_8003DF0C (which also writes a reduced index into *idxOut on the
 * stack). Pure C matches at 2.7.2-cdk (see codegen_nudges fourth recipe). */
S_8003DF0C *func_8003DF74(S_8003DF0C *arg0, S_8003DF74_Ent *arg1, S_8003DF74_Vec *arg2, s16 arg3) {
    S_8003DF74_Vec tmp;
    u16 idxOut;
    S_8003DF0C *var_s0;

    var_s0 = func_8003DF0C(arg0, arg3, &idxOut);
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
