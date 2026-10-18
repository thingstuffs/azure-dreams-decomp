#include "common.h"
#include "m2c_compat.h"

void copy_callback_value_to_destination();        /* extern */
extern u8 D_80017AF4;
extern u8 D_80017B0C;
extern u8 D_80017B18;
extern u8 D_80017F44;

/* Apply three value tables to consecutive global destinations and return their base. */
M2C_UNK *build_three_record_value_block(void) {
    copy_callback_value_to_destination(&D_80017F44, &D_80017AF4);
    copy_callback_value_to_destination(&D_80017F44 + 0x14, &D_80017B0C);
    copy_callback_value_to_destination(&D_80017F44 + 0x28, &D_80017B18);
    return &D_80017F44;
}
