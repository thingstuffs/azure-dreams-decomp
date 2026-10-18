#include "common.h"
#include "m2c_compat.h"

M2C_UNK SD_Call();                     /* extern */
void call_the_handler_selects_nonzero_entry(); /* extern */
void store_the_valid_shared_angle_in_offset_hex_10();                  /* extern */
extern M2C_UNK D_800924EC;
extern M2C_UNK D_800D0110;

/* Reset and initialize the record, then assign its handler. */
void initialize_action_object_and_play_sound(s32 **record, s32 unused, s32 setup_value) {
    SD_Call(0x50B);
    store_the_valid_shared_angle_in_offset_hex_10(record);
    call_the_handler_selects_nonzero_entry(&D_800D0110, record, setup_value);
    *record = &D_800924EC;
}
