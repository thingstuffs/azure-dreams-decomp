#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene.h"

extern u8 D_8001EC35[];
extern u8 D_8001ED0E[];

/* Select a data pointer based on the result of querying 0xD81. */
void *select_data_pointer_based_result(void) {
    if (get_script_flag_mask(Ftt_pad80) != 0) {
        return D_8001ED0E;
    }
    return D_8001EC35;
}
