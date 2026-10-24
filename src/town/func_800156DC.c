/* Relink of matched town/func_800B1C0C; one recorded literal variant; all other changed words are paired relocations. */
#include "common.h"
#include "shared/item_menu.h"

/* Owning menu state as this copy lays it out: the selected position is read from +0x24
 * (set_item_menu_entry_coordinates reads ItemMenuState.position at +0x18). */
typedef struct ItemMenuStatePosition24View {
    u8 pad_00[0x24];
    s32 position;
} ItemMenuStatePosition24View;

/* Places the selection cursor pair (parts 4 and 5) on the entry chosen by the last decimal digit
 * of the selected position: two columns of five rows. */
void position_decimal_digit_parts(ItemMenuObject *object) {
    s32 slot;
    s32 column;

    slot = ((ItemMenuStatePosition24View *)object->menu)->position % 10;
    column = slot / 5;
    object->parts[4]->position->x = (column << 7) - 0x38;
    object->parts[4]->position->y = ((slot - column * 5) << 4) + 8;
    object->parts[5]->position->x = object->parts[4]->position->x + 0x38;
    object->parts[5]->position->y = object->parts[4]->position->y - 9;
}
