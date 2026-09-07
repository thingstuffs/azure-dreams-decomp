#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003719C_4 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8003719C_4;   /* temp_v0 in func_8003719C */

typedef struct S_8003719C_5 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_8003719C_5;   /* ((S_8003719C_4 *)temp_v0)->unk_20 in func_8003719C */


typedef struct S_8003719C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
    M2C_UNK (*unk_10)(void *, s32, void *);
    u8 pad_14[0xC];
    void * unk_20;
} S_8003719C_0;   /* temp_v0 in func_8003719C */

typedef struct S_8003719C_1 {
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
} S_8003719C_1;   /* temp_s1 in func_8003719C */

typedef struct S_8003719C_2 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_8003719C_2;   /* arg1 in func_8003719C */

typedef struct S_8003719C_3 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    M2C_UNK * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
} S_8003719C_3;   /* temp_s4 in func_8003719C */


M2C_UNK func_80033C1C();                 /* extern */
M2C_UNK func_800350B0();                 /* extern */
M2C_UNK func_80036C7C(); /* extern */
M2C_UNK func_80037394();         /* extern */
void *func_8003FF2C(); /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_8006A988;
extern M2C_UNK D_8006A994;
extern M2C_UNK D_8006A9A0;
extern M2C_UNK D_8006A9AC;
extern M2C_UNK D_8006A9B8;
extern M2C_UNK D_8006A9C4;
extern M2C_UNK D_80081E90;
extern M2C_UNK D_80081EA0;
extern M2C_UNK D_80082B80;
extern M2C_UNK D_80082B90;
extern M2C_UNK D_80082BA0;
extern M2C_UNK D_80082BB0;
extern M2C_UNK D_80082BC0;
extern M2C_UNK func_80033D54;

void func_8003719C(s32 arg0, S_8003719C_2 *arg1, s32 *arg2, s16 arg3, s32 arg4, s32 arg5) {
    s32 temp_s7;
    S_8003719C_1 *temp_s1;
    S_8003719C_3 *temp_s4;
    void *temp_v0;

    temp_v0 = func_8003FF2C(0x11, arg0, 0x49, &D_80082BC0);
    ((S_8003719C_0 *)temp_v0)->unk_10 = func_80037394;
    func_8004491C(temp_v0, &func_80033D54);
    temp_s1 = temp_v0 + 0x20;
    temp_s7 = ((S_8003719C_0 *)temp_v0)->unk_08;
    temp_s4 = ((S_8003719C_0 *)temp_v0)->unk_0C;
    temp_s1->unk_44 = arg2;
    temp_s1->unk_48 = 1;
    temp_s1->unk_4A = arg3;
    func_80033C1C(arg1, *arg2);
    ((S_8003719C_0 *)temp_v0)->unk_20 = arg1;
    arg1->unk_60 = 6;
    ((S_8003719C_5 *)(((S_8003719C_4 *)temp_v0)->unk_20))->unk_10 = 0x47;
    ((S_8003719C_5 *)(((S_8003719C_4 *)temp_v0)->unk_20))->unk_14 = 2;
    temp_s1->unk_04 = 0;
    temp_s1->unk_08 = 0;
    func_800350B0(arg5, temp_s1);
    temp_s4->unk_0C = 0xC0C0C0;
    func_80036C7C(temp_s1->unk_44 + 3, &D_8006A988, &D_80082B80);
    func_80036C7C(temp_s1->unk_44 + 3, &D_8006A994, &D_80082B90);
    func_80036C7C(temp_s1->unk_44 + 3, &D_8006A9A0, &D_80082BA0);
    func_80036C7C(temp_s1->unk_44 + 3, &D_8006A9AC, &D_80082BB0);
    func_80036C7C(temp_s1->unk_44 + 3, &D_8006A9B8, &D_80081E90);
    func_80036C7C(temp_s1->unk_44 + 3, &D_8006A9C4, &D_80081EA0);
    temp_s4->unk_08 = &D_80082B90;
    temp_s4->unk_00 = 0;
    temp_s4->unk_04 = 0;
    temp_s4->unk_05 = 0;
    temp_s4->unk_14 = (u16) (temp_s4->unk_14 | 0x1C);
    temp_s1->unk_66 = (s16) arg4;
    func_80037394(temp_s1, temp_s7, temp_s4);
}
