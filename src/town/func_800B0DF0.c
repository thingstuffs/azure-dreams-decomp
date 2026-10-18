#include "common.h"
#include "shared/types3a_types.h"


extern ItemMenuSceneState D_80110EB8;

/* Initializes D_80110EB8 with the supplied value and a fixed value of 7. */
s32 initialize_item_menu_scene_value(s32 value) {
    D_80110EB8.unk0 = value;
    D_80110EB8.unk8 = 7;
    return 1;
}
