#include "common.h"
#include "dungeon/monster/beldo_large.h"
#include "engine/graphics.h"

extern u16 encounter_image_load_commands[8];

/* Update the shared data for mode one and pass it to the handler. */
void upload_encounter_texture_variant(s32 mode)
{
    if (mode == 1) {
        encounter_image_load_commands[4] += 0x40;
    }
    run_image_load_commands(encounter_image_load_commands, 0);
}
