#include "common.h"
#include "m2c_compat.h"

void card_boot_init_server(void);                            /* extern */
void close_timer_2_update_event(void);                            /* extern */
extern s8 D_80080A84;

/* Run setup callbacks and set the active flag. */
void card_boot_stop_timer_and_init_server(void) {
    close_timer_2_update_event();
    D_80080A84 = 1;
    card_boot_init_server();
}
