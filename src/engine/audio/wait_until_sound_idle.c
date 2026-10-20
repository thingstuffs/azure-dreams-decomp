#include "slus/owned_80044698.h"

#include "slus/owned_80044698.h"

void wait_until_sound_idle(void)
{
    s32 first_poll_done = 0;
    s32 poll_state;
    s32 frame_value;

    for (;;) {
        poll_state = func_80053EF0(1);
        if (poll_state == 0) {
            return;
        }

        frame_value = first_poll_done;
        if (frame_value == 0) {
            first_poll_done = 1;
            if (poll_state != 3) {
                SD_Call(0xC1);
            }
        }

        update_vsync_frame_id(2);

        frame_value = (u32)VSync(1) >> 8 & 0x1FF;
        if ((u32)frame_value != sound_idle_vsync_frame_alias) {
            sound_idle_vsync_frame_alias = (u16)frame_value;
        }
    }
}
u16 sound_idle_vsync_frame_alias = 0;
