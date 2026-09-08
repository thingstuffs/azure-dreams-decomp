#include "common.h"
#include "records/Rec_D_800E3D7C.h"



typedef s32 M2C_UNK;

typedef struct S_800D6AD4_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800D6AD4_6;   /* temp_v0 in func_800D6AD4 */


typedef struct S_800D6AD4_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800D6AD4_8;   /* ((S_800D6AD4_6 *)temp_v0)->unk_08 in func_800D6AD4 */

typedef struct S_800D6AD4_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D6AD4_9;   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_800D6AD4 */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FD64();
extern M2C_UNK func_8004491C();
extern M2C_UNK D_800D6804[3];
extern M2C_UNK D_800D68F4[3];

typedef struct S_800D6AD4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800D6AD4_0;   /* temp_v0 in func_800D6AD4 */

typedef struct S_800D6AD4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800D6AD4_1;   /* temp_v1 in func_800D6AD4 */

typedef struct S_800D6AD4_2 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800D6AD4_2;   /* temp_v1_2 in func_800D6AD4 */

typedef struct S_800D6AD4_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800D6AD4_3;   /* temp_v1_3 in func_800D6AD4 */

typedef struct S_800D6AD4_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800D6AD4_4;   /* temp_v0_2 in func_800D6AD4 */

typedef struct S_800D6AD4_5 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    s16 unk_34;
} S_800D6AD4_5;   /* temp_s0 in func_800D6AD4 */

void func_800D6AD4(Rec_D_800E3D7C *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5) {
    s32 held_arg4 = arg4;
    s32 held_arg5 = arg5;
    s32 temp_a2;
    S_800D6AD4_5 *temp_s0;
    void *temp_v0;
    S_800D6AD4_4 *temp_v0_2;
    S_800D6AD4_1 *temp_v1;
    S_800D6AD4_2 *temp_v1_2;
    S_800D6AD4_3 *temp_v1_3;

    temp_v0 = func_8003FD64(0x211, arg0);
    if (temp_v0 != 0) {
        ((S_800D6AD4_0 *)temp_v0)->unk_10 = D_800D6804;
        ((S_800D6AD4_8 *)(((S_800D6AD4_6 *)temp_v0)->unk_08))->unk_02 =
            (u16)((S_800D6AD4_9 *)(arg0->unk_08.at00_pv.v))->unk_02;
        ((S_800D6AD4_8 *)(((S_800D6AD4_6 *)temp_v0)->unk_08))->unk_06 =
            (u16)((S_800D6AD4_9 *)(arg0->unk_08.at00_pv.v))->unk_06;
        ((S_800D6AD4_8 *)(((S_800D6AD4_6 *)temp_v0)->unk_08))->unk_0A =
            (u16)((S_800D6AD4_9 *)(arg0->unk_08.at00_pv.v))->unk_0A;
        temp_v1 = ((S_800D6AD4_0 *)temp_v0)->unk_08;
        temp_v1->unk_02 =
            (u16)(temp_v1->unk_02 + arg2);
        temp_v1_2 = ((S_800D6AD4_0 *)temp_v0)->unk_08;
        temp_v1_2->unk_06 =
            (u16)(temp_v1_2->unk_06 + arg3);
        temp_v1_3 = ((S_800D6AD4_0 *)temp_v0)->unk_08;
        temp_a2 = held_arg5 << 0x12;
        temp_v1_3->unk_0A =
            (u16)(temp_v1_3->unk_0A + held_arg4);
        temp_v0_2 = ((S_800D6AD4_0 *)temp_v0)->unk_08;
        temp_s0 = temp_v0 + 0x20;
        temp_v0_2->unk_10 = 0;
        temp_v0_2->unk_0C = 0;
        ((S_800D6AD4_8 *)(((S_800D6AD4_6 *)temp_v0)->unk_08))->unk_14 =
            (s32)(0xFFFA0000 - temp_a2);
        temp_s0->unk_32 = 0x14;
        temp_s0->unk_34 = 0x14;
        func_8004491C(temp_v0, D_800D68F4, temp_a2);
        ((S_800D6AD4_0 *)temp_v0)->unk_20 = arg1;
        temp_s0->unk_08 = arg1;
        ASM_KEEP(held_arg4);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(held_arg5);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    }
}
