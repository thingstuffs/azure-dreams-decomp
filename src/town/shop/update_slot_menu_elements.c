#include "common.h"
#include "m2c_compat.h"
#include "town/person/entity_display_owner_g00624.h"
#include "engine/util.h"
#include "town/shop.h"
#include "shared/item_menu.h"

/*
 * Updates four display elements in the selected slot from the owner and layout, creating paired
 * text values with modes one and 0x90 and offsetting the second copy by (-1, +1).
 */
void update_slot_menu_elements(StorageMenuObject *owner, EntityDisplayLayout *layout, s32 slot_index) {
    s32 slot_offset;
    ItemMenuPart *element;

    slot_offset = slot_index;
    element = (owner->parts + slot_offset)[0];
    element->handler = owner->data;
    element->position->x = (u16)layout->unk_04;
    element->position->y = (u16)layout->unk_06;
    element = (owner->parts + slot_offset)[12];
    element->handler = layout->unk_10;
    element->position->x = (u16)layout->unk_08;
    element->position->y = (u16)layout->unk_0A;
    element = (owner->parts + slot_offset)[6];
    element->handler = create_label_glyph_entries(layout->unk_00, 1);
    element->position->x = (u16)layout->unk_0C;
    element->position->y = (u16)layout->unk_0E;
    element = (owner->parts + slot_offset)[18];
    element->handler = create_label_glyph_entries(layout->unk_00, 0x90);
    element->position->x = (s16)(layout->unk_0C - 1);
    element->position->y = (s16)(layout->unk_0E + 1);
}
