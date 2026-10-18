#include "common.h"

void copy_callback_value_to_destination();        /* extern */
extern u8 D_80017B0C;
extern u8 D_80017B18;
extern u8 D_80017F08;

/* Process two locations in the data block and return its base address. */
s32 *build_two_record_value_block(void) {
    copy_callback_value_to_destination(&D_80017F08, &D_80017B0C);
    copy_callback_value_to_destination(&D_80017F08 + 0x14, &D_80017B18);
    return &D_80017F08;
}
