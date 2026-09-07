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
    register Entity *self ASM_REG("$11");
    register s32 node_index ASM_REG("$7");
    u8 *slot_base;
    u8 *pointer_cursor;
    s32 node_offset;
    s32 data_offset;
    Template3 *common;
    u8 *source_page;
    Template4 *data_template;
    s32 template_word_0;
    s32 template_word_1;
    s32 template_word_2;
    s32 template_word_3;

    self = entity;
    ASM_KEEP(self);
    node_index = 0;
    if (node_count > 0) {
#ifdef NON_MATCHING
        source_page = (u8 *)&D_8002E5D8 + 0x1A28;
#else
        source_page = (u8 *)0x80030000;
#endif
        ASM_KEEP(source_page);
        data_template = (Template4 *)(source_page - 0x1A28);
        common = &self->common;
        data_offset = 0x958;
        slot_base = (u8 *)self;
        node_offset = 0x8E8;
        pointer_cursor = (u8 *)self;
        do {
            Template4 *data;

            data = (Template4 *)((u8 *)self + data_offset);
            data_offset += 0x10;
            template_word_0 = *(s32 *)(source_page - 0x1A28);
            *(Node **)(pointer_cursor + 0x8CC) =
                (Node *)((u8 *)self + node_offset);
            *(s32 *)(slot_base + 0x958) = template_word_0;
            template_word_1 = data_template->unk4;
            node_offset += 0x10;
            *(s32 *)(slot_base + 0x95C) = template_word_1;
            template_word_2 = data_template->unk8;
            pointer_cursor += 4;
            *(s32 *)(slot_base + 0x960) = template_word_2;
            template_word_3 = data_template->unkC;
            node_index++;
            *(Template4 **)(slot_base + 0x8EC) = data;
            *(Template3 **)(slot_base + 0x8F0) = common;
            *(s32 *)(slot_base + 0x964) = template_word_3;
            slot_base += 0x10;
        } while (node_index < node_count);
    }

    self->common.unk0 = D_8002E5E8.unk0;
    self->common.unk4 = D_8002E5E8.unk4;
    self->common.unk8 = D_8002E5E8.unk8;
}
