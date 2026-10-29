#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player/script_flags.h"
#include "town/scene/event.h"


/* Process IDs 0x1462, 0x1474, and 0xD89 in sequence. */
void dispatch_three_progress_events(void) {
    set_script_flag_bit(Ft_s07_mia_bikou_end);
    set_script_flag_bit(Ft_mia_love);
    set_script_flag_bit(Ftt_pad88);
}
