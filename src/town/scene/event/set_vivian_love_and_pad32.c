#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/event.h"


/* Call func_80018A64 with IDs 0x1476 and 0x5C3 in sequence. */
void set_vivian_love_and_pad32(void) {
    set_script_flag_bit(Ft_vivian_love);
    set_script_flag_bit(F_sbs11_pad32);
}
