#include "common.h"
#include "records/Rec_D_800E3D7C.h"



#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

typedef struct S_80164ED0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80164ED0_2;   /* temp_v0 in func_80164ED0 */


typedef struct S_80164ED0_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80164ED0_4;   /* ((S_80164ED0_2 *)temp_v0)->unk_08 in func_80164ED0 */

typedef struct S_80164ED0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80164ED0_5;   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_80164ED0 */

typedef struct S_80164ED0_6 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80164ED0_6;   /* ((S_80164ED0_2 *)temp_v0)->unk_0C in func_80164ED0 */


void *func_8003FD64();
M2C_UNK func_8004491C();
s32 rand();
extern u8 D_80164BC4[];
extern u8 D_80164DA4[];

typedef struct S_80164ED0_0 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80164ED0_0;   /* temp_v0 in func_80164ED0 */

typedef struct S_80164ED0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    s16 unk_34;
} S_80164ED0_1;   /* temp_s0 in func_80164ED0 */

void func_80164ED0(Rec_D_800E3D7C *arg0, s32 arg1, s16 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    register s32 held_arg4 ASM_REG("$19") = arg4;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 held_arg5 ASM_REG("$20") = arg5;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    S_80164ED0_1 *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x211, arg0);
    if (temp_v0 != NULL) {
        ((S_80164ED0_0 *)temp_v0)->unk_10 = D_80164DA4;
        ((S_80164ED0_4 *)(((S_80164ED0_2 *)temp_v0)->unk_08))->unk_02 = (s16)
            (((S_80164ED0_5 *)(arg0->unk_08.at00_pv.v))->unk_02 + arg3);
        ((S_80164ED0_4 *)(((S_80164ED0_2 *)temp_v0)->unk_08))->unk_06 = (s16)
            (((S_80164ED0_5 *)(arg0->unk_08.at00_pv.v))->unk_06 + held_arg4);
        ((S_80164ED0_4 *)(((S_80164ED0_2 *)temp_v0)->unk_08))->unk_0A = (s16)
            (((S_80164ED0_5 *)(arg0->unk_08.at00_pv.v))->unk_0A + held_arg5);
        ((S_80164ED0_6 *)(((S_80164ED0_2 *)temp_v0)->unk_0C))->unk_06 = 6;
        ((S_80164ED0_4 *)(((S_80164ED0_2 *)temp_v0)->unk_08))->unk_0C = (s32)
            (((rand() & 0x7FFF) - 0x4000) << 6);
        ((S_80164ED0_4 *)(((S_80164ED0_2 *)temp_v0)->unk_08))->unk_10 = (s32)
            (((rand() & 0x7FFF) - 0x4000) << 6);
        temp_s0 = temp_v0 + 0x20;
        ((S_80164ED0_4 *)(((S_80164ED0_2 *)temp_v0)->unk_08))->unk_14 = (s32)
            (((rand() & 0x7FFF) - 0x4000) << 6);
        temp_s0->unk_32 = arg2;
        temp_s0->unk_34 = arg2;
        func_8004491C(temp_v0, D_80164BC4);
        ((S_80164ED0_0 *)temp_v0)->unk_20 = arg1;
        temp_s0->unk_08 = arg1;
    }
}
