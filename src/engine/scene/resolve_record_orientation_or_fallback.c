#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/vector.h"
#include "engine/graphics.h"
#include "engine/scene.h"

#ifndef NULL
#define NULL 0
#endif

/* actor: entity/actor-like struct; only the status/flag halfword at 0x14 is
 * touched directly here (bits 0x6000), the rest is opaque and forwarded on
 * to runtime_transform_sprite_attachment_point. */

/* Compute orientation from a matching record, or reset it when actor flags require a fallback. */
SpriteAttachment *resolve_record_orientation_or_fallback(SpriteAttachment *records, SpriteFrameState *actor, GteShortVector *out_vec, s16 record_id) {
    GteShortVector orientation;
    SpriteAttachment *record;

    record = find_flagged_record_by_id(records, record_id);
    if (record != NULL) {
        runtime_transform_sprite_attachment_point(actor, (void *)record, &orientation);
        out_vec->vx = orientation.vx;
        out_vec->vy = orientation.vy;
        out_vec->vz = orientation.vz;
    } else if (actor->flags & 0x6000) {
        record = records;
        out_vec->vy = 0;
        out_vec->vx = 0;
        out_vec->vz = (s16)-0x40;
    }
    return record;
}
