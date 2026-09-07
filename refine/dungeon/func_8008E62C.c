#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();                  /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80048A44(); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80093A94;

typedef struct S_80093D8C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x2];
    s16 unk_26;
} S_80093D8C_0;   /* temp_v0 in func_80093D8C */

typedef struct S_80093D8C_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80093D8C_1;   /* temp_v1 in func_80093D8C */

typedef struct S_80093D8C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80093D8C_2;   /* arg1 in func_80093D8C */

typedef struct S_80093D8C_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80093D8C_3;   /* temp_a0 in func_80093D8C */

typedef struct S_80093D8C_4 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_80093D8C_4;   /* arg2 in func_80093D8C */

/* Create a sprite effect at the supplied position and attach it to its owner. */
void func_80093D8C(s32 sort_order, S_80093D8C_2 *source_pos, S_80093D8C_4 *owner) {
    S_80093D8C_3 *sprite;
    S_80093D8C_0 *effect;
    S_80093D8C_1 *position;

    effect = func_8003FD64(0x310, sort_order - 0x20);
    if (effect != NULL) {
        position = effect->unk_08;
        effect->unk_10 = &D_80093A94;
        position->unk_02 = (u16) source_pos->unk_02;
        position->unk_06 = (u16) source_pos->unk_06;
        position->unk_0A = (u16) source_pos->unk_0A;
        sprite = effect->unk_0C;
        sprite->unk_28 = (s32) owner->unk_28;
        sprite->unk_1E = 0x1000;
        sprite->unk_14 = 0xCU;
        sprite->unk_10 = 0x20;
        sprite->unk_0C = 0xF8F8F8;
        sprite->unk_1C = 0;
        sprite->unk_06 = 4;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0x200);
        func_80048A44(sprite, 0xD0, 0, 2);
        func_8004491C(effect, &D_80045340);
        effect->unk_20 = owner;
        effect->unk_26 = 0x10;
    }
}
