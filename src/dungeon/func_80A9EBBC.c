#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80174318;

typedef struct S_801743BC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x26];
    s16 unk_3A;
} S_801743BC_0;   /* temp_v0 in func_801743BC */

typedef struct S_801743BC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801743BC_1;   /* temp_v1 in func_801743BC */


typedef struct S_801743BC_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801743BC_3;   /* temp_v0_2 in func_801743BC */

/* Creates an effect at the supplied position and initializes its sprite. */
void func_801743BC(M2C_UNK unused, Rec_D_800E3D7C *source_pos) {
    S_801743BC_0 *effect;
    S_801743BC_3 *sprite;
    S_801743BC_1 *effect_pos;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        effect->unk_3A = 0x2D;
        effect->unk_10 = &D_80174318;
        func_8004491C(effect, &D_80045340);
        effect_pos = effect->unk_08;
        effect_pos->unk_02 = (u16) source_pos->unk_00.at02_u16.v;
        effect_pos->unk_06 = (u16) source_pos->unk_04.at02_u16.v;
        effect_pos->unk_0A = (u16) source_pos->unk_08.at02_u16.v;
        sprite = effect->unk_0C;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0C = 0;
        sprite->unk_0E = 0;
        sprite->unk_0D = 0;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0x80);
    }
}
