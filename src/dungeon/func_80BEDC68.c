#include "modules/dungeon_resource16_slot0.h"

void func_80173468(R16_80173468_Actor *actor, s32 action, R16_80173468_Entity *entity, R16_80173468_MapObject *map_object)
{
    if (func_800AC82C(actor, action, entity, map_object) != 0) {
        if ((func_800AD9B4(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)func_80171014);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_8017425C) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_8017420C);
        func_80047784(entity,(s16)(((u8 *)D_8017420C)[((gameWork.view.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}
