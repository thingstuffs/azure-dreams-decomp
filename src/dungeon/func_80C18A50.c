#include "modules/dungeon_resource17_slot0.h"

void func_80174250(R17_80174250_Actor *actor, s32 action, R17_80174250_Entity *entity, R17_80174250_MapObject *map_object)
{
    if (func_800AC82C(actor, action, entity, map_object) != 0) {
        if ((dungeonCheckActorFloorTrap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)func_801713A8);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_801744FC) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_80174494);
        func_80047784(entity,(s16)(((u8 *)D_80174494)[((gameWork.view.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}
