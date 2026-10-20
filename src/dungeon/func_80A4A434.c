#include "modules/dungeon_resource06_slot0.h"

void func_80173C34(R06_80173C34_Actor *actor, s32 action, R06_80173C34_Entity *entity, R06_80173C34_MapObject *map_object)
{
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)initialize_destination_state);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_80175894) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_8017586C);
        select_sprite_entry(entity,(s16)(((u8 *)D_8017586C)[((g_game_work.view.camera_rotation.parts.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}
