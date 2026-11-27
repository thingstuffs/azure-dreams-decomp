#include "dungeon/level/floor_flags.h"
#include "common.h"
#include "shared/dungeon_floor.h"

typedef s32 M2C_UNK;

#include "dungeon/effect/screen.h"
extern M2C_UNK map_marker_ellipse_parameters;

/* Submit a fixed command and set the global activation flag. */
void begin_map_marker_draw(void) {
    GpuRectBuffer command;

    command.words[0] = 0x01000340;
    command.words[1] = 0x00200020;
    draw_textured_ellipse(&map_marker_ellipse_parameters, &command.rect, 1, 0);
    dungeon_floor_flags |= FLOOR_MAP_VIEW_HOLD;
}
