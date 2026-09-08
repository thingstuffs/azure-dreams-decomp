#include "common.h"

#ifndef NULL
#define NULL 0
#endif

/* Opaque record type; matches the already-matched func_8004CAE8's own type
 * (src/w_8004CAE8.c defines its full layout: flags/id table entry). This
 * function never dereferences it directly, only forwards the pointer. */
typedef struct S_8004CAE8 S_8004CAE8;
extern S_8004CAE8 *func_8004CAE8(S_8004CAE8 *a0, u32 a1);

/* actor: entity/actor-like struct; only the status/flag halfword at 0x14 is
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

/* Compute orientation from a matching record, or reset it when actor flags require a fallback. */
S_8004CAE8 *func_8003DE58(S_8004CAE8 *records, S_8003DE58_Ent *actor, S_8003DE58_Vec *out_vec, s16 record_id) {
    S_8003DE58_Vec orientation;
    register S_8004CAE8 *record ASM_REG("$16");   /* MATCH pin: slus-diff */

    record = func_8004CAE8(records, record_id);
    if (record != NULL) {
        func_8003DBD0(actor, (void *)record, &orientation);
        out_vec->x = orientation.x;
        out_vec->y = orientation.y;
        out_vec->z = orientation.z;
    } else if (actor->unk14 & 0x6000) {
        record = records;
        out_vec->y = 0;
        out_vec->x = 0;
        out_vec->z = (s16)-0x40;
    }
    return record;
}
