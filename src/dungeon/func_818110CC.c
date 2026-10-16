#include "modules/dungeon_ovl_1830850.h"

s32 inventoryCopyStateVectorAfterBuffers(ovl_1830850_818110CC_Unk818110CC *state, s32 input)
{
    s32 success = 0;
    s32 *buffer = state->unk58;
    s32 call_result;

    call_result = func_80049004(buffer, input, 6);
    state->unk54 = call_result;
    if (call_result != 0) {
        call_result = func_80048FBC(buffer, 6);
        state->unk74 = call_result;
        if (call_result != 0) {
            state->unk38[0] = D_8002E5E8.unk0;
            state->unk38[1] = D_8002E5E8.unk4;
            state->unk38[2] = D_8002E5E8.unk8;
            textureSetTheFieldOffsetHex8InEachEntryPointerArray(state->unk54, state->unk38, 13);
            success = 1;
        }
    }
    return success;
}
