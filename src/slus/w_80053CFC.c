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

void func_80053CFC(S_80053CFC *arg0, s32 arg1)
{
    register s32 saved_arg1 ASM_REG("$6");   /* MATCH pin: slus-diff */
    s32 low;
    S_80081568_Hi *global_ptr;

    saved_arg1 = arg1;
    ASM_KEEP_INPUT(saved_arg1);   /* MATCH pin: slus-diff */
    D_80081568 = arg0->field_0;
    D_8008156C = arg0->field_4;
    __asm__ volatile("" : "=r"(saved_arg1) : "0"(saved_arg1), "m"(D_80081568) : "memory");
    low = saved_arg1 & 0x7FFFFF;
    global_ptr = &D_80081568_hi;
    D_80081568 = ((((u32)D_80081568 + 0x7FF) >> 11) << 23) | low;
    __asm__ volatile("" : : "r"(global_ptr));
    func_8003E4FC(6, global_ptr, saved_arg1);
    func_8003F320();
}
