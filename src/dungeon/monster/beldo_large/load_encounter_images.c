#include "common.h"
#include "dungeon/monster/beldo_large.h"
#include "engine/graphics.h"
#include "dungeon/globals.h"

/* Update the shared data for mode one and pass it to the handler. */
void load_encounter_images(s32 mode)
{
    if (mode == 1) {
        encounter_image_load_commands[4] += 0x40;
    }
    run_image_load_commands(encounter_image_load_commands, 0);
}
