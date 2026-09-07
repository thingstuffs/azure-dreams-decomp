#include "common.h"

#include "common.h"

extern u32 D_8008099C[];
extern u8 D_8007216C[];

extern void func_80037D50(u8 *arg0, u8 arg1);

/* Initializes state fields and copies the global default byte. */
void func_80034EF8(u8 *state, s32 init_value)
{
    u8 default_byte;

    *(u32 *)0x8008099C = 0;
    func_80037D50(state, (u8)init_value);
    state[2] = init_value;
    state[0] = 0;
    state[1] = 0;
    default_byte = D_8007216C[0];
    state[0x3D] = 0;
    *(u32 *)(state + 0x34) = 0;
    state[0x3C] = default_byte;
}
