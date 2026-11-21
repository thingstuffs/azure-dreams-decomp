/* Card-grid entry positioning and selected-row updates. */
#include "common.h"
#include "frontend/card.h"
#include "frontend/card/message.h"
#include "frontend/card/server_menu.h"

/* Sets the linked record X halfword to twice column_tripled minus half the object width plus 0xA2. */
static __inline__ void store_first_coord(
    s32 *record,
    void *object,
    u32 column_tripled
    ) {
    *(s16 *)((u8 *)*(void **)((u8 *)record + 4) + 8) =
        (s16)((s32)(column_tripled << 1) - (*(s32 *)((u8 *)object + 0x18) / 2) + 0xA2);
}

/* Sets the linked record Y halfword to row times 0x11 minus half the object height plus 0x7A. */
static __inline__ void store_second_coord(s32 *record, void *object, s32 row)
{
    *(s16 *)((u8 *)*(void **)((u8 *)record + 4) + 0xA) =
        (s16)((row * 0x11) - (*(s32 *)((u8 *)object + 0x1C) / 2) + 0x7A);
}

/* Positions the object's record and updates the selected row. */
void configure_card_grid_entry(void *object, s32 column, s32 mode, s32 row, s32 value)
{
    u32 column_tripled;
    struct CardDevRowEntry *entries;
    struct CardDevRowEntry **row_data;
    u32 saved_value;
    void *position;
    void *record;

    column_tripled = (u32)column * 3U;
    record = *(s32 **)((u8 *)object + 0x6A0);
    position = (u8 *)object + 0x12C;
    store_first_coord(record, object, column_tripled);
    store_second_coord(record, object, row);
    saved_value = (u32)value;
    saved_value = (saved_value + (u32)row) - (u32)row;
    init_menu_row_entry(object, position, mode);
    *(s32 *)record = (s32)(unsigned long)position;
    row_data = *(struct CardDevRowEntry ***)((u8 *)object + row * 4 + 0x68C);
    entries = *row_data;
    card_dev_mark_row_entry_range(entries, (s32)saved_value, mode);
}
