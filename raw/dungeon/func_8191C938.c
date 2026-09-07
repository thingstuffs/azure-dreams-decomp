#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((u8 *)(expr) + (offset)))
#ifndef NULL
#define NULL 0
#endif

extern void func_8002426C() __attribute__((noreturn));
extern s32 func_8003DB94(void *, void *, s16);
extern void *func_8003FC64(u32);
extern s32 func_8004491C(void *, void *);
extern s32 rand(void);
extern u8 D_80024048[];
extern u8 D_80045340[];
extern u8 D_800DED70[];

typedef struct CopyBlock {
    s32 word[6];
} CopyBlock;

void *func_8191C938(void *arg0)
{
    s32 temp_v0_2;
    CopyBlock *temp_a0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0;
    CopyBlock *temp_v0_3;
    register void *result ASM_REG("$2");
    register u16 override;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, s32 **, 0x10) = D_80024048;
        M2C_FIELD(temp_v0, void **, 0x20) = arg0;
        M2C_FIELD(temp_s0, s16 *, 4) = 0;
        M2C_FIELD(temp_s0, s16 *, 6) = 6;
        temp_v0_2 = rand();
        M2C_FIELD(temp_s0, s16 *, 8) = temp_v0_2 % 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0xA) = 0x10;
        temp_s0_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0_2, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s0_2, u8 *, 0xC) = 0x80;
        M2C_FIELD(temp_s0_2, s8 *, 0xE) = 0;
        M2C_FIELD(temp_s0_2, s16 *, 0x12) = 0x7DCF;
        M2C_FIELD(temp_s0_2, u16 *, 0x14) |= 0xC;
        M2C_FIELD(temp_s0_2, u16 *, 0x10) |= 0x20;
        M2C_FIELD(temp_s0_2, u16 *, 0x14) |= 0x100;
        func_8003DB94(temp_s0_2, D_800DED70, 0);
        M2C_FIELD(temp_s0_2, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_s0_2, s16 *, 0x1C) = 0x1000;
        func_8004491C(temp_v0, D_80045340);
        temp_a0 = M2C_FIELD(temp_v0, CopyBlock **, 8);
        temp_v0_3 = M2C_FIELD(arg0, CopyBlock **, 0x20);
        *temp_a0 = *temp_v0_3;
        override = M2C_FIELD(arg0, u16 *, 0x16);
        ASM_KEEP(override);
        result = temp_v0;
        ASM_KEEP(result);
        M2C_FIELD(temp_a0, u16 *, 0xA) = override;
        func_8002426C(temp_a0);
        return temp_v0;
    }
    result = NULL;
    ASM_KEEP(result);
    return result;
}
