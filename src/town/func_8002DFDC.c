/* Relink of matched town/func_800CB1C8; every changed retail word is a paired relocation. */
#define D_800D6330 D_800D6988
#define D_800D6338 D_800D6990
#define D_800D6360 D_800D69B8
#define D_800D6364 D_800D69BC
#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800D6988;
extern M2C_UNK D_800D6990;
extern M2C_UNK D_800D69B8;
extern M2C_UNK D_800D69BC;

typedef struct S_800C8928_0 {
    u8 pad_00[0x58];
    M2C_UNK * unk_58;
    M2C_UNK * unk_5C;
    u8 pad_60[0x1C];
    M2C_UNK * unk_7C;
    M2C_UNK * unk_80;
} S_800C8928_0;   /* arg0 in func_800CB73C */

/* Assign the four object data pointers. */
void func_800CB73C(S_800C8928_0 *object) {
    object->unk_58 = &D_800D69B8;
    object->unk_5C = &D_800D69BC;
    object->unk_7C = &D_800D6988;
    object->unk_80 = &D_800D6990;
}
