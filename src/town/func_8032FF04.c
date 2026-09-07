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

void func_8001A704(s32 arg0, s32 arg1, s32 arg2)
{
    volatile u8 *root = D_80016000;
    void *entry_ptr;
    register void *position ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
    s32 index;
    s32 value;

    entry_ptr = (*(void *volatile *)((u8 *)root + 0x30));
    index = (*(volatile s32 *)((u8 *)root + 8));
    index <<= 5;
    entry_ptr = (*(void *volatile *)((u8 *)entry_ptr + 0));
    ASM_KEEP(entry_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
    index += (s32)entry_ptr;
    position = (*(void *volatile *)((u8 *)root + 0x1C));
    ASM_KEEP(position);   /* MATCH pin: retail schedule: same instructions, different order without it */
    arg1 <<= 5;
    value = ((S_8001A704_0 *)((void *)index))->unk_0C;
    ASM_KEEP(value);   /* MATCH pin: retail schedule: same instructions, different order without it */
    arg1 += value;
    ((S_8001A704_1 *)position)->unk_04 = arg1;
    {
        register void *position2 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

        position2 = (*(void *volatile *)((u8 *)root + 0x1C));
        ASM_KEEP(position2);   /* MATCH pin: retail schedule: same instructions, different order without it */
        arg2 <<= 5;
        value = ((S_8001A704_0 *)((void *)index))->unk_0E;
        ASM_KEEP(value);   /* MATCH pin: retail schedule: same instructions, different order without it */
        arg2 += value;
        ((S_8001A704_2 *)position2)->unk_08 = arg2;
    }
}

/* MECHANISM: Frameless leaf; volatile pointer-chain reads plus zero-byte keeps
   preserve three load-delay gaps. Guarded pins encode the measured v0/v1/a3
   roles, while a block-local destination reuses the dead root in a0. */
