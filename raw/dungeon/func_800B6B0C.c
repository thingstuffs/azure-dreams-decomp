#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((s8 *)(base) + (offset)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800BC2E8(void);
extern u8 D_800BC388[9];
extern u8 D_800BC3E4[9];

void *func_800BC26C(s32 arg0, s32 arg1, s32 arg2)
{
    void *result;
    u8 *fields;
    register s32 store_arg1 ASM_REG("$19");

    result = func_8003FD64(0x110, (void *)arg0);
    if (result != NULL) {
        do { store_arg1 = arg1; } while (0);
        ASM_KEEP(store_arg1);
        FIELD(result, void *, 0x10) = D_800BC388;
        func_8004491C(result, D_800BC3E4);
        fields = (u8 *)result + 0x20;
        FIELD(result, s32, 0x20) = arg0;
        FIELD(fields, s32, 4) = arg2;
        if ((arg1 << 16) != 0) {
            func_800BC2E8();
            return (void *)0x7F80;
        }
        FIELD(fields, s16, 0xC) = 0x7FC0;
        FIELD(fields, s16, 0xE) = store_arg1;
    }
    return result;
}
