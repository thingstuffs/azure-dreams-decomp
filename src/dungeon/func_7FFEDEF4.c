#include "modules/dungeon_town_map.h"

s32 town_map_set(s32 value_7c, s32 value_78) {
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
        resource = runtimeFindUnusedPoolSlot();
        if (resource == 0) {
            break;
        }
        runtimeInitializeStateValue(resource, 0);
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
                unlinkActiveNode(*object_cursor);
                pushNodeOntoFreeList(*object_cursor);
            } while (object_cursor != objects);
            ++object_cursor;
        }
        if (resource_cursor != resources) {
            do {
                --resource_cursor;
                runtimeClearValue(*resource_cursor);
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
