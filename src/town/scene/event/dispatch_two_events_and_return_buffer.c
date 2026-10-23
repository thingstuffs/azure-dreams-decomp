#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"

void set_script_flag_bit(s32);                     /* extern */
extern M2C_UNK scene_event_buffer;

/* Passes two fixed IDs to set_script_flag_bit and returns the address of D_8001DCD4. */
s32 *dispatch_two_events_and_return_buffer(void) {
    set_script_flag_bit(Ftt_pad124);
    set_script_flag_bit(Ftt_pad70);
    return &scene_event_buffer;
}
