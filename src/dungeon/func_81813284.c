#include "modules/dungeon_ovl_1831cd8.h"

s32 allocate_menu_object_buffers(ovl_1831cd8_81813284_Unk818110CC *object, s32 buffer_param)
{
    s32 success = 0;
    s32 *buffers = object->unk8C;
    s32 allocated_buffer;

    allocated_buffer = func_80049004(buffers, buffer_param, 8);
    object->unk88 = allocated_buffer;
    if (allocated_buffer != 0) {
        allocated_buffer = func_80048FBC(buffers, 8);
        object->unk4C = allocated_buffer;
        if (allocated_buffer != 0) {
            object->unk6C[0] = D_8002E5E8.unk0;
            object->unk6C[1] = D_8002E5E8.unk4;
            object->unk6C[2] = D_8002E5E8.unk8;
            texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(object->unk88, object->unk6C, 15);
            success = 1;
        }
    }
    return success;
}
