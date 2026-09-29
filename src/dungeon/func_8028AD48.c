#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
/* Decrease the paired values and step count while the count is positive. */
void func_8001DD48(void *step_state)
{
    if (((s16 *) step_state)[2] > 0) {
        ((u16 *) step_state)[0] = (u16) (((u16 *) step_state)[0] - 1);
        ((u16 *) step_state)[1] = (u16) (((u16 *) step_state)[1] - 0x20);
        ((u16 *) step_state)[2] = (u16) (((u16 *) step_state)[2] - 1);
    }
}
