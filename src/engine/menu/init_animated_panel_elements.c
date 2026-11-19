#include "engine/menu/gp_order_bytes_owner.h"

#include "common.h"

u8 menu_element_order[4] = { 1, 3, 2, 4 };

#include "engine/menu.h"

/* Initializes four menu elements and links them in the order listed by menu_element_order. */
void init_animated_panel_elements(AnimatedMenuPanelBody *obj)
{
    s32 i;
    AnimatedPanelLink *tail;
    AnimatedPanelLink *next;
    u8 *order;
    u8 elem_index;
    s32 end_marker;

    obj->vector.unk0 = display_vector_defaults.unk0;
    obj->vector.unk4 = display_vector_defaults.unk4;
    obj->vector.unk8 = display_vector_defaults.unk8;
    for (i = 0; i < 4; i++) {
        obj->elements[i].block.words[0] = display_block_defaults.words[0];
        obj->elements[i].block.words[1] = display_block_defaults.words[1];
        obj->elements[i].block.words[2] = display_block_defaults.words[2];
        obj->elements[i].block.words[3] = display_block_defaults.words[3];
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
