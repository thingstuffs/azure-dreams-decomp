#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

typedef struct {
    s32 unk0;
    void *unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Entry8007359C;

extern Entry8007359C *D_8007359C[4];


typedef struct S_800A34BC_0 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800A34BC_0;   /* ((*(u8 *)((u8 *)arg0 + 0x13)) * 0x14) + (s8 *)D_8007359C[0] in func_800A34BC */

void func_800A34BC(void *arg0) {
    void *temp_v0;

    temp_v0 = ((S_800A34BC_0 *)(((*(u8 *)((u8 *)arg0 + 0x13)) * 0x14) + (s8 *)D_8007359C[0]))->unk_04;
    (*(Copy12 *)((u8 *)arg0 + 0x34)) = (*(Copy12 *)((u8 *)temp_v0 + 0));
    (*(s8 *)((u8 *)arg0 + 0x3C)) = 0;
}
