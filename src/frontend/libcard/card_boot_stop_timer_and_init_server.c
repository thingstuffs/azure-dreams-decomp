#include "common.h"
#include "frontend/libcard/interfaces.h"
#include "m2c_compat.h"

#include "modules/main_server_ship_interfaces.h"
#include "engine/audio/sequence.h"
#include "frontend/libcard.h"
extern s8 animation_tick_scale;

/* Run setup callbacks and set the active flag. */
void card_boot_stop_timer_and_init_server(void) {
    close_timer_2_update_event();
    animation_tick_scale = 1;
    card_boot_init_server();
}
