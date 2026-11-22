#include "common.h"
#include "engine/node.h"
#include "shared/object_node.h"
#include "engine/scene.h"
#include "frontend/settings.h"
#include "main/data.h"

/* Initializes an available record with a value and 40 bytes of data, then submits it for processing. */
void create_settings_value_entry(void (*update)(MainTitleValueEntry *), const MainTitleValueEntry *data) {
    ObjectNodeHeader *record;
    MainTitleValueEntry *entry;

    record = allocate_flagged_object_node(1);
    if (record != 0) {
        entry = NODE_BODY(record);
        *entry = *data;
        record->update_callback = update;
        register_node(record, &display_registration_tag);
    }
}
