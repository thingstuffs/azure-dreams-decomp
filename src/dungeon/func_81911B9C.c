#include "modules/dungeon_ovl_1930844.h"

void dungeonCreateObjectHex212InitializeDataPointerMode(s32 *initial_value) {
    ovl_1930844_81911B9C_S_81911B9C_0 *object;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        object->unk_10 = (void *)dungeonDrawAFullScreenColorOverlayMarkEffectCompleteCountdownEnds;
        ((ovl_1930844_81911B9C_S_81911B9C_2 *)(((ovl_1930844_81911B9C_S_81911B9C_1 *)object)->unk_0C))->unk_05 = 0x10;
        object->unk_20 = (s32) *initial_value;
    }
}
