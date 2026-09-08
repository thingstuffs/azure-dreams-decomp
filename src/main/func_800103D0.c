#include "common.h"
#include "records/Rec_func_800233D0_arg0.h"


typedef struct S_800233D0_1 {
    u8 pad_00[0x1A8];
    void * unk_1A8;
    u8 pad_1AC[0xC];
    void * unk_1B8;
    u8 pad_1BC[0xC];
    void * unk_1C8;
    u8 pad_1CC[0xC];
    void * unk_1D8;
} S_800233D0_1;   /* cursor in func_800233D0 */

typedef struct S_800233D0_2 {
    s32 unk_00;
} S_800233D0_2;   /* ((Rec_func_800233D0_arg0 *)arg0)->unk_1A0 in func_800233D0 */

typedef struct S_800233D0_3 {
    void * unk_00;
} S_800233D0_3;   /* ((Rec_func_800233D0_arg0 *)arg0)->unk_1A4 in func_800233D0 */

typedef struct S_800233D0_4 {
    void * unk_00;
} S_800233D0_4;   /* ((S_800233D0_1 *)cursor)->unk_1A8 in func_800233D0 */

typedef struct S_800233D0_5 {
    void * unk_00;
} S_800233D0_5;   /* ((S_800233D0_1 *)cursor)->unk_1B8 in func_800233D0 */

typedef struct S_800233D0_6 {
    void * unk_00;
} S_800233D0_6;   /* ((S_800233D0_1 *)cursor)->unk_1C8 in func_800233D0 */

typedef struct S_800233D0_7 {
    void * unk_00;
} S_800233D0_7;   /* ((S_800233D0_1 *)cursor)->unk_1D8 in func_800233D0 */


extern s32 func_80049E6C(s32 kind);
extern u8 D_80077E84[];
extern u8 D_80077EF0[];
extern u8 D_80077EFC[];


/* Initialize the object's shared references and three data block references. */
void func_800233D0(void *object)
{
    u8 *slot_cursor;
    void *shared_data;
    void *primary_table;
    void *secondary_table;
    s32 kind_value;
    s32 slot_index;
    s32 block_offset;

    kind_value = func_80049E6C(3);
    slot_index = 0;
    primary_table = D_80077EF0;
    secondary_table = D_80077EFC;
    shared_data = (u8 *)object + 4;
    block_offset = 0x90;
    ((S_800233D0_2 *)(((Rec_func_800233D0_arg0 *)object)->unk_1A0))->unk_00 = kind_value;
    ((S_800233D0_3 *)(((Rec_func_800233D0_arg0 *)object)->unk_1A4))->unk_00 = D_80077E84;
    slot_cursor = object;
    do {
        ((S_800233D0_4 *)(((S_800233D0_1 *)slot_cursor)->unk_1A8))->unk_00 = primary_table;
        ((S_800233D0_5 *)(((S_800233D0_1 *)slot_cursor)->unk_1B8))->unk_00 = secondary_table;
        ((S_800233D0_6 *)(((S_800233D0_1 *)slot_cursor)->unk_1C8))->unk_00 = shared_data;
        ((S_800233D0_7 *)(((S_800233D0_1 *)slot_cursor)->unk_1D8))->unk_00 = (u8 *)object + block_offset;
        block_offset += 0x48;
        slot_index++;
        slot_cursor += 4;
    } while (slot_index < 3);
}
