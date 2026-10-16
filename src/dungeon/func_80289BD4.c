#include "modules/dungeon_floor_generate.h"

s16 dungeonChooseUnblockedCardinalDirection(s16 x, s16 y, s16 dir)
{
    s32 turn;
    s32 d;
    s16 nx;
    s16 ny;
    MapGrid *map = &gameWork.map;

    nx = x + dirStepX[dir];
    ny = y + dirStepY[dir];
    if (D_800EA000[(ny << map->shiftX) + nx].flags != 0) {
        for (turn = 2; turn < 7; turn += 4) {
            d = (dir + turn) & 6;
            nx = x + dirStepX[d];
            ny = y + dirStepY[d];
            if (D_800EA000[(ny << map->shiftX) + nx].flags == 0) {
                return (dir + turn) & 6;
            }
        }
    }
    return dir;
}
