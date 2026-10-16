#include "modules/dungeon_resource08_slot0.h"

void func_80173F20(R08_80173F20_Actor *actor, s32 action, R08_80173F20_Entity *entity, R08_80173F20_MapObject *map_object)
{
    if (func_800AC82C(actor, action, entity, map_object) != 0) {
        if ((dungeonCheckActorFloorTrap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)dungeonUpdateActorBehaviorAndEffect);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_80174C8C) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_80174C2C);
        func_80047784(entity,(s16)(((u8 *)D_80174C2C)[((gameWork.view.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}
