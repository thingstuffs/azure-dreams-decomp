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


void func_800233D0(void *arg0)
{
    u8 *cursor;
    void *base4;
    void *source0;
    void *source1;
    s32 result;
    s32 index;
    s32 offset;

    result = func_80049E6C(3);
    index = 0;
    source0 = D_80077EF0;
    source1 = D_80077EFC;
    base4 = (u8 *)arg0 + 4;
    offset = 0x90;
    ((S_800233D0_2 *)(((Rec_func_800233D0_arg0 *)arg0)->unk_1A0))->unk_00 = result;
    ((S_800233D0_3 *)(((Rec_func_800233D0_arg0 *)arg0)->unk_1A4))->unk_00 = D_80077E84;
    cursor = arg0;
    do {
        ((S_800233D0_4 *)(((S_800233D0_1 *)cursor)->unk_1A8))->unk_00 = source0;
        ((S_800233D0_5 *)(((S_800233D0_1 *)cursor)->unk_1B8))->unk_00 = source1;
        ((S_800233D0_6 *)(((S_800233D0_1 *)cursor)->unk_1C8))->unk_00 = base4;
        ((S_800233D0_7 *)(((S_800233D0_1 *)cursor)->unk_1D8))->unk_00 = (u8 *)arg0 + offset;
        offset += 0x48;
        index++;
        cursor += 4;
    } while (index < 3);
}
