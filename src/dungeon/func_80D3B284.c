#include "common.h"

typedef struct S_80170A84_0_pre {
    u16 unk_00;
} S_80170A84_0_pre;   /* the 0x2 bytes before arg0 in func_80170A84, addressed as arg0[-1] */

typedef struct S_80170A84_0 {
    u8 pad_00[0x2C];
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    u8 pad_2E[0x8];
    union { u16 s; s16 u; } unk_36;   /* accessed as both */
    s16 unk_38;
    u8 pad_3A[0x6];
    void * unk_40;
    u32 * unk_44;
} S_80170A84_0;   /* arg0 in func_80170A84 */

typedef struct S_80170A84_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80170A84_1_pre;   /* the 0x14 bytes before base in func_80170A84, addressed as base[-1] */

typedef struct S_80170A84_1 {
    u8 pad_00[0x9B];
    u8 unk_9B;
    u8 pad_9C[0x15];
    u8 unk_B1;
    u8 pad_B2[0x1];
    u8 unk_B3;
} S_80170A84_1;   /* base in func_80170A84 */

typedef struct S_80170A84_2 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_80170A84_2;   /* arg2 in func_80170A84 */

typedef struct S_80170A84_3 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80170A84_3;   /* ((S_80170A84_1_pre *)base)[-1].unk_00 in func_80170A84 */



extern void *D_80170808[];
extern s32 D_800814A0[3];

void func_80170A84(void *arg0, void *arg1, S_80170A84_2 *arg2)
{
    u8 *base;
    u32 *source;
    void *volatile *table;
    u16 copied;
    u16 angle;
    u16 state;
    u16 twenty;
    s32 dispatch;
    static void *const keepalive[] = {
        &&case_0, &&case_1, &&case_2,
        &&case_3, &&case_4, &&case_5,
        &&done
    };

    base = ((S_80170A84_0 *)arg0)->unk_40;
    source = ((S_80170A84_0 *)arg0)->unk_44;
    copied = ((S_80170A84_3 *)(((S_80170A84_1_pre *)base)[-1].unk_00))->unk_06;

    angle = arg2->unk_1A + 400;
    arg2->unk_1A = angle;
    arg2->unk_06 = copied;
    if (angle >= 4097) {
        arg2->unk_1A = angle - 4096;
    }

    dispatch = ((S_80170A84_0 *)arg0)->unk_2C.s;
    if ((u32)dispatch >= 6) {
        goto done;
    }
    table = D_80170808;
    (void)keepalive;
    goto *table[dispatch];

case_0:
    {
        u16 count = ((S_80170A84_0 *)arg0)->unk_36.s;
        s16 limit = ((S_80170A84_0 *)arg0)->unk_38;
        s32 value;

        count++;
        value = ((count << 16) >> 9) / limit;
        ((S_80170A84_0 *)arg0)->unk_36.s = count;
        arg2->unk_0C = value;
        arg2->unk_0D = value;
        arg2->unk_0E = value;
    }
    if (((S_80170A84_0 *)arg0)->unk_36.u < 5) {
        goto done;
    }
    state = ((S_80170A84_0 *)arg0)->unk_2C.u;
    state++;
    goto skip_counter;

case_5:
    if (((S_80170A84_1 *)base)->unk_9B >= 4) {
        ((S_80170A84_0 *)arg0)->unk_36.s = 0;
        ((S_80170A84_0 *)arg0)->unk_38 = 20;
        ((S_80170A84_0 *)arg0)->unk_2C.u++;
    }
    if (((S_80170A84_1 *)base)->unk_B3 != 3 || ((S_80170A84_1 *)base)->unk_B1 != 2) {
        goto done;
    }
    ((S_80170A84_0 *)arg0)->unk_2C.u = 4;
    ((S_80170A84_0 *)arg0)->unk_38 = 20;
    ((S_80170A84_0 *)arg0)->unk_36.s = 20;
    goto done;

case_1:
    {
        u16 count = ((S_80170A84_0 *)arg0)->unk_36.s;
        s16 limit = ((S_80170A84_0 *)arg0)->unk_38;
        s32 value;

        count++;
        value = ((count << 16) >> 9) / limit;
        ((S_80170A84_0 *)arg0)->unk_36.s = count;
        arg2->unk_0C = value;
        arg2->unk_0D = value;
        arg2->unk_0E = value;
    }
    if (((S_80170A84_0 *)arg0)->unk_36.u < ((S_80170A84_0 *)arg0)->unk_38) {
        goto done;
    }
    state = ((S_80170A84_0 *)arg0)->unk_2C.u;
    twenty = 20;
    ((S_80170A84_0 *)arg0)->unk_38 = twenty;
    goto common_counter;

case_2:
    {
        u16 count = ((S_80170A84_0 *)arg0)->unk_36.s;
        s16 limit = ((S_80170A84_0 *)arg0)->unk_38;
        s32 value;

        count--;
        value = ((count << 16) >> 9) / limit;
        ((S_80170A84_0 *)arg0)->unk_36.s = count;
        arg2->unk_0C = value;
        arg2->unk_0D = value;
        arg2->unk_0E = value;
    }
    if (((S_80170A84_0 *)arg0)->unk_36.u > 0) {
        goto done;
    }
    ((S_80170A84_0_pre *)arg0)[-1].unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
    goto done;

case_3:
    {
        u16 count = ((S_80170A84_0 *)arg0)->unk_36.s;
        s16 limit = ((S_80170A84_0 *)arg0)->unk_38;
        s32 value;

        count--;
        value = ((count << 16) >> 9) / limit;
        ((S_80170A84_0 *)arg0)->unk_36.s = count;
        arg2->unk_0C = value;
        arg2->unk_0D = value;
        arg2->unk_0E = value;
    }
    if (((S_80170A84_0 *)arg0)->unk_36.u > 0) {
        goto done;
    }
    state = ((S_80170A84_0 *)arg0)->unk_2C.u;
    twenty = 20;

common_counter:
    ((S_80170A84_0 *)arg0)->unk_36.s = twenty;
    state++;

skip_counter:
    ((S_80170A84_0 *)arg0)->unk_2C.u = state;
    goto done;

case_4:
    {
        u16 count = ((S_80170A84_0 *)arg0)->unk_36.s;

        ((S_80170A84_0 *)arg0)->unk_36.s = count - 1;
        if ((count << 16) > 0) {
            goto done;
        }
    }
    ((S_80170A84_0 *)arg0)->unk_2C.u = 2;
    ((S_80170A84_0 *)arg0)->unk_36.s = 0;
    ((S_80170A84_0 *)arg0)->unk_38 = 20;

done:
    ((u32 *)arg1)[0] = source[0];
    ((u32 *)arg1)[1] = source[1];
    ((u32 *)arg1)[2] = source[2];
}
