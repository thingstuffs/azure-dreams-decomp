#include "common.h"

typedef struct S_80174DA0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80174DA0_0;   /* obj in func_80174DA0 */

typedef struct S_80174DA0_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80174DA0_1;   /* arg0 in func_80174DA0 */

typedef struct S_80174DA0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_80174DA0_2;   /* dst in func_80174DA0 */

typedef struct S_80174DA0_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_80174DA0_3;   /* aux in func_80174DA0 */

typedef struct S_80174DA0_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    u8 * unk_10;
    u8 pad_14[0x2];
    u8 unk_16;
    u8 pad_17[0x5];
    void * unk_1C;
} S_80174DA0_4;   /* tail in func_80174DA0 */

typedef struct S_80174DA0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174DA0_5;   /* ((S_80174DA0_1 *)arg0)->unk_08 in func_80174DA0 */



extern void *func_8003FD64();
extern u8 D_80174AD4[9];
extern u8 D_80175F90[9];

void func_80174DA0(S_80174DA0_1 *arg0, s32 arg1, u8 *arg2)
{
    void *obj;
    S_80174DA0_2 *dst;
    S_80174DA0_3 *aux;
    S_80174DA0_4 *tail;
    void *p8;
    u16 value;

    obj = func_8003FD64(0x12, arg0);
    if (obj != 0) {
        ((S_80174DA0_0 *)obj)->unk_10 = D_80174AD4;
        dst = ((S_80174DA0_0 *)obj)->unk_08;

        value = ((S_80174DA0_5 *)(arg0->unk_08))->unk_02;
        dst->unk_0E = value;
        dst->unk_02 = value;

        value = ((S_80174DA0_5 *)(arg0->unk_08))->unk_06;
        dst->unk_12 = value;
        dst->unk_06 = value;

        value = ((S_80174DA0_5 *)(arg0->unk_08))->unk_0A;
        dst->unk_16 = value;
        dst->unk_0A = value;

        aux = ((S_80174DA0_0 *)obj)->unk_0C;
        aux->unk_08 = D_80175F90;
        aux->unk_1E = 0x1000;
        aux->unk_1C = 0x1000;
        aux->unk_0C = 0;
        aux->unk_06 = 8;

        p8 = arg0->unk_08;
        tail = (u8 *)obj + 0x20;
        tail->unk_0C = arg1;
        tail->unk_10 = arg2;
        tail->unk_1C = p8;
        tail->unk_16 = *arg2;
        ((S_80174DA0_0 *)obj)->unk_20 = 0x40;
        tail->unk_04 = 0;
    }
}
