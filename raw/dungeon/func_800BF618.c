#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_8003FD64();
M2C_UNK func_800A56E0();
extern M2C_UNK D_80083460;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800C4C00;

void func_800C4D78(s32 arg0, s32 arg1) {
    void *temp_v0;
    u8 *counter_base;
    register s32 held_arg0 ASM_REG("$17") = arg0;
    register s32 held_arg1 ASM_REG("$16") = arg1;

    temp_v0 = func_8003FD64(0x200, &D_80083498);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s16 *, 0x26) = 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800C4C00;
        M2C_FIELD(temp_v0, s32 *, 0x20) = held_arg0;
        if ((held_arg1 << 0x10) != 0) {
            func_800A56E0(0x501);
        }
        counter_base = (u8 *)&D_80083460;
        M2C_FIELD(counter_base, u16 *, 0xA) =
            (u16)(M2C_FIELD(counter_base, u16 *, 0xA) + 1);
        ASM_KEEP(held_arg0);
        ASM_KEEP(held_arg1);
    }
}

/* MECHANISM: A short-lived D_80083460 base preserves the retail lui/addiu/lhu form.
   Pinned arg roles reproduce s1=arg0 and s0=arg1 across the allocator call.
   Tail keepalives force sw-before-sll while leaving the retail prologue schedule intact. */
