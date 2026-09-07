#include "common.h"

typedef struct S_801746EC_0 {
    u8 pad_00[0x1E];
    s16 unk_1E;
    u8 pad_20[0x30];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    u8 pad_5C[0x8];
    s32 unk_64;
} S_801746EC_0;   /* work in func_801746EC */

typedef struct S_801746EC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_801746EC_1;   /* node in func_801746EC */

typedef struct S_801746EC_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_801746EC_2;   /* part in func_801746EC */

typedef struct S_801746EC_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801746EC_3;   /* coords in func_801746EC */

typedef struct S_801746EC_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801746EC_4;   /* arg1 in func_801746EC */

typedef struct S_801746EC_5 {
    u8 pad_00[0x1C];
    s16 unk_1C;
} S_801746EC_5;   /* arg0 in func_801746EC */



typedef struct {
    s16 x;
    s16 y;
} Pair16;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s32);
extern s32 rand(void);

extern s32 D_80045340;
extern u8 D_800DECF8[];
extern s32 D_80174300;
extern Pair16 D_8017610C[];

/* Spawn an effect with randomized position and velocity based on the source direction. */
void func_801746EC(S_801746EC_5 *source, S_801746EC_4 *origin)
{
    void *effect;
    S_801746EC_0 *motion;
    S_801746EC_2 *sprite;
    S_801746EC_3 *position;
    s32 velocity_bias;

    effect = func_8003FC64(0x212);
    if (effect != 0) {
        motion = (u8 *)effect + 0x20;
        motion->unk_1E = 0x4;
        ((S_801746EC_1 *)effect)->unk_10 = &D_80174300;
        func_8004491C(effect, &D_80045340);

        sprite = ((S_801746EC_1 *)effect)->unk_0C;
        sprite->unk_10 = 0x20;
        sprite->unk_14 |= 0xC;
        sprite->unk_1A = (rand() & 7) << 9;
        sprite->unk_06 = 0;

        position = ((S_801746EC_1 *)effect)->unk_08;
        position->unk_02 = origin->unk_02;
        position->unk_06 = origin->unk_06;
        position->unk_0A = origin->unk_0A;
        position->unk_02 = ({ position->unk_02 - 0x20; }) + (rand() & 0x3F);
        position->unk_06 = ({ position->unk_06 - 0x20; }) + (rand() & 0x3F);
        position->unk_0A = ({ position->unk_0A - 0x40; }) + (rand() & 0x3F);

        motion->unk_58 = 0xFFFA0000;
        motion->unk_64 = 0x20000;
        motion->unk_50 = D_8017610C[source->unk_1C].x << 18;
        motion->unk_54 = D_8017610C[source->unk_1C].y << 18;

        velocity_bias = 0xFFF80000;
        motion->unk_50 = (motion->unk_50 + velocity_bias) + ((rand() & 0x3FFF) << 6);
        motion->unk_54 = (motion->unk_54 + velocity_bias) + ((rand() & 0x3FFF) << 6);
        motion->unk_58 = (motion->unk_58 + velocity_bias) + ((rand() & 0x3FFF) << 6);

        sprite = ((S_801746EC_1 *)effect)->unk_0C;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        sprite->unk_14 |= 0x100;
        sprite->unk_12 = 0x7DCE;
        func_8003DB94(sprite, D_800DECF8, 0);
    }
}
