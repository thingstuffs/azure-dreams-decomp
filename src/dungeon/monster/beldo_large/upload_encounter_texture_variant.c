#include "common.h"

extern u16 D_80016000[8];
extern void run_image_load_commands(void *data_base, s32 scratch);

/* Update the shared data for mode one and pass it to the handler. */
void upload_encounter_texture_variant(s32 mode)
{
    if (mode == 1) {
        D_80016000[4] += 0x40;
    }
    run_image_load_commands(D_80016000, 0);
}
