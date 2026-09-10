#include "common.h"

extern s32 func_80053EF0(s32 a0);
extern s16 SD_Call(s32 a0);
extern void func_80044618(s32 a0);
extern s32 VSync(s32 mode);

extern u16 D_80080B00;

/* Pumps frames until polling returns zero, handling the first poll and caching the VSync field. */
void func_80044698(void)
{
    s32 first_poll_done = 0;
    s32 poll_state;
    s32 frame_value;

    for (;;)
    {
        poll_state = func_80053EF0(1);
        if (poll_state == 0)
        {
            return;
        }

        frame_value = first_poll_done;
        if (frame_value == 0)
        {
            first_poll_done = 1;
            if (poll_state != 3)
            {
                SD_Call(0xC1);
            }
        }

        func_80044618(2);

        frame_value = (u32)VSync(1) >> 8 & 0x1FF;
        if ((u32)frame_value != D_80080B00)
        {
            D_80080B00 = (u16)frame_value;
        }
    }
}
