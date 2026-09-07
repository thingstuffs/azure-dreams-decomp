#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D58D8_0_pre {
    void * unk_00;
    u8 pad_04[0xE];
    u16 unk_12;
} S_800D58D8_0_pre;   /* the 0x14 bytes before arg0 in func_800D58D8, addressed as arg0[-1] */

typedef struct S_800D58D8_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x68];
    s16 unk_94;
    u16 unk_96;
} S_800D58D8_0;   /* arg0 in func_800D58D8 */

typedef struct S_800D58D8_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x1];
    u16 unk_06;
    u8 pad_08[0x24];
    s32 unk_2C;
} S_800D58D8_1;   /* arg2 in func_800D58D8 */

typedef struct S_800D58D8_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800D58D8_2;   /* temp_v0_3 in func_800D58D8 */

typedef struct S_800D58D8_3 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x4];
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
} S_800D58D8_3;   /* temp_a0 in func_800D58D8 */

typedef struct S_800D58D8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D58D8_4;   /* temp_s0_2 in func_800D58D8 */

typedef struct S_800D58D8_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D58D8_5;   /* arg1 in func_800D58D8 */

typedef struct S_800D58D8_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800D58D8_6;   /* temp_a1 in func_800D58D8 */


typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3u16;

M2C_UNK func_8003DB94();  /* extern */
s32 func_8003DE58(void *, void *, Vec3u16 *, s32);     /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80047738();              /* extern */
M2C_UNK func_800478B8();                      /* extern */
extern s32 D_80045340[];
extern s32 D_800814A0;
extern s16 D_80083228[];
extern s32 D_800D586C[];
extern s32 D_800DE870[];

void func_800D58D8(void *arg0, void *arg1, void *arg2) {
    Vec3u16 delta;
    s16 temp_s0;
    void *temp_v0;
    u16 temp_v0_2;
    void *temp_a0;
    void *temp_a1;
    void *temp_s0_2;
    void *temp_v0_3;

    temp_s0 = ((s32) (D_80083228[0] + ((S_800D58D8_0 *)arg0)->unk_2A + 0x100) >> 9) & 7;
    if (((S_800D58D8_0 *)arg0)->unk_94 != temp_s0) {
        temp_v0 = ((S_800D58D8_1 *)arg2)->unk_2C;
        if (temp_v0 != 0) {
            func_80047738(arg2, *((u8 *)temp_v0 + temp_s0), ((S_800D58D8_1 *)arg2)->unk_04);
        }
        ((S_800D58D8_0 *)arg0)->unk_94 = temp_s0;
    }
    func_800478B8(arg2);
    temp_v0_2 = ((S_800D58D8_0 *)arg0)->unk_96 - 1;
    ((S_800D58D8_0 *)arg0)->unk_96 = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        temp_v0_3 = func_8003FC64(0x12);
        if (temp_v0_3 != NULL) {
            func_8004491C(temp_v0_3, &D_80045340);
            temp_a0 = ((S_800D58D8_2 *)temp_v0_3)->unk_0C;
            ((S_800D58D8_3 *)temp_a0)->unk_10 = 0x20;
            ((S_800D58D8_3 *)temp_a0)->unk_14 = (u16) (((S_800D58D8_3 *)temp_a0)->unk_14 | 0xC);
            temp_s0_2 = ((S_800D58D8_2 *)temp_v0_3)->unk_08;
            ((S_800D58D8_4 *)temp_s0_2)->unk_02 = (u16) ((S_800D58D8_5 *)arg1)->unk_02;
            ((S_800D58D8_4 *)temp_s0_2)->unk_06 = (u16) ((S_800D58D8_5 *)arg1)->unk_06;
            ((S_800D58D8_4 *)temp_s0_2)->unk_0A = (u16) ((S_800D58D8_5 *)arg1)->unk_0A;
            temp_a0 = ((S_800D58D8_2 *)temp_v0_3)->unk_0C;
            ((S_800D58D8_3 *)temp_a0)->unk_1E = 0x1800;
            ((S_800D58D8_3 *)temp_a0)->unk_1C = 0x1800;
            ((S_800D58D8_3 *)temp_a0)->unk_0E = 0x80;
            ((S_800D58D8_3 *)temp_a0)->unk_0D = 0x80;
            ((S_800D58D8_3 *)temp_a0)->unk_0C = 0x80;
            ((S_800D58D8_3 *)temp_a0)->unk_06 = (u16) ((S_800D58D8_1 *)arg2)->unk_06;
            ((S_800D58D8_2 *)temp_v0_3)->unk_10 = &D_800D586C;
            temp_a1 = ((S_800D58D8_0_pre *)arg0)[-1].unk_00;
            if (func_8003DE58(((S_800D58D8_6 *)temp_a1)->unk_08, temp_a1, &delta, 0) != 0) {
                ((S_800D58D8_4 *)temp_s0_2)->unk_02 = (u16) (((S_800D58D8_4 *)temp_s0_2)->unk_02 + delta.x);
                ((S_800D58D8_4 *)temp_s0_2)->unk_06 = (u16) (((S_800D58D8_4 *)temp_s0_2)->unk_06 + delta.y);
                ((S_800D58D8_4 *)temp_s0_2)->unk_0A = (u16) (((S_800D58D8_4 *)temp_s0_2)->unk_0A + delta.z);
            }
            func_8003DB94(((S_800D58D8_2 *)temp_v0_3)->unk_0C, &D_800DE870, 0);
        }
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_800D58D8_0_pre *)arg0)[-1].unk_12 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: A six-byte Vec3u16 output object forces the retail 0x30 frame and s0-s4 save set.
   Reusing temp_a0 across disjoint render-pointer live ranges colors both reloads as $a0.
   A scalar global RMW removes the displacement cascade; u8 stores materialize positive 0x80. */
