#include "common.h"
#include "m2c_compat.h"

void set_script_flag_bit();                     /* extern */
extern M2C_UNK D_8001DCD4;

/* Passes two fixed IDs to set_script_flag_bit and returns the address of D_8001DCD4. */
M2C_UNK *dispatch_two_events_and_return_buffer(void) {
    set_script_flag_bit(0xDAC);
    set_script_flag_bit(0xD77);
    return &D_8001DCD4;
}
