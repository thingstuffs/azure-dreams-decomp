#include "modules/dungeon_ovl_1831370.h"

void func_8002654C(s32 objectAddress)
{
    ovl_1831370_8181154C_S_8002654C_0 *objectState;

    objectState = (void *)(objectAddress + 0x20);
    memset(objectState->unk_14, 0,
           (D_800294F8[objectState->unk_10] * 2) | 1);
    func_800263C0(objectState->unk_70, objectState->unk_14);
    objectState->unk_08 = 0;
    func_80026370(objectState->unk_70, 0);
}
