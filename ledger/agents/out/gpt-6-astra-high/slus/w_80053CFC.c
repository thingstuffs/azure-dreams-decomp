#include "common.h"

#ifdef NON_MATCHING
#define ASM_REG(reg)
#define ASM_KEEP_INPUT(var) ((void)0)
#else
#define ASM_REG(reg) asm(reg)
#define ASM_KEEP_INPUT(var) __asm__ __volatile__("" : : "r"(var))
#endif

typedef struct {
    s32 field_0;
    s32 field_4;
} S_80053CFC;

typedef struct {
    s32 field_0;
    s32 field_4;
    s32 field_8;
} S_80081568_Hi;

extern void func_8003E4FC(s32 arg0, void *arg1, s32 arg2);
extern void func_8003F320(void);
extern volatile s32 D_80081568;
extern s32 D_8008156C;
extern S_80081568_Hi D_80081568_hi asm("D_80081568");

/* Builds and submits a command from the source fields and packed value. */
void func_80053CFC(S_80053CFC *source, s32 packed_value)
{
    register s32 saved_value ASM_REG("$6");   /* MATCH pin: slus-diff */
    s32 low_bits;
    S_80081568_Hi *command;

    saved_value = packed_value;
    ASM_KEEP_INPUT(saved_value);   /* MATCH pin: slus-diff */
    D_80081568 = source->field_0;
    D_8008156C = source->field_4;
    __asm__ volatile("" : "=r"(saved_value) : "0"(saved_value), "m"(D_80081568) : "memory");
    low_bits = saved_value & 0x7FFFFF;
    command = &D_80081568_hi;
    D_80081568 = ((((u32)D_80081568 + 0x7FF) >> 11) << 23) | low_bits;
    __asm__ volatile("" : : "r"(command));
    func_8003E4FC(6, command, saved_value);
    func_8003F320();
}
