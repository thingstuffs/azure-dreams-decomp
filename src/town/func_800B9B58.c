#include "common.h"
#include "shared/game_work.h"

extern u8 D_80162004[];
extern void *func_800B7420();

/* Initialize the shared buffer pointer and paired parameters, then process the buffer. */
void func_800B72B8(void)
{
    GameWork *base = &gameWork;
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
    func_800B7420(base, size, limit);
}
