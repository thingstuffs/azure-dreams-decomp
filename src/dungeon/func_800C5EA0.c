#include "common.h"


typedef struct {
    u16 unk0;
    u16 flags;
    u8 pad4[6];
    u16 fieldA;
    void *fieldC;
    void *field10;
} D_80083460_t;

extern D_80083460_t D_80083460;
extern s32 D_8008346C;
extern s32 D_800814A0[3];

void func_8009A028(void *arg0);


typedef struct S_800CB600_0_pre {
    u16 unk_00;
} S_800CB600_0_pre;   /* the 0x2 bytes before arg0 in func_800CB600, addressed as arg0[-1] */

typedef struct S_800CB600_0 {
    u8 pad_00[0x8A];
    union { u16 u; s16 s; } unk_8A;   /* accessed as both */
    u8 pad_8C[0x6];
    u16 unk_92;
    union { u16 u; s16 s; } unk_94;   /* accessed as both */
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 unk_9A;
    u8 pad_9B[0x2];
    u8 unk_9D;
} S_800CB600_0;   /* arg0 in func_800CB600 */

typedef struct S_800CB600_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
    u16 unk_1E;
} S_800CB600_1;   /* arg2 in func_800CB600 */

typedef struct S_800CB600_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800CB600_2;   /* arg1 in func_800CB600 */

typedef struct S_800CB600_3 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800CB600_3;   /* temp_a0 in func_800CB600 */

void func_800CB600(void *arg0, S_800CB600_2 *arg1, S_800CB600_1 *arg2) {
    u16 temp_v0;
    s8 value;
    s32 product;
    s32 phase;
    s16 temp_a0_value;
    s16 temp_v0_4;
    s16 temp_v0_5;
    u16 temp_v1_2;
    u16 temp_v1_3;
    u16 temp_v1_4;
    S_800CB600_3 *temp_a0;
    D_80083460_t *state;

    temp_v0 = ((S_800CB600_0 *)arg0)->unk_94.u + 1;
    ((S_800CB600_0 *)arg0)->unk_94.u = temp_v0;
    if ((s16)temp_v0 >= 0x41) {
        ((S_800CB600_0 *)arg0)->unk_94.u = 0x40;
    }

    product = ((S_800CB600_0 *)arg0)->unk_94.s * 2;
    product *= ((S_800CB600_0 *)arg0)->unk_9D & 1;
    value = (u8)((S_800CB600_0 *)arg0)->unk_94.u + product;
    arg2->unk_0C = value;
    arg2->unk_0E = value;
    arg2->unk_0D = value;

    phase = ((S_800CB600_0 *)arg0)->unk_9A;
    ((S_800CB600_0 *)arg0)->unk_9D = ((S_800CB600_0 *)arg0)->unk_9D + 1;
    if (phase == 0) {
        temp_v0 = ((S_800CB600_0 *)arg0)->unk_8A.u - 8;
        ((S_800CB600_0 *)arg0)->unk_8A.u = temp_v0;
        if ((s16)temp_v0 < -0x80) {
            ((S_800CB600_0 *)arg0)->unk_8A.s = -0x80;
        }

        arg1->unk_0A =
            (s16)(((S_800CB600_0 *)arg0)->unk_92 + ((S_800CB600_0 *)arg0)->unk_8A.u);

        temp_v1_2 = arg2->unk_1C;
        temp_a0_value = ((S_800CB600_0 *)arg0)->unk_96.s;
        temp_v1_3 = temp_v1_2 + ((0x1000 - temp_v1_2) / temp_a0_value);
        arg2->unk_1C = temp_v1_3;
        arg2->unk_1E = temp_v1_3;

        temp_v0 = ((S_800CB600_0 *)arg0)->unk_96.u - 1;
        ((S_800CB600_0 *)arg0)->unk_96.u = temp_v0;
        if ((s16)temp_v0 > 0) {
            return;
        }

        state = &D_80083460;
        ((S_800CB600_0 *)arg0)->unk_96.u = 0;
        if (state->fieldC != 0) {
            return;
        }
        if (state->field10 != 0) {
            return;
        }
        if (state->flags & 8) {
            return;
        }

        state->fieldC = arg0;
        ((S_800CB600_0 *)arg0)->unk_98 |= 0x80;
        ((S_800CB600_0 *)arg0)->unk_9A++;
        return;
    }

    if (phase == 1) {
        if (D_8008346C != 0) {
            return;
        }

        func_8009A028(arg0);
        temp_a0 = (u8 *)arg0 - 0x20;
        temp_a0->unk_10 |= 0x80000000;
        ((S_800CB600_0 *)arg0)->unk_96.u = 0x10;
        ((S_800CB600_0 *)arg0)->unk_9A++;
        return;
    }

    temp_v1_4 = arg2->unk_1C;
    temp_v0_4 = ((S_800CB600_0 *)arg0)->unk_96.s;
    temp_v0_5 = temp_v1_4 / temp_v0_4;
    temp_v1_4 -= temp_v0_5;
    arg2->unk_1C = temp_v1_4;
    arg2->unk_1E = temp_v1_4;

    temp_v0 = ((S_800CB600_0 *)arg0)->unk_96.u - 1;
    ((S_800CB600_0 *)arg0)->unk_96.u = temp_v0;
    if ((s16)temp_v0 > 0) {
        return;
    }

    D_80083460.fieldA--;
    ((S_800CB600_0_pre *)arg0)[-1].unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
}
