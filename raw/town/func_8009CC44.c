#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80094984();
extern s32 func_80098928();
extern u8 D_80082660;

void func_8009A3A4(void *arg0, s32 arg1, s32 arg2) {
    register s32 arg1_save ASM_REG("$18") = arg1;

    ASM_KEEP(arg1_save);
    func_80094984(FIELD(FIELD(arg0, void *, 0x44), s32, 0x14), arg0);
    {
        register void *call_arg0 ASM_REG("$4") = arg0;
        register s32 call_arg1 ASM_REG("$5") = arg1_save;
        register s32 call_arg2 ASM_REG("$6") = arg2;

        ASM_KEEP(call_arg0);
        ASM_KEEP(call_arg1);
        ASM_KEEP(call_arg2);
        *(&D_80082660 + (FIELD(call_arg0, s32, 0x40) * 8)) = 0;
        func_80098928(call_arg0, call_arg1, call_arg2);
    }
}

/* MECHANISM: The call-spanning arguments are held in retail's s0/s2/s1 roles,
   producing the 0x20 frame and save sequence. Guarded a0/a1/a2 staging precedes
   the byte-table address, whose clear fills the second call's delay slot. */
