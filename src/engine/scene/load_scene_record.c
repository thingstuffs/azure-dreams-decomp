#include "common.h"
#include "engine/graphics.h"
#include "engine/scene.h"

extern s32 allocate_and_initialize_node_2(void *a0);

typedef struct S_800510A0 {
    s32 unk0;
    void *unk4;
    s32 unk8;
    s32 unkC;
} S_800510A0;

/* Processes the record's unkC field and stores the result for unk4 in unk8. */
void load_scene_record(S_800510A0 *record)
{
    scene_load_texture_and_data_pair(&record->unkC);
    record->unk8 = allocate_and_initialize_node_2(record->unk4);
}
