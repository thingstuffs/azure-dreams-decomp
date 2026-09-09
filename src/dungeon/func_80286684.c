#include "common.h"

extern s32 func_80019894(s32);
extern void Control_CD(s32, void *, s32);
extern void func_8003F320(void);
extern void func_8004425C(s32);
extern void func_8004450C(s16);
extern void func_80044698(void);
extern void SD_Call(s32);

typedef struct Object {
    s32 field_0;
} Object;

extern Object *D_8006E704[];
extern Object *D_8006E704_remat[] __asm__("D_8006E704");
extern s8 D_80080AF3;
extern Object *D_80080AF4[2];
extern Object *D_80080AF4_fresh[2] __asm__("D_80080AF4");
extern s16 D_80080AFC;
extern s16 D_80080AFC_fresh __asm__("D_80080AFC");
extern s32 D_801BEE40[4];
extern s32 D_801C4640[4];

/* Loads an object into the alternate buffer and optionally activates it. */
s32 func_80019684(s16 object_index, s16 mode, s32 activate) {
    register s32 activate_flag ASM_REG("$18") = activate;
    u16 saved_index = ({ ASM_KEEP_NV(activate_flag); 0; });
    register s16 saved_object_index = object_index;
    s16 saved_mode = mode;
    s16 activate_tail = (s16)activate_flag;
    s32 object_offset = (s32)object_index << 16;
    Object **objects = D_8006E704;
    register Object **slot ASM_REG("$16") =
        (Object **)((u8 *)objects + (object_offset >> 14));
    Object **buffers = D_80080AF4;
    u16 buffer_index;
    Object *requested_object;
    register Object *header_object ASM_REG("$4");
    Object *load_object;
    u32 header;
    register u32 buffer_addr ASM_REG("$2");
    register u32 mask ASM_REG("$3");
    if (*slot == buffers[D_80080AFC]) {
        return 1;
    }

    if ((func_80019894(1) << 16) != 0) {
        func_8004425C(0xC);
    }
    {
        register s32 activate_test ASM_REG("$2") = activate_flag << 16;
        if (activate_test == 0) {
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
        mask = 0xFF800000;
        header_object->field_0 &= mask;
        load_object = *slot;
        header = load_object->field_0;
        {
            mask = 0x007F0000;
            if (D_80080AFC != 0) {
                mask |= 0xFFFF;
                buffer_addr = (u32)D_801C4640;
            } else {
                mask |= 0xFFFF;
                buffer_addr = (u32)D_801BEE40;
            }
            buffer_addr &= mask;
            buffer_addr = header | buffer_addr;
        }
        {
            register s32 reload_offset;
            register Object **reload_objects ASM_REG("$2");
            s32 cd_command = 6;
            ASM_KEEP_NV(cd_command);
            reload_offset = (s32)saved_object_index << 16;
            load_object->field_0 = buffer_addr;
            reload_objects = D_8006E704_remat;
            reload_offset >>= 14;
            slot = (Object **)((u8 *)reload_objects + reload_offset);
            Control_CD(cd_command, *slot, 0);
            D_80080AF4_fresh[D_80080AFC_fresh] = *slot;
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
