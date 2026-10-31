#include "shared/actor_status_flags.h"
#include "dungeon/monster/troll/update_direction_tables_kind_flags_processes_state.h"
#include "shared/sprite_frame_state.h"

/* Updates direction tables by kind and flags, then processes the object state. */
void update_direction_tables_kind_flags_processes_state(Obj0 *owner, ObjectPosition *context, SpriteFrameState *display_arg, Obj3 *state_arg)
{
    SpriteFrameState *display= display_arg;
    Obj3 *state = state_arg;
    u8 *selected_table;
    u8 *current_table;
    u8 kind;
    s32 direction_index;

    kind = state->kind48;
    switch (kind) {
    case 13:
        if ((state->flags1c & ACTOR_ASLEEP) != 0 || state->flag25 == 0) {
            current_table = display->frameTable;
            selected_table = D_8016FE54;
        } else {
            current_table = display->frameTable;
            selected_table = D_8016FE24;
        }
        if (current_table != selected_table) {
            display->frameTable = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
            select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)selected_table), 0);
        }
        break;
    case 14:
        if ((state->flags1c & ACTOR_ASLEEP) != 0 || state->flag25 == 0) {
            current_table = display->frameTable;
            selected_table = D_8016FE5C;
        } else {
            current_table = display->frameTable;
            selected_table = D_8016FE2C;
        }
        if (current_table != selected_table) {
            display->frameTable = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
            select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)selected_table), 0);
        }
        break;
    case 15:
        if ((state->flags1c & ACTOR_ASLEEP) != 0 || state->flag25 == 0) {
            current_table = display->frameTable;
            selected_table = D_8016FE64;
        } else {
            current_table = display->frameTable;
            selected_table = D_8016FE34;
        }
        if (current_table != selected_table) {
            display->frameTable = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
            select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)selected_table), 0);
        }
        break;
    default:
        break;
    }

    if (update_actor_transform_from_parent(owner, context, display, state) != 0) {
        if ((check_actor_floor_trap(display, state) << 16) > 0) {
            owner->field8c = func_8016C4BC;
        }
        return;
    }

    switch (state->kind48) {
    case 13:
        if (display->frameTable != D_8016FE54 ||
            (state->flags1c & (ACTOR_MP_EMPTY | ACTOR_ASLEEP)) != 0) {
            return;
        }
        display->frameTable = &D_8016FDC4;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)&D_8016FDC4), 0);
        return;
    case 14:
        if (display->frameTable != D_8016FE5C ||
            (state->flags1c & (ACTOR_MP_EMPTY | ACTOR_ASLEEP)) != 0) {
            return;
        }
        display->frameTable = &D_8016FDCC;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)&D_8016FDCC), 0);
        return;
    case 15:
        if (display->frameTable != D_8016FE64 ||
            (state->flags1c & (ACTOR_MP_EMPTY | ACTOR_ASLEEP)) != 0) {
            return;
        }
        display->frameTable = &D_8016FDD4;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)&D_8016FDD4), 0);
        return;
    default:
        return;
    }

}
