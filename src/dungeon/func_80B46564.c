#include "modules/dungeon_resource12_slot0.h"

void func_80173D64(R12_80173D64_Actor *actor, s32 action, R12_80173D64_Entity *entity, R12_80173D64_MapObject *map_object)
{
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)update_actor_state_and_select_target);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_80175A9C) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_80175A4C);
        select_sprite_entry(entity,(s16)(((u8 *)D_80175A4C)[((g_game_work.view.camera_rotation.parts.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}
