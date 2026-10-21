#include "common.h"
#include "engine/cd.h"

extern u8 cd_command_write_index;

/* Returns the difference between adjacent byte indices with wraparound at 32. */
s32 get_cd_command_queue_depth(void)
{
    u8 *index_ptr = &cd_command_write_index;
    u32 current_index = cd_command_write_index;

    if (index_ptr[0] < index_ptr[-1]) {
        current_index += 0x20;
    }

    return current_index - index_ptr[-1];
}
