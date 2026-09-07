#include "common.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

void *func_7003CF18();
s32 func_700750E0();
M2C_UNK func_7010BD54();
extern s32 D_80086AD8;
extern u16 D_80094422;
extern M2C_UNK D_8010BA44;
extern Copy12 D_8010BF30;


typedef struct S_7FFE9150_0_pre {
    u16 unk_00;
} S_7FFE9150_0_pre;   /* the 0x2 bytes before arg0 in func_7FFE9150, addressed as arg0[-1] */

typedef struct S_7FFE9150_0 {
    u8 pad_00[0x16];
    u16 unk_16;
    u8 pad_18[0x6];
    u16 unk_1E;
    u8 pad_20[0x4];
    void * unk_24;
    u8 pad_28[0x14];
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
} S_7FFE9150_0;   /* arg0 in func_7FFE9150 */

typedef struct S_7FFE9150_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_7FFE9150_1;   /* arg1 in func_7FFE9150 */

typedef struct S_7FFE9150_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_7FFE9150_2;   /* temp_a0 in func_7FFE9150 */

typedef struct S_7FFE9150_3 {
    s32 unk_00;
    s32 unk_04;
} S_7FFE9150_3;   /* temp_s0 in func_7FFE9150 */

typedef struct S_7FFE9150_4 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x10];
    s16 unk_1C;
} S_7FFE9150_4;   /* temp_v1 in func_7FFE9150 */

typedef struct S_7FFE9150_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_7FFE9150_5;   /* ((S_7FFE9150_2 *)temp_a0)->unk_08 in func_7FFE9150 */

void func_7FFE9150(void *arg0, void *arg1, M2C_UNK arg2) {
    u16 temp_v0;
    u16 temp_v0_3;
    void *temp_a0;
    void *temp_s0;
    void *temp_v0_2;
    void *temp_v1;

    temp_a0 = ((S_7FFE9150_0 *)arg0)->unk_24;
    ((S_7FFE9150_1 *)arg1)->unk_02 = (s16)(((S_7FFE9150_5 *)(((S_7FFE9150_2 *)temp_a0)->unk_08))->unk_02 + ((S_7FFE9150_0 *)arg0)->unk_3C);
    ((S_7FFE9150_1 *)arg1)->unk_06 = (s16)(((S_7FFE9150_5 *)(((S_7FFE9150_2 *)temp_a0)->unk_08))->unk_06 + ((S_7FFE9150_0 *)arg0)->unk_3E);
    ((S_7FFE9150_1 *)arg1)->unk_0A = (s16)(((S_7FFE9150_5 *)(((S_7FFE9150_2 *)temp_a0)->unk_08))->unk_0A + ((S_7FFE9150_0 *)arg0)->unk_40);
    temp_v0 = ((S_7FFE9150_0 *)arg0)->unk_16 + 1;
    ((S_7FFE9150_0 *)arg0)->unk_16 = temp_v0;
    if ((s16)temp_v0 < 0x14) {
        temp_v0_2 = func_7003CF18(0x212);
        if (temp_v0_2 != 0) {
            func_7010BD54(temp_v0_2, arg0, arg1, arg2);
            temp_s0 = (*(void **)((u8 *)temp_v0_2 + 8));
            (*(s16 *)((u8 *)temp_v0_2 + 0x3E)) = 0x14;
            (*(s16 *)((u8 *)temp_v0_2 + 0x40)) = 0x14;
            (*(M2C_UNK **)((u8 *)temp_v0_2 + 0x10)) = &D_8010BA44;
            ((S_7FFE9150_3 *)temp_s0)->unk_00 = (s32)((((func_700750E0() & 0x7FFF) - 0x4000) << 7) + ((S_7FFE9150_3 *)temp_s0)->unk_00);
            ((S_7FFE9150_3 *)temp_s0)->unk_04 = (s32)((((func_700750E0() & 0x7FFF) - 0x4000) << 7) + ((S_7FFE9150_3 *)temp_s0)->unk_04);
            temp_v1 = (*(void **)((u8 *)temp_v0_2 + 0xC));
            (*(Copy12 *)((u8 *)temp_v0_2 + 0x62)) = D_8010BF30;
            ((S_7FFE9150_4 *)temp_v1)->unk_08 = (void *)((u8 *)temp_v0_2 + 0x62);
            ((S_7FFE9150_4 *)temp_v1)->unk_1C = 0x400;
        }
    }
    temp_v0_3 = ((S_7FFE9150_0 *)arg0)->unk_1E - 1;
    ((S_7FFE9150_0 *)arg0)->unk_1E = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        u16 *global_count = &D_80094422;
        u16 next_global_count;

        (*(u16 *)((u8 *)arg0 + -2)) = (u16)(((S_7FFE9150_0_pre *)arg0)[-1].unk_00 | 0x8000);
        next_global_count = *global_count - 1;
        D_80086AD8 |= 0x8000;
        *global_count = next_global_count;
    }
}
