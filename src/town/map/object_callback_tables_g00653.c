/* Initializes a town object, replaces table callbacks, and dispatches the callback entries. */
/* inferred-strong object_callback_tables_g00653; joins PD:town/engine:800D4668; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D4668. */
#include "town/map/object_callback_tables_g00653.h"
#include "shared/object_node.h"
#include "town/map.h"
#include "town/map/trigger_callbacks.h"

/* Initializes an object and replaces the callbacks in the active table entries. */
void install_map_trigger_handlers(void) {
    Callback *callback_slot = (Callback *)town_map_callback_entries;
    ObjectNodeHeader *object = allocate_flagged_object_node(0x11);

    if (object != 0) {
        object->update_callback = D_800C1E50;
        if (town_map_callback_entries[0].handler != 0) {
            do {
                *callback_slot = (Callback)trigger_entity_action_when_allowed;
                callback_slot += 6;
            } while (*callback_slot != 0);
        }
    }
}

/* Invoke each callback with its entry address until the null terminator. */
void run_map_trigger_callbacks(void) {
    Callback *callback;

    callback = (Callback *)town_map_callback_entries;
    if (*callback != 0) {
        do {
            (*callback)((map_trigger_record *)callback);
            callback += 6;
        } while (*callback != 0);
    }
}
