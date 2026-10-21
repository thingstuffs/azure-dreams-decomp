#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"
#include "main.h"


/* Call card_boot_erase_slot_file with argument 5. */
void card_boot_erase_temporary_file(void) {
    card_boot_erase_slot_file(5);
}
