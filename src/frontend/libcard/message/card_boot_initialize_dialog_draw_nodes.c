#include "common.h"
#include "frontend/libcard/message.h"

typedef struct Template4 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Template4;

typedef struct Template3 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Template3;

typedef struct Node {
    s32 unk0;
    Template4 *data;
    Template3 *common;
    s32 unkC;
} Node;

typedef struct Entity {
    u8 pad0[0x8B0];
    Template3 common;
    u8 pad1[0x8CC - 0x8BC];
    Node *ptr_array[7];
    Node node_array[7];
    Template4 data_array[7];
} Entity;

extern Template4 display_block_defaults;
extern Template3 display_vector_defaults;

/* Initialize entity nodes with template data and link them to shared common data. */
void card_boot_initialize_dialog_draw_nodes(Entity *entity, s32 node_count)
{
    s32 i;
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;

    for (i = 0; i < node_count; i++) {
        w0 = display_block_defaults.unk0;
        entity->ptr_array[i] = &entity->node_array[i];
        entity->data_array[i].unk0 = w0;
        w1 = display_block_defaults.unk4;
        entity->data_array[i].unk4 = w1;
        w2 = display_block_defaults.unk8;
        entity->data_array[i].unk8 = w2;
        w3 = display_block_defaults.unkC;
        entity->node_array[i].data = &entity->data_array[i];
        entity->node_array[i].common = &entity->common;
        entity->data_array[i].unkC = w3;
    }
    entity->common.unk0 = display_vector_defaults.unk0;
    entity->common.unk4 = display_vector_defaults.unk4;
    entity->common.unk8 = display_vector_defaults.unk8;
}
