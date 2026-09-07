#include "common.h"

typedef struct S_8002E5D8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} S_8002E5D8;

typedef struct S_8002E5E8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_8002E5E8;

extern S_8002E5D8 D_8002E5D8;
extern S_8002E5E8 D_8002E5E8;

typedef struct S_8004F330_Node {
    s32 unk0;
    S_8002E5D8 *unk4;
    S_8002E5E8 *unk8;
    s32 unkC;
} S_8004F330_Node;

typedef struct S_8004F330_Entity {
    u8 pad0[0x204];
    S_8002E5E8 hdr;
    u8 pad1[0x220 - 0x210];
    S_8004F330_Node *ptrArray[7];
    S_8004F330_Node nodeArray[7];
    S_8002E5D8 bodyArray[7];
} S_8004F330_Entity;

/* Initialize entity nodes with default bodies and a shared header. */
void func_8004F330(S_8004F330_Entity *entity, s32 node_count)
{
    register S_8004F330_Entity *self ASM_REG("$11") = entity;   /* MATCH pin: slus-diff */
    s32 node_index;
    register u8 *body_base ASM_REG("$6");   /* MATCH pin: slus-diff */
    register u8 *ptr_base ASM_REG("$8");   /* MATCH pin: slus-diff */
    register s32 node_offset ASM_REG("$9");   /* MATCH pin: slus-diff */
    register s32 body_offset ASM_REG("$10");   /* MATCH pin: slus-diff */
    S_8002E5E8 *hdr;
    u8 *template_page;
    register S_8002E5D8 *body_template ASM_REG("$12");   /* MATCH pin: slus-diff */
    s32 body_word_0;
    s32 body_word_1;
    s32 body_word_2;
    s32 body_word_3;

    ASM_USE(self);   /* MATCH pin: slus-diff */
    if (node_count > 0) {
        node_index = 0;
        template_page = (u8 *)0x80030000;
        ASM_KEEP(template_page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        body_template = (S_8002E5D8 *)(template_page - 0x1A28);
        hdr = &self->hdr;
        body_offset = 0x2AC;
        body_base = (u8 *)self;
        node_offset = 0x23C;
        ptr_base = (u8 *)self;
        do {
            S_8002E5D8 *body;

            body = (S_8002E5D8 *)((u8 *)self + body_offset);
            body_offset += 0x10;
            body_word_0 = *(s32 *)(template_page - 0x1A28);
            *(S_8004F330_Node **)(ptr_base + 0x220) =
                (S_8004F330_Node *)((u8 *)self + node_offset);
            *(s32 *)(body_base + 0x2AC) = body_word_0;
            body_word_1 = body_template->unk4;
            node_offset += 0x10;
            *(s32 *)(body_base + 0x2B0) = body_word_1;
            body_word_2 = body_template->unk8;
            ptr_base += 4;
            *(s32 *)(body_base + 0x2B4) = body_word_2;
            body_word_3 = body_template->unkC;
            node_index += 1;
            *(S_8002E5D8 **)(body_base + 0x240) = body;
            *(S_8002E5E8 **)(body_base + 0x244) = hdr;
            *(s32 *)(body_base + 0x2B8) = body_word_3;
            body_base += 0x10;
        } while (node_index < node_count);
    }

    self->hdr.unk0 = D_8002E5E8.unk0;
    self->hdr.unk4 = D_8002E5E8.unk4;
    self->hdr.unk8 = D_8002E5E8.unk8;
}
