#include "common.h"
#include "m2c_compat.h"

void write_resource_command(s32, s8);                /* extern */
extern s32 town_map_resource_ids[];

/* Submit the indexed table value with code 0x23. */
void send_resource_command_23(s32 entry_index) {
    write_resource_command(town_map_resource_ids[entry_index], 0x23);
}
