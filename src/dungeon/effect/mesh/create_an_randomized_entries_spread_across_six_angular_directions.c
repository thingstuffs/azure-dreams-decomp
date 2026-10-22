#include "common.h"
#include "shared/object_node.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_81977B40_0 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_81977B40_0;   /* object in create_an_n_30_randomized_entries_spread_across_six_angular_directions */

typedef struct S_81977B40_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0x14];
    s32 unk_20;
    u8 pad_24[0x22];
    s16 unk_46;
    u8 pad_48[0x3A];
    s16 unk_82;
} S_81977B40_1;   /* base in create_an_n_30_randomized_entries_spread_across_six_angular_directions */

extern void *allocate_list_node();
extern void register_node();
extern s32 rand();

extern u8 D_80024D84[9];
extern u8 D_800251E8[9];

typedef struct S_81977B40_2 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A[30];
    s16 unk_46[30];
    s16 unk_82[30];
} S_81977B40_2;   /* object data in create_an_n_30_randomized_entries_spread_across_six_angular_directions */

/* Creates an object with 30 randomized entries spread across six angular directions. */
void create_an_n_30_randomized_entries_spread_across_six_angular_directions(void *source_data)
{
    s32 entry_index;
    ObjectNodeHeader *object;
    S_81977B40_2 *data;

    object = allocate_list_node(0x212, ((u8 *)(&scene_object_list_anchor)));
    entry_index = 0;
    if (object != NULL) {
        object->unk_10 = D_800251E8;
        data = (S_81977B40_2 *)((u8 *)object + 0x20);
        ((S_81977B40_0 *)object)->unk_20 = ((S_81977B40_1 *)source_data)->unk_20;
        data->unk_04 = 0;
        data->unk_06 = 0;
        data->unk_08 = 0;
        do {
            data->unk_0A[entry_index] = 0;
            data->unk_46[entry_index] = ((entry_index % 6) * 0x2AA) + (rand() % 33) - 0x10;
            data->unk_82[entry_index] = (rand() % 9) - 4;
            entry_index++;
        } while (entry_index < 0x1E);
        register_node(object, D_80024D84);
    }
}
