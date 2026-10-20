#include "modules/dungeon_resource03_slot0.h"

void func_80173A30(R03_80173A30_Actor *actor, s32 action, R03_80173A30_Entity *entity, R03_80173A30_MapObject *map_object)
{
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)func_80170E54);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_80173CDC) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_80173C74);
        select_sprite_entry(entity,(s16)(((u8 *)D_80173C74)[((g_game_work.view.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}
