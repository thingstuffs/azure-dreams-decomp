#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80E3CC80_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0x2C];
    s16 unk_40;
} S_80E3CC80_0;   /* object in func_80E3CC80 */

typedef struct S_80E3CC80_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80E3CC80_1;   /* a in func_80E3CC80 */

typedef struct S_80E3CC80_2 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x14];
    s32 unk_28;
} S_80E3CC80_2;   /* arg1 in func_80E3CC80 */

typedef struct S_80E3CC80_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    u8 pad_14[0x2];
    s16 unk_16;
} S_80E3CC80_3;   /* b in func_80E3CC80 */

typedef struct S_80E3CC80_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80E3CC80_4;   /* arg0 in func_80E3CC80 */



extern void *func_8003FC64(s32 size);
extern void func_8004491C(void *object, void *data);
extern void func_80047784(void *object, s32 arg1, s32 arg2);
extern s32 rand(void);
extern u8 D_80045340[];
extern u8 D_801763D0[];

/* Spawns up to sixteen particles with randomized offsets and velocities. */
void func_80E3CC80(S_80E3CC80_4 *origin, S_80E3CC80_2 *source_sprite) {
    s32 remaining;
    s32 image;
    u16 sprite_flags;
    u16 source_y;
    S_80E3CC80_0 *particle;
    S_80E3CC80_1 *sprite;
    S_80E3CC80_3 *motion;

    remaining = 0x10;
    do {
        particle = func_8003FC64(0x300);
        if (particle != NULL) {
            particle->unk_10 = D_801763D0;
            func_8004491C(particle, D_80045340);
            sprite = particle->unk_0C;
            sprite->unk_1E = 0x800;
            sprite->unk_1C = 0x800;
            sprite->unk_0C = 0x808080;
            sprite->unk_10 = 0x20;
            image = source_sprite->unk_28;
            sprite->unk_28 = image;
            sprite_flags = sprite->unk_14;
            source_y = source_sprite->unk_12;
            sprite->unk_14 = sprite_flags | 0xC;
            sprite->unk_12 = source_y - 0x80;
            func_80047784(sprite, 0x41, 0);
            motion = particle->unk_08;
            motion->unk_02 = origin->unk_02;
            motion->unk_06 = origin->unk_06;
            motion->unk_0A = origin->unk_0A - (rand() & 0x1F);
            motion->unk_16 = ((0 - (rand() & 0xF)) - 8) * 2;
            motion->unk_0C = ((rand() & 3) - 2) << 0x10;
            motion->unk_10 = ((rand() & 3) - 2) << 0x10;
            particle->unk_40 = 0x10;
        }
        remaining -= 1;
    } while (remaining > 0);
}

/* MECHANISM: Named word and halfword read locals extend the arg1 value live ranges,
   reproducing retail's load-before-store emission order in the setup block.
   Natural locals retain the 0x30 frame and s0-s5 roles without register pins. */
