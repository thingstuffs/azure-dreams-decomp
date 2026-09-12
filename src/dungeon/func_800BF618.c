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

/* Creates an object with the supplied payload, optionally triggers an event, and increments the counter. */
void func_800C4D78(s32 payload, s32 trigger_event) {
    S_800C4D78_0 *object;
    u8 *counter_base;
    s32 held_event = trigger_event;

    object = func_8003FD64(0x200, &D_80083498);
    if (object != NULL) {
        object->unk_26 = 0x20;
        object->unk_10 = &D_800C4C00;
        object->unk_20 = payload;
        if ((held_event << 0x10) != 0) {
            func_800A56E0(0x501);
        }
        counter_base = (u8 *)&D_80083460;
        ((S_800C4D78_1 *)counter_base)->unk_0A =
            (u16)(((S_800C4D78_1 *)counter_base)->unk_0A + 1);
        ASM_KEEP(held_event);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    }
}

/* MECHANISM: A short-lived D_80083460 base preserves the retail lui/addiu/lhu form.
   Pinned arg roles reproduce s1=payload and s0=trigger_event across the allocator call.
   Tail keepalives force sw-before-sll while leaving the retail prologue schedule intact. */
