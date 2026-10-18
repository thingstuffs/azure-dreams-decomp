#include "common.h"
#include "m2c_compat.h"

s32 select_status_code_from_callback();                            /* extern */
void clear_script_flag_bit();                     /* extern */
s32 get_script_flag_mask();                         /* extern */
extern M2C_UNK D_8001B314;
extern M2C_UNK *D_8001C370;
extern s8 D_8001ED72;
extern s8 D_8001F092;

/* Initializes the active data pointer and refreshes two status flags. */
void initialize_active_event_data(void) {
    D_8001C370 = &D_8001B314;
    clear_script_flag_bit(0xD52);
    clear_script_flag_bit(0xD76);
    clear_script_flag_bit(0xD77);
    if (get_script_flag_mask(0xD32) == 0) {
        select_status_code_from_callback();
    }
    D_8001ED72 = get_script_flag_mask(0x1463) == 0;
    D_8001F092 = get_script_flag_mask(0x9B) != 0;
}
