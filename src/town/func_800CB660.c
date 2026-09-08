#define ARG0_TYPE s16
#define ARG1_TYPE s16
#define ARG2_TYPE s16
#define ARG3_TYPE s16
#include "common.h"
typedef struct Header { u8 pad_00[2]; s16 field_02; u8 pad_04[2]; s16 field_06; u8 pad_08[2]; s16 field_0A; } Header;
typedef struct Work { u8 pad_00[0x6C]; s16 field_6C; u8 pad_6E[0x28]; s8 field_96; } Work;
typedef struct Node { u8 pad_00[8]; Header *header; s32 aux; u8 pad_10[0x10]; Work work; } Node;
extern s32 func_80033B2C(s32); extern void func_80033CD8(Work *, void *); extern Node *func_8009C390(void *, s32, void *, void *); extern s16 func_800C2AE8(Header *); extern void func_800C2E84(Work *, s32, void *);
extern s32 D_80045340; extern u8 D_80083498[]; extern u8 D_800C8E9C[]; extern u8 D_800C8F80[]; extern u8 D_800D620C[];
/* Creates a node and initializes its header and work data. */
void func_800C8DC0(ARG0_TYPE work_value, ARG1_TYPE work_byte, ARG2_TYPE header_value_02, ARG3_TYPE header_value_06)
{
    Node *node;
    Header *header;
    Work *work;
    s32 node_aux;
    if (func_80033B2C(1) == 0) return;
    node = func_8009C390(D_80083498, 0, D_800C8E9C, D_800C8F80);
    if (node == 0) return;
    header = node->header;
    node_aux = node->aux;
    work = &node->work;
    work->field_6C = work_value;
    work->field_96 = work_byte;
    header->field_02 = header_value_02;
    header->field_06 = header_value_06;
    header->field_0A = func_800C2AE8(header);
    func_800C2E84(work, node_aux, D_800D620C);
    func_80033CD8(work, &D_80045340);
}
