#include "common.h"
#include "town/player/object.h"
#include "town/player/state.h"
#include "town/player/record.h"

extern u8 D_80098544[8];

/* Ease the object's value toward -0x800000 until the timer expires, then advance the state. */
void ease_object_value_and_advance_state(UnsignedCountdownView *state_arg, ObjectPosition *object) {
    TownPlayerRecord *state = (TownPlayerRecord *)state_arg;

    u16 ticks_left;
    s32 current_value;

    ticks_left = state->timer - 1;
    state->timer = ticks_left;
    if ((ticks_left << 16) > 0) {
        current_value = object->z.v;
        current_value += ((s32)0xFF800000 - current_value) / 2;
        object->z.v = current_value;
        return;
    }

    object->z.v = (s32)0xFF800000;
    clear_entity_record_fields(object);
    state->timer = 10;
    state->unk_04 = D_80098544;
}
