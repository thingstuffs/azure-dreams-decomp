#include "common.h"
#include "m2c_compat.h"

s32 func_800374F4();                         /* extern */
M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64(s32);               /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                           /* extern */
extern M2C_UNK D_80045340;
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern M2C_UNK D_800A86BC;
extern M2C_UNK D_800F15AC;

typedef struct S_800A878C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800A878C_0;   /* temp_v0 in func_800A878C */

typedef struct S_800A878C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A878C_1;   /* temp_s1 in func_800A878C */

typedef struct S_800A878C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_800A878C_2;   /* arg0 in func_800A878C */

typedef struct S_800A878C_3 {
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
} S_800A878C_3;   /* temp_s0 in func_800A878C */

typedef struct S_800A878C_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    s32 unk_04;
} S_800A878C_4;   /* temp_s3 in func_800A878C */

void *func_800A878C(S_800A878C_2 *arg0, u32 arg1) {
    s16 *temp_a0_2;
    s16 temp_s0_3;
    s16 temp_v0_2;
    s32 temp_a0;
    s32 temp_s0_2;
    s32 var_v0;
    s32 var_v0_2;
    u32 temp_a1;
    S_800A878C_3 *temp_s0;
    S_800A878C_1 *temp_s1;
    S_800A878C_4 *temp_s3;
    void *temp_v0;

    temp_a1 = (arg1 >> 9) & 7;
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s1 = ((S_800A878C_0 *)temp_v0)->unk_08;
        temp_s0 = ((S_800A878C_0 *)temp_v0)->unk_0C;
        ((S_800A878C_0 *)temp_v0)->unk_10 = &D_800A86BC;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = temp_a1;
        temp_s1->unk_02 = (s16) (arg0->unk_02 - (D_8006CCD8[temp_a0] * 0x10));
        temp_a0_2 = &D_8006CCE8[temp_a0];
        temp_s1->unk_06 = (s16) (arg0->unk_06 - (*temp_a0_2 * 0x10));
        temp_s1->unk_0A = (u16) arg0->unk_0A;
        var_v0 = 0 - (arg0->unk_0C * ((rand(temp_a0_2) & 1) + 2));
        temp_s3 = temp_v0 + 0x20;
        if (var_v0 < 0) {
            var_v0 += 0xF;
        }
        temp_s1->unk_0C = (s32) (var_v0 >> 4);
        var_v0_2 = 0 - (arg0->unk_10 * ((rand() & 1) + 2));
        if (var_v0_2 < 0) {
            var_v0_2 += 0xF;
        }
        temp_s1->unk_10 = (s32) (var_v0_2 >> 4);
        temp_s1->unk_14 = (s32) ((~rand() & 1) << 0xF);
        func_8003DB94(temp_s0, &D_800F15AC, 0);
        temp_s0->unk_0E = 0xFF;
        temp_s0->unk_0D = 0xFF;
        temp_s0->unk_0C = 0xFF;
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        temp_s0->unk_10 = 0x60;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
        temp_s0_2 = func_800374F4(7);
        temp_s0_3 = temp_s0_2 + func_800374F4(7);
        temp_s3->unk_02 = temp_s0_3;
        temp_s1->unk_14 = (s32) (0 - (temp_s0_3 << 0x10));
        temp_v0_2 = temp_s3->unk_02;
        temp_s3->unk_04 = (s32) ((s32) (temp_v0_2 * temp_v0_2) / 2);
    }
    return temp_v0;
}

/* MECHANISM: The one-argument allocator ABI and pre-call masked index recover the 0x28 frame and s3 role.
   Sized s16 direction tables and unsigned byte stores recover the scaled lh accesses and li 0xff.
   Spelling the first-table read before the second-table pointer delays the shared sll past lui/addiu. */
