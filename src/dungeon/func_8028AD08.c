#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
/* Advance the paired values and step count while the count is below nine. */
void func_8001DD08(void *step_state)
{
    if ((*((u16 *) (((u8 *) step_state) + 4))) < 9) {
        *((u16 *) (((u8 *) step_state) + 0)) = (*((u16 *) (((u8 *) step_state) + 0))) + 1;
        *((u16 *) (((u8 *) step_state) + 2)) = (*((u16 *) (((u8 *) step_state) + 2))) + 0x20;
        *((u16 *) (((u8 *) step_state) + 4)) = (*((u16 *) (((u8 *) step_state) + 4))) + 1;
    }
}
