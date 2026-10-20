#include "dungeon/level/generate.h"

void clear_generation_cell_masks(void) {
    mask_generation_cell_rect(0, 0, 0x40, 0x40, 0);
}
