#include "shared/actor_status_flags.h"
#include "dungeon/monster/troll/select_directional_object_effect_tables.h"
#include "shared/sprite_frame_state.h"

/* Selects direction-dependent table entries for kinds 13 through 15 around the object update. */
void select_directional_object_effect_tables(ActorRecord *owner, ObjectPosition *context, SpriteFrameState *display_arg, ActorRecord *state_arg)
{
    SpriteFrameState *display= display_arg;
    ActorRecord *state = state_arg;
    u8 *selected_table;
    u8 *current_table;
    u8 kind;
    s32 direction_index;

    kind = state->unk_48;
    switch (kind) {
    case 13:
        if ((state->flags1C & ACTOR_ASLEEP) != 0 || state->mp == 0) {
            current_table = display->frameTable;
            selected_table = D_80151E54;
        } else {
            current_table = display->frameTable;
            selected_table = D_80151E24;
        }
        if (current_table != selected_table) {
            display->frameTable = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9;
            select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)selected_table), 0);
        }
        break;
    case 14:
        if ((state->flags1C & ACTOR_ASLEEP) != 0 || state->mp == 0) {
            current_table = display->frameTable;
            selected_table = D_80151E5C;
        } else {
            current_table = display->frameTable;
            selected_table = D_80151E2C;
        }
        if (current_table != selected_table) {
            display->frameTable = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9;
            select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)selected_table), 0);
        }
        break;
    case 15:
        if ((state->flags1C & ACTOR_ASLEEP) != 0 || state->mp == 0) {
            current_table = display->frameTable;
            selected_table = D_80151E64;
        } else {
            current_table = display->frameTable;
            selected_table = D_80151E34;
        }
        if (current_table != selected_table) {
            display->frameTable = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9;
            select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)selected_table), 0);
        }
        break;
    default:
        break;
    }

    if (update_actor_transform_from_parent(owner, context, display, state) != 0) {
        if ((check_actor_floor_trap(display, state) << 16) > 0) {
            owner->unk_8C.address = func_8014E4BC;
        }
        return;
    }

    switch (state->unk_48) {
    case 13:
        if (display->frameTable != D_80151E54 ||
            (state->flags1C & (ACTOR_MP_EMPTY | ACTOR_ASLEEP)) != 0) {
            return;
        }
        display->frameTable = &D_80151DC4;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)&D_80151DC4), 0);
        return;
    case 14:
        if (display->frameTable != D_80151E5C ||
            (state->flags1C & (ACTOR_MP_EMPTY | ACTOR_ASLEEP)) != 0) {
            return;
        }
        display->frameTable = &D_80151DCC;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)&D_80151DCC), 0);
        return;
    case 15:
        if (display->frameTable != D_80151E64 ||
            (state->flags1C & (ACTOR_MP_EMPTY | ACTOR_ASLEEP)) != 0) {
            return;
        }
        display->frameTable = &D_80151DD4;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)&D_80151DD4), 0);
        return;
    default:
        return;
    }
}
