#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"

typedef struct MapCell {
    u16 unk_00;
    u16 unk_02;
    u16 blocked;
} MapCell;

extern MapCell D_800EA000[];

/* Chooses an available neighboring direction, checking perpendicular alternatives when needed. */
s16 func_8001CBD4(s16 x, s16 y, s16 dir)
{
    s32 turn;
    s32 d;
    s16 nx;
    s16 ny;
    MapGrid *map = &gameWork.map;

    nx = x + dirStepX[dir];
    ny = y + dirStepY[dir];
    if (D_800EA000[(ny << map->shiftX) + nx].blocked != 0) {
        for (turn = 2; turn < 7; turn += 4) {
            d = (dir + turn) & 6;
            nx = x + dirStepX[d];
            ny = y + dirStepY[d];
            if (D_800EA000[(ny << map->shiftX) + nx].blocked == 0) {
                return (dir + turn) & 6;
            }
        }
    }
    return dir;
}
