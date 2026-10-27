#include "common.h"
#include "shared/item_menu.h"
#include "engine/graphics.h"

/* S_8002E5E8: 3-field vector-like struct (x,y,z), source data copied into target entities' ->vec */


extern DisplayPositionWords display_vector_defaults;



/* Copies all three words of display_vector_defaults into each object vector. */
void apply_vector_3_template_to_nodes(ItemMenuPart **objects, s32 object_count)
{
    s32 object_index;

    for (object_index = 0; object_index < object_count; object_index++, objects++) {
        (*objects)->vector->unk0 = display_vector_defaults.unk0;
        (*objects)->vector->unk4 = display_vector_defaults.unk4;
        (*objects)->vector->unk8 = display_vector_defaults.unk8;
    }
}
