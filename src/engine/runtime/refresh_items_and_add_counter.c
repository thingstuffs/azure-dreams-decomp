#include "common.h"

#include "engine/entity.h"
#include "engine/item.h"
#include "engine/runtime.h"
#include "engine/scene.h"

/* Runs runtime updates and adds the counter increment, capping the total at one billion. */
void refresh_items_and_add_counter(void) {
    GameState *page;
    u32 total;

    reset_entry_flags();
    delete_negative_status_familiar_items();
    refresh_monster_items_from_creature_records();

    page = GAME_STATE;
    total = page->town_money;
    total += page->carry.dungeon_money;
    page->town_money = total;
    if (total > 1000000000U) {
        page->town_money = 1000000000U;
    }
}
