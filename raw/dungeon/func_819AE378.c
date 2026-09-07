#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct UnalignedWord {
    u32 value;
} __attribute__((packed)) UnalignedWord;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

extern void *func_8003FC64(s32);
extern s32 func_8004491C(void *, void *);
extern M2C_UNK D_80025A34;
extern M2C_UNK D_80025AAC;

void *func_80025B78(void *arg0, void *arg1, void *arg2)
{
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v0 = func_8003FC64(0x202);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80025A34;
        func_8004491C(temp_v0, &D_80025AAC);
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1, u16 *, 2) = M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(temp_v1, u16 *, 6) = M2C_FIELD(arg1, u16 *, 6);
        M2C_FIELD(temp_v1, u16 *, 0xA) = M2C_FIELD(arg1, u16 *, 0xA);
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v1_2, u16 *, 0x1C) = M2C_FIELD(arg2, u16 *, 0x1C);
        M2C_FIELD(temp_v1_2, u16 *, 0x1E) = M2C_FIELD(arg2, u16 *, 0x1E);
        M2C_FIELD(temp_v1_2, u16 *, 0x20) = M2C_FIELD(arg2, u16 *, 0x20);
        M2C_FIELD(temp_v1_2, u16 *, 0x16) = M2C_FIELD(arg2, u16 *, 0x16);
        M2C_FIELD(temp_v1_2, u16 *, 0x18) = M2C_FIELD(arg2, u16 *, 0x18);
        M2C_FIELD(temp_v1_2, u16 *, 0x1A) = M2C_FIELD(arg2, u16 *, 0x1A);
        M2C_FIELD(temp_v1_2, s32 *, 0xC) = M2C_FIELD(arg2, s32 *, 0xC);
        M2C_FIELD(temp_v1_2, u16 *, 0x14) = M2C_FIELD(arg2, u16 *, 0x14);
        M2C_FIELD(temp_v1_2, s32 *, 0) = M2C_FIELD(arg2, s32 *, 0);
        M2C_FIELD(temp_v1_2, s32 *, 8) = M2C_FIELD(arg2, s32 *, 8);
        M2C_FIELD(temp_v1_2, u16 *, 0x10) = M2C_FIELD(arg2, u16 *, 0x10);
        M2C_FIELD(temp_v1_2, u8 *, 4) = M2C_FIELD(arg2, u8 *, 4);
        {
            register u32 copy0 ASM_REG("$2");
            register u32 copy1 ASM_REG("$3");
            register u32 copy2 ASM_REG("$4");
            register u32 copy3;

            copy0 = ((UnalignedWord *)arg0)[0].value;
            copy1 = ((UnalignedWord *)arg0)[1].value;
            copy2 = ((UnalignedWord *)arg0)[2].value;
            copy3 = ((UnalignedWord *)arg0)[3].value;
            ASM_KEEP(copy0);
            ASM_KEEP(copy1);
            ASM_KEEP(copy2);
            ASM_KEEP(copy3);
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[0].value = copy0;
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[1].value = copy1;
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[2].value = copy2;
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[3].value = copy3;
            copy0 = ((UnalignedWord *)arg0)[4].value;
            copy1 = ((UnalignedWord *)arg0)[5].value;
            copy2 = ((UnalignedWord *)arg0)[6].value;
            copy3 = ((UnalignedWord *)arg0)[7].value;
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[4].value = copy0;
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[5].value = copy1;
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[6].value = copy2;
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[7].value = copy3;
        }
    }
    return temp_v0;
}
