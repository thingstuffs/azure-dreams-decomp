#include "common.h"
#include "town/scene.h"

extern u8 D_800170C8[];
extern u8 variant_default_response[];

/* Returns the byte array selected by the variant. */
void *select_variant_data(s32 unused_0, s32 unused_1, s32 variant) {
    if (variant != 1) {
        return variant_default_response;
    }
    return D_800170C8;
}
