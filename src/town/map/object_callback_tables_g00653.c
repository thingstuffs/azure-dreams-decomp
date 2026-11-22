/* Initializes a town object, replaces table callbacks, and dispatches the callback entries. */
/* inferred-strong object_callback_tables_g00653; joins PD:town/engine:800D4668; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D4668. */
#include "town/map/object_callback_tables_g00653.h"
#include "shared/object_node.h"
#include "town/map.h"
#include "town/map/trigger_callbacks.h"

/* Initializes an object and replaces the callbacks in the active table entries. */
void install_map_trigger_handlers(void) {
    map_trigger_record *entry = town_map_callback_entries;
    ObjectNodeHeader *object = allocate_flagged_object_node(0x11);

    if (object != 0) {
        object->update_callback = D_800C1E50;
        if (entry->handler != 0) {
            do {
                entry->handler = trigger_entity_action_when_allowed;
                entry++;
            } while (entry->handler != 0);
        }
    }
}

/* Invoke each callback with its entry address until the null terminator. */
void run_map_trigger_callbacks(void) {
    map_trigger_record *entry = town_map_callback_entries;
    if (entry->handler != 0) {
        do {
            entry->handler(entry);
            entry++;
        } while (entry->handler != 0);
    }
}
