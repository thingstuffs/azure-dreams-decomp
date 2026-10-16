#include "modules/dungeon_ovl_1831370.h"

void dungeonCopyStringToObjectBuffer(s8 *object, s32 sourceString) {
    ovl_1831370_8181161C_Func8181161CData *textData = (ovl_1831370_8181161C_Func8181161CData *)(object + 0x20);

    memset(textData->field_14, 0, (D_800294F8[textData->index] << 1) | 1);
    strcpy(textData->field_14, sourceString);
    inventorySetObjectEntryAddress(textData->field_70, textData->field_14);
}
