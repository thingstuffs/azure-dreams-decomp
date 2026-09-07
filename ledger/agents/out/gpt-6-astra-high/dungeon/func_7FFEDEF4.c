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

/* Allocate and initialize eleven linked objects and their resources. */
s32 func_8008B654(s32 value_7c, s32 value_78) {
    register s32 count;
    void *objects[11];
    void *resources[11];
    void **object_cursor;
    void **resource_cursor;
    void *object;
    void *resource;
    count = 0;
    object_cursor = objects;
    resource_cursor = resources;
    while (1) {
        object = func_8003FC64(0x11);
        if (object == 0) {
            break;
        }
        resource = func_80033BE4();
        if (resource == 0) {
            break;
        }
        func_80033C1C(resource, 0);
        *object_cursor++ = object;
        *resource_cursor++ = resource;
        count++;
        if (count >= 11) {
            break;
        }
    }

    if (count < 11) {
        if (object_cursor != objects) {
            do {
                --object_cursor;
                func_8003FFF0(*object_cursor);
                func_80040044(*object_cursor);
            } while (object_cursor != objects);
            ++object_cursor;
        }
        if (resource_cursor != resources) {
            do {
                --resource_cursor;
                func_80033C84(*resource_cursor);
            } while (resource_cursor != resources);
        }
        return 0;
    }

    object_cursor = objects;
    resource_cursor = resources;
    count = 0;
    {
        s8 *link_slots = &D_800CFC2C;
        while (1) {
            s8 linked_slot = *(s8 *)(count + (s32)link_slots);
            void *linked_data;
            if (linked_slot == count) {
                linked_data = 0;
            } else {
                linked_data = (u8 *)objects[linked_slot] + 0x20;
            }
            {
                struct object_data {
                    u8 pad[0x74];
                    s32 field_74;
                    s32 field_78;
                    s32 field_7c;
                } *payload = (struct object_data *)((u8 *)*object_cursor + 0x20);
                payload->field_74 = 0;
                payload->field_78 = value_78;
                payload->field_7c = value_7c;
                func_8008B818(count++, linked_data, *object_cursor++, *resource_cursor++);
            }
            if (count >= 11) {
                D_800FC418 = 0;
                return 1;
            }
        }
    }
}
