#include "common.h"
#include "m2c_compat.h"

void uploadVramRowAndCache(); /* extern */
extern M2C_UNK D_80173DBC;

/* Initializes the global resource with size 0x7AC0 and options 1 and 2. */
void dungeonUploadEncounterTexture(void) {
    uploadVramRowAndCache(&D_80173DBC, 0x7AC0, 1, 2);
}
