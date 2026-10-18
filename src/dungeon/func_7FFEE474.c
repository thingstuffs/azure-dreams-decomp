#include "modules/dungeon_town_map.h"

void decrease_substructure_value_and_reset(town_map_7FFEE474_MainStruct *object) {
    object->sub->unk8 -= 0x200;
    if ((s16)object->sub->unk8 < 0) {
        object->sub->unk8 = 0;
        object->unk68 = (void *)handle_town_map_input;
        object->unk64 = (s8)D_800CFC70[object->unk66];
        object->unk6c = D_800CFC7C[object->unk66];
    }
}
