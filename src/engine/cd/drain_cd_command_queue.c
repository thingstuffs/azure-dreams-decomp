#include "common.h"
#include "engine/cd.h"
#include "engine/graphics.h"
#include "engine/scene.h"
#include "slus.h"

/* Repeat the update sequence while get_cd_command_queue_depth reports pending work. */
void drain_cd_command_queue(void)
{
    while (get_cd_command_queue_depth()) {
        render_cd_wait_animation_on_new_field();
        update_vsync_frame_id(2);
        service_cd_command_queue();
    }
}
