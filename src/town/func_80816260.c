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

/* Fades an effect in and out around an object event, then marks completion. */
void func_80020260(void *effect) {
    s16 state;
    s32 color;
    s32 faded_color;
    void *object;

    state = ((S_80020260_0 *)effect)->unk_00.s;
    object = ((S_80020260_0 *)effect)->unk_04;

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
    ((S_80020260_0 *)effect)->unk_16 &= 0xFFFD;
    ((S_80020260_0 *)effect)->unk_00.u++;
    goto done;

state_1:
    color = ((S_80020260_0 *)effect)->unk_08;
    if (color <= 0x40403F) {
        ((S_80020260_0 *)effect)->unk_08 = color + 0x80808;
    }
    if ((((S_80020260_1 *)object)->unk_2A & 1) == 0) {
        goto done;
    }
    ((S_80020260_0 *)effect)->unk_00.u++;
    goto done;

state_2:
    faded_color = ((S_80020260_0 *)effect)->unk_08 + (s32)0xFFF7F7F8;
    ((S_80020260_0 *)effect)->unk_08 = faded_color;
    if (faded_color <= 0x80808) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    return;
}

/* MECHANISM: Retail is a frameless leaf; 0x80020358 is its local epilogue.
   State labels preserve block order and the jump delay-slot stores.
   Split state-1/state-2 values free $a0 for the object and yield $v1/$v0 roles. */
