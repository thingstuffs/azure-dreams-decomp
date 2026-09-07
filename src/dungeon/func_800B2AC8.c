#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800B8228_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800B8228_0;   /* temp_v0 in func_800B8228 */

typedef struct S_800B8228_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_800B8228_1;   /* temp_v1 in func_800B8228 */

typedef struct S_800B8228_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800B8228_2;   /* temp_s0 in func_800B8228 */

typedef struct S_800B8228_3 {
    u8 pad_00[0xB0];
    s16 unk_B0;
    s16 unk_B2;
} S_800B8228_3;   /* temp_v1_2 in func_800B8228 */


typedef struct {
    u32 value;
} __attribute__((packed)) PackedWord;


extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_800A56E0(s32);
extern s32 func_800A7A38(void *, s32);
extern void func_800A7A7C(s32, s32, s32, void *, void *);
extern void func_800BC26C(void *, s32, s32, s32);

extern u8 D_80045340[];
extern u8 D_8006E240[9];
extern u8 D_800B80D8[];

void *func_800B8228(u32 arg0, u32 arg1, s32 arg2, void *arg3) {
    S_800B8228_2 *temp_s0;
    void *temp_v0;
    S_800B8228_1 *temp_v1;
    S_800B8228_3 *temp_v1_2;

    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 == NULL)
        goto failure;

    {
        func_8004491C(temp_v0, D_80045340);
        ((S_800B8228_0 *)temp_v0)->unk_10 = D_800B80D8;
        temp_v1 = ((S_800B8228_0 *)temp_v0)->unk_08;
        temp_v1->unk_02 = arg0;
        temp_v1->unk_06 = arg1;
        temp_v1->unk_0A = arg2;
        temp_v1->unk_16 = -0x12;
        temp_s0 = ((S_800B8228_0 *)temp_v0)->unk_0C;
        temp_s0->unk_0C = 0x808080;
        temp_s0->unk_1E = 0xC90;
        temp_s0->unk_1C = 0xC90;
        temp_s0->unk_08 = func_800A7A38(arg3,
                                               temp_s0->unk_0C);
        temp_v1_2 = (u8 *)temp_v0 + 0x20;
        temp_v1_2->unk_B0 = arg0 >> 6;
        temp_v1_2->unk_B2 = arg1 >> 6;
        *(PackedWord *)((u8 *)temp_v0 + 0xB8) = *(PackedWord *)arg3;
        func_800BC26C(temp_v0, 0, 0, 0);
        func_800A56E0(0x51C);
    }

    goto done;

failure:
    func_800A7A7C((s32)(arg0 << 0xA) >> 0x10,
                  (s32)(arg1 << 0xA) >> 0x10,
                  (s32)(arg2 << 0x10) >> 0x10,
                  D_8006E240, arg3);

done:
    return temp_v0;
}
