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

/* Update a timed effect's size and position, then set its completion flags. */
void func_801743E8(void *effect, Rec_D_800E3D7C *position, Rec_func_800AA258_arg2 *visual)
{
    s32 state;
    u16 size_or_state;
    Page8008 *flag_page;

    state = ((S_801743E8_0 *)effect)->unk_9B;
    ((S_801743E8_0 *)effect)->unk_96.s--;

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
    if (visual->unk_14 & 0x8000) {
        ((S_801743E8_0 *)effect)->unk_9B = 3;
        goto exit;
    }
    ((S_801743E8_0 *)effect)->unk_96.s = 3;
    ((S_801743E8_0 *)effect)->unk_9B++;

state_1:
    size_or_state = visual->unk_1E - 0x50;
    visual->unk_1E = size_or_state;
    visual->unk_1C = size_or_state;
    if (((S_801743E8_0 *)effect)->unk_96.u < 0) {
        state = 2;
        size_or_state = ((S_801743E8_0 *)effect)->unk_9B;
        ((S_801743E8_0 *)effect)->unk_96.s = state;
        goto increment_state;
    }
    goto exit;

state_2:
    position->unk_08.at00_s32.v += 0x28000;
    size_or_state = visual->unk_1E - 0x80;
    visual->unk_1E = size_or_state;
    visual->unk_1C = size_or_state;
    if (((S_801743E8_0 *)effect)->unk_96.u >= 0) {
        goto exit;
    }
    size_or_state = ((S_801743E8_0 *)effect)->unk_9B;

increment_state:
    size_or_state++;
    ((S_801743E8_0 *)effect)->unk_9B = size_or_state;
    goto exit;

state_3:
    flag_page = (Page8008 *)0x80080000;
    ((S_801743E8_0_pre *)effect)[-1].unk_00 |= 0x8000;
    do {
        flag_page->flags |= 0x8000;
    } while (0);

exit:
    return;
}
