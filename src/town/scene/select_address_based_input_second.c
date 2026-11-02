#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"

extern char D_8001B9E8[];

/* Return D_8001B9E8 when query 0x930 succeeds, otherwise null. */
char *select_address_based_input(void) {
    char *result;

    if (get_script_flag_mask(F_sbs32_pad06) == 0) {
        result = 0;
    } else {
        result = D_8001B9E8;
    }
    return result;
}
