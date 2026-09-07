#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008F664();              /* extern */
extern s32 D_80083788[];
extern M2C_UNK D_8009B8E8;
extern s32 D_800D0428[];

typedef struct S_8009C148_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_8009C148_0;   /* arg1 in func_8009C148 */

typedef struct S_8009C148_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8009C148_1;   /* arg2 in func_8009C148 */

typedef struct S_8009C148_2 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
} S_8009C148_2;   /* arg0 in func_8009C148 */

/* Initializes the target parameters and updates the owner's state. */
void func_8009C148(S_8009C148_2 *owner, S_8009C148_0 *target, S_8009C148_1 *parameters) {
    s32 combinedValue;

    target->unk_15 = 0;
    combinedValue = D_80083788[0] + D_800D0428[0];
    parameters->unk_0C = 0;
    parameters->unk_10 = 0;
    parameters->unk_14 = 0;
    parameters->unk_08 = combinedValue;
    func_8008F664(target, parameters);
    owner->unk_50 = &D_8009B8E8;
    owner->unk_6C = 4;
}
