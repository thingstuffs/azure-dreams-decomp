#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *func_80033BE4(void);
extern void func_80033C1C(void *, s32);
extern void func_80033C84(void *);
extern void *func_8003FC64(s32);
extern void func_8003FFF0(void *);
extern void func_80040044(void *);
extern void func_8008B818(s32, void *, void *, void *);
extern s8 D_800CFC2C;
extern s8 D_800FC418;

s32 func_8008B654(s32 arg0, s32 arg1) {
    register s32 count;
    void *objects[11];
    void *resources[11];
    void **object_write;
    void **resource_write;
    void *allocated;
    void *resource;
    count = 0;
    object_write = objects;
    resource_write = resources;
    while (1) {
        allocated = func_8003FC64(0x11);
        if (allocated == 0) {
            break;
        }
        resource = func_80033BE4();
        if (resource == 0) {
            break;
        }
        func_80033C1C(resource, 0);
        *object_write++ = allocated;
        *resource_write++ = resource;
        count++;
        if (count >= 11) {
            break;
        }
    }

    if (count < 11) {
        if (object_write != objects) {
            do {
                --object_write;
                func_8003FFF0(*object_write);
                func_80040044(*object_write);
            } while (object_write != objects);
            ++object_write;
        }
        if (resource_write != resources) {
            do {
                --resource_write;
                func_80033C84(*resource_write);
            } while (resource_write != resources);
        }
        return 0;
    }

    object_write = objects;
    resource_write = resources;
    count = 0;
    {
        s8 *order = &D_800CFC2C;
        while (1) {
            s8 slot = *(s8 *)(count + (s32)order);
            void *other_data;
            if (slot == count) {
                other_data = 0;
            } else {
                other_data = (u8 *)objects[slot] + 0x20;
            }
            {
                struct object_data {
                    u8 pad[0x74];
                    s32 field_74;
                    s32 field_78;
                    s32 field_7c;
                } *data = (struct object_data *)((u8 *)*object_write + 0x20);
                data->field_74 = 0;
                data->field_78 = arg1;
                data->field_7c = arg0;
                func_8008B818(count++, other_data, *object_write++, *resource_write++);
            }
            if (count >= 11) {
                D_800FC418 = 0;
                return 1;
            }
        }
    }
}
