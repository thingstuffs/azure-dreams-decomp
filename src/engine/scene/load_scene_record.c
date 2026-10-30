#include "common.h"
#include "engine/graphics.h"
#include "engine/scene.h"

extern void *create_catalog_display_node(void *a0);

typedef struct S_800510A0 {
    s32 unk0;
    void *unk4;
    void *unk8;
    s32 unkC;
} S_800510A0;

/* Load the scene data, store the allocated node, and return it to the task dispatcher. */
void *load_scene_record(void *data)
{
    S_800510A0 *record = data;
    void *node;

    scene_load_texture_and_data_pair(&record->unkC);
    node = create_catalog_display_node(record->unk4);
    record->unk8 = node;
    return node;
}
