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

void func_8016604C(S_8016604C_0 *arg0) {
    s32 temp_coord;
    s32 temp_coord2;
    s32 temp_rand2;
    s32 temp_v1;
    s32 var_s2;
    s32 var_s3;
    S_8016604C_2 *temp_s0;
    M2C_UNK *temp_s5;
    void *temp_v0;
    S_8016604C_1 *temp_v0_2;

    var_s3 = -2;
    temp_s5 = &D_80165AB8;
    do {
        var_s2 = -5;
        do {
            if (!(rand() & 7)) {
                temp_v0 = func_8003FC64(0x12);
                if (temp_v0 != NULL) {
                    (*(M2C_UNK **)((u8 *)temp_v0 + 0x10)) = temp_s5;
                    temp_v1 = rand();
                    temp_coord = ((S_8016604C_3 *)(arg0->unk_08))->unk_02 + (var_s3 << 6);
                    temp_coord -= 0x20;
                    ((S_8016604C_4 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_02 = (s16) (temp_coord + (temp_v1 & 0x3F));
                    temp_rand2 = rand();
                    temp_coord2 = ((S_8016604C_3 *)(arg0->unk_08))->unk_06 + (var_s2 << 6);
                    temp_coord2 -= 0x20;
                    ((S_8016604C_4 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_06 = (s16) (temp_coord2 + (temp_rand2 & 0x3F));
                    ((S_8016604C_4 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_0A = (s16) (((S_8016604C_3 *)(arg0->unk_08))->unk_0A - 0x100);
                    temp_v0_2 = (*(void **)((u8 *)temp_v0 + 8));
                    temp_v0_2->unk_10 = 0;
                    temp_v0_2->unk_0C = 0;
                    ((S_8016604C_4 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_14 = 0x200000;
                    func_8004491C(temp_v0, &D_80045C34);
                    temp_s0 = (*(void **)((u8 *)temp_v0 + 0xC));
                    temp_s0->unk_14 = (u16) (temp_s0->unk_14 & 0xFFF3);
                    temp_v1 = 0x1000 / (s32) (func_80167088(5) + 6);
                    temp_s0->unk_0C = 0xFF;
                    temp_s0->unk_0E = 0x20;
                    temp_s0->unk_0D = 0x20;
                    temp_s0->unk_1E = (s16) temp_v1;
                    temp_s0->unk_1C = (s16) temp_v1;
                    (*(Packed12 *)((u8 *)temp_v0 + 0x56)) = D_80173B34;
                    temp_s0->unk_08 = (void *) (temp_v0 + 0x56);
                }
            }
            var_s2 += 1;
        } while (var_s2 <= 0);
        var_s3 += 1;
    } while (var_s3 < 3);
}

/* MECHANISM: True-space nested loops plus a held D_80165AB8 base produce the exact 0x30 frame and s5/s4/s3/s2 roles at cdk-G0.
   A byte-aligned 12-byte aggregate produces the retail lwl/lwr/swl/swr copy; distinct RNG/coordinate locals preserve v1/a0 allocation.
   The final 0xFF field is u8 so GCC materializes 0xff rather than canonicalizing it to -1. */
