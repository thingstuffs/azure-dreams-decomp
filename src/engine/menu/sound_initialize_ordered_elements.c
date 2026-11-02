#include "engine/menu/gp_order_bytes_owner.h"

#include "common.h"

u8 menu_element_order[4] = { 1, 3, 2, 4 };

#include "engine/menu/gp_order_bytes_owner.h"
#include "engine/menu.h"

/* Initializes four menu elements and links them in the order listed by menu_element_order. */
void sound_initialize_ordered_elements(AnimatedMenuPanelBody *obj)
{
    s32 i;
    AnimatedPanelLink *tail;
    AnimatedPanelLink *next;
    u8 *order;
    u8 elem_index;
    s32 end_marker;

    obj->vector.unk0 = display_vector_defaults.f0;
    obj->vector.unk4 = display_vector_defaults.f4;
    obj->vector.unk8 = display_vector_defaults.f8;
    for (i = 0; i < 4; i++) {
        obj->elements[i].block.words[0] = display_block_defaults.f0;
        obj->elements[i].block.words[1] = display_block_defaults.f4;
        obj->elements[i].block.words[2] = display_block_defaults.f8;
        obj->elements[i].block.words[3] = display_block_defaults.fC;
        obj->elements[i].link.self = &obj->elements[i];
        obj->elements[i].link.parent = &obj->vector.unk0;
    }

    tail = &obj->elements[0].link;
    elem_index = menu_element_order[0];
    end_marker = 4;
    if (elem_index != end_marker) {
        s32 expected_marker;

        expected_marker = end_marker;
        order = menu_element_order;
        do {
            elem_index = *(order++);
            next = &obj->elements[elem_index].link;
            tail->next = next;
            tail = next;
        } while (*order != expected_marker);
    }
    tail->next = 0;
}
