#include "common.h"
#include "engine/graphics.h"
#include "engine/scene.h"

#ifndef NULL
#define NULL 0
#endif

/* Opaque record type; matches the already-matched find_flagged_record_by_id's own type
 * (src/w_8004CAE8.c defines its full layout: flags/id table entry). This
 * function never dereferences it directly, only forwards the pointer. */
typedef struct S_8004CAE8 S_8004CAE8;

/* actor: entity/actor-like struct; only the status/flag halfword at 0x14 is
 * touched directly here (bits 0x6000), the rest is opaque and forwarded on
 * to runtime_transform_sprite_attachment_point. */
typedef struct S_8003DE58_Ent {
    u8 pad[0x14];
    u16 unk14;
} S_8003DE58_Ent;

/* Output vector (3 signed halfwords, e.g. rotation/orientation); also used
 * as the local stack temp filled in by runtime_transform_sprite_attachment_point's third parameter. */
typedef struct S_8003DE58_Vec {
    s16 x;
    s16 y;
    s16 z;
} S_8003DE58_Vec;

/* Compute orientation from a matching record, or reset it when actor flags require a fallback. */
S_8004CAE8 *resolve_record_orientation_or_fallback(S_8004CAE8 *records, S_8003DE58_Ent *actor, S_8003DE58_Vec *out_vec, s16 record_id) {
    S_8003DE58_Vec orientation;
    S_8004CAE8 *record;

    record = find_flagged_record_by_id(records, record_id);
    if (record != NULL) {
        runtime_transform_sprite_attachment_point(actor, (void *)record, &orientation);
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
