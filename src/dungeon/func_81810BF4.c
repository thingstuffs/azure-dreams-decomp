#include "modules/dungeon_ovl_1830850.h"

void inventory_apply_step_and_reset_after_five(ovl_1830850_81810BF4_Entity *entity) {
    s32 next_state;
    s32 t;

    t = entity->state;
    *(s16 *)((u8 *)entity->object + 6) = t << 10;
    next_state = entity->state + 1;
    entity->state = next_state;
    if (next_state >= 5) {
        entity->state = 0;
        *(void **)((u8 *)entity - 0x10) = (void *)update_inventory_menu;
    }
    inventory_handle_menu_actions_and_repeat((ovl_1830850_81810A0C_DungeonArg *)entity);
}
