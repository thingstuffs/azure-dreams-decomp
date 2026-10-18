#include "modules/dungeon_ovl_1830850.h"

ovl_1830850_81811168_DungeonObj81811168 *inventory_allocate_and_initialize_child(s32 parent_obj, s32 initial_value, s32 text_addr)
{
    ovl_1830850_81811168_DungeonObj81811168 *obj;
    ovl_1830850_81811168_DungeonSub81811168 *state;

    obj = (ovl_1830850_81811168_DungeonObj81811168 *)func_8003FC64(0);
    state = &obj->sub20;
    if (obj != 0) {
        if (inventory_copy_state_vector_after_buffers(state, 13) != 0) {
            obj->field0C = (u8 *)obj + 0x64;
            state->value50 = (s32)inventory_create_context_entry_13(state->value54);
            inventory_initialize_object_from_embedded_data(state, parent_obj, initial_value, text_addr);
            func_8004491C(obj, (void *)func_8004CAA0);
            inventory_set_embedded_state_one(obj);
        } else {
            func_8004B248((u8 *)obj + 0x78);
            obj->flags1E |= 0x8000;
            obj = 0;
            object_flag_block.flags |= 0x8000;
        }
    }
    return obj;
}
