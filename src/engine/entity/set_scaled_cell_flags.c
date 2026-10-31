#include "common.h"
#include "shared/game_work.h"
#include "engine/entity.h"

/* Sets the flags bit 0x8000 on four 6-byte table entries per party-slot index
 * i in [10, 12): entries at byte offsets (i << D_8008333C.field14) * 6 +
 * {0x78, 0x7E, 0xFC, 0x102} from D_8008333C.field0. Sibling clear_scaled_cell_flags_8000
 * clears the same bit (&= 0x7FFF) on the identical index set. */
typedef struct S_80043B4C_entry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u16 flags;
} S_80043B4C_entry;


/* Sets flag 0x8000 in four sub-tables at scaled indices 10 and 11. */
void set_scaled_cell_flags_8000(void)
{
    MapGrid *table = &g_game_work.map;
    u8 *entries = table->cells;
    s32 slot;

    for (slot = 10; slot < 12; slot++) {
        ((S_80043B4C_entry *)(entries + (slot << table->shiftX) * 6 + 0x78))->flags |= 0x8000;
        ((S_80043B4C_entry *)(entries + (slot << table->shiftX) * 6 + 0x7E))->flags |= 0x8000;
        ((S_80043B4C_entry *)(entries + (slot << table->shiftX) * 6 + 0xFC))->flags |= 0x8000;
        ((S_80043B4C_entry *)(entries + (slot << table->shiftX) * 6 + 0x102))->flags |= 0x8000;
    }
}
