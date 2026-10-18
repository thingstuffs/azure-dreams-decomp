#include "common.h"

extern s32 get_script_flag_mask(s32 flagIndex);
extern void set_script_flag_bit(s32 bit_index);
extern void clear_script_flag_bit(s32 bit_index);
extern u8 D_8001E259[];
extern u8 D_8001E405[];

/* Select a handler and data pointer based on the query for 0xD53. */
void *select_handler_data_for_flag_d_53(void) {
    if (get_script_flag_mask(0xD53) != 0) {
        clear_script_flag_bit(0xD53);
        return D_8001E259;
    }
    set_script_flag_bit(0xD53);
    return D_8001E405;
}
