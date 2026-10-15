#include "modules/dungeon_floor_generate.h"

s32 func_80019684(s16 object_index, s16 mode, s16 activate) {
    s16 activate_flag = activate;
    u16 saved_index = 0;
    register s16 saved_object_index = object_index;
    s16 saved_mode = mode;
    s16 activate_tail = (s16)activate_flag;
    s32 object_offset = (s32)object_index << 16;
    floor_generate_isolated_80286684_Object **objects = D_8006E704;
    floor_generate_isolated_80286684_Object **slot =
        (floor_generate_isolated_80286684_Object **)((u8 *)objects + (object_offset >> 14));
    floor_generate_isolated_80286684_Object **buffers = D_80080AF4;
    u16 buffer_index;
    floor_generate_isolated_80286684_Object *requested_object;
    floor_generate_isolated_80286684_Object *header_object;
    floor_generate_isolated_80286684_Object *load_object;
    u32 header;
    u32 buffer_addr;
    u32 mask_2;
    if (*slot == buffers[D_80080AFC]) {
        return 1;
    }

    if ((func_80019894(1) << 16) != 0) {
        func_8004425C(0xC);
    }
    {
        buffer_addr = (u32)(activate_flag << 16);
        if ((s32)buffer_addr == 0) {
            saved_index = (u16)D_80080AFC;
        }
    }

    buffer_index = (u16)D_80080AFC;
    requested_object = *slot;
    buffer_index ^= 1;
    D_80080AFC = buffer_index;
    if (requested_object != buffers[(s16)buffer_index]) {
        if (D_80080AF3 != (s16)mode) {
            func_80044698();
        }

        header_object = *slot;
        mask_2 = 0xFF800000;
        header_object->field_0 &= mask_2;
        load_object = *slot;
        header = load_object->field_0;
        {
            if (D_80080AFC != 0) {
                buffer_addr = (u32)D_801C4640 & 0x007FFFFF;
            } else {
                buffer_addr = (u32)D_801BEE40 & 0x007FFFFF;
            }
            header |= buffer_addr;
            buffer_addr = header;
        }
        {
            register s32 reload_left;
            register s32 reload_offset;
            register floor_generate_isolated_80286684_Object **reload_objects;
            s16 cd_command = 6;
            reload_left = (s32)saved_object_index << 16;
            load_object->field_0 = buffer_addr;
            reload_objects = D_8006E704;
            reload_offset = reload_left >> 14;
            {
                floor_generate_isolated_80286684_Object **reload_slot = (floor_generate_isolated_80286684_Object **)((u8 *)reload_objects + reload_offset);
                Control_CD(cd_command, *reload_slot, 0);
                D_80080AF4[D_80080AFC] = *reload_slot;
            }
            func_8003F320();
        }
    }

    func_8004450C(saved_mode);
    {
        s32 activate_tail_test =
            (s32)activate_tail << 16;
        if (activate_tail_test != 0) {
            s32 sound_command = 0x21;
            if (D_80080AFC != 0) {
                sound_command = 0x22;
            }
            SD_Call(sound_command);
            return 0;
        }
    }

    D_80080AFC = saved_index;
    return 0;
}
