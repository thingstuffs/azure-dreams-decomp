#include "modules/town_door.h"

/* Updates the object's state and applies completion effects when it reaches zero. */
void func_800A0CF8(u8 *object, s32 unused, s32 state_id, s32 state_arg) {
    s16 state;

    state = func_800A0F9C(D_80100B70, state_id, *(s16 *)(object + 0x90));
    *(s16 *)(object + 0x90) = state;
    if ((s32)(state << 0x10) == 0) {
        func_800A12AC(D_80100B70, state_id, state_arg);
        *(void **)(object + 0x50) = func_800A0DAC;
        func_8003E1C4(0);
        func_8003F540(0, D_8006CD58[0], 0x0600065E, 0x030008B6);
        SD_Call(0x300);
    }
}
