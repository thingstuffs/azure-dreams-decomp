#include "common.h"

typedef struct S_800CCD68_0 {
    u8 pad_00[0x68];
    u16 unk_68;
    union { s16 s; u16 u; } unk_6A;   /* accessed as both */
    u16 unk_6C;
    u8 pad_6E[0x4];
    u16 unk_72;
} S_800CCD68_0;   /* arg0 in func_800CCD68 */


/* Steps a timed four-phase value sequence and counts completed cycles. */
void func_800CCD68(S_800CCD68_0 *sequence)
{
    s32 value;
    s32 value_2;
    s32 state;

    state = sequence->unk_6A.s;
    switch (state) {
    case 0:
        value = 0xC00;
        goto set_value;
    case 1:
        value = --sequence->unk_6C;
        if ((value << 16) != 0) {
            return;
        }
        value = 0x800;
        sequence->unk_72 = value;
        goto advance_state;
    case 2:
        value = --sequence->unk_6C;
        if ((value << 16) != 0) {
            return;
        }
        value = 0x400;
set_value:
        sequence->unk_72 = value;
advance_state:
        value_2 = sequence->unk_6A.u;
        sequence->unk_6C = 3;
        value_2++;
        sequence->unk_6A.u = value_2;
        return;
    case 3:
        value = --sequence->unk_6C;
        if ((value << 16) != 0) {
            return;
        }
        value = sequence->unk_68;
        sequence->unk_72 = 0;
        sequence->unk_6C = state;
        sequence->unk_6A.s = 0;
        value++;
        sequence->unk_68 = value;
        return;
    }
}
