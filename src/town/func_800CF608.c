#include "common.h"

typedef struct S_800CCD68_0 {
    u8 pad_00[0x68];
    u16 unk_68;
    union { s16 s; u16 u; } unk_6A;   /* accessed as both */
    u16 unk_6C;
    u8 pad_6E[0x4];
    u16 unk_72;
} S_800CCD68_0;   /* arg0 in func_800CCD68 */



void func_800CCD68(S_800CCD68_0 *arg0)
{
    register s32 value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 state;

    state = arg0->unk_6A.s;
    value = 1;
    if (state == value) {
        goto state_1;
    }
    value = state < 2;
    if (value == 0) {
        goto state_ge_2;
    }
    value = 2;
    ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    value = 0xC00;
    if (state == 0) {
        goto set_value;
    }
    goto done;

state_ge_2:
#ifdef NON_MATCHING
    value = 2;
#endif
    ASM_UNDEF(value);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    if (state == value) {
        goto state_2;
    }
    value = 3;
    if (state == value) {
        goto state_3;
    }
    goto done;

state_1:
    value = --arg0->unk_6C;
    if ((value << 16) != 0) {
        goto done;
    }
    value = 0x800;
    arg0->unk_72 = value;
    goto advance_state;

state_2:
    value = --arg0->unk_6C;
    if ((value << 16) != 0) {
        goto done;
    }
    value = 0x400;
set_value:
    arg0->unk_72 = value;
advance_state:
    value = arg0->unk_6A.u;
    arg0->unk_6C = 3;
    value++;
    arg0->unk_6A.u = value;
    goto done;

state_3:
    value = --arg0->unk_6C;
    if ((value << 16) != 0) {
        goto done;
    }
    value = arg0->unk_68;
    arg0->unk_72 = 0;
    arg0->unk_6C = state;
    arg0->unk_6A.s = 0;
    value++;
    arg0->unk_68 = value;
done:
    return;
}

/* MECHANISM: The true-space function is a frameless leaf; both apparent calls are local
   joins, and explicit labels preserve retail block order. Fixed s32 v0/v1 lifetimes,
   a delay-slot keep, and output-only ASM_UNDEF prevent the final beqz fold; NON_MATCHING
   initializes that delay-carried value portably. */
