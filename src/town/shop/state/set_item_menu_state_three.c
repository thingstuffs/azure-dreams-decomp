#include "common.h"
#include "shared/item_menu.h"


extern ItemMenuSceneState item_menu_scene_state;

/* Stores the value, sets the state to 3, and returns 2. */
s32 set_item_menu_state_three(s32 value) {
    item_menu_scene_state.unk0 = value;
    item_menu_scene_state.unk8 = 3;
    return 2;
}
