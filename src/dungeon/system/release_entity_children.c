#include "sdk/libc.h"
#include "shared/game_state.h"
#include "shared/runtime_dispatch.h"
#include "common.h"
#include "dungeon/item.h"
#include "dungeon/menu.h"
#include "dungeon/menu/state.h"
#include "engine/menu.h"
struct ObjA464;

typedef struct {
    s32 field_0;
    const char *item_name;
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 item_category;
    s32 field_18;
    s32 item_index;
    s32 item_window;
    s32 menu_object;
    s32 selection_child;
    void *field_2C;
    void *field_30;
    void *field_34;
} Entity;

extern void remove_selection_child_object();

/* Processes entity fields and copies its string for selected type and state values. */
void release_entity_children(Entity *entity) {
    s32 state;

    close_item_window(entity->item_window);
    retire_menu_object(entity->menu_object);
    remove_selection_child_object(entity->selection_child);
    flag_object_and_release_inner(entity->field_2C, 0);
    flag_object_and_release_inner(entity->field_30, 0);
    flag_object_and_release_inner(entity->field_34, 0);
    if (runtime_dispatch_state.mode != 1) {
        set_dungeon_menu_flag_if_idle();
    }
    if (entity->item_category == 0x13) {
        state = entity->item_index;
        if (state == 2 || state == 0x39) {
            strcpy(GAME_STATE->kewne_name, entity->item_name);
        }
    }
}
