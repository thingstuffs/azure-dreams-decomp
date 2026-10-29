#include "common.h"
#include "town/person/state.h"

typedef struct S_800CCD68_0 {
    u8 pad_00[0x68];
    u16 unk_68;
    union { s16 s; u16 u; } unk_6A;   /* accessed as both */
    u16 unk_6C;
    u8 pad_6E[0x4];
    u16 unk_72;
} S_800CCD68_0;   /* arg0 in advance_four_phase_flag_sequence */


/* Steps a timed four-phase value sequence and counts completed cycles. */
void advance_four_phase_flag_sequence(S_800CCD68_0 *sequence)
{
    s32 value;
    s32 state;

    state = sequence->unk_6A.s;
    switch (state) {
    case 0:
        value = 0xC00;
        sequence->unk_72 = value;
        sequence->unk_6C = 3;
        sequence->unk_6A.u++;
        return;
    case 1:
        value = --sequence->unk_6C;
        if ((value << 16) != 0) {
            return;
        }
        value = 0x800;
        sequence->unk_72 = value;
        sequence->unk_6C = 3;
        sequence->unk_6A.u++;
        return;
    case 2:
        value = --sequence->unk_6C;
        if ((value << 16) != 0) {
            return;
        }
        value = 0x400;
        sequence->unk_72 = value;
        sequence->unk_6C = 3;
        sequence->unk_6A.u++;
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
