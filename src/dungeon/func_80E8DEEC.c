#include "common.h"
#include "records/Rec_D_800E3D7C.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_800A56E0();
extern M2C_UNK func_800AD058();
extern M2C_UNK func_80174D48();
extern s16 D_8008346A[];

typedef struct S_801736EC_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801736EC_0;   /* arg0 in func_801736EC */


typedef struct S_801736EC_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
} S_801736EC_2;   /* arg2 in func_801736EC */

void func_801736EC(S_801736EC_0 *arg0, M2C_UNK arg1, S_801736EC_2 *arg2, Rec_D_800E3D7C *arg3) {
    M2C_UNK one;
    M2C_UNK color;
    M2C_UNK temp_v1;

    temp_v1 = arg0->unk_9B;
    one = 1;
    if (temp_v1 == one) {
        goto block_10;
    }
    if (temp_v1 >= 2) {
        goto block_ge_2;
    }
    if (temp_v1 == 0) {
        goto block_8;
    }
    goto block_end;

block_ge_2:
    if (temp_v1 == 2) {
        goto block_20;
    }
    goto block_end;

block_8:
    if (D_8008346A[0] != 0) {
        goto block_end;
    }
    arg0->unk_9B = (u8)one;

block_10:
    if (arg3->unk_48.at01_u8.v != 0) {
        func_80174D48(arg1, arg2, arg3);
        arg3->unk_48.at00_s8.v = 0;
        arg3->unk_48.at01_u8.v = 0U;
    }
    color = 0x808080;
    ASM_KEEP(color);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    arg2->unk_10 = 0x20;
    arg2->unk_12 = (u16)(arg2->unk_12 - 0x80);
    arg2->unk_14 = (u16)(arg2->unk_14 | 0xC);
    arg3->unk_1C.as_s32 = arg3->unk_1C.as_s32 | 0x10000000;
    arg2->unk_0C = color;
    arg0->unk_96 = 0x10;
    arg0->unk_9B = (u8)(arg0->unk_9B + 1);
    func_800A56E0(0x805, color);
    goto block_end;

block_20:
    func_800AD058(arg0, arg1, arg2, arg3);

block_end:
    return;
}
