#include "common.h"

#include "common.h"
#include "engine/entity.h"
#include "engine/item.h"
#include "engine/runtime.h"
#include "engine/scene.h"

typedef struct {
    u8 pad[0x2D58];
    u32 increment;
    u32 total;
} CounterPage;

/* Runs runtime updates and adds the counter increment, capping the total at one billion. */
void add_counter_increment_capped(void) {
    CounterPage *page;
    u32 total;

    reset_entry_flags();
    remove_monster_items_with_negative_status();
    refresh_monster_items_from_creature_records();

    page = (CounterPage *)0x80010000;
    total = page->total + page->increment;
    page->total = total;
    if (total > 1000000000U) {
        page->total = 1000000000U;
    }
}
