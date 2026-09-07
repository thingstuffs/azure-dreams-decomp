#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80048A44(void *, u8, s32, s32);
extern void func_8008DBC4(void *, s32, s16, s32);
extern s32 func_80098C80(s32);
extern void func_8009F644(void *, s32, s16, s32);

extern s32 D_80082EB0;
extern s16 D_80083228;
extern u8 D_800DD130[];

void func_8008DB0C(void *arg0, s32 arg1, void *arg2, s32 arg3, u16 arg4) {
    u8 *table = D_800DD130;
    s32 value;
    register s32 held3 ASM_REG("$16") = arg3;

    FIELD(arg0, s8, 0x9A) = 0x26;
    FIELD(arg0, s8, 0x9B) = 0;
    FIELD(arg0, s32, 0x8C) = 0;
    FIELD(arg2, u8 *, 0x2C) = table;
    func_80048A44(
        arg2,
        table[((D_80083228 + FIELD(arg0, s16, 0x2A) + 0x100) >> 9) & 7],
        0,
        1);

    FIELD(arg0, s8, 0x72) = held3;
    FIELD(arg0, s8, 0x73) = (s8)arg4;

    if (D_80082EB0 != 0) {
        value = func_80098C80(D_80082EB0);
        func_8008DBC4(arg0, 0x68, FIELD(arg0, s16, 0x8A), (s16)value);
        return;
    }

    {
        register s32 call_kind ASM_REG("$5") = 0x88;
        ASM_KEEP(call_kind);
        {
            register void *call_obj ASM_REG("$4") = arg0;
            register s32 call_field ASM_REG("$6") = FIELD(call_obj, s16, 0x8A);
            register s32 zero_arg ASM_REG("$7") = 0;
            ASM_USE2(call_field, zero_arg);
            func_8009F644(call_obj, call_kind, call_field, zero_arg);
        }
    }
}

/* MECHANISM: The seed already held the 0x20 frame and s2/s1/s0 roles exactly.
   Final-call register locals materialize a0/a2/a3 in retail order; ASM_USE2
   keeps a2/a3 before jal so the required call delay slot remains a nop. */
