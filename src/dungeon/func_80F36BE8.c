#include "common.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801743E8_0_pre {
    u16 unk_00;
} S_801743E8_0_pre;   /* the 0x2 bytes before arg0 in func_801743E8, addressed as arg0[-1] */

typedef struct S_801743E8_0 {
    u8 pad_00[0x96];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801743E8_0;   /* arg0 in func_801743E8 */





typedef struct Page8008 {
    u8 pad[0x14A0];
    u32 flags;
} Page8008;

void func_801743E8(void *arg0, Rec_D_800E3D7C *arg1, Rec_func_800AA258_arg2 *arg2)
{
    s32 state;
    u16 value;
    register Page8008 *page ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    state = ((S_801743E8_0 *)arg0)->unk_9B;
    ((S_801743E8_0 *)arg0)->unk_96.s--;

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto exit;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto exit;

state_0:
    if (arg2->unk_14 & 0x8000) {
        ((S_801743E8_0 *)arg0)->unk_9B = 3;
        goto exit;
    }
    ((S_801743E8_0 *)arg0)->unk_96.s = 3;
    ((S_801743E8_0 *)arg0)->unk_9B++;

state_1:
    value = arg2->unk_1E - 0x50;
    arg2->unk_1E = value;
    arg2->unk_1C = value;
    if (((S_801743E8_0 *)arg0)->unk_96.u < 0) {
        state = 2;
        value = ((S_801743E8_0 *)arg0)->unk_9B;
        ((S_801743E8_0 *)arg0)->unk_96.s = state;
        goto increment_state;
    }
    goto exit;

state_2:
    arg1->unk_08.at00_s32.v += 0x28000;
    value = arg2->unk_1E - 0x80;
    arg2->unk_1E = value;
    arg2->unk_1C = value;
    if (((S_801743E8_0 *)arg0)->unk_96.u >= 0) {
        goto exit;
    }
    value = ((S_801743E8_0 *)arg0)->unk_9B;

increment_state:
    value++;
    ((S_801743E8_0 *)arg0)->unk_9B = value;
    goto exit;

state_3:
    page = (Page8008 *)0x80080000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ((S_801743E8_0_pre *)arg0)[-1].unk_00 |= 0x8000;
    page->flags |= 0x8000;

exit:
    return;
}

/* MECHANISM: True-space in-range jumps are local CFG, producing the frameless leaf.
   Separate counter/state live ranges give retail's v1/v0 shared-increment roles.
   A guarded v1 page pointer holds 0x80080000 for the 0x14A0 RMW displacement. */
