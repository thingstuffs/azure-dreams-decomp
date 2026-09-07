#include "common.h"
typedef long long s64;

typedef s32 M2C_UNK;

typedef struct {
    s32 words[6];
} Copy24;

typedef struct {
    s32 words[4];
} Copy16;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define MULT_HI(a, b) (0)

extern s32 D_80045C34[3];
void func_80025078() __attribute__((noreturn));
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
extern M2C_UNK D_80024C48;
extern M2C_UNK D_80025AF0;

s32 func_818C370C(void *arg0, void *arg1) {
    s32 temp_lo;
    s32 temp_ret;
    register s32 temp_v0_2 ASM_REG("$2");
    s32 temp_v1_2;
    s32 var_v0;
    s32 word4;
    s32 word5;
    char byte_value;
    void *temp_s0;
    void *temp_s2;
    void *temp_v0;
    void *temp_v1;
    register s32 tail_ret ASM_REG("$2");

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_s2 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024C48;
        M2C_FIELD(temp_v0, void **, 0x20) = arg0;
        M2C_FIELD(temp_s2, s16 *, 0xE) = 0;
        M2C_FIELD(temp_s2, s16 *, 0x10) = 0;
        temp_ret = func_80069EF8();
        M2C_FIELD(temp_s2, s16 *, 0x12) = (s16)(temp_ret % 7);
        byte_value = 0x80;
        M2C_FIELD(temp_s2, u16 *, 0x14) = M2C_FIELD(arg0, u16 *, 0x14);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, s8 *, 0xE) = byte_value;
        M2C_FIELD(temp_s0, s8 *, 0xD) = byte_value;
        M2C_FIELD(temp_s0, s8 *, 0xC) = byte_value;
        M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7DCF;
        M2C_FIELD(temp_s0, u16 *, 0x14) = M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC;
        M2C_FIELD(temp_s0, u16 *, 0x10) = M2C_FIELD(temp_s0, u16 *, 0x10) | 0x20;
        M2C_FIELD(temp_s0, u16 *, 0x14) = M2C_FIELD(temp_s0, u16 *, 0x14) | 0x100;
        func_8003DB94(temp_s0, &D_80025AF0, 0);
        temp_v0_2 = func_80069EF8();
        temp_v1_2 = temp_v0_2;
        ASM_KEEP(temp_v0_2);
        var_v0 = temp_v0_2 >> 0xC;
        if (temp_v1_2 < 0) {
            var_v0 = (temp_v1_2 + 0xFFF) >> 0xC;
        }
        M2C_FIELD(temp_s0, s16 *, 0x1A) = temp_v1_2 - (var_v0 << 0xC);
        temp_lo = 0x1400 / (s16)M2C_FIELD(temp_s2, u16 *, 0x14);
        M2C_FIELD(temp_s0, s16 *, 0x1E) = temp_lo;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = temp_lo;
        func_8004491C(temp_v0, D_80045C34);
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        ASM_KEEP(temp_v1);
        tail_ret = (s32)temp_v0;
        ASM_KEEP(tail_ret);
        *(Copy16 *)temp_v1 = *(Copy16 *)arg1;
        ASM_KEEP(tail_ret);
        word4 = ((Copy24 *)arg1)->words[4];
        word5 = ((Copy24 *)arg1)->words[5];
        ((Copy24 *)temp_v1)->words[4] = word4;
        ((Copy24 *)temp_v1)->words[5] = word5;
        func_80025078(word4, word5);
        return (s32)temp_v0;
    }
    return 0;
}
