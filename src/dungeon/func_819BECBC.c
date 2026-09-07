#include "common.h"

typedef struct S_800244BC_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    s16 unk_28;
    s16 unk_2A;
} S_800244BC_0;   /* temp_v0_2 in func_800244BC */

typedef struct S_800244BC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800244BC_1;   /* temp_v0 in func_800244BC */

typedef struct S_800244BC_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800244BC_2;   /* temp_v1 in func_800244BC */

typedef struct S_800244BC_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800244BC_3;   /* arg1 in func_800244BC */

typedef struct S_800244BC_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800244BC_4;   /* temp_v1_2 in func_800244BC */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 D_80024398[];
extern s32 D_80045340[];

void func_800244BC(s32 arg0, S_800244BC_3 *arg1)
{
    void *temp_v0;
    S_800244BC_0 *temp_v0_2;
    S_800244BC_2 *temp_v1;
    S_800244BC_4 *temp_v1_2;
    u16 flags;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_v0_2 = (u8 *)temp_v0 + 0x20;
        temp_v0_2->unk_28 = 0x27;
        temp_v0_2->unk_2A = 0x27;
        temp_v0_2->unk_20 = arg0;
        ((S_800244BC_1 *)temp_v0)->unk_10 = D_80024398;
        func_8004491C(temp_v0, D_80045340);
        temp_v1 = ((S_800244BC_1 *)temp_v0)->unk_08;
        temp_v1->unk_00 = arg1->unk_00;
        temp_v1->unk_04 = arg1->unk_04;
        temp_v1->unk_08 = arg1->unk_08;
        temp_v1_2 = ((S_800244BC_1 *)temp_v0)->unk_0C;
        flags = temp_v1_2->unk_14;
        temp_v1_2->unk_1E = 0x1000;
        temp_v1_2->unk_1C = 0x1000;
        temp_v1_2->unk_0E = 0x80;
        temp_v1_2->unk_0D = 0x80;
        temp_v1_2->unk_0C = 0x80;
        temp_v1_2->unk_14 = flags | 0x80;
    }
}
