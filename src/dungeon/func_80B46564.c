#include "modules/dungeon_resource12_slot0.h"

void func_80173D64(R12_80173D64_Actor *actor, s32 action, R12_80173D64_Entity *entity, R12_80173D64_MapObject *map_object)
{
    if (func_800AC82C(actor, action, entity, map_object) != 0) {
        if ((dungeonCheckActorFloorTrap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)func_80170E70);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_80175A9C) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_80175A4C);
        func_80047784(entity,(s16)(((u8 *)D_80175A4C)[((gameWork.view.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}
