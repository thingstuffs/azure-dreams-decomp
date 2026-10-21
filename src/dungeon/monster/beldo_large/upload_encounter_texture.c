#include "common.h"
#include "m2c_compat.h"

void upload_vram_row_and_cache(s32, s32, s32, s32); /* extern */
extern M2C_UNK beldo_large_pixels;

/* Initializes the global resource with size 0x7AC0 and options 1 and 2. */
void upload_encounter_texture(void) {
    upload_vram_row_and_cache((s32)(&beldo_large_pixels), 0x7AC0, 1, 2);
}
