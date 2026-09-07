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

void func_800A34BC(void *arg0) {
    void *temp_v0;

    temp_v0 = M2C_FIELD((M2C_FIELD(arg0, u8 *, 0x13) * 0x14) + (s8 *)D_8007359C[0], void **, 4);
    M2C_FIELD(arg0, Copy12 *, 0x34) = M2C_FIELD(temp_v0, Copy12 *, 0);
    M2C_FIELD(arg0, s8 *, 0x3C) = 0;
}
