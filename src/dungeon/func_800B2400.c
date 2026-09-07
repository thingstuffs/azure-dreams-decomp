#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800B7B60_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800B7B60_0;   /* temp_v0 in func_800B7B60 */

typedef struct S_800B7B60_1_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800B7B60_1_pre;   /* the 0x18 bytes before arg0 in func_800B7B60, addressed as arg0[-1] */

typedef struct S_800B7B60_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B7B60_2;   /* temp_v1 in func_800B7B60 */

typedef struct S_800B7B60_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B7B60_3;   /* temp_a1 in func_800B7B60 */


typedef struct {
    u8 pad[0xA];
    u16 value;
} Counter;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FC64();
extern M2C_UNK func_800B8024();
extern Counter D_80083460;
extern M2C_UNK D_800B7774;

void *func_800B7B60(void *arg0, s32 *arg1) {
    u16 temp_a2;
    S_800B7B60_3 *temp_a1;
    S_800B7B60_0 *temp_v0;
    S_800B7B60_2 *temp_v1;

    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = &D_800B7774;
        temp_v0->unk_20 = *arg1;
        temp_a1 = ((S_800B7B60_1_pre *)arg0)[-1].unk_00;
        temp_v1 = temp_v0->unk_08;
        temp_v1->unk_02 = temp_a1->unk_02;
        temp_v1->unk_06 = temp_a1->unk_06;
        temp_a2 = temp_a1->unk_0A;
        temp_v1->unk_0A = temp_a2;
        func_800B8024((s16) temp_v1->unk_02, (s16) temp_v1->unk_06, (s16) temp_a2);
        D_80083460.value++;
    }
    return temp_v0;
}
