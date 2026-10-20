#include "common.h"
#include "shared/game_work.h"

typedef struct Node8002BB08 Node8002BB08;
Node8002BB08 *init_card_boot_request_object();                /* extern */
#include "frontend/libcard/interfaces.h"
s32 func_80064F00(s32, s32);
s32 func_80064F20(s32);

/* Set up the request with scale 512 and center (160, 120), then dispatch in mode 0. */
void dispatch_menu_update_callback(s32 request) {
    card_boot_stop_timer_and_init_server();
    g_game_work.view.projection_distance = 0x200;
    func_80064F20(0x200);
    func_80064F00(0xA0, 0x78);
    init_card_boot_request_object(request, 0);
}
