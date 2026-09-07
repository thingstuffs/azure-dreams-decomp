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

void func_80022B48(Entity *arg0, s32 count)
{
    Entity *self;
    s32 index;
    u8 *data_base;
    u8 *pointer_base;
    s32 node_offset;
    s32 data_offset;
    Template3 *common;
    u8 *source_page;
    Template4 *source;
    s32 value0;
    s32 value1;
    s32 value2;
    s32 value3;

    self = arg0;
    if (count > 0) {
        index = 0;
        source_page = (u8 *)&D_8002E5D8 + 0x1A28;
        source = (Template4 *)(source_page - 0x1A28);
        common = &self->common;
        data_offset = 0x958;
        data_base = (u8 *)self;
        node_offset = 0x8E8;
        pointer_base = (u8 *)self;
        do {
            Template4 *data;

            data = (Template4 *)((u8 *)self + data_offset);
            data_offset += 0x10;
            value0 = *(s32 *)(source_page - 0x1A28);
            *(Node **)(pointer_base + 0x8CC) =
                (Node *)((u8 *)self + node_offset);
            *(s32 *)(data_base + 0x958) = value0;
            value1 = source->unk4;
            node_offset += 0x10;
            *(s32 *)(data_base + 0x95C) = value1;
            value2 = source->unk8;
            pointer_base += 4;
            *(s32 *)(data_base + 0x960) = value2;
            value3 = source->unkC;
            index++;
            *(Template4 **)(data_base + 0x8EC) = data;
            *(Template3 **)(data_base + 0x8F0) = common;
            *(s32 *)(data_base + 0x964) = value3;
            data_base += 0x10;
        } while (index < count);
    }

    self->common.unk0 = D_8002E5E8.unk0;
    self->common.unk4 = D_8002E5E8.unk4;
    self->common.unk8 = D_8002E5E8.unk8;
}
