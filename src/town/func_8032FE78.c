#include "common.h"

typedef struct S_8001A678_0 {
    u8 pad_00[0x8];
    union { u32 s; s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x10];
    void * unk_1C;
    u8 pad_20[0x10];
    void * unk_30;
} S_8001A678_0;   /* root in func_8001A678 */

typedef struct S_8001A678_1 {
    void * unk_00;
} S_8001A678_1;   /* entry_ptr in func_8001A678 */

typedef struct S_8001A678_2 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
} S_8001A678_2;   /* (void *)index in func_8001A678 */

typedef struct S_8001A678_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8001A678_3;   /* position in func_8001A678 */



extern u8 *D_80016000;

void func_8001A678(s32 unused, u32 arg1, u32 arg2)
{
    u8 *root = D_80016000;
    S_8001A678_1 *entry_ptr;
    S_8001A678_3 *position;
    u32 index;
    s32 value1;
    s32 value2;

    entry_ptr = ((S_8001A678_0 *)root)->unk_30;
    index = ((S_8001A678_0 *)root)->unk_08.s;
    do {
        index <<= 5;
    } while (0);
    do {
        entry_ptr = entry_ptr->unk_00;
    } while (0);
    index += (u32)entry_ptr;
    position = ((S_8001A678_0 *)root)->unk_1C;
    do {
        arg1 <<= 6;
    } while (0);
    value1 = ((S_8001A678_2 *)((void *)index))->unk_0C;
    value1 += 0x20;
    arg1 += value1;
    position->unk_04 = arg1;
    root = ((S_8001A678_0 *)root)->unk_1C;
    do {
        arg2 <<= 6;
    } while (0);
    value2 = ((S_8001A678_2 *)((void *)index))->unk_0E;
    value2 += 0x20;
    arg2 += value2;
    ((S_8001A678_0 *)root)->unk_08.u = arg2;
}
