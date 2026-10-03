#include "common.h"
#include "m2c_compat.h"

typedef struct S_8080BE0C_0_pre {
    u16 unk_00;
} S_8080BE0C_0_pre;   /* the 0x2 bytes before entry in func_80526A0C, addressed as entry[-1] */

typedef struct S_8080BE0C_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    s32 unk_04;
    u8 pad_08[0x4];
    void * unk_0C;
    u8 pad_10[0xC];
    u16 unk_1C;
} S_8080BE0C_0;   /* entry in func_80526A0C */

typedef struct S_8080BE0C_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8080BE0C_1;   /* data_ptr in func_80526A0C */


M2C_UNK func_80058588();               /* extern */
s32 func_80071424();                             /* extern */
extern s32 D_80084D5C;
extern s16 D_80530000[];

void func_80526A0C(void *entry) {
    s16 *value_ptr;
    s16 current_state;
    s32 remaining;
    s32 total;
    u16 countdown;
    u16 next_state;
    u16 flags;
    void *data_ptr;

    total = 0;
    remaining = 7;
    value_ptr = &D_80530000[0x333];
    data_ptr = ((S_8080BE0C_0 *)entry)->unk_0C;
    do {
        total += *value_ptr;
        value_ptr -= 1;
        remaining -= 1;
    } while (remaining >= 0);
    current_state = ((S_8080BE0C_0 *)entry)->unk_00.s;
    switch (current_state) {
    case 0:
        countdown = ((S_8080BE0C_0 *)entry)->unk_02 - 1;
        ((S_8080BE0C_0 *)entry)->unk_02 = countdown;
        if ((countdown << 0x10) > 0) {
            return;
        }
        next_state = ((S_8080BE0C_0 *)entry)->unk_00.u;
        flags = ((S_8080BE0C_0 *)entry)->unk_1C;
        next_state += 1;
        flags &= 0xFFFD;
        ((S_8080BE0C_0 *)entry)->unk_1C = flags;
        ((S_8080BE0C_0 *)entry)->unk_00.u = next_state;
        return;
    case 1:
        func_80058588(total, func_80071424(((S_8080BE0C_0 *)entry)->unk_04), ((S_8080BE0C_0 *)entry)->unk_04);
        if (((S_8080BE0C_1 *)data_ptr)->unk_2A & 1) {
            (*(u16 *)((u8 *)entry + -2)) = (u16) (((S_8080BE0C_0_pre *)entry)[-1].unk_00 | 0x8000);
            D_80084D5C |= 0x8000;
        }
        return;
    default:
        return;
    }
}
/* MECHANISM: The page-base symbol plus &D_80530000[0x333] emits retail's entry lui/addiu in v1.
   A noreturn tail ABI and explicit label order preserve default/state-0/state-1 CFG and jump slots.
   Split state/flags RMW temporaries establish the retail v1/v0 lifetimes and flags/state store order. */
