#include "common.h"

extern s32 func_80033BE4(void);
extern void func_80033C1C(s32, s32);
extern void func_80033C84(s32);
extern s32 func_8003FC64(s32);
extern void func_8003FFF0(s32);
extern void func_80040044(s32);
extern void func_8008B818(s32, s32, s32, s32);
extern s8 D_800CFC2C[11];
extern u8 D_800FC418;

/* town_map_set: allocate and initialize eleven linked map objects and their resources. */
s32 func_8008B654(s32 value_7c, s32 value_78) {
    s32 objects[12];
    s32 resources[12];
    s32 *object_slot;
    s32 *resource_slot;
    s32 *array_start;
    s32 object_index;
    s32 linked_data;
    s32 object_arg;
    s32 resource_arg;
    s32 new_object;
    s32 new_resource;
    s32 index;
    register s32 incomplete ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 hard_zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s8 *link_indices;
    s8 link_index;
    s8 *object_data;

    index = 0;
    object_slot = objects;
    resource_slot = resources;
allocate_pair:
    new_object = func_8003FC64(0x11);
    incomplete = index < 0xB;
    if (new_object != 0) {
        new_resource = func_80033BE4();
        ASM_KEEP_NV(new_resource);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        if ((new_resource == 0) || (func_80033C1C(new_resource, 0), *object_slot = new_object, object_slot += 1, *resource_slot = new_resource, ({ ASM_KEEP(new_resource); 0; }), index += 1, resource_slot += 1, ((index < 0xB) == 0))) {
            incomplete = index < 0xB;
        } else {
            goto allocate_pair;
        }
    }
    if (incomplete != 0) {
        if (object_slot != objects) {
            array_start = objects;
            do {
                object_slot -= 1;
                func_8003FFF0(*object_slot);
                func_80040044(*object_slot);
            } while (object_slot != array_start);
        }
        if (resource_slot != resources) {
            array_start = resources;
            do {
                resource_slot -= 1;
                func_80033C84(*resource_slot);
            } while (resource_slot != array_start);
        }
        return 0;
    }
    object_slot = objects;
    resource_slot = resources;
    index = hard_zero;
    link_indices = D_800CFC2C;
    do {
        link_index = *(s8 *)((u32)index + (u32)link_indices);
        if (link_index == index) {
            linked_data = 0;
        } else {
            linked_data = objects[link_index] + 0x20;
        }
        object_index = index;
        index += 1;
        object_data = (s8 *)(*object_slot + 0x20);
        *(s32 *)(object_data + 0x74) = 0;
        *(s32 *)(object_data + 0x78) = value_78;
        *(s32 *)(object_data + 0x7C) = value_7c;
        object_arg = *object_slot;
        object_slot += 1;
        resource_arg = *resource_slot;
        resource_slot += 1;
        func_8008B818(object_index, linked_data, object_arg, resource_arg);
    } while (index < 0xB);
    D_800FC418 = 0;
    return 1;
}
