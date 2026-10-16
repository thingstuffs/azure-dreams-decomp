#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"







extern u8 D_80027334[][8];
extern u8 D_800273BE;


/* Animate nearby tile heights and fade the color, then finalize the dungeon transition. */
void dungeonAnimateTileHeightsAndTransition(DungeonState *state, DungeonOrigin *origin) {
    FadeColor *fade_color;
    s32 grid_x;
    s32 grid_y;
    s32 tile_x;
    s32 grid_y_fixed;
    s32 tile_y;
    s32 grid_x_fixed;
    s32 scratch;
    s32 offset_y;
    s32 random_value;
    void *tile;
    u16 timer;

    (*(u16 *)&D_80027330)++;
    if (state->active == 0) {
        if (!(state->timer & 3)) {
            func_800419EC(8, 16);
        }
        fade_color = (FadeColor *)&D_80027398;
        fade_color->red += (0xF0 - fade_color->red) / (s16)state->timer;
        fade_color->green += (0x40 - fade_color->green) / (s16)state->timer;
        fade_color->blue += (0x20 - fade_color->blue) / (s16)state->timer;

        grid_y = 1;
        do {
            grid_x = 1;
            scratch = ((u16)origin->y >> 6) - 3;
            tile_y = scratch + grid_y;
            do {
                scratch = ((u16)origin->x >> 6) - 3;
                tile_x = scratch + grid_x;
                random_value = func_80069EF8() & 7;
                D_8002745C[grid_y][grid_x] += (s8)D_80027334[grid_y][grid_x] - random_value;
                tile = dungeonFindEligibleEntryAtCoordinates(D_800E3D7C, tile_x & 0xFFFF, tile_y & 0xFFFF);
                if (tile != 0 && tile != D_8002732C) {
                    *(u16 *)(*(u8 **)((u8 *)tile - 0x18) + 0xA) =
                        D_8002745C[grid_y][grid_x] + origin->height;
                }
                if (!(func_80069EF8() & 7)) {
                    func_8002592C((s16)(tile_x << 6), (s16)(tile_y << 6),
                                  (s16)D_8002745C[grid_y][grid_x], (s16)grid_x,
                                  (s16)grid_y);
                }
                grid_x++;
            } while (grid_x < 7);
            grid_y++;
        } while (grid_y < 7);

        timer = state->timer - 1;
        state->timer = timer;
        if ((timer << 16) <= 0) {
            grid_y = 0;
            do {
                grid_x = 0;
                grid_y_fixed = grid_y << 16;
                grid_x_fixed = grid_x;
                do {
                    scratch = grid_x - 3;
                    tile = dungeonFindEligibleEntryAtCoordinates(D_800E3D7C,
                                         (((u16)origin->x >> 6) + scratch) & 0xFFFF,
                                         (((u16)origin->y >> 6) + (offset_y = grid_y - 3)) & 0xFFFF);
                    if (tile != 0 && tile != D_8002732C) {
                        func_8009CE1C(
                            tile, 16, D_800273BE, 9,
                            (s16)dungeonForwardMonsterCoordinateDelta(grid_x_fixed >> 16,
                                               grid_y_fixed >> 16, 3, 3),
                            D_800273C0, 2);
                        *(s32 *)((u8 *)tile + 0x14) &= 0xFFEFFFFF;
                    }
                    dungeonCreateTerrainTileQuad(grid_x_fixed >> 16, grid_y_fixed >> 16, origin);
                    grid_x_fixed += 0x10000;
                    grid_x++;
                } while (grid_x < 7);
                grid_y++;
            } while (grid_y < 7);
            state->timer = 8;
            state->active++;
            return;
        }
    } else {
        timer = state->timer - 1;
        state->timer = timer;
        if ((timer << 16) <= 0) {
            *((u16 *)state - 1) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
    }
}
