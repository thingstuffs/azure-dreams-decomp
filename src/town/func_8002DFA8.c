/* Relink of matched town/func_800CB1C8; every changed retail word is a paired relocation. */
#define D_800D6330 D_800D69DC
#define D_800D6338 D_800D69E4
#define D_800D6360 D_800D6A0C
#define D_800D6364 D_800D6A10
#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800D69DC;
extern M2C_UNK D_800D69E4;
extern M2C_UNK D_800D6A0C;
extern M2C_UNK D_800D6A10;

typedef struct S_800C8928_0 {
    u8 pad_00[0x58];
    M2C_UNK * unk_58;
    M2C_UNK * unk_5C;
    u8 pad_60[0x1C];
    M2C_UNK * unk_7C;
    M2C_UNK * unk_80;
} S_800C8928_0;   /* arg0 in func_800CB708 */

/* Assign the four object data pointers. */
void func_800CB708(S_800C8928_0 *object) {
    object->unk_58 = &D_800D6A0C;
    object->unk_5C = &D_800D6A10;
    object->unk_7C = &D_800D69DC;
    object->unk_80 = &D_800D69E4;
}
