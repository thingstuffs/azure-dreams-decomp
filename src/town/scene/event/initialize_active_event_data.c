#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player/script_flags.h"

s32 select_status_code_from_callback(void);                            /* extern */
extern M2C_UNK D_8001B314;
extern s32 *D_8001C370;
extern s8 D_8001ED72;
extern s8 D_8001F092;

/* Initializes the active data pointer and refreshes two status flags. */
void initialize_active_event_data(void) {
    D_8001C370 = &D_8001B314;
    clear_script_flag_bit(Ftt_pad33);
    clear_script_flag_bit(Ftt_pad69);
    clear_script_flag_bit(Ftt_pad70);
    if (get_script_flag_mask(Ftt_pad01) == 0) {
        select_status_code_from_callback();
    }
    D_8001ED72 = get_script_flag_mask(F_s24_door_open) == 0;
    D_8001F092 = get_script_flag_mask(F_sakaba_close) != 0;
}
