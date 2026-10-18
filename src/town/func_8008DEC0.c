#include "common.h"
#include "m2c_compat.h"

void write_resource_command();                /* extern */
extern s32 D_800CFBA0[];

/* Submit the indexed table value with code 0x23. */
void send_resource_command_23(s32 entry_index) {
    write_resource_command(D_800CFBA0[entry_index], 0x23);
}
