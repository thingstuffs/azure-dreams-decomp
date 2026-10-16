#include "modules/dungeon_ovl_18b8824.h"

void *createRandomizedGrayscaleEffect(s32 object_tag, Rec_func_80024264_arg1 *initial_state)
{
    ovl_18b8824_81898A64_S_80024264_2 *state;
    ovl_18b8824_81898A64_S_80024264_1 *appearance;
    ovl_18b8824_81898A64_S_80024264_0 *object;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        object->unk_10 = (void *)dungeonHandleIncrementEntryCountersProcessTargetPropagateStatusFlags;
        appearance = object->unk_0C;
        object->unk_20 = object_tag;
        object->unk_24 = 0;
        appearance->unk_0E = 0x80;
        appearance->unk_0D = 0x80;
        appearance->unk_0C = 0x80;
        func_8003DB94(appearance, &D_80024EF4, 0);
        appearance->unk_1C = 0x2000;
        appearance->unk_1E = 0x1000;
        appearance->unk_1A = 0xC00;
        func_8004491C(object, func_80045340);
        state = object->unk_08;
        state->unk_00 = initial_state->unk_00.at00_s32.v;
        state->unk_04 = initial_state->unk_04.at00_s32.v;
        state->unk_08 = initial_state->unk_08.at00_s32.v + 0x500000;
        state->unk_0C = initial_state->unk_0C.at00_s32.v;
        state->unk_10 = initial_state->unk_10.at00_s32.v;
        state->unk_14 = initial_state->unk_14;
        return object;
    } else {
        return NULL;
    }
}
