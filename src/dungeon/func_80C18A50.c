#include "modules/dungeon_resource17_slot0.h"

void func_80174250(R17_80174250_Actor *actor, s32 action, R17_80174250_Entity *entity, R17_80174250_MapObject *map_object)
{
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)update_entity_movement_and_ground_height);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_801744FC) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_80174494);
        select_sprite_entry(entity,(s16)(((u8 *)D_80174494)[((g_game_work.view.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}
