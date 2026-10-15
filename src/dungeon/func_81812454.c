#include "modules/dungeon_ovl_1831cd8.h"

void func_80027454(s32 *state, s32 mode, s32 value, s32 extra_value)
{
    if (mode == 0) {
        func_80027328(state, value);
        return;
    }
    if (*state != 0x13) {
        func_80027384(state, value);
        return;
    }
    func_800273E4(state, value, extra_value);
}
