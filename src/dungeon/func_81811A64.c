#include "modules/dungeon_ovl_1831370.h"

void *allocate_initialized_child_object(s32 parent_object, s32 type_code, s32 config_value) {
    u8 *object;
    u8 *state;

    object = func_8003FC64(0);
    state = object + 0x20;
    if (object != 0) {
        if (get_and_position_object_handle(state) != 0) {
            *(void **)(object + 0xC) = object + 0x80;
            *(s32 *)(state + 0x6C) = (s32)forward_value_to_shared_helper(*(S_800491F4 ***)(state + 0x70));
            initialize_embedded_object_state(state, parent_object, type_code, config_value);
            func_8004491C(object, func_8004CAA0);
        } else {
            func_8004B1A4(*(s32 *)(state + 0x74));
            *(u16 *)(object + 0x1E) |= 0x8000;
            object = 0;
            object_flag_block.flags |= 0x8000;
        }
    }
    return object;
}
