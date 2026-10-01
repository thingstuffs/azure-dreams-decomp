#include "common.h"
#include "shared/record_ptrs.h"

typedef struct S_8001A7F4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    void * unk_1C;
} S_8001A7F4_0;   /* base in func_8001A7F4 */

typedef struct S_8001A7F4_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8001A7F4_1;   /* dst in func_8001A7F4 */


/* Scale and offset the two coordinates stored in the global destination. */
void func_8001A7F4(s32 unused, s32 x, s32 y)
{
    void *base;

    (void)unused;
    base = *(void **)((s8 *)(&D_80016000));
    ((S_8001A7F4_1 *)((S_8001A7F4_0 *)base)->unk_1C)->unk_04 = (x << 6) / 10 + 0x220;
    ((S_8001A7F4_0 *)((S_8001A7F4_0 *)base)->unk_1C)->unk_08 = (y << 6) / 10 + 0x220;
}

