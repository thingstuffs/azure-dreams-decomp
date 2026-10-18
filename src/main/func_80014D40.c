#include "common.h"
#include "m2c_compat.h"

typedef struct Node8002BB08 Node8002BB08;
Node8002BB08 *init_card_boot_request_object();                /* extern */
void card_boot_stop_timer_and_init_server();                            /* extern */
M2C_UNK save_and_clear_entity_flag_ten();                            /* extern */

/* Run the extra setup callback and dispatch the request in mode 2. */
void dispatch_request_mode_two(s32 request) {
    save_and_clear_entity_flag_ten();
    card_boot_stop_timer_and_init_server();
    init_card_boot_request_object(request, 2);
}
