#include "shared/object_node.h"
#include "common.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "frontend/settings.h"
#include "main/data.h"

/* Initializes a node with its callback address and 48 bytes of data, then submits it. */
void create_settings_color_effect(void (*update)(ColorEffect *), const ColorEffect *data) {
    ObjectNodeHeader *record;
    ColorEffect *effect;

    record = allocate_flagged_object_node(1);
    if (record != 0) {
        effect = NODE_BODY(record);
        *effect = *data;
        record->update_callback = update;
        register_node(record, &text_sprite_builder_address);
    }
}
