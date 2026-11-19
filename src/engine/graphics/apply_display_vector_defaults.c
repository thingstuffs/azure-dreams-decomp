#include "common.h"
#include "shared/menu_display.h"
#include "shared/item_menu.h"
#include "engine/graphics.h"

/* Copies all three words of display_vector_defaults into each object vector. */
void apply_display_vector_defaults(ItemMenuPart **objects, s32 object_count)
{
    s32 object_index;

    for (object_index = 0; object_index < object_count; object_index++, objects++) {
        (*objects)->vector->unk0 = display_vector_defaults.unk0;
        (*objects)->vector->unk4 = display_vector_defaults.unk4;
        (*objects)->vector->unk8 = display_vector_defaults.unk8;
    }
}
