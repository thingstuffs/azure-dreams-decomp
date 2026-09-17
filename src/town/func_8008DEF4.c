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

s32 town_map_set(s32 value_7c, s32 value_78)
{
    s32 objects[12];
    s32 resources[12];
    s32 index = 0;
    s32 *object_slot = objects;
    s32 *resource_slot = resources;
    s32 *array_start;
    s32 new_object;
    s32 new_resource;
    s32 link_index;
    s32 linked_data;
    s8 *object_data;

    do {
        new_object = func_8003FC64(0x11);
        if (new_object == 0) {
            break;
        }
        new_resource = func_80033BE4();
        if (new_resource == 0) {
            break;
        }
        func_80033C1C(new_resource, 0);
        *object_slot++ = new_object;
        *resource_slot++ = new_resource;
        index++;
    } while (index < 11);

    if (index < 11) {
        if (object_slot != objects) {
            array_start = objects;
            do {
                object_slot--;
                func_8003FFF0(*object_slot);
                func_80040044(*object_slot);
            } while (object_slot != array_start);
        }
        if (resource_slot != resources) {
            array_start = resources;
            do {
                resource_slot--;
                func_80033C84(*resource_slot);
            } while (resource_slot != array_start);
        }
        return 0;
    }

    object_slot = objects;
    resource_slot = resources;
    index = 0;
    do {
        link_index = D_800CFC2C[index];
        if (link_index == index) {
            linked_data = 0;
        } else {
            linked_data = objects[link_index] + 0x20;
        }
        object_data = (s8 *)(*object_slot + 0x20);
        *(s32 *)(object_data + 0x74) = 0;
        *(s32 *)(object_data + 0x78) = value_78;
        *(s32 *)(object_data + 0x7C) = value_7c;
        func_8008B818(index, linked_data, *object_slot++, *resource_slot++);
        index++;
    } while (index < 11);
    D_800FC418 = 0;
    return 1;
}
