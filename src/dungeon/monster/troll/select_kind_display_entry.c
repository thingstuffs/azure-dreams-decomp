#include "shared/actor_status_flags.h"
#include "common.h"
#include "engine/graphics/select_sprite_entry_api.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "dungeon/data.h"

extern s32 D_8015DDC4;
extern s32 D_8015DDCC;
extern s32 D_8015DDD4;
extern u8 D_8015DE24[];
extern u8 D_8015DE2C[];
extern u8 D_8015DE34[];
extern u8 D_8015DE54[];
extern u8 D_8015DE5C[];
extern u8 D_8015DE64[];

struct SpriteFrameState;
extern s32 update_actor_transform_from_parent(void *, void *, void *, void *);


/* Updates the kind-specific display table and selects its direction entry. */
void select_kind_display_entry(ActorRecord *owner, ObjectPosition *context, SpriteFrameState *display_arg, ActorRecord *state_arg)
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
            selected_table = D_8015DE54;
        } else {
            current_table = display->frameTable;
            selected_table = D_8015DE24;
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
            selected_table = D_8015DE5C;
        } else {
            current_table = display->frameTable;
            selected_table = D_8015DE2C;
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
            selected_table = D_8015DE64;
        } else {
            current_table = display->frameTable;
            selected_table = D_8015DE34;
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
            owner->unk_8C.address = troll_slot_c_action_callback;
        }
        return;
    }

    switch (state->unk_48) {
    case 13:
        if (display->frameTable != D_8015DE54 ||
            (state->flags1C & (ACTOR_MP_EMPTY | ACTOR_ASLEEP)) != 0) {
            return;
        }
        display->frameTable = &D_8015DDC4;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)&D_8015DDC4), 0);
        return;
    case 14:
        if (display->frameTable != D_8015DE5C ||
            (state->flags1C & (ACTOR_MP_EMPTY | ACTOR_ASLEEP)) != 0) {
            return;
        }
        display->frameTable = &D_8015DDCC;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)&D_8015DDCC), 0);
        return;
    case 15:
        if (display->frameTable != D_8015DE64 ||
            (state->flags1C & (ACTOR_MP_EMPTY | ACTOR_ASLEEP)) != 0) {
            return;
        }
        display->frameTable = &D_8015DDD4;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)&D_8015DDD4), 0);
        return;
    default:
        return;
    }
}
