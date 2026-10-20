#include "common.h"

#include "common.h"

extern u8 D_8007216C[];

extern void update_text_row_scale(u8 *entity, u8 unused);

/* Initializes state fields and copies the global default byte. */
void init_graphics_state_fields(u8 *state, s32 init_value)
{
    u8 default_byte;

    *(u32 *)0x8008099C = 0;
    update_text_row_scale(state, (u8)init_value);
    state[2] = init_value;
    state[0] = 0;
    state[1] = 0;
    default_byte = D_8007216C[0];
    state[0x3D] = 0;
    *(u32 *)(state + 0x34) = 0;
    state[0x3C] = default_byte;
}
