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

s16 func_80017EBC(s16 arg0) {
    s16 count = 0;
    u8 *base = (u8 *)D_800E2970;
    DungeonEntry *temp_v1 = (DungeonEntry *)(base + (arg0 * 20));
    DungeonState *state = &D_8008333C;
    s16 height = temp_v1->height;
    u16 y = temp_v1->y;
    s16 h_rem = height;

    if (height > 0) {
        DungeonEntry *entry = temp_v1;

        while (h_rem > 0) {
            DungeonCell *cell = (DungeonCell *)((u8 *)state->cells + (((s16)y << state->shift) * 6) + (entry->x * 6));
            s16 width = entry->width;

            while (width > 0) {
                if (!(cell->flags & 0x8500)) {
                    count++;
                }
                cell++;
                width--;
            }
            y++;
            h_rem--;
        }
    }
    return count;
}
