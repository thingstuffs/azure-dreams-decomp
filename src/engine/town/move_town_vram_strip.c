#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/graphics.h"
#include "engine/town.h"

/* Calls move_vram_rect with a fixed set of parameters. */
void move_town_vram_strip(void) {
    move_vram_rect(0x90, 0x1F2, 0x10, 1, 0, 0x1F2);
}
