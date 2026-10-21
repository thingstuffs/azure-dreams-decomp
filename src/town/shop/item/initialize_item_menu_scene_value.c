#include "common.h"
#include "shared/item_menu.h"


extern ItemMenuSceneState item_menu_scene_state;

/* Initializes D_80110EB8 with the supplied value and a fixed value of 7. */
s32 initialize_item_menu_scene_value(s32 value) {
    item_menu_scene_state.unk0 = value;
    item_menu_scene_state.unk8 = 7;
    return 1;
}
