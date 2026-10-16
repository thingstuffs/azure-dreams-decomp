#include "modules/dungeon_ovl_1831cd8.h"

void dungeonUpdateMenuObjectData(void *object) {
    dungeonStoreScaledMenuRatio(((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_88, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_00, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_04);
    dungeonDrawMenuProgressBar(object, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_00, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_04);
    dungeonSetMenuObjectScaleFields(((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_88, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_00, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_04);
    dungeonRefreshMenuEntryResources(((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_88, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_40);
    advanceTimedTaggedStream(object + 0x2C);
}
