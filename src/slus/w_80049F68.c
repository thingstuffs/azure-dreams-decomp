#include "slus/gp_order_bytes_owner.h"

void soundInitializeOrderedElements(S_80049F68_Obj *obj)
{
    s32 i;
    S_80049F68_Link *tail;
    S_80049F68_Link *next;
    u8 *order;
    u8 elem_index;
    s32 end_marker;

    obj->unkA0 = D_8002E5E8.f0;
    obj->unkA4 = D_8002E5E8.f4;
    obj->unkA8 = D_8002E5E8.f8;
    for (i = 0; i < 4; i++) {
        obj->elem[i].f00 = D_8002E5D8.f0;
        obj->elem[i].f04 = D_8002E5D8.f4;
        obj->elem[i].f08 = D_8002E5D8.f8;
        obj->elem[i].f0C = D_8002E5D8.fC;
        obj->elem[i].link.self = &obj->elem[i];
        obj->elem[i].link.parent = &obj->unkA0;
    }

    tail = &obj->elem[0].link;
    elem_index = D_80080B30[0];
    end_marker = 4;
    if (elem_index != end_marker) {
        s32 expected_marker;

        expected_marker = end_marker;
        order = D_80080B30;
        do {
            elem_index = *(order++);
            next = &obj->elem[elem_index].link;
            tail->next = next;
            tail = next;
        } while (*order != expected_marker);
    }
    tail->next = 0;
}
