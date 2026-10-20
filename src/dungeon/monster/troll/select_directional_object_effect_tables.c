#include "dungeon/monster/troll/select_directional_object_effect_tables.h"


/* Selects direction-dependent table entries for kinds 13 through 15 around the object update. */
void select_directional_object_effect_tables(Obj0 *owner, void *context, Obj2 *render_arg, Obj3 *state_arg)
{
    Obj2 *render_obj = render_arg;
    Obj3 *state = state_arg;
    u32 selected_table;
    u32 current_table;
    u8 kind;
    s32 direction_index;

    kind = state->kind48;
    switch (kind) {
    case 13:
        if ((state->flags1c & 0x200) != 0 || state->flag25 == 0) {
            current_table = (u32)render_obj->table2c;
            selected_table = (u32)D_80151E54;
        } else {
            current_table = (u32)render_obj->table2c;
            selected_table = (u32)D_80151E24;
        }
        if (current_table != selected_table) {
            *(u32 *)((u8 *)render_obj + 0x2c) = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
            select_sprite_entry(render_obj, *(u8 *)((direction_index & 7) + selected_table), 0);
        }
        break;

    case 14:
        if ((state->flags1c & 0x200) != 0 || state->flag25 == 0) {
            current_table = (u32)render_obj->table2c;
            selected_table = (u32)D_80151E5C;
        } else {
            current_table = (u32)render_obj->table2c;
            selected_table = (u32)D_80151E2C;
        }
        if (current_table != selected_table) {
            *(u32 *)((u8 *)render_obj + 0x2c) = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
            select_sprite_entry(render_obj, *(u8 *)((direction_index & 7) + selected_table), 0);
        }
        break;

    case 15:
        if ((state->flags1c & 0x200) != 0 || state->flag25 == 0) {
            current_table = (u32)render_obj->table2c;
            selected_table = (u32)D_80151E64;
        } else {
            current_table = (u32)render_obj->table2c;
            selected_table = (u32)D_80151E34;
        }
        if (current_table != selected_table) {
            *(u32 *)((u8 *)render_obj + 0x2c) = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
            select_sprite_entry(render_obj, *(u8 *)((direction_index & 7) + selected_table), 0);
        }
        break;

    default:
        break;
    }


    if (update_actor_transform_from_parent(owner, context, render_obj, state) != 0) {
        if ((check_actor_floor_trap(render_obj, state) << 16) > 0) {
            owner->field8c = func_8014E4BC;
        }
        return;
    }

    switch (state->kind48) {
    case 13:
        if (render_obj->table2c != D_80151E54 ||
            (state->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 *)((u8 *)render_obj + 0x2c) = (u32)&D_80151DC4;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
        select_sprite_entry(render_obj, *(u8 *)((direction_index & 7) + (u32)&D_80151DC4), 0);
        return;
    case 14:
        if (render_obj->table2c != D_80151E5C ||
            (state->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 *)((u8 *)render_obj + 0x2c) = (u32)&D_80151DCC;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
        select_sprite_entry(render_obj, *(u8 *)((direction_index & 7) + (u32)&D_80151DCC), 0);
        return;
    case 15:
        if (render_obj->table2c != D_80151E64 ||
            (state->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 *)((u8 *)render_obj + 0x2c) = (u32)&D_80151DD4;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
        select_sprite_entry(render_obj, *(u8 *)((direction_index & 7) + (u32)&D_80151DD4), 0);
        return;
    default:
        return;
    }

}
