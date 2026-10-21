#include "common.h"
#include "shared/game_work.h"
#include "engine/camera.h"
#include "engine/resource.h"

struct S_8004D70C_D80083160 {
    char pad0[0xCC];
    char f_CC[0x44];
    char f_110[0x44];
    char f_154[0x44];
    char f_198[0x44];
};

/* Processes two dispatch-slot pairs, then rebuilds matrices. */
void run_view_callbacks(void)
{
    struct S_8004D70C_D80083160 *dispatch_table = ((struct S_8004D70C_D80083160 *)&g_game_work);
    run_view_slot_callback(&dispatch_table->f_CC, &dispatch_table->f_110, 0);
    run_view_slot_callback(&dispatch_table->f_154, &dispatch_table->f_198, 1);
    compose_and_install_camera_transform();
}
