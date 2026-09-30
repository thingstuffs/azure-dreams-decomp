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
} S_81977B40_0;   /* object in func_81977B40 */

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
} S_81977B40_1;   /* base in func_81977B40 */


extern void *func_8003FD64();
extern void func_8004491C();
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
} S_81977B40_2;   /* object data in func_81977B40 */

/* Creates an object with 30 randomized entries spread across six angular directions. */
void func_81977B40(void *source_data)
{
    s32 entry_index;
    void *object;
    S_81977B40_2 *data;

    object = func_8003FD64(0x212, ((u8 *)(&D_80083498)));
    entry_index = 0;
    if (object != NULL) {
        ((S_81977B40_0 *)object)->unk_10 = D_800251E8;
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
        func_8004491C(object, D_80024D84);
    }
}
