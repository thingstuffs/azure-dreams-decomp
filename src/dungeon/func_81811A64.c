#include "modules/dungeon_ovl_1831370.h"

void *dungeonAllocateInitializedChildObject(s32 parent_object, s32 type_code, s32 config_value) {
    u8 *object;
    u8 *state;

    object = func_8003FC64(0);
    state = object + 0x20;
    if (object != 0) {
        if (dungeonGetAndPositionObjectHandle(state) != 0) {
            *(void **)(object + 0xC) = object + 0x80;
            *(s32 *)(state + 0x6C) = (s32)dungeonForwardValueToSharedHelper(*(S_800491F4 ***)(state + 0x70));
            dungeonInitializeEmbeddedObjectState(state, parent_object, type_code, config_value);
            func_8004491C(object, func_8004CAA0);
        } else {
            func_8004B1A4(*(s32 *)(state + 0x74));
            *(u16 *)(object + 0x1E) |= 0x8000;
            object = 0;
            objectFlagBlock.flags |= 0x8000;
        }
    }
    return object;
}
