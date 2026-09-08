#include "common.h"
#include "m2c_compat.h"

typedef struct Packed12 {
    u8 bytes[12];
} Packed12;

void *func_8003FC64(s32);
void func_8004491C(void *, void *);
s32 rand(void);
s32 func_80167088(s32);
extern u8 D_80045C34[];
extern M2C_UNK D_80165AB8;
extern Packed12 D_80173B34;


typedef struct S_8016604C_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8016604C_0;   /* arg0 in func_8016604C */

typedef struct S_8016604C_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_8016604C_1;   /* temp_v0_2 in func_8016604C */

typedef struct S_8016604C_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8016604C_2;   /* temp_s0 in func_8016604C */

typedef struct S_8016604C_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8016604C_3;   /* ((S_8016604C_0 *)arg0)->unk_08 in func_8016604C */

typedef struct S_8016604C_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8016604C_4;   /* (*(void **)((u8 *)temp_v0 + 8)) in func_8016604C */

/* Spawn particles at random positions in a grid around the source. */
void func_8016604C(S_8016604C_0 *source) {
    s32 x_base;
    s32 y_base;
    s32 y_random;
    s32 jitter_or_scale;
    s32 grid_y;
    s32 grid_x;
    S_8016604C_2 *sprite;
    M2C_UNK *effect_data;
    void *particle;
    S_8016604C_1 *motion;

    grid_x = -2;
    effect_data = &D_80165AB8;
    do {
        grid_y = -5;
        do {
            if (!(rand() & 7)) {
                particle = func_8003FC64(0x12);
                if (particle != NULL) {
                    (*(M2C_UNK **)((u8 *)particle + 0x10)) = effect_data;
                    jitter_or_scale = rand();
                    x_base = ((S_8016604C_3 *)(source->unk_08))->unk_02 + (grid_x << 6);
                    x_base -= 0x20;
                    ((S_8016604C_4 *)((*(void **)((u8 *)particle + 8))))->unk_02 = (s16) (x_base + (jitter_or_scale & 0x3F));
                    y_random = rand();
                    y_base = ((S_8016604C_3 *)(source->unk_08))->unk_06 + (grid_y << 6);
                    y_base -= 0x20;
                    ((S_8016604C_4 *)((*(void **)((u8 *)particle + 8))))->unk_06 = (s16) (y_base + (y_random & 0x3F));
                    ((S_8016604C_4 *)((*(void **)((u8 *)particle + 8))))->unk_0A = (s16) (((S_8016604C_3 *)(source->unk_08))->unk_0A - 0x100);
                    motion = (*(void **)((u8 *)particle + 8));
                    motion->unk_10 = 0;
                    motion->unk_0C = 0;
                    ((S_8016604C_4 *)((*(void **)((u8 *)particle + 8))))->unk_14 = 0x200000;
                    func_8004491C(particle, &D_80045C34);
                    sprite = (*(void **)((u8 *)particle + 0xC));
                    sprite->unk_14 = (u16) (sprite->unk_14 & 0xFFF3);
                    jitter_or_scale = 0x1000 / (s32) (func_80167088(5) + 6);
                    sprite->unk_0C = 0xFF;
                    sprite->unk_0E = 0x20;
                    sprite->unk_0D = 0x20;
                    sprite->unk_1E = (s16) jitter_or_scale;
                    sprite->unk_1C = (s16) jitter_or_scale;
                    (*(Packed12 *)((u8 *)particle + 0x56)) = D_80173B34;
                    sprite->unk_08 = (void *) (particle + 0x56);
                }
            }
            grid_y += 1;
        } while (grid_y <= 0);
        grid_x += 1;
    } while (grid_x < 3);
}

/* MECHANISM: True-space nested loops plus a held D_80165AB8 base produce the exact 0x30 frame and s5/s4/s3/s2 roles at cdk-G0.
   A byte-aligned 12-byte aggregate produces the retail lwl/lwr/swl/swr copy; distinct RNG/coordinate locals preserve v1/a0 allocation.
   The final 0xFF field is u8 so GCC materializes 0xff rather than canonicalizing it to -1. */
