#include "common.h"
#include "shared/sprite_frame_state.h"

#include "engine/graphics.h"
#include "engine/scene.h"

#ifndef NULL
#define NULL 0
#endif

/* Table entry scanned by find_last_flagged_record_by_id (matched neighbor). */
typedef struct SpriteAttachmentEntry {
    /* 0x0 */ u8 flags;
    /* 0x1 */ u8 pad1[5];
    /* 0x6 */ u16 id;
    /* 0x8 */ u8 pad2[4];
} SpriteAttachmentEntry; /* size 0xC */

/* arg1: entity/actor-like struct; only the status/flag halfword at 0x14 is
 * touched directly here (bits 0x6000); rest is opaque and forwarded to
 * transform_sprite_attachment_point. */

/* Looks up an entry and fills its vector, using a fixed fallback for flagged entities. */
SpriteAttachmentEntry *get_sprite_attachment_vector(SpriteAttachmentEntry *table, SpriteFrameState *entity, SpriteAttachmentVector *out_vec, s16 entry_id) {
    SVECTOR vector;
    u16 entry_index;
    SpriteAttachmentEntry *entry;

    entry = find_last_flagged_record_by_id(table, entry_id, &entry_index);
    if (entry != NULL) {
        transform_sprite_attachment_point(entity, entry, &vector);
        out_vec->x = vector.vx;
        out_vec->y = vector.vy;
        out_vec->z = vector.vz;
    } else if (entity->flags & 0x6000) {
        entry = table;
        out_vec->y = 0;
        out_vec->x = 0;
        out_vec->z = (s16)-0x40;
    }
    return entry;
}
