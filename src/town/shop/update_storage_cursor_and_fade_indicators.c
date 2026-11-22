#include "town/person/four_slot_object_owner_g00628.h"
#include "engine/graphics.h"
#include "town/shop/item/update_item_menu_record_g01150.h"

void update_storage_cursor_and_fade_indicators(StorageDisplayBody *object)
{
    advance_timed_tagged_stream(&object->cursor);
    fade_color_to_gray(object->parts[38], 0);
    fade_color_to_gray(object->parts[39], 0);
}
