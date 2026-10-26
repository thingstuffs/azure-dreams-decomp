#include "common.h"
#include "engine/node.h"
#include "slus/data.h"

/* Registers a node under an existing or newly allocated registration ID. */
s32 register_node(ObjectNodeHeader *entry, void *registration_id)
{
    s32 slot;
    s32 first_free;
    s32 last_free;
    s32 no_slot;
    ObjectNodeHeader *head;
    s32 success;

    first_free = -1;
    last_free = 0;
    slot = last_free;
    no_slot = first_free;

    for (; slot < 0x20; slot++) {
        if (registered_draw_callbacks[slot] == registration_id) {
            head = registered_draw_objects[slot];
            entry->chain_next = head;
            if (head != 0) {
                head->draw_prev = entry;
                registered_draw_objects[slot] = entry;
            } else {
                registered_draw_objects[slot] = entry;
            }
            success = 1;
            entry->draw_prev = (ObjectNodeHeader *)&registered_draw_objects[slot];
            entry->draw_slot = slot;
            return success;
        }
        if (registered_draw_callbacks[slot] == 0) {
            if (first_free == no_slot) {
                first_free = slot;
            }
            last_free = slot;
        }
    }

    if (first_free >= 0) {
        entry->chain_next = 0;
        if (node_registration_ids[0] != 0) {
            s32 preferred_index = 0;
            do {
                if (node_registration_ids[preferred_index] == registration_id) {
                    registered_draw_callbacks[first_free] = registration_id;
                    registered_draw_objects[first_free] = entry;
                    success = 1;
                    entry->draw_prev = (ObjectNodeHeader *)&registered_draw_objects[first_free];
                    entry->draw_slot = first_free;
                    return success;
                }
                preferred_index++;
            } while (node_registration_ids[preferred_index] != 0);
        }

        registered_draw_callbacks[last_free] = registration_id;
        registered_draw_objects[last_free] = entry;
        success = 1;
        entry->draw_prev = (ObjectNodeHeader *)&registered_draw_objects[last_free];
        entry->draw_slot = last_free;
        return success;
    }
    return 0;
}
