#include "common.h"
#include "town/person/state.h"



/* Steps a timed four-phase value sequence and counts completed cycles. */
void step_heading_turn_sequence(TownObjectRecord *sequence)
{
    s32 value;
    s32 state;

    state = ((s16)sequence->unk_6A);
    switch (state) {
    case 0:
        value = 0xC00;
        sequence->heading = value;
        sequence->timer = 3;
        sequence->unk_6A++;
        return;
    case 1:
        value = --sequence->timer;
        if ((value << 16) != 0) {
            return;
        }
        value = 0x800;
        sequence->heading = value;
        sequence->timer = 3;
        sequence->unk_6A++;
        return;
    case 2:
        value = --sequence->timer;
        if ((value << 16) != 0) {
            return;
        }
        value = 0x400;
        sequence->heading = value;
        sequence->timer = 3;
        sequence->unk_6A++;
        return;
    case 3:
        value = --sequence->timer;
        if ((value << 16) != 0) {
            return;
        }
        value = sequence->unk_68;
        sequence->heading = 0;
        sequence->timer = state;
        sequence->unk_6A = 0;
        value++;
        sequence->unk_68 = value;
        return;
    }
}
