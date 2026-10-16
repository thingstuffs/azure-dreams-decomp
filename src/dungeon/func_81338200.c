#include "common.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"

extern void func_80035208();
extern void dungeonClearEntryFlagAndLinkOwner();
extern void dungeonSetMonsterDataPointer(void);
extern u8 D_800E045C[];
extern s32 D_80175D50;

/* Reset state flags, relink the two attached objects, and submit the global buffer. */
void dungeonResetMultiFormActorState(s32 reset_arg_a, s32 reset_arg_b, s32 reset_arg_c, s32 reset_arg_d) {
    s32 object_index;
    s32 object;
    u8 *state;

    object_index = 0;
    state = (u8 *)(D_80175D50 + 0x20);
    *(u16 *)(state + 0x46) &= 0x7FFF;
    D_80013714 &= 0xFFF6;
    dungeonSetMonsterDataPointer();
    state[0xAF] = 0;
    do {
        object = *(s32 *)((object_index * 4) + ((s32)D_800E3D7C) + 0xAC);
        if (object != 0) {
            dungeonClearEntryFlagAndLinkOwner(object - 0x20);
        }
        object_index++;
    } while (object_index < 2);
    func_80035208(D_800E045C);
}
