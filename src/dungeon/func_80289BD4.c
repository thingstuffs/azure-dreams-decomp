#include "dungeon/level/generate.h"

s16 choose_unblocked_cardinal_direction(s16 x, s16 y, s16 dir)
{
    s32 turn;
    s32 d;
    s16 nx;
    s16 ny;
    MapGrid *map = &g_game_work.map;

    nx = x + dir_step_x[dir];
    ny = y + dir_step_y[dir];
    if (D_800EA000[(ny << map->shiftX) + nx].flags != 0) {
        for (turn = 2; turn < 7; turn += 4) {
            d = (dir + turn) & 6;
            nx = x + dir_step_x[d];
            ny = y + dir_step_y[d];
            if (D_800EA000[(ny << map->shiftX) + nx].flags == 0) {
                return (dir + turn) & 6;
            }
        }
    }
    return dir;
}
