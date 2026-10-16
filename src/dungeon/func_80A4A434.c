#include "modules/dungeon_resource06_slot0.h"

void func_80173C34(R06_80173C34_Actor *actor, s32 action, R06_80173C34_Entity *entity, R06_80173C34_MapObject *map_object)
{
    if (func_800AC82C(actor, action, entity, map_object) != 0) {
        if ((dungeonCheckActorFloorTrap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)func_8017140C);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_80175894) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_8017586C);
        func_80047784(entity,(s16)(((u8 *)D_8017586C)[((gameWork.view.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}
