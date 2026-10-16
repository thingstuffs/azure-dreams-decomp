#include "modules/dungeon_ovl_1831370.h"

void dungeonCleanupObjectResources(ovl_1831370_81811B94_CleanupObject *object)
{
    ovl_1831370_81811B94_CleanupData *cleanup;

    if (object != 0) {
        cleanup = &object->cleanup;
        dungeonReleaseObjectHandle(cleanup->field_70);
        func_8004B1A4(cleanup->field_74);
        object->flags |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
