#include "common.h"

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

extern Template4 D_8002E5D8;
extern Template3 D_8002E5E8;

/* Initialize entity nodes with template data and link them to shared common data. */
void func_80022B48(Entity *entity, s32 node_count)
{
    s32 i;
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;

    for (i = 0; i < node_count; i++) {
        w0 = D_8002E5D8.unk0;
        entity->ptr_array[i] = &entity->node_array[i];
        entity->data_array[i].unk0 = w0;
        w1 = D_8002E5D8.unk4;
        entity->data_array[i].unk4 = w1;
        w2 = D_8002E5D8.unk8;
        entity->data_array[i].unk8 = w2;
        w3 = D_8002E5D8.unkC;
        entity->node_array[i].data = &entity->data_array[i];
        entity->node_array[i].common = &entity->common;
        entity->data_array[i].unkC = w3;
    }
    entity->common.unk0 = D_8002E5E8.unk0;
    entity->common.unk4 = D_8002E5E8.unk4;
    entity->common.unk8 = D_8002E5E8.unk8;
}
