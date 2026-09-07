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

typedef struct S_800C4D78_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
    u8 pad_24[0x2];
    s16 unk_26;
} S_800C4D78_0;   /* temp_v0 in func_800C4D78 */

typedef struct S_800C4D78_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C4D78_1;   /* counter_base in func_800C4D78 */

void func_800C4D78(s32 arg0, s32 arg1) {
    S_800C4D78_0 *temp_v0;
    u8 *counter_base;
    register s32 held_arg0 ASM_REG("$17") = arg0;   /* MATCH pin: retail register colouring depends on it */
    register s32 held_arg1 ASM_REG("$16") = arg1;   /* MATCH pin: load-bearing for the whole function shape */

    temp_v0 = func_8003FD64(0x200, &D_80083498);
    if (temp_v0 != NULL) {
        temp_v0->unk_26 = 0x20;
        temp_v0->unk_10 = &D_800C4C00;
        temp_v0->unk_20 = held_arg0;
        if ((held_arg1 << 0x10) != 0) {
            func_800A56E0(0x501);
        }
        counter_base = (u8 *)&D_80083460;
        ((S_800C4D78_1 *)counter_base)->unk_0A =
            (u16)(((S_800C4D78_1 *)counter_base)->unk_0A + 1);
        ASM_KEEP(held_arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ASM_KEEP(held_arg1);   /* MATCH pin: keeps a statement from moving across a call/branch */
    }
}

/* MECHANISM: A short-lived D_80083460 base preserves the retail lui/addiu/lhu form.
   Pinned arg roles reproduce s1=arg0 and s0=arg1 across the allocator call.
   Tail keepalives force sw-before-sll while leaving the retail prologue schedule intact. */
