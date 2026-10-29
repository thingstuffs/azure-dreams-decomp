#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"

extern u8 D_8001E259[];
extern u8 D_8001E405[];

/* Select a handler and data pointer based on the query for 0xD53. */
void *select_handler_data_for_flag_d_53(void) {
    if (get_script_flag_mask(Ftt_pad34) != 0) {
        clear_script_flag_bit(Ftt_pad34);
        return D_8001E259;
    }
    set_script_flag_bit(Ftt_pad34);
    return D_8001E405;
}
