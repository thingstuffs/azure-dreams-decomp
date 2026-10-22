#include "dungeon/monster/troll/update_direction_table_for_entity_kinds.h"
#include "shared/sprite_frame_state.h"

/* Updates the direction table and selected entry for entity kinds 13 through 15. */
void update_direction_table_for_entity_kinds(Obj0 *owner, void *context, Obj2 *sprite_arg, Obj3 *entity_arg)
{
    SpriteFrameState *sprite= sprite_arg;
    Obj3 *entity = entity_arg;
    u32 selected_table;
    u32 current_table;
    u8 kind;
    s32 direction_index;

    kind = entity->kind48;
    switch (kind) {
    case 13:
        if ((entity->flags1c & 0x200) != 0 || entity->flag25 == 0) {
            current_table = (u32)*(u8 **)&sprite->frameTable;
            selected_table = (u32)D_80169E54;
        } else {
            current_table = (u32)*(u8 **)&sprite->frameTable;
            selected_table = (u32)D_80169E24;
        }
        if (current_table != selected_table) {
            sprite->frameTable = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->value2a + 0x100) >> 9;
            select_sprite_entry(sprite, *(u8 *)((direction_index & 7) + selected_table), 0);
        }
        break;
    case 14:
        if ((entity->flags1c & 0x200) != 0 || entity->flag25 == 0) {
            current_table = (u32)*(u8 **)&sprite->frameTable;
            selected_table = (u32)D_80169E5C;
        } else {
            current_table = (u32)*(u8 **)&sprite->frameTable;
            selected_table = (u32)D_80169E2C;
        }
        if (current_table != selected_table) {
            sprite->frameTable = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->value2a + 0x100) >> 9;
            select_sprite_entry(sprite, *(u8 *)((direction_index & 7) + selected_table), 0);
        }
        break;
    case 15:
        if ((entity->flags1c & 0x200) != 0 || entity->flag25 == 0) {
            current_table = (u32)*(u8 **)&sprite->frameTable;
            selected_table = (u32)D_80169E64;
        } else {
            current_table = (u32)*(u8 **)&sprite->frameTable;
            selected_table = (u32)D_80169E34;
        }
        if (current_table != selected_table) {
            sprite->frameTable = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->value2a + 0x100) >> 9;
            select_sprite_entry(sprite, *(u8 *)((direction_index & 7) + selected_table), 0);
        }
        break;
    default:
        break;
    }
    if (update_actor_transform_from_parent(owner, context, sprite, entity) != 0) {
        if ((check_actor_floor_trap(sprite, entity) << 16) > 0) {
            owner->field8c = func_801664BC;
        }
        return;
    }

    switch (entity->kind48) {
    case 13:
        if (*(u8 **)&sprite->frameTable != D_80169E54 ||
            (entity->flags1c & 0x208) != 0) {
            return;
        }
        sprite->frameTable = (u32)&D_80169DC4;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->value2a + 0x100) >> 9;
        select_sprite_entry(sprite, *(u8 *)((direction_index & 7) + (u32)&D_80169DC4), 0);
        return;
    case 14:
        if (*(u8 **)&sprite->frameTable != D_80169E5C ||
            (entity->flags1c & 0x208) != 0) {
            return;
        }
        sprite->frameTable = (u32)&D_80169DCC;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->value2a + 0x100) >> 9;
        select_sprite_entry(sprite, *(u8 *)((direction_index & 7) + (u32)&D_80169DCC), 0);
        return;
    case 15:
        if (*(u8 **)&sprite->frameTable != D_80169E64 ||
            (entity->flags1c & 0x208) != 0) {
            return;
        }
        sprite->frameTable = (u32)&D_80169DD4;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->value2a + 0x100) >> 9;
        select_sprite_entry(sprite, *(u8 *)((direction_index & 7) + (u32)&D_80169DD4), 0);
        return;
    default:
        return;
    }
}
