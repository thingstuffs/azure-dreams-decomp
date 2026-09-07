#include "common.h"


extern s32 D_800814A0[3];


typedef struct S_801747B8_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    u8 pad_10[0x4];
    u16 unk_14;
} S_801747B8_0;   /* arg2 in func_801747B8 */

typedef struct S_801747B8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801747B8_1;   /* arg1 in func_801747B8 */

typedef struct S_801747B8_2 {
    u8 pad_00[0x20];
    u16 unk_20;
    u8 pad_22[0x4];
    u16 unk_26;
    u8 pad_28[0x4];
    u16 unk_2C;
} S_801747B8_2;   /* dst in func_801747B8 */

typedef struct S_801747B8_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_801747B8_3;   /* (*(void * *)((u8 *)arg0 + 0x18)) in func_801747B8 */

typedef struct S_801747B8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801747B8_4;   /* (*(void * *)((u8 *)arg0 + 0x1C)) in func_801747B8 */

void func_801747B8(void *arg0, S_801747B8_1 *arg1, S_801747B8_0 *arg2)
{
    s16 state;
    s32 count;
    u8 *dst;

    arg2->unk_08 = ((S_801747B8_3 *)((*(void * *)((u8 *)arg0 + 0x18))))->unk_08;
    arg2->unk_14 =
        ((S_801747B8_3 *)((*(void * *)((u8 *)arg0 + 0x18))))->unk_14 | 0xC;

    if ((*(u8 *)((u8 *)arg0 + 0x17)) == 0) {
        state = (*(s16 *)((u8 *)arg0 + 0x34));
        if (arg2->unk_0C.u8 < (0x80 >> state)) {
            arg2->unk_0C.s32 += 0x101010;
            goto continuation;
        }
        (*(u8 *)((u8 *)arg0 + 0x17))++;
        goto continuation;
    }

    if (arg2->unk_0C.u8 == 0) {
        goto no_adjustment;
    }
    arg2->unk_0C.s32 += -0x80808;
    goto continuation;

no_adjustment:
    (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
    D_800814A0[0] |= 0x8000;

continuation:
    arg1->unk_02 = (*(u16 *)((u8 *)arg0 + 0x20));
    arg1->unk_06 = (*(u16 *)((u8 *)arg0 + 0x26));
    arg1->unk_0A = (*(u16 *)((u8 *)arg0 + 0x2C));

    count = 0;
    if ((*(s16 *)((u8 *)arg0 + 0x34)) > 0) {
        do {
            (*(u16 *)((u8 *)arg0 + count * 2 + 0x20)) = (*(u16 *)((u8 *)arg0 + count * 2 + 0x22));
            (*(u16 *)((u8 *)arg0 + count * 2 + 0x26)) = (*(u16 *)((u8 *)arg0 + count * 2 + 0x28));
            (*(u16 *)((u8 *)arg0 + count * 2 + 0x2C)) = (*(u16 *)((u8 *)arg0 + count * 2 + 0x2E));
            count++;
        } while (count < (*(s16 *)((u8 *)arg0 + 0x34)));
    }

    dst = (u8 *)(count * 2 + (s32)(u32)arg0);
    ((S_801747B8_2 *)dst)->unk_20 = ((S_801747B8_4 *)((*(void * *)((u8 *)arg0 + 0x1C))))->unk_02;
    ((S_801747B8_2 *)dst)->unk_26 = ((S_801747B8_4 *)((*(void * *)((u8 *)arg0 + 0x1C))))->unk_06;
    ((S_801747B8_2 *)dst)->unk_2C = ((S_801747B8_4 *)((*(void * *)((u8 *)arg0 + 0x1C))))->unk_0A;
}
