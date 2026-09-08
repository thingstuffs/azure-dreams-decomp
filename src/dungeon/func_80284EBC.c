#include "common.h"

typedef struct {
    u16 x;
    u16 y;
    s16 width;
    s16 height;
    s8 pad[12];
} DungeonEntry;

typedef struct {
    u16 f0;
    u16 f2;
    u16 flags;
} DungeonCell;

typedef struct {
    DungeonCell *cells;
    u8 pad4[0x10];
    s16 shift;
} DungeonState;

extern DungeonEntry D_800E2970[];
extern DungeonState D_8008333C;

/* Counts cells in the selected dungeon entry with no flags in mask 0x8500. */
s16 func_80017EBC(s16 entry_index) {
    s16 count = 0;
    u8 *entry_base = (u8 *)D_800E2970;
    DungeonEntry *region = (DungeonEntry *)(entry_base + (entry_index * 20));
    DungeonState *state = &D_8008333C;
    s16 height = region->height;
    u16 y = region->y;
    s16 rows_left = height;

    if (height > 0) {
        DungeonEntry *entry = region;

        while (rows_left > 0) {
            DungeonCell *cell = (DungeonCell *)((u8 *)state->cells + (((s16)y << state->shift) * 6) + (entry->x * 6));
            s16 cols_left = entry->width;

            while (cols_left > 0) {
                if (!(cell->flags & 0x8500)) {
                    count++;
                }
                cell++;
                cols_left--;
            }
            y++;
            rows_left--;
        }
    }
    return count;
}
