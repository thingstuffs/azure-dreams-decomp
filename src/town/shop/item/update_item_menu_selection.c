#include "common.h"
#include "shared/game_work.h"

typedef struct TownState {
    u8 pad00[8];
    s32 input;
    u8 pad0C[4];
    s32 flags;
} TownState;

typedef struct TownInner {
    u8 pad00[4];
    s32 handle;
    u8 pad08[8];
    s32 band;
    u8 pad14[4];
    s32 position;
    s32 limit;
    s32 *table;
} TownInner;

typedef struct TownAux {
    u8 pad00[0x98];
    s32 down;
    void *up;
} TownAux;

typedef struct TownObject {
    TownInner *inner;
    s32 old_state;
    u8 pad08[4];
    s32 counter;
    s32 enabled;
    u8 pad14[4];
    s32 resource;
    u8 pad1C[0xA8 - 0x1C];
    TownAux *aux;
} TownObject;

extern s32 D_800891F4;
extern u8 D_800AF96C[];

extern s32 advance_index_with_directional_clamp(s32, s32, s32);
extern void get_item_name_with_shared_text_table(s32);
extern void sort_entries_by_category(void *);
extern void SD_Call(s32);
extern void set_item_menu_data_pointer(s32);
extern void set_item_menu_entry_coordinates(TownObject *);
extern void update_item_menu_record(TownObject *);
extern s32 place_selected_item_menu_entry(TownObject *);

/* Handles town menu actions, selection movement, and scrolling between bands. */
void update_item_menu_selection(TownObject *obj)
{
    s32 held_buttons;
    s32 move_step;
    s32 next_position;
    s32 next_band;
    TownInner *action_inner;
    TownInner *move_inner;
    TownInner *selection;
    TownInner *refreshed_inner;

    held_buttons = g_game_work.buttons;
    move_step = 0;
    if (held_buttons == 0) {
        return;
    }
    if (obj->enabled == 0) {
        return;
    }
    if (obj->inner->limit == 0) {
        if (((s32)g_game_work.pressed_buttons) & 0x20) {
            SD_Call(0x515);
            set_item_menu_data_pointer(obj->resource);
        }
        return;
    }

    if (((s32)g_game_work.pressed_buttons) & 0x20) {
        SD_Call(0x515);
        set_item_menu_data_pointer(obj->resource);
        return;
    }
    if (((s32)g_game_work.pressed_buttons) & 0x40) {
        SD_Call(0x514);
        obj->inner->handle = place_selected_item_menu_entry(obj);
        if (obj->inner->handle != 0) {
            return;
        }
        obj->old_state = *(s32 *)((u8 *)obj - 0x10);
        *(void **)((u8 *)obj - 0x10) = D_800AF96C;
        return;
    } else if (((s32)g_game_work.pressed_buttons) & 0x10) {
        SD_Call(0x503);
        sort_entries_by_category((void *)0x8001029C);
        update_item_menu_record(obj);
        action_inner = obj->inner;
        get_item_name_with_shared_text_table(action_inner->table[action_inner->position]);
        return;
    }

    if (!(held_buttons & 0xF000)) {
        return;
    }
    if (((s32)g_game_work.pressed_buttons) & 0xF000) {
        obj->counter = 0;
        if (((s32)g_game_work.pressed_buttons) & 0x8000)
            move_step = -5;
        else if (((s32)g_game_work.pressed_buttons) & 0x2000)
            move_step = 5;
        else if (((s32)g_game_work.pressed_buttons) & 0x1000)
            move_step = -1;
        else if (((s32)g_game_work.pressed_buttons) & 0x4000)
            move_step = 1;
    } else {
        if (obj->counter >= 5) {
            if (held_buttons & 0x8000)
                move_step = -5;
            else if (held_buttons & 0x2000)
                move_step = 5;
            else if (held_buttons & 0x1000)
                move_step = -1;
            else if (held_buttons & 0x4000)
                move_step = 1;
            obj->counter = *(s32 *)&obj->counter - 1;
        } else {
            obj->counter++;
            return;
        }
    }

    move_inner = obj->inner;
    next_position = advance_index_with_directional_clamp(move_inner->position, move_step, move_inner->limit);
    selection = obj->inner;
    if (next_position >= selection->limit) {
        selection->position = next_position;
        return;
    }
    if (next_position == selection->position) {
        return;
    }
    SD_Call(0x502);
    obj->inner->position = next_position;
    next_band = obj->inner->position / 10;
    set_item_menu_entry_coordinates(obj);
    refreshed_inner = obj->inner;
    get_item_name_with_shared_text_table(refreshed_inner->table[refreshed_inner->position]);
    if (next_band == obj->inner->band) {
        return;
    }
    if (next_band < obj->inner->band) {
        *(s32 *)((void **)(void *)obj->aux->down)[1] = D_800891F4;
    } else {
        *(s32 *)((void **)obj->aux->up)[1] = D_800891F4;
    }
    obj->inner->band = next_band;
    update_item_menu_record(obj);
}
