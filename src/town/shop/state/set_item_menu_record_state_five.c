#include "common.h"
#include "shared/item_menu.h"


extern ItemMenuSceneState item_menu_scene_state;

/* Stores a value in the town record and sets its final field to 5. */
s32 set_item_menu_record_state_five(s32 value) {
    item_menu_scene_state.unk0 = value;
    item_menu_scene_state.unk8 = 5;
    return 1;
}
