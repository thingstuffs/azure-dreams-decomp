#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800CB82C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_800CB82C_0;   /* temp_v0 in func_800CB82C */

typedef struct S_800CB82C_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800CB82C_1;   /* temp_a1 in func_800CB82C */

typedef struct S_800CB82C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800CB82C_2;   /* arg0 in func_800CB82C */

typedef struct S_800CB82C_3 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
} S_800CB82C_3;   /* temp_a0_2 in func_800CB82C */

typedef struct S_800CB82C_4 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 unk_09;
    u8 pad_0A[0x9];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    u8 unk_72;
    u8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
    u8 pad_8A[0x6];
    s32 unk_90;
} S_800CB82C_4;   /* temp_a0_3 in func_800CB82C */

typedef struct S_800CB82C_5 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800CB82C_5;   /* &D_800E3CC8 in func_800CB82C */

typedef struct S_800CB82C_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CB82C_6_pre;   /* the 0x14 bytes before arg2 in func_800CB82C, addressed as arg2[-1] */

typedef struct S_800CB82C_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800CB82C_6;   /* arg2 in func_800CB82C */

typedef struct S_800CB82C_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CB82C_7;   /* temp_v1 in func_800CB82C */



/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80045340[];
extern s32 D_800814A0[3];
extern s32 D_80083460[3];
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();                /* extern */
M2C_UNK func_80099FDC();                      /* extern */
s32 func_800A94A0(); /* extern */
extern M2C_UNK D_800CB600;
extern M2C_UNK D_800E03BC;
extern u8 D_800E3CC8;

void *func_800CB82C(void *arg0, void *arg1, void *arg2) {
    u16 temp_a0;
    s32 temp_global;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_a1;
    void *temp_v0;
    void *temp_v1;
    u16 *counter;
    u16 counter_value;

    temp_v0 = func_8003FC64(0x102);
    if (temp_v0 != NULL) {
        ((S_800CB82C_0 *)temp_v0)->unk_10 = &D_800CB600;
        func_8004491C(temp_v0, D_80045340);
        temp_a1 = ((S_800CB82C_0 *)temp_v0)->unk_08;
        ((S_800CB82C_1 *)temp_a1)->unk_02 = (u16) ((S_800CB82C_2 *)arg0)->unk_02;
        ((S_800CB82C_1 *)temp_a1)->unk_06 = (u16) ((S_800CB82C_2 *)arg0)->unk_06;
        ((S_800CB82C_1 *)temp_a1)->unk_0A = (u16) ((S_800CB82C_2 *)arg0)->unk_08.at02.v;
        temp_a0_2 = ((S_800CB82C_0 *)temp_v0)->unk_0C;
        ((S_800CB82C_3 *)temp_a0_2)->unk_08 = &D_800E03BC;
        ((S_800CB82C_3 *)temp_a0_2)->unk_14 = (u16) (((S_800CB82C_3 *)temp_a0_2)->unk_14 | 0xC);
        ((S_800CB82C_3 *)temp_a0_2)->unk_24 = (s8) ((u16) ((S_800CB82C_1 *)temp_a1)->unk_02 >> 6);
        ((S_800CB82C_3 *)temp_a0_2)->unk_25 = (s8) ((u16) ((S_800CB82C_1 *)temp_a1)->unk_06 >> 6);
        temp_a0_3 = temp_v0 + 0x20;
        (*(s16 *)((u8 *)temp_a0_3 + 0x96)) = 0x10;
        ((S_800CB82C_4 *)temp_a0_3)->unk_08 = (u8) D_800E3CC8;
        ((S_800CB82C_4 *)temp_a0_3)->unk_09 = (u8) ((S_800CB82C_5 *)(&D_800E3CC8))->unk_01;
        ((S_800CB82C_4 *)temp_a0_3)->unk_60 = arg2;
        temp_v1 = ((S_800CB82C_6_pre *)arg2)[-1].unk_00;
        ((S_800CB82C_4 *)temp_a0_3)->unk_72 = (u8) ((S_800CB82C_7 *)temp_v1)->unk_24;
        ((S_800CB82C_4 *)temp_a0_3)->unk_73 = (u8) ((S_800CB82C_7 *)temp_v1)->unk_25;
        ((S_800CB82C_4 *)temp_a0_3)->unk_88 = (u16) ((Rec_D_800E3D7C *)arg1)->unk_88.as_u16;
        ((S_800CB82C_4 *)temp_a0_3)->unk_13 = 0xFF;
        ((S_800CB82C_4 *)temp_a0_3)->unk_14 = (s32) ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32;
        ((S_800CB82C_4 *)temp_a0_3)->unk_1C = (s32) ((Rec_D_800E3D7C *)arg1)->unk_1C.as_s32;
        ((S_800CB82C_4 *)temp_a0_3)->unk_2A = (s16) (((S_800CB82C_6 *)arg2)->unk_2A - 0x800);
        ((S_800CB82C_4 *)temp_a0_3)->unk_90 = (s32) ((S_800CB82C_2 *)arg0)->unk_08.at00.v;
        if (func_800A94A0(temp_a0_3, temp_v0 + 0x28, 0, temp_v0 + 0xB8) == 0) {
            temp_a0 = ((S_800CB82C_0 *)temp_v0)->unk_1E | 0x8000;
            temp_global = D_800814A0[0] | 0x8000;
            ((S_800CB82C_0 *)temp_v0)->unk_1E = temp_a0;
            D_800814A0[0] = temp_global;
            return NULL;
        }
        func_80099FDC(temp_v0);
        counter = (u16 *)D_80083460;
        counter_value = counter[5];
        counter_value = (u16) (counter_value + 1);
        counter[5] = counter_value;
    }
    return temp_v0;
}
