#include "common.h"

#include "common.h"

extern s8 fade_manager_state[9];
extern u32 D_800814A0_scalar;
extern void unlink_node_if_registered(void *runtime_data);


/* Processes the runtime data and sets both 0x8000 flags. */
void flag_fade_manager_dirty(void)
{
    u16 *runtime_data = (u16 *)fade_manager_state;

    unlink_node_if_registered(runtime_data);
    runtime_data[-1] |= 0x8000;
    D_800814A0_scalar |= 0x8000;
}
