#include "common.h"
#include "m2c_compat.h"

/* manual g1 strike 2: preserve the incoming second argument through the call */
#include "common.h"


void pack_tagged_resource_descriptor(int tag, int id, int *record, int value);
extern M2C_UNK sprite_image_read_descriptor;

/* Selects an entry offset and requests data in the shared buffer. */
s32 *build_sprite_image_read_descriptor(s16 entry_id, s32 request_arg) {
    s32 entry_offset;

    if (entry_id == 0x38) {
        entry_offset = 0x426D;
    } else if (entry_id >= 0x3A) {
        entry_offset = ((entry_id - 0x3A) * 0x2B) + 0x1BA7;
    } else {
        entry_offset = ((entry_id - 1) * 0x2B) + 0x56F0;
    }
    pack_tagged_resource_descriptor(0x11, request_arg, &sprite_image_read_descriptor, entry_offset);
    return &sprite_image_read_descriptor;
}
