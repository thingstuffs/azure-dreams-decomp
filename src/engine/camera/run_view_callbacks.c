#include "common.h"
#include "shared/game_work.h"
#include "engine/camera.h"
#include "engine/resource.h"

/* Processes two dispatch-slot pairs, then rebuilds matrices. */
void run_view_callbacks(void)
{
    GameWork *dispatch_table = &g_game_work;
    run_view_slot_callback(&dispatch_table->view.slot[0], &dispatch_table->view.slot[1], 0);
    run_view_slot_callback(&dispatch_table->view.slot[2], &dispatch_table->view.slot[3], 1);
    compose_and_install_camera_transform();
}
