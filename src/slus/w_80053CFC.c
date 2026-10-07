#include "common.h"

#define ASM_REG(reg) asm(reg)
#define ASM_KEEP_INPUT(var) __asm__ __volatile__("" : : "r"(var))

typedef struct {
    s32 field_0;
    s32 field_4;
} S_80053CFC;

extern void Control_CD(s32 command_code, void *command_ptr, s32 value);
extern void func_8003F320(void);
extern s32 D_80081568;
extern s32 D_8008156C;

/* Builds and submits a command from the source fields and packed value. */
void func_80053CFC(S_80053CFC *source, s32 packed_value)
{
    s32 saved_value;
    s32 low_bits;
    s32 *command;

    do {
        saved_value = packed_value;
    } while (0);
    D_80081568 = source->field_0;
    D_8008156C = source->field_4;
    __asm__ volatile("" : "=r"(saved_value) : "0"(saved_value), "m"(D_80081568) : "memory");
    low_bits = saved_value & 0x7FFFFF;
    command = (s32 *)&D_80081568;
    *command = ((((u32)*command + 0x7FF) >> 11) << 23) | low_bits;
    Control_CD(6, (void *)command, saved_value);
    func_8003F320();
}
