#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_800CAFDC_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800CAFDC_5;   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_800CAFDC */




void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s16 rand();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800CAED0;
extern M2C_UNK D_800E03B0;

typedef struct S_800CAFDC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800CAFDC_0;   /* temp_v0 in func_800CAFDC */

typedef struct S_800CAFDC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    u8 pad_14[0x2];
    s16 unk_16;
} S_800CAFDC_1;   /* temp_s1 in func_800CAFDC */

typedef struct S_800CAFDC_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    M2C_UNK * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800CAFDC_2;   /* temp_v1 in func_800CAFDC */

typedef struct S_800CAFDC_3 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x18];
    s16 unk_B0;
} S_800CAFDC_3;   /* temp_s0 in func_800CAFDC */

void func_800CAFDC(Rec_D_800E3D7C *arg0, s16 arg1, s32 arg2) {
    s16 temp_v0_2;
    s32 var_s3;
    S_800CAFDC_3 *temp_s0;
    S_800CAFDC_1 *temp_s1;
    void *temp_v0;
    S_800CAFDC_2 *temp_v1;

    var_s3 = 2;
    do {
        temp_v0 = func_8003FD64(0x212, arg0);
        if (temp_v0 != NULL) {
            ((S_800CAFDC_0 *)temp_v0)->unk_10 = &D_800CAED0;
            func_8004491C(temp_v0, &D_80045340);
            temp_s1 = ((S_800CAFDC_0 *)temp_v0)->unk_08;
            temp_s1->unk_02 = (s16) ((((S_800CAFDC_5 *)(arg0->unk_08.at00_pv.v))->unk_02 + (rand() & 0x3F)) - 0x20);
            temp_s1->unk_06 = (s16) ((((S_800CAFDC_5 *)(arg0->unk_08.at00_pv.v))->unk_06 + (rand() & 0x3F)) - 0x20);
            temp_s1->unk_0A = (s16) ((((S_800CAFDC_5 *)(arg0->unk_08.at00_pv.v))->unk_0A + (rand() & 0x3F)) - 0x20);
            temp_v0_2 = rand();
            temp_s1->unk_0C = (s32) (func_80064584(temp_v0_2) << 5);
            temp_s1->unk_10 = (s32) (func_800644B8(temp_v0_2) << 5);
            temp_s1->unk_16 = (s16) ((0 - (rand() & 7)) - 8);
            temp_v1 = ((S_800CAFDC_0 *)temp_v0)->unk_0C;
            temp_s0 = temp_v0 + 0x20;
            temp_v1->unk_1E = 0x1000;
            temp_v1->unk_1C = 0x1000;
            temp_v1->unk_08 = &D_800E03B0;
            temp_v1->unk_0C = arg2;
            temp_v1->unk_06 = 8;
            temp_s0->unk_B0 = arg1;
            temp_s0->unk_96 = (s16) ((rand() & 0xFF) | 0x80);
        }
        var_s3 -= 1;
    } while (var_s3 > 0);
}
