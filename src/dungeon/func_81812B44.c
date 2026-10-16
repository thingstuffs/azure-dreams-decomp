#include "modules/dungeon_ovl_1831cd8.h"

void dungeonStoreScaledMenuRatio(ovl_1831cd8_81812B44_S_80027B44_0 *object, s32 numerator, s32 denominator) {
    ((ovl_1831cd8_81812B44_S_80027B44_2 *)(((ovl_1831cd8_81812B44_S_80027B44_1 *)(object->unk_04))->unk_04))->unk_0A =
        (s16) ((s32) (numerator * 0x90) / denominator);
}
