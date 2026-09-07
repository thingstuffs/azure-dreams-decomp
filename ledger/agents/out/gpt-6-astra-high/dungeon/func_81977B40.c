#include "common.h"

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
extern u8 D_80083498[9];

/* Creates an object with 30 randomized entries spread across six angular directions. */
void func_81977B40(void *source_data)
{
    s16 angle;
    s32 angle_roll;
    s32 offset_roll;
    s32 parent;
    s32 entry_index;
    void *object;
    u8 *cursor;
    u8 *object_data;

    cursor = source_data;
    object = func_8003FD64(0x212, D_80083498);
    entry_index = 0;
    if (object != NULL) {
        do { ((S_81977B40_0 *)object)->unk_10 = D_800251E8; } while (0);
        object_data = (u8 *)object + 0x20;
        ASM_KEEP(object_data);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        parent = ((S_81977B40_1 *)cursor)->unk_20;
        cursor = object_data;
        ((S_81977B40_0 *)object)->unk_20 = parent;
        ((S_81977B40_1 *)cursor)->unk_04 = 0;
        ((S_81977B40_1 *)cursor)->unk_06 = 0;
        ((S_81977B40_1 *)cursor)->unk_08 = 0;
        do {
            ((S_81977B40_1 *)cursor)->unk_0A = 0;
            angle_roll = rand();
            angle = ((entry_index % 6) * 0x2AA) + (angle_roll % 33) - 0x10;
            ((S_81977B40_1 *)cursor)->unk_46 = angle;
            offset_roll = rand();
            entry_index++;
            ((S_81977B40_1 *)cursor)->unk_82 = (offset_roll % 9) - 4;
            cursor += 2;
        } while (entry_index < 0x1E);
        func_8004491C(object, D_80024D84);
    }
}
