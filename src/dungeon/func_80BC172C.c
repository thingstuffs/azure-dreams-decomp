#include "common.h"
#include "m2c_compat.h"

typedef struct S_80BC172C_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80BC172C_2;   /* held_arg0 in func_80BC172C */

typedef struct S_80BC172C_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80BC172C_3;   /* temp_v0 in func_80BC172C */

typedef struct S_80BC172C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80BC172C_4;   /* ((S_80BC172C_2 *)held_arg0)->unk_08 in func_80BC172C */

typedef struct S_80BC172C_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80BC172C_5;   /* ((S_80BC172C_3 *)temp_v0)->unk_08 in func_80BC172C */

typedef struct S_80BC172C_6 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80BC172C_6;   /* ((S_80BC172C_3 *)temp_v0)->unk_0C in func_80BC172C */




extern u8 D_80170884[];
extern void *func_8003FD64(s32, void *);
extern M2C_UNK func_8004491C(void *, void *);
extern s32 rand(void);
extern M2C_UNK D_80170BFC;

typedef struct S_80BC172C_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80BC172C_0;   /* temp_v0 in func_80BC172C */

typedef struct S_80BC172C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
} S_80BC172C_1;   /* temp_s0 in func_80BC172C */

void func_80BC172C(void *arg0, register s16 arg1, register s32 arg2, register s32 arg3, register s32 arg4, register s32 arg5, register s32 arg6) {
    register void *held_arg0 = arg0;
    register s16 held_arg1 = arg1;
    register s32 held_arg2 = arg2;
    register s32 held_arg4 = arg4;
    register s32 held_arg5 = arg5;
    register s32 held_arg6 = arg6;
    S_80BC172C_1 *temp_s0;
    void *temp_v0;
    u16 temp_coord;

    temp_v0 = func_8003FD64(0x211, held_arg0);
    if (temp_v0 != NULL) {
        ((S_80BC172C_0 *)temp_v0)->unk_10 = &D_80170BFC;
        do {
        temp_coord = ((S_80BC172C_4 *)(((S_80BC172C_2 *)held_arg0)->unk_08))->unk_02;
        ((S_80BC172C_5 *)(((S_80BC172C_3 *)temp_v0)->unk_08))->unk_02 = (s16) (temp_coord + held_arg4);
        ((S_80BC172C_5 *)(((S_80BC172C_3 *)temp_v0)->unk_08))->unk_06 = (s16) (((S_80BC172C_4 *)(((S_80BC172C_2 *)held_arg0)->unk_08))->unk_06 + held_arg5);
        ((S_80BC172C_5 *)(((S_80BC172C_3 *)temp_v0)->unk_08))->unk_0A = (s16) ((((S_80BC172C_4 *)(((S_80BC172C_2 *)held_arg0)->unk_08))->unk_0A + held_arg6) - 0x64);
        } while (0);
        ((S_80BC172C_6 *)(((S_80BC172C_3 *)temp_v0)->unk_0C))->unk_06 = 6;
        ((S_80BC172C_5 *)(((S_80BC172C_3 *)temp_v0)->unk_08))->unk_0C = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
        ((S_80BC172C_5 *)(((S_80BC172C_3 *)temp_v0)->unk_08))->unk_10 = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
        temp_s0 = temp_v0 + 0x20;
        ((S_80BC172C_5 *)(((S_80BC172C_3 *)temp_v0)->unk_08))->unk_14 = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
        temp_s0->unk_14 = held_arg1;
        temp_s0->unk_32 = 5;
        temp_s0->unk_34 = 5;
        func_8004491C(temp_v0, D_80170884);
        ((S_80BC172C_0 *)temp_v0)->unk_20 = held_arg2;
        temp_s0->unk_08 = held_arg2;
    }
}
