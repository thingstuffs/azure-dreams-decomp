#include "common.h"
#include "shared/game_work.h"

extern u8 D_80162004[];
extern void *no_op_building_callback();

/* Initialize the shared buffer pointer and paired parameters, then process the buffer. */
void initialize_building_shared_buffer(void)
{
    GameWork *base = &g_game_work;
    MapGrid *map = &base->map;
    s32 limit;
    s32 size;
    s32 setting;

    limit = 0x7F;
    size = 0x2000;
    map->shiftX = 7;
    map->maskX = limit;
    map->spanX = size;
    setting = 7;
    map->shiftY = setting;
    map->maskY = limit;
    map->spanY = size;
    base->map.cells = D_80162004;
    no_op_building_callback(base, size, limit);
}
