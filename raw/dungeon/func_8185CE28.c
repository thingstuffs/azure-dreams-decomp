#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800247B4(void) __attribute__((noreturn));
extern M2C_UNK func_8003DB94();
extern void *func_8003FC64(s32);
extern M2C_UNK func_8004491C();
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern M2C_UNK D_80024330[];
extern M2C_UNK D_80045340[];
extern M2C_UNK D_800DEAE0[];

s32 func_8185CE28(s32 arg0, void *arg1, s16 arg2)
{
    s16 temp_v1;
    s32 temp_a0;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_a0 = arg2 * 3;
        M2C_FIELD(temp_v0, s32 *, 0x20) = arg0;
        temp_s1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = D_80024330;
        temp_v1 = temp_a0 % 8;
        M2C_FIELD(temp_s1, s16 *, 0x1C) = temp_v1 << 9;
        M2C_FIELD(temp_s1, s16 *, 0x20) = 0x20;
        M2C_FIELD(temp_s1, s16 *, 0x1E) = 0;
        M2C_FIELD(temp_s1, s16 *, 0x22) = -8;
        M2C_FIELD(temp_s1, s16 *, 0x24) = temp_v1;
        M2C_FIELD(temp_s1, u16 *, 6) = M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(temp_s1, u16 *, 0xA) = M2C_FIELD(arg1, u16 *, 6);
        M2C_FIELD(temp_s1, u16 *, 0xE) = M2C_FIELD(arg1, u16 *, 0xA);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
        func_8003DB94(temp_s0, D_800DEAE0, 0);
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1800;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1800;
        M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7E0B;
        M2C_FIELD(temp_s0, u16 *, 0x14) |= 0xC;
        M2C_FIELD(temp_s0, u16 *, 0x10) |= 0x20;
        M2C_FIELD(temp_s0, u16 *, 0x14) |= 0x100;
        func_8004491C(temp_v0, D_80045340);
        temp_s0 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s0, s16 *, 2) = M2C_FIELD(temp_s1, u16 *, 6) +
            ((func_800644B8(M2C_FIELD(temp_s1, s16 *, 0x1C)) >> 4) *
             M2C_FIELD(temp_s1, s16 *, 0x20) >> 8);
        M2C_FIELD(temp_s0, s16 *, 6) = M2C_FIELD(temp_s1, u16 *, 0xA) +
            ((func_80064584(M2C_FIELD(temp_s1, s16 *, 0x1C)) >> 4) *
             M2C_FIELD(temp_s1, s16 *, 0x20) >> 8);
        {
            u16 final_z = M2C_FIELD(temp_s1, u16 *, 0xE);
            ASM_KEEP(final_z);
#ifndef NON_MATCHING
            __asm__ __volatile__("" : : : "$2");
#endif
            {
                register s32 v0pin ASM_REG("$2");
                v0pin = (s32)temp_v0;
                ASM_KEEP(v0pin);
                M2C_FIELD(temp_s0, s16 *, 0xA) = final_z - 8;
                func_800247B4();
            }
        }
    }
    {
        register s32 zero_v0 ASM_REG("$2");
        zero_v0 = 0;
        ASM_KEEP(zero_v0);
        return zero_v0;
    }
}
