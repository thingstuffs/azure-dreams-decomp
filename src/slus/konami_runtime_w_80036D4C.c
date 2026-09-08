#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_D_80081FDC.h"

typedef struct S_80036D4C_4 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80036D4C_4;   /* temp_v0 in func_80036D4C */

typedef struct S_80036D4C_5 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_80036D4C_5;   /* ((S_80036D4C_4 *)temp_v0)->unk_20 in func_80036D4C */


typedef struct S_80036D4C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80036D4C_0;   /* temp_v0 in func_80036D4C */

typedef struct S_80036D4C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x38];
    s32 * unk_44;
    s8 unk_48;
    u8 pad_49[0x1];
    s16 unk_4A;
    u8 pad_4C[0x1A];
    s16 unk_66;
} S_80036D4C_1;   /* temp_s1 in func_80036D4C */


typedef struct S_80036D4C_3 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    M2C_UNK * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
} S_80036D4C_3;   /* temp_s2 in func_80036D4C */


M2C_UNK func_80033C1C();                 /* extern */
M2C_UNK func_800350B0();                 /* extern */
M2C_UNK func_80036C7C(); /* extern */
void *func_8003FF2C(); /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_8006A958;
extern M2C_UNK D_8006A964;
extern M2C_UNK D_8006A970;
extern M2C_UNK D_80082B50;
extern M2C_UNK D_80082B60;
extern M2C_UNK D_80082B70;
extern M2C_UNK D_80082BC0;
extern M2C_UNK func_80033D54;
extern M2C_UNK func_80036F24;

void func_80036D4C(s32 arg0, Rec_D_80081FDC *arg1, s32 *arg2, s16 arg3, s32 arg4, s32 arg5) {
    S_80036D4C_1 *temp_s1;
    S_80036D4C_3 *temp_s2;
    void *temp_v0;

    temp_v0 = func_8003FF2C(0x11, arg0, 0x49, &D_80082BC0);
    ((S_80036D4C_0 *)temp_v0)->unk_10 = &func_80036F24;
    func_8004491C(temp_v0, &func_80033D54);
    temp_s1 = temp_v0 + 0x20;
    temp_s2 = ((S_80036D4C_0 *)temp_v0)->unk_0C;
    temp_s1->unk_44 = arg2;
    temp_s1->unk_48 = 1;
    temp_s1->unk_4A = arg3;
    func_80033C1C(arg1, *arg2);
    ((S_80036D4C_0 *)temp_v0)->unk_20 = arg1;
    arg1->unk_60 = 6;
    ((S_80036D4C_5 *)(((S_80036D4C_4 *)temp_v0)->unk_20))->unk_10 = 0x47;
    ((S_80036D4C_5 *)(((S_80036D4C_4 *)temp_v0)->unk_20))->unk_14 = 2;
    temp_s1->unk_04 = 0;
    temp_s1->unk_08 = 0;
    func_800350B0(arg5, temp_s1);
    temp_s2->unk_0C = 0xC0C0C0;
    func_80036C7C(temp_s1->unk_44 + 3, &D_8006A958, &D_80082B50);
    func_80036C7C(temp_s1->unk_44 + 3, &D_8006A964, &D_80082B60);
    func_80036C7C(temp_s1->unk_44 + 3, &D_8006A970, &D_80082B70);
    temp_s2->unk_08 = &D_80082B60;
    temp_s2->unk_00 = 0;
    temp_s2->unk_04 = 0;
    temp_s2->unk_05 = 0;
    temp_s2->unk_14 = (u16) (temp_s2->unk_14 | 0x1C);
    temp_s1->unk_66 = (s16) arg4;
}
