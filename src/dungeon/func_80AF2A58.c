#include "modules/dungeon_resource10_slot0.h"

void func_80174258(R10_80174258_Actor *actor, s32 action, R10_80174258_Entity *entity, R10_80174258_MapObject *map_object)
{
    if (func_800AC82C(actor, action, entity, map_object) != 0) {
        if ((dungeonCheckActorFloorTrap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)func_801717F4);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_801759E8) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_80175980);
        func_80047784(entity,(s16)(((u8 *)D_80175980)[((gameWork.view.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}
