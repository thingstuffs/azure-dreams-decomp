#include "common.h"
#include "m2c_compat.h"

typedef struct Node8002BB08 Node8002BB08;
Node8002BB08 *init_card_boot_request_object();                /* extern */
#include "frontend/libcard/interfaces.h"

/* Run setup and dispatch the request in mode 1. */
void card_boot_open_save_slot_selection(s32 request) {
    card_boot_stop_timer_and_init_server();
    init_card_boot_request_object(request, 1);
}
