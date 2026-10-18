#include "common.h"

extern s16 find_entry_at_tile_coordinates(s16 x, s16 y, s16 z);

typedef struct {
    u8 pad[3];
    u8 flags;
} DungeonEntry;

extern DungeonEntry D_800E3648[];

/* Store the looked-up dungeon entry index if flag 0x80 is set, or report failure. */
s32 find_flagged_tile_entry(void *state, void *unused, void *position, void *lookup_context) {
    s16 entry_index;
    s32 failed;

    entry_index = find_entry_at_tile_coordinates(
        *((u8 *)position + 0x24),
        *((u8 *)position + 0x25),
        *(s16 *)((u8 *)lookup_context + 0x88));
    *(s16 *)((u8 *)state + 0x100) = entry_index;

    if (entry_index < 0) {
        failed = 1;
    } else {
        if (D_800E3648[entry_index].flags & 0x80) {
            failed = 0;
        } else {
            *(s16 *)((u8 *)state + 0x100) = -1;
            failed = 1;
        }
    }
    return failed;
}
