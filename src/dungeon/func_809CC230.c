#include "modules/dungeon_resource03_slot0.h"

void func_80173A30(R03_80173A30_Actor *actor, s32 action, R03_80173A30_Entity *entity, R03_80173A30_MapObject *map_object)
{
    if (func_800AC82C(actor, action, entity, map_object) != 0) {
        if ((dungeonCheckActorFloorTrap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)func_80170E54);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_80173CDC) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_80173C74);
        func_80047784(entity,(s16)(((u8 *)D_80173C74)[((gameWork.view.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}
