#include "dungeon/level/floor_flags.h"
#include "common.h"
#include "shared/dungeon_floor.h"

typedef s32 M2C_UNK;

void draw_textured_ellipse();
extern M2C_UNK D_800DD80C;

/* Submit a fixed command and set the global activation flag. */
void submit_activation_command(void) {
    s32 command[2];

    command[0] = 0x01000340;
    command[1] = 0x00200020;
    draw_textured_ellipse(&D_800DD80C, command, 1, 0);
    dungeon_floor_flags |= FLOOR_MAP_VIEW_HOLD;
}
