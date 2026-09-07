#include "common.h"

typedef struct S_818D4D48_0 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
} S_818D4D48_0;   /* held_arg0 in func_818D4D48; pointer addresses record offset 0x2 */

typedef struct S_818D4D48_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
} S_818D4D48_1;   /* arg2 in func_818D4D48 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

extern s16 D_80025118;
extern s32 D_800814A0[3];

void func_818D4D48(void *arg0, M2C_UNK arg1, S_818D4D48_1 *arg2)
{
    void *held_arg0 = arg0;
    u16 temp_a0;
    u16 temp_count;
    u16 temp_v1;

    temp_count = ((S_818D4D48_0 *)((u8 *)held_arg0 - 0x2))->unk_04;
    D_80025118 = 1;
    ((S_818D4D48_0 *)((u8 *)held_arg0 - 0x2))->unk_04 = (u16)(temp_count - 1);

    arg2->unk_0C = (u8)((arg2->unk_0C * 0xA) / 13);
    arg2->unk_0D = (u8)((arg2->unk_0D * 0xA) / 13);
    arg2->unk_0E = (u8)((arg2->unk_0E * 0xA) / 13);

    temp_a0 = arg2->unk_1A;
    temp_v1 = temp_a0 + 0x300;
    arg2->unk_1A = temp_v1;

    if ((u32)(temp_v1 & 0xFFFF) >= 0x1001U) {
        arg2->unk_1A = (u16)(temp_a0 - 0xD00);
    }

    if ((s16)((S_818D4D48_0 *)((u8 *)held_arg0 - 0x2))->unk_04 <= 0) {
        ((S_818D4D48_0 *)((u8 *)held_arg0 - 0x2))->unk_00 = (u16)(((S_818D4D48_0 *)((u8 *)held_arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }

    if (arg2->unk_14 & 0x8000) {
        ((S_818D4D48_0 *)((u8 *)held_arg0 - 0x2))->unk_00 = (u16)(((S_818D4D48_0 *)((u8 *)held_arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
    
}

/* MECHANISM: The frameless leaf uses only its compiler-required 0x10 scratch frame and holds
   arg0 in a3 for the full tail. Splitting the count RMW around D_80025118's store keeps the
   global page in a0 and the division magic in a1, reproducing retail's early schedule. */
