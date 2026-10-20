#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x2D58];
    u32 increment;
    u32 total;
} CounterPage;

extern void reset_entry_flags(void);
extern void remove_monster_items_with_negative_status(void);
extern void refresh_monster_items_from_creature_records(void);

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
