#include "modules/dungeon_resource08_slot0.h"

void dungeonAdvanceObjectAngleAndHeight(u16 *record_data, s32 unused, R08_80174180_Object *object) {
    u16 height;

    object->field_1A += 0x320;
    height = object->field_1E + 0x200;
    object->field_1E = height;
    object->field_1C = height;
    if (height >= 0x2000) {
        record_data[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
