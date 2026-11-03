#include "common.h"
#include "town/person/state.h"



/* Steps a timed four-phase value sequence and counts completed cycles. */
void advance_four_phase_flag_sequence(TownObjectRecord *sequence)
{
    s32 value;
    s32 state;

    state = sequence->unk_6A.as_s16;
    switch (state) {
    case 0:
        value = 0xC00;
        sequence->heading.as_u16 = value;
        sequence->timer.as_u16 = 3;
        sequence->unk_6A.as_u16++;
        return;
    case 1:
        value = --sequence->timer.as_u16;
        if ((value << 16) != 0) {
            return;
        }
        value = 0x800;
        sequence->heading.as_u16 = value;
        sequence->timer.as_u16 = 3;
        sequence->unk_6A.as_u16++;
        return;
    case 2:
        value = --sequence->timer.as_u16;
        if ((value << 16) != 0) {
            return;
        }
        value = 0x400;
        sequence->heading.as_u16 = value;
        sequence->timer.as_u16 = 3;
        sequence->unk_6A.as_u16++;
        return;
    case 3:
        value = --sequence->timer.as_u16;
        if ((value << 16) != 0) {
            return;
        }
        value = sequence->unk_68;
        sequence->heading.as_u16 = 0;
        sequence->timer.as_u16 = state;
        sequence->unk_6A.as_s16 = 0;
        value++;
        sequence->unk_68 = value;
        return;
    }
}
