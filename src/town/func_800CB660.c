#define ARG0_TYPE s16
#define ARG1_TYPE s16
#define ARG2_TYPE s16
#define ARG3_TYPE s16
#include "common.h"
#include "shared/position_views.h"

typedef struct Work { u8 pad_00[0x6C]; s16 field_6C; u8 pad_6E[0x28]; s8 field_96; } Work;
typedef struct Node { u8 pad_00[8]; SignedPositionView *header; s32 aux; u8 pad_10[0x10]; Work work; } Node;
extern s32 test_resident_bitmap_bit(s32);
extern void func_80033CD8(Work * , void *);
extern Node * create_town_effect_object(void * , s32, void * , void *);
extern s16 query_lowered_transform_position(SignedPositionView *);
extern void initialize_object_entries(Work * , s32, void *);
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_800C8E9C[];
extern u8 D_800C8F80[];
extern u8 D_800D620C[];
/* mia_storker_set: Creates a node and initializes its header and work data. */
void mia_storker_set(ARG0_TYPE work_value, ARG1_TYPE work_byte, ARG2_TYPE header_value_02, ARG3_TYPE header_value_06)
{
    Node *node;
    SignedPositionView *header;
    Work *work;
    s32 node_aux;
    if (test_resident_bitmap_bit(1) == 0)
        return;
    node = create_town_effect_object(D_80083498, 0, D_800C8E9C, D_800C8F80);
    if (node == 0)
        return;
    header = node->header;
    node_aux = node->aux;
    work = &node->work;
    work->field_6C = work_value;
    work->field_96 = work_byte;
    header->unk_02 = header_value_02;
    header->unk_06 = header_value_06;
    header->unk_0A = query_lowered_transform_position(header);
    initialize_object_entries(work, node_aux, D_800D620C);
    func_80033CD8(work, &D_80045340);
}
