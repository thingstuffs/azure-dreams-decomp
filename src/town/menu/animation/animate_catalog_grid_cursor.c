#include "town/menu/catalog.h"
#include "common.h"

typedef struct SpriteFields {
    u32 pad0;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
} SpriteFields;

typedef struct DisplayPair {
    u32 pad0;
    SpriteFields *src;
    SpriteFields *dst;
} DisplayPair;

typedef struct TownSlots {
    void **slots[97];
    DisplayPair *display;
} TownSlots;

typedef struct TownObject {
    u8 pad0[4];
    s16 state;
    u8 pad6[9];
    u8 digit;
    u8 row;
    u8 index;
    u8 column;
    u8 pad13[0x45];
    TownSlots *town;
} TownObject;

extern u8 is_catalog_entry_available(u32);
extern void *catalog_normal_digits[10];
extern u16 catalog_cursor_rows[2];
extern u16 catalog_cursor_columns[8];
extern u8 catalog_number_marker[16];

/* Updates numbered slots and sprite display fields according to the object state. */
void animate_catalog_grid_cursor(TownObject *object)
{
    s32 slot_base;
    s32 entry_id;
    s32 slot_index;
    s32 row_offset;
    s32 column;
    s16 state;
    DisplayPair *display;
    SpriteFields *source_sprite;
    SpriteFields *hidden_sprite;

    state = ((TownObject *)(object))->state;
    switch (state) {
    case CATALOG_CURSOR_NUMBER:
        column = ((TownObject *)(object))->column;
        row_offset = ((TownObject *)(object))->row << 3;
        slot_base = (row_offset + column) * 3;
        slot_index = slot_base + 33;
        entry_id = (((TownObject *)(object))->digit << 4) + row_offset + column;
        if (is_catalog_entry_available((u8)entry_id) != 0) {
            *((TownObject *)(object))->town->slots[slot_index] = catalog_number_marker;
            slot_index = slot_base + 34;
            *((TownObject *)(object))->town->slots[slot_index] = catalog_normal_digits[(entry_id + 1) / 10];
            slot_index = slot_base + 35;
            *((TownObject *)(object))->town->slots[slot_index] = catalog_normal_digits[(entry_id + 1) % 10];
        }
        break;
    case CATALOG_CURSOR_HIDE:
        hidden_sprite = ((TownObject *)(object))->town->display->src;
        hidden_sprite->f6 = 0;
        hidden_sprite->f4 = 0;
        return;
    case CATALOG_CURSOR_POSITION:
        ((TownObject *)(object))->town->display->src->f8 = catalog_cursor_rows[((TownObject *)(object))->row];
        ((TownObject *)(object))->town->display->src->fA = catalog_cursor_columns[((TownObject *)(object))->index];
        break;
    default:
        return;
    }
    ((TownObject *)(object))->town->display->dst->f6 = ((TownObject *)(object))->town->display->src->f8;
    ((TownObject *)(object))->town->display->dst->f8 = ((TownObject *)(object))->town->display->src->fA;
    source_sprite = ((TownObject *)(object))->town->display->src;
    source_sprite->f6 = 0x800;
    source_sprite->f4 = 0x800;

    return;
}
