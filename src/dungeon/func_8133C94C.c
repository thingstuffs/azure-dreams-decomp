#include "common.h"
#include "m2c_compat.h"

void upload_vram_row_and_cache(); /* extern */
extern M2C_UNK D_80173DBC;

/* Initializes the global resource with size 0x7AC0 and options 1 and 2. */
void upload_encounter_texture(void) {
    upload_vram_row_and_cache(&D_80173DBC, 0x7AC0, 1, 2);
}
