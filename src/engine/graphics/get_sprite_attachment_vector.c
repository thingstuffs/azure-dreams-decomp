#include "common.h"

#include "common.h"
#include "engine/graphics.h"
#include "engine/scene.h"

#ifndef NULL
#define NULL 0
#endif

/* Table entry scanned by find_last_flagged_record_by_id (matched neighbor). */
typedef struct S_8003DF0C {
    /* 0x0 */ u8 flags;
    /* 0x1 */ u8 pad1[5];
    /* 0x6 */ u16 id;
    /* 0x8 */ u8 pad2[4];
} S_8003DF0C; /* size 0xC */

/* arg1: entity/actor-like struct; only the status/flag halfword at 0x14 is
 * touched directly here (bits 0x6000); rest is opaque and forwarded to
 * runtime_transform_sprite_attachment_point. */
typedef struct S_8003DF74_Ent {
    u8 pad[0x14];
    u16 unk14;
} S_8003DF74_Ent;

/* Output vector (3 signed halfwords); also the stack temp filled by
 * runtime_transform_sprite_attachment_point's third parameter. */
typedef struct S_8003DF74_Vec {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} S_8003DF74_Vec;

/* Looks up an entry and fills its vector, using a fixed fallback for flagged entities. */
S_8003DF0C *get_sprite_attachment_vector(S_8003DF0C *table, S_8003DF74_Ent *entity, S_8003DF74_Vec *out_vec, s16 entry_id) {
    S_8003DF74_Vec vector;
    u16 entry_index;
    S_8003DF0C *entry;

    entry = find_last_flagged_record_by_id(table, entry_id, &entry_index);
    if (entry != NULL) {
        runtime_transform_sprite_attachment_point(entity, (void *)entry, &vector);
        out_vec->x = vector.x;
        out_vec->y = vector.y;
        out_vec->z = vector.z;
    } else if (entity->unk14 & 0x6000) {
        entry = table;
        out_vec->y = 0;
        out_vec->x = 0;
        out_vec->z = (s16)-0x40;
    }
    return entry;
}
