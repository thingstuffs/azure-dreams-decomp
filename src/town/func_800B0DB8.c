#include "common.h"
#include "shared/item_menu.h"


extern ItemMenuSceneState D_80110EB8;

/* Stores the value, sets the state to 3, and returns 2. */
s32 set_item_menu_state_three(s32 value) {
    D_80110EB8.unk0 = value;
    D_80110EB8.unk8 = 3;
    return 2;
}
