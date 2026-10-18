#include "modules/dungeon_resource07_slot0.h"

void func_80173EF4(R07_80173EF4_Actor *actor, s32 action, R07_80173EF4_Entity *entity, R07_80173EF4_MapObject *map_object)
{
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)func_80170E54);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_80174190) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_80174138);
        func_80047784(entity,(s16)(((u8 *)D_80174138)[((g_game_work.view.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}
