#include "town/shop/item/update_item_menu_record_g01150.h"

/* Places the selection cursor pair (parts 4 and 5) on the entry chosen by the last decimal digit
 * of the selected position: two columns of five rows. */
void set_item_menu_entry_coordinates(TownObject *object) {
    s32 slot;
    s32 column;

    slot = object->inner->position % 10;
    column = slot / 5;
    object->parts[4]->position->x = (column << 7) - 0x38;
    object->parts[4]->position->y = ((slot - column * 5) << 4) + 8;
    object->parts[5]->position->x = object->parts[4]->position->x + 0x38;
    object->parts[5]->position->y = object->parts[4]->position->y - 9;
}
