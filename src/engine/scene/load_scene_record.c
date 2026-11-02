#include "common.h"
#include "engine/graphics.h"
#include "engine/scene.h"

extern void *create_catalog_display_node(void *a0);

/* Load the scene data, store the allocated node, and return it to the task dispatcher. */
void *load_scene_record(void *data)
{
    SceneLoadBody *record = data;
    void *node;

    scene_load_texture_and_data_pair(&record->unk_0C);
    node = create_catalog_display_node(record->task);
    record->result = node;
    return node;
}
