#include "common.h"

typedef struct S_80020260_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u8 pad_02[0x2];
    void * unk_04;
    s32 unk_08;
    u8 pad_0C[0xA];
    u16 unk_16;
} S_80020260_0;   /* arg0 in func_80020260 */

typedef struct S_80020260_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0xA];
    s16 unk_36;
} S_80020260_1;   /* object in func_80020260 */



extern s32 D_800814A0;

void func_80020260(void *arg0) {
    s16 state;
    s32 value_1;
    s32 value_2;
    void *object;

    state = ((S_80020260_0 *)arg0)->unk_00.s;
    object = ((S_80020260_0 *)arg0)->unk_04;

    if (state == 1) {
        goto state_1;
    }
    if (state >= 2) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    goto done;

state_ge_2:
    if (state == 2) {
        goto state_2;
    }
    goto done;

state_0:
    if (((S_80020260_1 *)object)->unk_36 != 0xFF) {
        goto done;
    }
    ((S_80020260_0 *)arg0)->unk_16 &= 0xFFFD;
    ((S_80020260_0 *)arg0)->unk_00.u++;
    goto done;

state_1:
    value_1 = ((S_80020260_0 *)arg0)->unk_08;
    if (value_1 <= 0x40403F) {
        ((S_80020260_0 *)arg0)->unk_08 = value_1 + 0x80808;
    }
    if ((((S_80020260_1 *)object)->unk_2A & 1) == 0) {
        goto done;
    }
    ((S_80020260_0 *)arg0)->unk_00.u++;
    goto done;

state_2:
    value_2 = ((S_80020260_0 *)arg0)->unk_08 + (s32)0xFFF7F7F8;
    ((S_80020260_0 *)arg0)->unk_08 = value_2;
    if (value_2 <= 0x80808) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    return;
}

/* MECHANISM: Retail is a frameless leaf; 0x80020358 is its local epilogue.
   State labels preserve block order and the jump delay-slot stores.
   Split state-1/state-2 values free $a0 for the object and yield $v1/$v0 roles. */
