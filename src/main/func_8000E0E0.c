#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"

/* Returns the first value in (*(s32 (*)[])(&card_operation_state)). */
s32 card_boot_get_operation_state(void) {
    return *(*(s32 (*)[])(&card_operation_state));
}
