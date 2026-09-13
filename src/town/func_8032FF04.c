#include "common.h"


extern u8 *volatile D_80016000;


typedef struct S_8001A704_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
} S_8001A704_0;   /* (void *)index in func_8001A704 */

typedef struct S_8001A704_1 {
    u8 pad_00[0x4];
    volatile s32 unk_04;
} S_8001A704_1;   /* position in func_8001A704 */

typedef struct S_8001A704_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8001A704_2;   /* position2 in func_8001A704 */

/* Set position coordinates to the selected entry's offsets plus scaled x and y. */
void func_8001A704(s32 unused, s32 x, s32 y)
{
    volatile u8 *root = D_80016000;
    void *entry_ptr;
    void *position;
    s32 index;
    s16 value;

    entry_ptr = (*(void *volatile *)((u8 *)root + 0x30));
    index = (*(volatile s32 *)((u8 *)root + 8));
    index <<= 5;
    entry_ptr = (*(void *volatile *)((u8 *)entry_ptr + 0));
    index += (s32)entry_ptr;
    position = (*(void *volatile *)((u8 *)root + 0x1C));
    x <<= 5;
    value = ((S_8001A704_0 *)((void *)index))->unk_0C;
    x += value;
    ((S_8001A704_1 *)position)->unk_04 = x;
    {
        void *position2;

        position2 = (*(void *volatile *)((u8 *)root + 0x1C));
        y <<= 5;
        value = ((S_8001A704_0 *)((void *)index))->unk_0E;
        y += value;
        ((S_8001A704_2 *)position2)->unk_08 = y;
    }
}

/* MECHANISM: Frameless leaf; volatile pointer-chain reads plus zero-byte keeps
   preserve three load-delay gaps. Guarded pins encode the measured v0/v1/a3
   roles, while a block-local destination reuses the dead root in a0. */
