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

/* Conditionally creates and initializes a type 0x12 object. */
void func_800F63D0(void) {
    S_800F63D0_1 *graphics;
    S_800F63D0_0 *object;
    S_800F63D0_2 *animation;

    if (func_80033BC0(0xA2) == 0) {
        func_80041284(&D_800F6F28);
        object = func_8003FC64(0x12);
        if (object != NULL) {
            object->unk_10 = &D_800F62BC;
            func_8004491C(object, &D_80045C34);
            graphics = object->unk_08;
            graphics->unk_02 = 0x820;
            graphics->unk_06 = 0x820;
            graphics->unk_0A = func_800BCA68(VFIELD(graphics, u16, 2), 0x820);
            animation = object->unk_0C;
            animation->unk_1E = 0x1000;
            animation->unk_1C = 0x1000;
            animation->unk_08 = &D_800F6F30;
            animation->unk_10 = 0x20;
            animation->unk_14 = 0xC;
            animation->unk_06 = 6;
        }
    }
}
