#include "common.h"
#include "m2c_compat.h"
#include "shared/item_menu.h"

struct S8004CBFC_a1;
void initialize_scaled_entry_cursor(FrameState *state, struct S8004CBFC_a1 *entry, int *cursor);      /* extern */
extern M2C_UNK D_80071244;
extern struct S8004CBFC_a1 shop_cursor_template;


/* When the menu lists entries, start the cursor stream on part 4 and point part 5 at the cursor frame. */
void update_item_menu_enabled_record(ItemMenuObject *object) {
    if (object->menu->count != 0) {
        initialize_scaled_entry_cursor(&object->cursor, &shop_cursor_template, (int *)&object->parts[4]->handler);
        object->parts[5]->handler = &D_80071244;
    }
}
