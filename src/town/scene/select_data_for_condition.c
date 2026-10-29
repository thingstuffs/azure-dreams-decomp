#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene.h"

extern u8 D_8001EB20[];
extern u8 D_8001EC6A[];

/* Select one of two data pointers based on the query for 0xD83. */
void *select_data_for_condition_d_83(void) {
    void *dispatch_result;

    if (get_script_flag_mask(Ftt_pad82) != 0) {
        dispatch_result = D_8001EC6A;
    } else {
        dispatch_result = D_8001EB20;
    }
    return dispatch_result;
}
