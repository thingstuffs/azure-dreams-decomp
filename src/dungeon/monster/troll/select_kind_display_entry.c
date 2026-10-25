#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad00[0x8c];
    void *field8c;
} Obj0;

typedef struct {
    u8 pad00[0x2c];
    u8 *table2c;
} Obj2;

typedef struct {
    u8 pad00[0x1c];
    u32 flags1c;
    u8 pad20[5];
    u8 flag25;
    u8 pad26[4];
    s16 value2a;
    u8 pad2c[0x1c];
    u8 kind48;
} Obj3;

extern u8 troll_slot_c_action_callback[];
extern s32 D_8015DDC4;
extern s32 D_8015DDCC;
extern s32 D_8015DDD4;
extern u8 D_8015DE24[];
extern u8 D_8015DE2C[];
extern u8 D_8015DE34[];
extern u8 D_8015DE54[];
extern u8 D_8015DE5C[];
extern u8 D_8015DE64[];

extern void select_sprite_entry(Obj2 *, u8, s32);
extern s32 update_actor_transform_from_parent(Obj0 *, void *, Obj2 *, Obj3 *);


/* Updates the kind-specific display table and selects its direction entry. */
void select_kind_display_entry(Obj0 *owner, void *context, Obj2 *display_arg, Obj3 *state_arg)
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
            selected_table = D_8015DE54;
        } else {
            current_table = display->frameTable;
            selected_table = D_8015DE24;
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
            selected_table = D_8015DE5C;
        } else {
            current_table = display->frameTable;
            selected_table = D_8015DE2C;
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
            selected_table = D_8015DE64;
        } else {
            current_table = display->frameTable;
            selected_table = D_8015DE34;
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
            owner->field8c = troll_slot_c_action_callback;
        }
        return;
    }

    switch (state->kind48) {
    case 13:
        if (display->frameTable != D_8015DE54 ||
            (state->flags1c & (ACTOR_MP_EMPTY | ACTOR_ASLEEP)) != 0) {
            return;
        }
        display->frameTable = &D_8015DDC4;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)&D_8015DDC4), 0);
        return;
    case 14:
        if (display->frameTable != D_8015DE5C ||
            (state->flags1c & (ACTOR_MP_EMPTY | ACTOR_ASLEEP)) != 0) {
            return;
        }
        display->frameTable = &D_8015DDCC;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)&D_8015DDCC), 0);
        return;
    case 15:
        if (display->frameTable != D_8015DE64 ||
            (state->flags1c & (ACTOR_MP_EMPTY | ACTOR_ASLEEP)) != 0) {
            return;
        }
        display->frameTable = &D_8015DDD4;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)&D_8015DDD4), 0);
        return;
    default:
        return;
    }
}
