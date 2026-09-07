#include "common.h"
typedef s32 M2C_UNK;
#ifdef __mips__
static const u32 bank_words[] __asm__("func_81994800") __attribute__((section(".text.func_81994800"), aligned(4))) = {
    0x8002458C,0x01400340,0x00400040,0x01800340,0x00400040,0x01C00340,0x00400040,0x01000380,
    0x00400040,0x01400380,0x00400040,0x01800380,0x00400040,0x01C00380,0x00400040,0x01000340,
    0x00400040,0x00000000,0x800245F0,0x80024674,0x8002478C,0x80024D98,0x8002512C,
};
__asm__(".globl func_81994800\n.type func_81994800,@function\n.size func_81994800,260\n");
#define BODY_NAME func_8199485C
#else
#define BODY_NAME func_81994800
#endif
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
extern s16 D_80025384;
extern s32 D_800814A0;
void BODY_NAME(void *arg0, void *arg1, void *arg2)
#ifdef __mips__
    __attribute__((section(".text.func_81994800")))
#endif
;
void BODY_NAME(void *arg0, void *arg1, void *arg2) {
    s32 temp_lo; u16 temp_a0;
    temp_a0 = M2C_FIELD(arg0, u16 *, 0x2A) - 1;
    temp_lo = (s32)((s32)(temp_a0 << 0x10) >> 9) / (s16)M2C_FIELD(arg0, s16 *, 0x2C);
    D_80025384 = 1; M2C_FIELD(arg0, u16 *, 0x2A) = temp_a0;
    M2C_FIELD(arg2, u8 *, 0xD) = (u8)(M2C_FIELD(arg2, u8 *, 0xD) - 4);
    M2C_FIELD(arg2, s8 *, 0xE) = (s8)temp_lo; M2C_FIELD(arg2, s8 *, 0xC) = (s8)temp_lo;
    if (M2C_FIELD(arg2, s16 *, 6) >= -6) M2C_FIELD(arg2, s16 *, 6) = (s16)((u16)M2C_FIELD(arg2, s16 *, 6) - 2);
    if ((s16)M2C_FIELD(arg0, u16 *, 0x2A) <= 0) {
        M2C_FIELD(((M2C_FIELD(arg0, s16 *, 0x32) * 2) + M2C_FIELD(arg0, s32 *, 0x60)), s16 *, 0x46) = 0;
        M2C_FIELD(arg0, u16 *, -2) = (u16)(M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
    }
}
