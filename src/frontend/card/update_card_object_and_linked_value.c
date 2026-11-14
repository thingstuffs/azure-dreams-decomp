#include "shared/object_node.h"
#include "common.h"
#include "shared/object_links.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"

void update_linked_object_value_and_flags(void *object);                      /* extern */

/* Run the object update and invoke its follow-up when flag 0x2000 is set. */
void update_card_object_and_linked_value(void *object_data, s32 first_value, s32 second_value) {
    u16 object_flags;
    func_80047938(object_data, first_value, second_value);
    object_flags = ((ObjectNodeHeader *)object_data - 1)->flags;
    object_data = (s8 *) object_data - 0x20;
    if (object_flags & 0x2000) {
        update_linked_object_value_and_flags(object_data);
    }
}
