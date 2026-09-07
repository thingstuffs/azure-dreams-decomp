#include "common.h"



typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800374F4();
extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern M2C_UNK D_80045340;
extern M2C_UNK D_800A8440;
extern M2C_UNK D_800D1464;

typedef struct S_800A84D0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800A84D0_0;   /* temp_v0 in func_800A84D0 */

typedef struct S_800A84D0_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A84D0_1;   /* temp_s1 in func_800A84D0 */

typedef struct S_800A84D0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A84D0_2;   /* arg0 in func_800A84D0 */

typedef struct S_800A84D0_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800A84D0_3;   /* temp_s0 in func_800A84D0 */

typedef struct S_800A84D0_4 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800A84D0_4;   /* temp_v1 in func_800A84D0 */

void *func_800A84D0(S_800A84D0_2 *arg0) {
    s32 temp_s0_2;
    S_800A84D0_3 *temp_s0;
    S_800A84D0_1 *temp_s1;
    void *temp_v0;
    S_800A84D0_4 *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s1 = ((S_800A84D0_0 *)temp_v0)->unk_08;
        temp_s0 = ((S_800A84D0_0 *)temp_v0)->unk_0C;
        ((S_800A84D0_0 *)temp_v0)->unk_10 = &D_800A8440;
        func_8004491C(temp_v0, &D_80045340);
        temp_s1->unk_02 = (u16) arg0->unk_02;
        temp_s1->unk_06 = (u16) arg0->unk_06;
        temp_s1->unk_0A = (u16) arg0->unk_0A;
        func_8003DB94(temp_s0, &D_800D1464, 0);
        temp_s0->unk_0E = 0xFF;
        temp_s0->unk_0D = 0xFF;
        temp_s0->unk_0C = 0xFF;
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        temp_s0->unk_10 = 0x60;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
        temp_s0_2 = func_800374F4(7);
        temp_v1 = temp_v0 + 0x20;
        temp_v1->unk_02 = (s16) (temp_s0_2 + func_800374F4(7));
    }
    return temp_v0;
}

/* MECHANISM: Preserve the seed's 0x28 frame and s3/s2/s1/s0 held-value layout.
   Unsigned byte stores force li 0x00ff at word 33; signed s8 had emitted li -1. */
