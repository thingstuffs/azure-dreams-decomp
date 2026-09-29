#include "common.h"
#include "shared/entity.h"

s32 func_800A5894(EntityRec *state) {
    if (state->z.v > -0x400000) {
        return (state->z.w.i * 0xC00) + 0x30000;
    }
    return 0;
}
