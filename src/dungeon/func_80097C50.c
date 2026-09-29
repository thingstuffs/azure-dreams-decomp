#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"

typedef struct {
    u32 word0;
    u32 word1;
} __attribute__((packed)) UA64;

typedef struct MapTile {
    u16 type;
    u16 height;
    u16 unk_04;
} MapTile;

extern void func_800672D8(void *, u8 *);
extern UA64 D_80088CB0;
extern u8 D_800E50A8[];
extern MapTile D_800EA000[];

/* Update packed map levels for the current region or neighboring tiles, then submit the map. */
void func_8009D3B0(void) {
    UA64 map_params;
    MapGrid *grid;
    TileObject *obj;
    DungeonRoom *room;
    MapTile *tile;
    u8 *cell;
    s32 index;
    s16 level;
    s32 lv;
    u8 packed;
    s16 x;
    s16 y;
    s16 n;   /* the room scan's x end, then the neighbour scan's direction */
    s16 y_end;
    GameWork *gw;

    map_params = D_80088CB0;
    gw = &gameWork;
    grid = &gw->map;
    obj = &D_80082E80;
    if (obj->unk_026 >= 0) {
        room = &D_800E2970[obj->unk_026];
        y = room->y - 1;
        n = room->x + room->w + 1;
        y_end = room->h + y + 2;
        for (; y < y_end; y++) {
            for (x = room->x - 1; x < n; x++) {
                index = (y << grid->shiftX) + x;
                tile = &D_800EA000[index];
                if (tile->type != 0 && tile->type != 3) {
                    cell = &D_800E50A8[index / 2];
                    level = (s16)(tile->height + 0x200) / 64;
                    if (level >= 16) {
                        level = 15;
                    } else if (level <= 0) {
                        level = 1;
                    }
                    lv = level;
                    packed = *cell;
                    if (x & 1) {
                        *cell = packed | (lv << 4);
                    } else {
                        *cell = packed | lv;
                    }
                }
            }
        }
    } else {
        for (n = 7; n >= 0; n--) {
            x = D_80082E80.tileX + dirStepX[n];
            y = D_80082E80.tileY + dirStepY[n];
            index = (y << grid->shiftX) + x;
            tile = &D_800EA000[index];
            if (tile->type != 0 && tile->type != 3) {
                cell = &D_800E50A8[index / 2];
                level = (s16)(tile->height + 0x200) / 64;
                if (level >= 16) {
                    level = 15;
                } else if (level <= 0) {
                    level = 1;
                }
                lv = level;
                packed = *cell;
                if (x & 1) {
                    *cell = packed | (lv << 4);
                } else {
                    *cell = packed | lv;
                }
            }
        }
    }
    func_800672D8(&map_params, D_800E50A8);
}
