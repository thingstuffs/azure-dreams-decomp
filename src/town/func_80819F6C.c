#include "common.h"

typedef struct S_80023F6C_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u8 pad_02[0x2];
    void * unk_04;
    s32 unk_08;
} S_80023F6C_0;   /* arg0 in func_80023F6C */

typedef struct S_80023F6C_1 {
    s16 unk_00;
} S_80023F6C_1;   /* object in func_80023F6C */



extern s32 D_800814A0;

/* Wait for the linked object to clear, then reduce the level and set completion flags. */
void func_80023F6C(void *entry) {
    void *object;
    s16 state;
    u16 prev_state;
    s32 level;

    object = ((S_80023F6C_0 *)entry)->unk_04;
    state = ((S_80023F6C_0 *)entry)->unk_00.s;
    prev_state = ((S_80023F6C_0 *)entry)->unk_00.u;

    switch (state) {
    case 0:
        if (((S_80023F6C_1 *)object)->unk_00 == 0) {
            ((S_80023F6C_0 *)entry)->unk_00.u = prev_state + 1;
        }
        break;

    case 1:
        level = ((S_80023F6C_0 *)entry)->unk_08 + 0xFFF7F7F8U;
        ((S_80023F6C_0 *)entry)->unk_08 = level;
        if (level <= 0x80808) {
            (*(u16 *)((u8 *)entry + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        break;

    default:
        break;
    }

    ASM_KEEP(entry); /* Retains the register allocation required for a byte-exact match. */
}
