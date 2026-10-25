#include "town/menu/catalog.h"
#include "common.h"

typedef struct HalfFields {
    u8 pad0[4];
    u16 field4;
    u16 field6;
    u16 field8;
    u16 fieldA;
} HalfFields;

typedef struct Pair {
    u8 pad0[4];
    HalfFields *first;
    HalfFields *second;
} Pair;

typedef struct Pool {
    u32 *slots[97];
    Pair *pair;
} Pool;

typedef struct TownObject {
    u8 pad0[4];
    s16 state;
    u8 pad6[9];
    u8 digit;
    u8 side;
    u8 pad11[0x47];
    Pool *pool;
} TownObject;

extern u8 is_catalog_entry_available(u8 value);
extern u32 catalog_normal_digits[];
extern u16 catalog_cursor_rows[];
extern u16 catalog_cursor_columns;
extern u8 catalog_number_marker[];

/* Updates the object's number display and paired fields for its current state. */
void animate_catalog_final_category_cursor(TownObject *obj)
{
    s32 side_offset;
    s32 entry_index;
    s32 slot_index;
    s32 index_base;
    s32 side_stride16;
    s32 side_stride8;
    Pair *pair;
    HalfFields *primary;
    HalfFields *secondary;

    switch (((TownObject *)(obj))->state) {
    case CATALOG_CURSOR_NUMBER:
        index_base = 1 - ((TownObject *)(obj))->side;
        side_stride8 = index_base << 3;
        side_stride16 = index_base << 4;
        side_offset = side_stride16 + side_stride8;
        slot_index = side_offset + 33;
        index_base = ((TownObject *)(obj))->digit << 4;
        index_base = index_base + 1;
        entry_index = index_base - ((TownObject *)(obj))->side;

        if (is_catalog_entry_available((u8)entry_index) != 0) {
            s32 display_number = entry_index + 1;

            *((TownObject *)(obj))->pool->slots[slot_index] = (u32)catalog_number_marker;
            slot_index = side_offset + 34;
            *((TownObject *)(obj))->pool->slots[slot_index] = catalog_normal_digits[display_number / 10];
            slot_index = side_offset + 35;
            *((TownObject *)(obj))->pool->slots[slot_index] = catalog_normal_digits[display_number % 10];
        }
        break;

    case CATALOG_CURSOR_HIDE:
    {
        HalfFields *first_pair = ((TownObject *)(obj))->pool->pair->first;
        first_pair->field6 = 0;
        first_pair->field4 = 0;
        return;
    }

    case CATALOG_CURSOR_POSITION:
        ((TownObject *)(obj))->pool->pair->first->field8 = catalog_cursor_rows[((TownObject *)(obj))->side];
        ((TownObject *)(obj))->pool->pair->first->fieldA = catalog_cursor_columns;
        break;

    default:
        return;
    }

    pair = ((TownObject *)(obj))->pool->pair;
    primary = pair->first;
    secondary = pair->second;
    secondary->field6 = primary->field8;
    pair = ((TownObject *)(obj))->pool->pair;
    primary = pair->first;
    secondary = pair->second;
    secondary->field8 = primary->fieldA;
    primary = ((TownObject *)(obj))->pool->pair->first;
    primary->field6 = 0x800;
    primary->field4 = 0x800;
}
