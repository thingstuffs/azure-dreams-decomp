#include "common.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/message.h"
#include "frontend/card/server_aliases.h"

typedef struct {
    s32 word_index;
    s32 unk4;
    s32 index;
} Struct8001B74C_arg0;

/* Resolve and apply the last table entry when the object's table is enabled. */
void layout_last_row_item(Struct8001B74C_arg0 *object) {
    s32 resolved_a;
    s32 resolved_b;
    s32 resolved_c;
    s32 table_index = object->index;
    s32 last_index = D_80408ADD[table_index][0] - 1;

    if (D_80408ADD[table_index][1] != 0) {
        find_text_word_bounds(card_layout_text_items[table_index][last_index], object->word_index, &resolved_a, &resolved_b, &resolved_c);
        position_object_record_and_update_row(object, resolved_a, resolved_b, last_index, resolved_c);
    }
}
