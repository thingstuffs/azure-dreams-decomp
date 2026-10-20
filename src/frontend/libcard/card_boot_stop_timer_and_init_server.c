#include "common.h"
#include "frontend/libcard/interfaces.h"
#include "m2c_compat.h"

#include "modules/main_server_ship_interfaces.h"
void close_timer_2_update_event(void);                            /* extern */
extern s8 D_80080A84;

/* Run setup callbacks and set the active flag. */
void card_boot_stop_timer_and_init_server(void) {
    close_timer_2_update_event();
    D_80080A84 = 1;
    card_boot_init_server();
}
