#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80171020_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80171020_4;   /* temp_v0 in func_80171020 */


typedef struct S_80171020_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80171020_6;   /* ((S_80171020_4 *)temp_v0)->unk_08 in func_80171020 */

typedef struct S_80171020_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80171020_7;   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_80171020 */




void *func_8003FD64();
M2C_UNK func_8004491C();
s32 rand();
extern M2C_UNK D_80170D2C;
extern M2C_UNK D_80170F0C;

typedef struct S_80171020_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80171020_0;   /* temp_v0 in func_80171020 */

typedef struct S_80171020_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0xA];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x8];
    s32 unk_54;
} S_80171020_1;   /* temp_s0 in func_80171020 */

typedef struct S_80171020_2 {
    s32 unk_00;
} S_80171020_2;   /* temp_a2 in func_80171020 */

typedef struct S_80171020_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80171020_3;   /* temp_a2_2 in func_80171020 */

void func_80171020(Rec_D_800E3D7C *arg0, s16 arg1, s32 arg2, s32 arg3, volatile s32 arg4, volatile s32 arg5, volatile s32 arg6) {
    register s32 temp_s2 = arg4;
    register s32 temp_s3 = arg5;
    register s32 temp_s4 = arg6;
    register s16 temp_s5 = arg1;
    register s32 temp_s6 = arg2;
    S_80171020_2 *temp_a2;
    S_80171020_3 *temp_a2_2;
    S_80171020_1 *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x211, arg0);
    if (temp_v0 == NULL) {
        return;
    }
        ((S_80171020_0 *)temp_v0)->unk_10 = &D_80170F0C;
        ((S_80171020_6 *)(((S_80171020_4 *)temp_v0)->unk_08))->unk_02 = (s16) (((S_80171020_7 *)(arg0->unk_08.at00_pv.v))->unk_02 + temp_s2);
        ((S_80171020_6 *)(((S_80171020_4 *)temp_v0)->unk_08))->unk_06 = (s16) (((S_80171020_7 *)(arg0->unk_08.at00_pv.v))->unk_06 + temp_s3);
        ((S_80171020_6 *)(((S_80171020_4 *)temp_v0)->unk_08))->unk_0A = (s16) (((S_80171020_7 *)(arg0->unk_08.at00_pv.v))->unk_0A + temp_s4);
        temp_s0 = temp_v0 + 0x20;
        temp_s0->unk_40 = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        temp_s0->unk_44 = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        temp_s0->unk_48 = (s32) (((rand() & 0x3FFF) - 0x6000) * 0x10);
        temp_a2 = ((S_80171020_0 *)temp_v0)->unk_08;
        temp_a2->unk_00 = (s32) (temp_a2->unk_00 + (temp_s0->unk_40 * 2));
        temp_a2_2 = ((S_80171020_0 *)temp_v0)->unk_08;
        temp_a2_2->unk_04 = (s32) (temp_a2_2->unk_04 + (temp_s0->unk_44 * 2));
        temp_s0->unk_54 = 0x8000;
        temp_s0->unk_14 = temp_s5;
        temp_s0->unk_32 = 0x14;
        temp_s0->unk_34 = 0x14;
        func_8004491C(temp_v0, &D_80170D2C, temp_a2_2);
        ((S_80171020_0 *)temp_v0)->unk_20 = temp_s6;
    temp_s0->unk_08 = temp_s6;
}
