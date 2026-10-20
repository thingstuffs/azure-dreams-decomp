#include "common.h"
#include "m2c_compat.h"

/* manual g1 strike 2: preserve the incoming second argument through the call */
#include "common.h"

void pack_tagged_resource_descriptor(int tag, int id, int *record, int value);
extern M2C_UNK sprite_metadata_read_descriptor;

/* Builds and returns a shared descriptor for the record ID and packed value. */
s32 *build_sprite_metadata_read_descriptor(s16 record_id, s32 packed_value) {
    s32 count;
    s32 offset;

    if (record_id == 0x38) {
        offset = 0x421F;
        count = 0x4E;
    } else {
        if (record_id >= 0x3A) {
            offset = ((record_id - 0x3A) * 0x2B) + 0x1B8D;
        } else {
            offset = ((record_id - 1) * 0x2B) + 0x56D6;
        }
        count = 0x1A;
    }
    pack_tagged_resource_descriptor(count, packed_value, &sprite_metadata_read_descriptor, offset);
    return &sprite_metadata_read_descriptor;
}
