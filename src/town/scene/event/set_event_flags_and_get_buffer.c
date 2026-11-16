#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player/script_flags.h"
#include "town/scene/event.h"
#include "town/scene/event_buffer_data.h"


/* Sets script flags Ftt_pad124 and Ftt_pad70, then returns scene_event_buffer. */
u8 *set_event_flags_and_get_buffer(void) {
    set_script_flag_bit(Ftt_pad124);
    set_script_flag_bit(Ftt_pad70);
    return scene_event_buffer;
}
