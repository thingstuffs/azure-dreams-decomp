#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct {
    s32 words[3];
} __attribute__((packed)) Packed12;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_7003CF18();
M2C_UNK func_7010C274();

extern s32 D_80086AD8;
extern u16 D_80094422;
extern u8 D_800E0F20[16];
extern M2C_UNK D_8010BF40;
extern Packed12 D_8010C450;


typedef struct S_7FFE99BC_0_pre {
    u16 unk_00;
} S_7FFE99BC_0_pre;   /* the 0x2 bytes before arg0 in func_7FFE99BC, addressed as arg0[-1] */

typedef struct S_7FFE99BC_0 {
    void * unk_00;
    u8 pad_04[0x12];
    u16 unk_16;
    u8 pad_18[0x6];
    u16 unk_1E;
} S_7FFE99BC_0;   /* arg0 in func_7FFE99BC */

typedef struct S_7FFE99BC_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_7FFE99BC_1;   /* temp_a0 in func_7FFE99BC */

typedef struct S_7FFE99BC_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_7FFE99BC_2;   /* temp_v1_2 in func_7FFE99BC */

typedef struct S_7FFE99BC_3 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_7FFE99BC_3;   /* ((S_7FFE99BC_0 *)arg0)->unk_00 in func_7FFE99BC */

void func_7FFE99BC(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s16 temp_v1;
    u16 temp_v0_2;
    void *temp_a0;
    void *temp_v0;
    void *temp_v1_2;

    temp_v1 = ((S_7FFE99BC_0 *)arg0)->unk_16 + 1;
    ((S_7FFE99BC_0 *)arg0)->unk_16 = (u16)temp_v1;
    if ((temp_v1 < 0x17) && (temp_v1 & 1)) {
        temp_v0 = func_7003CF18(0x212);
        if (temp_v0 != NULL) {
            func_7010C274(temp_v0, arg0, arg1, arg2);
            (*(s16 *)((u8 *)temp_v0 + 0x3E)) = 0x1E;
            (*(s16 *)((u8 *)temp_v0 + 0x40)) = 0x1E;
            (*(M2C_UNK **)((u8 *)temp_v0 + 0x10)) = &D_8010BF40;
            temp_a0 = (*(void **)((u8 *)temp_v0 + 8));
            ((S_7FFE99BC_1 *)temp_a0)->unk_0A =
                (u16)(((S_7FFE99BC_1 *)temp_a0)->unk_0A -
                (D_800E0F20[(u8)((S_7FFE99BC_3 *)(((S_7FFE99BC_0 *)arg0)->unk_00))->unk_13] >> 1));
            temp_v1_2 = (*(void **)((u8 *)temp_v0 + 0xC));
            (*(Packed12 *)((u8 *)temp_v0 + 0x62)) = D_8010C450;
            ((S_7FFE99BC_2 *)temp_v1_2)->unk_08 = (void *)(temp_v0 + 0x62);
            ((S_7FFE99BC_2 *)temp_v1_2)->unk_1E = 0x3E8;
            ((S_7FFE99BC_2 *)temp_v1_2)->unk_1C = 0x3E8;
            ((S_7FFE99BC_2 *)temp_v1_2)->unk_06 = 0x64;
        }
    }
    temp_v0_2 = ((S_7FFE99BC_0 *)arg0)->unk_1E - 1;
    ((S_7FFE99BC_0 *)arg0)->unk_1E = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        u16 *counter = &D_80094422;
        u16 next_counter;

        (*(u16 *)((u8 *)arg0 + -2)) =
            (u16)(((S_7FFE99BC_0_pre *)arg0)[-1].unk_00 | 0x8000);
        next_counter = *counter - 1;
        D_80086AD8 |= 0x8000;
        *counter = next_counter;
    }
}
