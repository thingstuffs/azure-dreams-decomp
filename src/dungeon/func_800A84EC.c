#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80083498;
extern M2C_UNK D_800ADB8C;
extern M2C_UNK D_800ADBCC;

typedef struct S_800ADC4C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s8 * unk_20;
    u8 pad_24[0x4];
    s16 unk_28;
} S_800ADC4C_0;   /* temp_v0 in func_800ADC4C */

typedef struct S_800ADC4C_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800ADC4C_1;   /* temp_v1 in func_800ADC4C */


typedef struct S_800ADC4C_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800ADC4C_3;   /* temp_v0_2 in func_800ADC4C */

void *func_800ADC4C(Rec_D_800E3D7C *arg0, s32 arg1, s16 arg2, s8 *arg3) {
    S_800ADC4C_0 *temp_v0;
    S_800ADC4C_3 *temp_v0_2;
    S_800ADC4C_1 *temp_v1;

    temp_v0 = func_8003FD64(0x12, &D_80083498);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = &D_800ADB8C;
        func_8004491C(temp_v0, &D_800ADBCC);
        temp_v1 = temp_v0->unk_08;
        temp_v1->unk_02 = (u16) arg0->unk_00.at02_u16.v;
        temp_v1->unk_06 = (u16) arg0->unk_04.at02_u16.v;
        temp_v1->unk_0A = (u16) arg0->unk_08.at02_u16.v;
        temp_v0_2 = temp_v0->unk_0C;
        temp_v0_2->unk_08 = arg1;
        temp_v0_2->unk_0C = 0x808080;
        temp_v0_2->unk_1E = 0x1000;
        temp_v0_2->unk_1C = 0x1000;
        temp_v0->unk_28 = arg2;
        temp_v0->unk_20 = arg3;
        *arg3 = 0;
    }
    return temp_v0;
}
