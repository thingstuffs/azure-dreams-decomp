#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_806C51B0_0 {
    void * unk_00;
} S_806C51B0_0;   /* &D_80016000 in func_806C51B0 */

typedef struct S_806C51B0_1 {
    u8 pad_00[0x1C];
    void * unk_1C;
    void * unk_20;
} S_806C51B0_1;   /* ((S_806C51B0_0 *)(&D_80016000))->unk_00 in func_806C51B0 */

typedef struct S_806C51B0_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_806C51B0_2;   /* ((S_806C51B0_1 *)(((S_806C51B0_0 *)(&D_80016000))->unk_00))->unk_1C in func_806C51B0 */

typedef struct S_806C51B0_3 {
    u8 pad_00[0x208];
    M2C_UNK (*unk_208)(M2C_UNK);
    u8 pad_20C[0x1C];
    M2C_UNK (*unk_228)(M2C_UNK);
} S_806C51B0_3;   /* ((S_806C51B0_1 *)(((S_806C51B0_0 *)(&D_80016000))->unk_00))->unk_20 in func_806C51B0 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK D_80016000;
extern s32 D_800190C0[3];


void func_806C51B0(void) {
    s32 *command;
    s32 value;

    D_800190C0[0] = ((S_806C51B0_2 *)(((S_806C51B0_1 *)(((S_806C51B0_0 *)(&D_80016000))->unk_00))->unk_1C))->unk_04 << 16;
    value = ((S_806C51B0_2 *)(((S_806C51B0_1 *)(((S_806C51B0_0 *)(&D_80016000))->unk_00))->unk_1C))->unk_08;
    do { command = D_800190C0; } while (0);
    command[2] = 0;
    command[1] = value << 16;
    ((S_806C51B0_3 *)(((S_806C51B0_1 *)(((S_806C51B0_0 *)(&D_80016000))->unk_00))->unk_20))->unk_208(0);
    ((S_806C51B0_3 *)(((S_806C51B0_1 *)(((S_806C51B0_0 *)(&D_80016000))->unk_00))->unk_20))->unk_228(0);
}
