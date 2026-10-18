#include "modules/dungeon_ovl_1831cd8.h"

void *create_menu_child_object(s32 parent_obj, s32 descriptor_value)
{
    ovl_1831cd8_8181345C_Obj8181345C *obj;
    ovl_1831cd8_8181345C_Sub8181345C *sub;

    obj = func_8003FC64(0);
    sub = &obj->sub;
    if (obj != 0) {
        if (allocate_menu_object_buffers(sub, 15) != 0) {
            obj->field0C = (u8 *)obj + 0x98;
            sub->field84 = build_menu_entry_chain(sub->field88);
            initialize_menu_object_from_data(sub, parent_obj, descriptor_value);
            func_8004491C(obj, (void *)func_8004CAA0);
            clear_menu_embedded_state(obj);
        } else {
            func_8004B248((u8 *)obj + 0xAC);
            obj->flags |= 0x8000;
            obj = 0;
            object_flag_block.flags |= 0x8000;
        }
    }
    return obj;
}
