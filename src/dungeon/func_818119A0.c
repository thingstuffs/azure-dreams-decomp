#include "modules/dungeon_ovl_1831370.h"

void dungeonInitializeEmbeddedObjectState(void *state, s32 parent, s32 type, s32 config) {
    dungeonInitializeObjectPhaseData(state, parent, type, config);
    dungeonInitializeOwnerDefaults(state, state + 0x60, state + 0x38, state + 0x48);
    dungeonInitializeObjectDestinationFields(state, ((ovl_1831370_818119A0_S_800269A0_0 *)state)->unk_70);
}
