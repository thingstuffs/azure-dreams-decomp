#include "shared/object_node.h"
#include "common.h"
#include "frontend/card.h"
#include "frontend/card/load.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/server_imports.h"

#ifndef NULL
#define NULL 0
#endif

/* Allocates and initializes an object and installs its callback. */
CardDevLoadNode *card_dev_create_load_screen(ObjectNodeHeader *request, s32 mode) {
    CardDevLoadNode *object;

    object = allocate_card_object_8003C480(0);
    if (object != NULL) {
        object->body.mode = mode;
        card_dev_load_forward_object_value(&object->body, request);
        card_dev_run_temp_slot_operation();
        card_dev_cache_slot_summary();
        object->body.background = init_card_background_object(&object->node, 0);
        object->body.information = init_card_info_object(&object->node, object->body.selection);
        object->body.slot_display = init_card_sme_object(object);
        object->body.window_count = 0;
        object->node.update_callback = card_dev_build_load_slot_windows;
    }
    return object;
}
