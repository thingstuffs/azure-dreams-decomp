#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player/script_flags.h"

extern M2C_UNK scene_event_buffer;

/* Sets script flags Ftt_pad124 and Ftt_pad70, then returns scene_event_buffer. */
s32 *dispatch_two_events_and_return_buffer(void) {
    set_script_flag_bit(Ftt_pad124);
    set_script_flag_bit(Ftt_pad70);
    return &scene_event_buffer;
}
