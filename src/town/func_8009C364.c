#include "common.h"

extern void initialize_player_data_reference(void *);

/* Decrement the object countdown and call its handler when it becomes negative. */
void tick_player_countdown(void *object)
{
    u16 countdown;

    countdown = *(u16 *)((u8 *)object + 0xA) - 1;
    *(u16 *)((u8 *)object + 0xA) = countdown;
    if ((s16)countdown < 0) {
        initialize_player_data_reference(object);
    }
}
