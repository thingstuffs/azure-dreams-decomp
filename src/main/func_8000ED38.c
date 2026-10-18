#include "modules/main_server_ship.h"
#include "common.h"



/* Returns the first value in the indexed 32-word entry. */
s32 card_boot_get_slot_marker(s32 entry_index) {
    return (*(s32 (*)[])(&D_80083E98))[entry_index * 32];
}
