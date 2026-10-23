#include "common.h"
#include "shared/item_menu.h"


extern ItemMenuSceneState item_menu_scene_state;

/* Stores the supplied item-menu value, sets the field at offset 8 to 7, and returns one. */
s32 initialize_item_menu_scene_value(s32 value) {
    item_menu_scene_state.unk0 = value;
    item_menu_scene_state.unk8 = 7;
    return 1;
}
