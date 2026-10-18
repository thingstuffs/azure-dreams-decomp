#include "modules/town_door.h"

/* into_dn_door_jobs: Run dungeon entrance setup and reset entry flags. */
void into_dn_door_jobs(void) {
    process_terminated_shop_ids();
    clear_resident_bitmap_bit(0x16);
    apply_building_pending_updates();
    dispatch_conditional_table_pairs();
    D_8008146C = 1;
    D_80082E60.flags16 = 0;
    D_80013714 &= 0xFFF8;
}
