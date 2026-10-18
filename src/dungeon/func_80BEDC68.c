#include "modules/dungeon_resource16_slot0.h"

void func_80173468(R16_80173468_Actor *actor, s32 action, R16_80173468_Entity *entity, R16_80173468_MapObject *map_object)
{
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_8017425C) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_8017420C);
        func_80047784(entity,(s16)(((u8 *)D_8017420C)[((g_game_work.view.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}
