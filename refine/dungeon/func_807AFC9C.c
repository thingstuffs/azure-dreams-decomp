#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();                  /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800F7348;
extern M2C_UNK D_800FBE24;

typedef struct S_807AFC9C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_807AFC9C_0;   /* temp_v0 in func_807AFC9C */

typedef struct S_807AFC9C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_807AFC9C_1;   /* temp_s0 in func_807AFC9C */

typedef struct S_807AFC9C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_807AFC9C_2;   /* arg1 in func_807AFC9C */

typedef struct S_807AFC9C_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    M2C_UNK * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_807AFC9C_3;   /* temp_a0 in func_807AFC9C */

typedef struct S_807AFC9C_4 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_807AFC9C_4;   /* arg2 in func_807AFC9C */

typedef struct S_807AFC9C_5 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x4];
    s16 unk_0C;
} S_807AFC9C_5;   /* temp_v1 in func_807AFC9C */

/* Spawns an effect near the origin with color channels selected by the source flags. */
void func_807AFC9C(s32 spawn_arg, S_807AFC9C_2 *origin, S_807AFC9C_4 *source) {
    S_807AFC9C_3 *sprite;
    S_807AFC9C_1 *position;
    void *effect;
    S_807AFC9C_5 *effect_state;

    effect = func_8003FD64(0x212, spawn_arg);
    if (effect != NULL) {
        ((S_807AFC9C_0 *)effect)->unk_10 = &D_800F7348;
        func_8004491C(effect, &D_80045340);
        position = ((S_807AFC9C_0 *)effect)->unk_08;
        position->unk_02 = (s16) ((origin->unk_02 + (rand() & 0x3F)) - 0x20);
        position->unk_06 = (s16) ((origin->unk_06 + (rand() & 0x3F)) - 0x20);
        position->unk_0A = (s16) ((origin->unk_0A + (rand() & 0x3F)) - 0x20);
        sprite = ((S_807AFC9C_0 *)effect)->unk_0C;
        sprite->unk_08 = &D_800FBE24;
        if (source->unk_14 & 1) {
            sprite->unk_0C = 0x20;
        }
        if (source->unk_14 & 2) {
            sprite->unk_0E = 0x20;
        }
        if (source->unk_14 & 4) {
            sprite->unk_0D = 0x20;
        }
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_06 = 8;
        effect_state = effect + 0x20;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        effect_state->unk_0C = 0x10;
        ((S_807AFC9C_0 *)effect)->unk_20 = source;
        effect_state->unk_04 = origin;
    }
}
