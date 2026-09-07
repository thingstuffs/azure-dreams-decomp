#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800F63D0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800F63D0_0;   /* temp_v0 in func_800F63D0 */

typedef struct S_800F63D0_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800F63D0_1;   /* temp_s0 in func_800F63D0 */

typedef struct S_800F63D0_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    M2C_UNK * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800F63D0_2;   /* temp_v1 in func_800F63D0 */


extern s32 func_80033BC0();
extern void *func_8003FC64();
extern M2C_UNK func_80041284();
extern M2C_UNK func_8004491C();
extern s16 func_800BCA68();
extern u8 D_80045C34[]; /* overlays/dungeon/first_pass_matched/func_80D403A8.c */
extern M2C_UNK D_800F62BC;
extern M2C_UNK D_800F6F28;
extern M2C_UNK D_800F6F30;

#define VFIELD(expr, type, offset) (*(volatile type *)((s8 *)(expr) + (offset)))

void func_800F63D0(void) {
    S_800F63D0_1 *temp_s0;
    S_800F63D0_0 *temp_v0;
    S_800F63D0_2 *temp_v1;

    if (func_80033BC0(0xA2) == 0) {
        func_80041284(&D_800F6F28);
        temp_v0 = func_8003FC64(0x12);
        if (temp_v0 != NULL) {
            temp_v0->unk_10 = &D_800F62BC;
            func_8004491C(temp_v0, &D_80045C34);
            temp_s0 = temp_v0->unk_08;
            temp_s0->unk_02 = 0x820;
            temp_s0->unk_06 = 0x820;
            temp_s0->unk_0A = func_800BCA68(VFIELD(temp_s0, u16, 2), 0x820);
            temp_v1 = temp_v0->unk_0C;
            temp_v1->unk_1E = 0x1000;
            temp_v1->unk_1C = 0x1000;
            temp_v1->unk_08 = &D_800F6F30;
            temp_v1->unk_10 = 0x20;
            temp_v1->unk_14 = 0xC;
            temp_v1->unk_06 = 6;
        }
    }
}
