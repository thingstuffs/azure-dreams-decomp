#include "common.h"
#include "shared/entity.h"

s32 compute_height_based_offset(EntityRec *state) {
    if (state->z.v > -0x400000) {
        return (state->z.w.i * 0xC00) + 0x30000;
    }
    return 0;
}
