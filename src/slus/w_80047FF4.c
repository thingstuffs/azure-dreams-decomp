#include "common.h"

#ifdef NON_MATCHING
#define LOCAL_ASM_REG(reg)
#define LOCAL_ASM_KEEP(var) ((void)0)
#else
#define LOCAL_ASM_REG(reg) asm(reg)
#define LOCAL_ASM_KEEP(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

typedef struct {
    s32 flag;
    u16 status;
    u16 pad6;
} S_80083D08;

extern S_80083D08 D_80083D08[6];
extern void *D_80080A90[4];
extern s32 func_80047C60(void *a0);
extern void *func_80047AB0(void *a0, s32 a1, s32 a2, s32 a3, void *a4);
extern void *func_80047EEC(s32 a0, void *a1);

void *func_80047FF4(s32 a0, void *a1)
{
    void *new_var;
    void **new_var2;
    void **new_var3;
    s32 idx;
    register s32 type LOCAL_ASM_REG("$2") = 0x38;

    if (a0 != type) {
        new_var = a1;
        new_var2 = D_80080A90;
        new_var3 = new_var2;
        idx = func_80047C60(new_var);
        (*(D_80083D08 + idx)).flag = (s32)a1;
        (*(&D_80083D08[idx])).pad6 = (u16)a0;
        return func_80047AB0(a1, idx + 5,
                             ((idx * 3) + 0x1D2) << 6,
                             0xD, new_var3[0]);
    }
    LOCAL_ASM_KEEP(type);
    return func_80047EEC(type, a1);
}
