#include "common.h"

extern int get_cd_command_queue_depth(void);
extern void render_cd_wait_animation_on_new_field(void);
extern void update_vsync_frame_id(int);
extern void func_8003E758(void);

/* Repeat the update sequence while get_cd_command_queue_depth reports pending work. */
void drain_cd_command_queue(void)
{
    while (get_cd_command_queue_depth()) {
        render_cd_wait_animation_on_new_field();
        update_vsync_frame_id(2);
        func_8003E758();
    }
}
