#include "engine/menu/gp_order_bytes_owner.h"

#include "common.h"

u8 menu_element_order[4] = { 1, 3, 2, 4 };

#include "engine/menu/gp_order_bytes_owner.h"
#include "engine/menu.h"

/* Initializes four menu elements and links them in the order listed by menu_element_order. */
void sound_initialize_ordered_elements(S_80049F68_Obj *obj)
{
    s32 i;
    S_80049F68_Link *tail;
    S_80049F68_Link *next;
    u8 *order;
    u8 elem_index;
    s32 end_marker;

    obj->unkA0 = display_vector_defaults.f0;
    obj->unkA4 = display_vector_defaults.f4;
    obj->unkA8 = display_vector_defaults.f8;
    for (i = 0; i < 4; i++) {
        obj->elem[i].f00 = display_block_defaults.f0;
        obj->elem[i].f04 = display_block_defaults.f4;
        obj->elem[i].f08 = display_block_defaults.f8;
        obj->elem[i].f0C = display_block_defaults.fC;
        obj->elem[i].link.self = &obj->elem[i];
        obj->elem[i].link.parent = &obj->unkA0;
    }

    tail = &obj->elem[0].link;
    elem_index = menu_element_order[0];
    end_marker = 4;
    if (elem_index != end_marker) {
        s32 expected_marker;

        expected_marker = end_marker;
        order = menu_element_order;
        do {
            elem_index = *(order++);
            next = &obj->elem[elem_index].link;
            tail->next = next;
            tail = next;
        } while (*order != expected_marker);
    }
    tail->next = 0;
}
